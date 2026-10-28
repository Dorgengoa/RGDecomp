#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Narrow-integer call ABI on x64 (docs/X64-PLAN.md section 0.7).

i686 clang passes and returns every 1- and 2-byte integer EXTENDED to 32 bits (IR
`signext` / `zeroext`); Win64 clang does not (only bool): a caller whose declaration
says `s16` leaves the register's upper bits as they were, a callee that returns `s16`
leaves EAX's upper half undefined.  When the caller's declaration and the callee's
definition disagree on the width, i686 still reads the right value and x64 does not:
CharaEffEntrySpawn_22fad0 declares `GetObjNodeByName_1ce3a0(u8 *, s16, char *)`, the
definition reads an `s32` id, so on x64 the battle effects of the first battle were
placed at the origin (no hit, the run hash parted at field 24,824).

The derive pass (tools/x64/derive.py `narrowabi`) rewrites the CALLER's declaration:
  argument  declaration narrow, definition 32-bit -> the declaration's parameter
            becomes s32 / u32 (same signedness: the caller extends as i686 does);
  pointer   declaration 32-bit integer, definition pointer -> the declaration's
            parameter becomes long long / unsigned long long (Win64 stores only the low
            4 bytes of a 32-bit stack argument; ModelCalcNodesBoundsMaybe_1531c0 arg 4);
  return    declaration 32-bit, definition narrow -> the declaration's return type
            becomes the definition's (the caller extends the callee's low bits as the
            i686 callee would).
Definitions and declarations that already agree are left alone; a declaration in the
TU that defines the function is never rewritten; C++ declarations are rewritten only
with C linkage (`extern "C"`), so no mangled name changes.

    python tools/x64/narrowabi.py [--root build/x64-src] [--tree game] [--check]

prints the census: every mismatching declaration (file, function, position, view,
definition).
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
ID = r"[A-Za-z_]\w*"
SIG = re.compile(r"(?m)^(?P<pre>[ \t]*(?:extern[ \t]+\"C\"[ \t]+)?(?:(?:extern|static|inline)[ \t]+)*)"
                 r"(?P<ret>(?:(?:const|volatile|unsigned|signed|struct|enum)[ \t]+)*" + ID + r"(?:[ \t]*\*)*)"
                 r"[ \t]+(?P<star>\**)(?P<name>" + ID + r")[ \t]*\((?P<params>[^;{}()]*)\)[ \t]*"
                 r"(?P<end>;|\{|\n[ \t]*\{)")
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "else", "do", "case", "goto", "new",
            "delete", "defined", "operator"}
NARROW_S = {"s8", "s16", "char", "signed char", "short", "short int", "signed short", "signed short int",
            "int8_t", "int16_t"}
NARROW_U = {"u8", "u16", "unsigned char", "unsigned short", "unsigned short int", "uint8_t", "uint16_t",
            "vc_u8", "uchar", "ushort"}
WIDE = {"s32", "u32", "int", "unsigned", "unsigned int", "signed", "signed int", "long", "unsigned long",
        "long int", "unsigned long int", "int32_t", "uint32_t", "vc_u32", "uint"}


def blank_comments(s: str) -> str:
    out = list(s)

    def wipe(a, b):
        for i in range(a, b):
            if out[i] != "\n":
                out[i] = " "
    i, n = 0, len(s)
    while i < n:
        if s.startswith("//", i):
            j = s.find("\n", i)
            j = n if j < 0 else j
            wipe(i, j)
            i = j
        elif s.startswith("/*", i):
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            wipe(i, j)
            i = j
        elif s[i] in "\"'":
            q = s[i]
            j = i + 1
            while j < n and s[j] != q and s[j] != "\n":
                j += 2 if s[j] == "\\" else 1
            i = j + 1
        else:
            i += 1
    return "".join(out)


def ptype(p: str) -> str:
    """the type of one parameter text (its name dropped)"""
    p = " ".join(p.replace("\t", " ").split())
    p = re.sub(r"\b(const|volatile|register)\b", "", p)
    p = " ".join(p.split())
    if not p or p == "void" or p == "...":
        return p
    if "*" in p or "[" in p or "(" in p or "&" in p:
        return "*"
    toks = p.split()
    if len(toks) > 1 and " ".join(toks) not in NARROW_S | NARROW_U | WIDE:
        toks = toks[:-1]          # drop the parameter name
    return " ".join(toks)


def cls(t: str) -> str:
    if t in NARROW_S:
        return "ns"
    if t in NARROW_U:
        return "nu"
    if t in WIDE:
        return "w"
    return "o"


def clinkage_spans(code: str) -> list[tuple[int, int]]:
    """byte spans of `extern "C" { .. }` blocks"""
    spans = []
    for m in re.finditer(r'extern\s+"C"\s*\{', code):
        d, i = 1, m.end()
        while i < len(code) and d:
            d += {"{": 1, "}": -1}.get(code[i], 0)
            i += 1
        spans.append((m.end(), i))
    return spans


def sigs(text: str, cxx: bool):
    """(kind, name, ret, [param types], match) for every one-line signature"""
    code = blank_comments(text)
    spans = clinkage_spans(code) if cxx else []
    out = []
    for m in SIG.finditer(code):
        name = m.group("name")
        if name in KEYWORDS or m.group("ret") in KEYWORDS or m.group("ret") in ("return", "else"):
            continue
        kind = "decl" if m.group("end") == ";" else "def"
        clink = (not cxx) or 'extern "C"' in m.group("pre") or any(a <= m.start() < b for a, b in spans)
        params = [ptype(p) for p in m.group("params").split(",")] if m.group("params").strip() else []
        ret = "*" if m.group("star") or "*" in m.group("ret") else ptype(m.group("ret").replace("extern", ""))
        out.append((kind, name, ret, params, m, clink))
    return out


def definitions(files) -> dict[str, tuple[str, list[str]]]:
    defs = {}
    for f in files:
        try:
            t = Path(f).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for kind, name, ret, params, m, clink in sigs(t, str(f).endswith((".cpp", ".hpp"))):
            if kind == "def" and clink:
                defs.setdefault(name, (ret, params))
    return defs


WIDEN = {"ns": "s32", "nu": "u32"}


def rewrite(text: str, defs: dict, cxx: bool) -> tuple[str, int, list[str]]:
    """the caller-declaration rewrite (module doc); returns (text, n, rows)"""
    ss = sigs(text, cxx)
    own = {name for kind, name, *_ in ss if kind == "def"}
    edits = []
    rows = []
    for kind, name, ret, params, m, clink in ss:
        if kind != "decl" or not clink or name in own or name not in defs:
            continue
        dret, dparams = defs[name]
        # arguments: declaration narrow, definition wide
        ptxt = m.group("params")
        pieces = ptxt.split(",")
        newp = list(pieces)
        changed = False
        for k, (vt, piece) in enumerate(zip(params, pieces)):
            if k >= len(dparams):
                break
            vc, dc = cls(vt), cls(dparams[k])
            if vc == "w" and dparams[k] == "*":
                # a 32-bit integer view of a POINTER parameter: Win64 stores only the low
                # 4 bytes of a 5th+ (stack) argument and the callee reads 8
                # (ModelMeshUpdateBoundsMaybe_150170 -> ModelCalcNodesBoundsMaybe_1531c0
                # arg 4): pass it zero-extended to 64 bits (pointers are below 2 GB)
                rep = "unsigned long long" if re.search(r"\b(u32|unsigned|uint32_t|uint|vc_u32)\b", vt) else "long long"
                if len(vt.split()) == 1:
                    newk = re.sub(r"\b" + re.escape(vt) + r"\b", rep, piece, count=1)
                else:
                    newk = piece.replace(vt, rep, 1)
                if newk != piece:
                    newp[k] = newk
                    changed = True
                    rows.append(f"{name}\targ{k}\t{vt}\t*")
                continue
            if vc in WIDEN and dc == "w":
                newp[k] = re.sub(r"\b" + re.escape(vt.split()[-1]) + r"\b", WIDEN[vc], piece, count=1) \
                    if len(vt.split()) == 1 else piece.replace(vt, WIDEN[vc], 1)
                if newp[k] == piece:
                    continue
                changed = True
                rows.append(f"{name}\targ{k}\t{vt}\t{dparams[k]}")
        rtxt = m.group("ret")
        newr = rtxt
        if cls(ret) == "w" and cls(dret) in WIDEN:
            newr = rtxt.replace(ret.split()[-1], dret, 1) if len(ret.split()) == 1 else rtxt.replace(ret, dret, 1)
            if newr != rtxt:
                rows.append(f"{name}\tret\t{ret}\t{dret}")
        if changed:
            edits.append((m.start("params"), m.end("params"), ",".join(newp)))
        if newr != rtxt:
            edits.append((m.start("ret"), m.end("ret"), newr))
    for a, b, s in sorted(edits, reverse=True):
        text = text[:a] + s + text[b:]
    return text, len(rows), rows


def tree_files(trees, root=PORT):
    for t in trees:
        base = Path(root) / t
        for ext in ("*.c", "*.cpp", "*.h"):
            yield from base.rglob(ext)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--tree", action="append")
    ap.add_argument("--root", default=str(PORT), help="tree root (an x64 derived tree: build/x64-src)")
    ap.add_argument("--check", action="store_true", help="exit 1 when any mismatch is left")
    a = ap.parse_args()
    trees = a.tree or ["game", "overrides", "missing"]
    files = list(tree_files(trees, a.root))
    defs = definitions(files)
    print(f"# {len(defs)} definitions")
    n = 0
    for f in files:
        t = f.read_text(encoding="utf-8", errors="replace")
        _, k, rows = rewrite(t, defs, str(f).endswith((".cpp", ".hpp")))
        for r in rows:
            print(f"{f.relative_to(PORT)}\t{r}")
        n += k
    print(f"# {n} mismatching declaration positions")
    return 0


if __name__ == "__main__":
    sys.exit(main())
