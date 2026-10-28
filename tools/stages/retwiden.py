#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Ingest stage `retwiden`: a game function that returns a 1- or 2-byte integer and whose
address is taken (vtables, callback tables, function pointers) returns the value extended
to 32 bits (docs/PROTOS.md "retwiden", BRINGUP.md "User play-test 2").

Why: on the EE every value lives in a full 64-bit GPR and mwcc's callee leaves a narrow
return value extended in $v0 (`sltu`, `andi`, `lbu`, `lh`, `sll/sra` ...), so a caller that
reads the slot through a wider type (the decomp's `VCM0(s32, 0x3D0)` view of a
`u8 UnitHasParent_3a3600()`, a callback typed `int (*)()`) sees the right value.  On i686
the callee returns only AL / AX; EAX's upper bits are whatever the last computation left
(a pointer, typically).  Direct calls are typed by the unified prototype (protos stage) and
read AL / AX correctly; calls through a slot or pointer use the caller's type and do not.
Found in play-test 2: `BattleRecordDefeat_3a3410` tests `ActorCastToUnit(..)->v3D0() != 0`
(slot 0x3D0 = UnitHasParent_3a3600, retail 0 for an enemy); the port read a pointer in
EAX's upper bytes, returned early and recorded no defeated enemy, so every battle awarded
0 EXP and 0 money.

Rewrite, per definition `T F(..) { .. }` with T in u8 / s8 / u16 / s16 / bool / char /
unsigned char / signed char / short / unsigned short whose name F appears anywhere in the
corpus other than in a call `F(` (an address use: `&F`, `(u32)F`, `F` as an argument):

  * the return type becomes the 4-byte type of the same signedness (u32 / s32; bool and
    unsigned types -> u32, plain char / short / signed types -> s32);
  * every `return E;` in the body becomes `return (T)(E);` (the value is still converted
    to T first, then extended: exactly what retail's register held);
  * declarations of F in the same file (`T F(..);`) get the new type.

Declarations in other files keep T (their direct calls read the low part of the widened
register, which is the same value).  Idempotent: a widened definition no longer has a
narrow type.  RG_PROTOS_NO_RETWIDEN=1 disables it (the bisection / test control).

Standalone dry run on game/:  python tools/stages/retwiden.py --game game [--list]
"""
from __future__ import annotations

import argparse
import os
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
import portxform as X  # noqa: E402  (read-only reuse: blank, blank_pp)

WIDE = {"u8": "u32", "s8": "s32", "u16": "u32", "s16": "s32", "bool": "u32", "char": "s32",
        "unsigned char": "u32", "signed char": "s32", "short": "s32", "unsigned short": "u32",
        "uchar": "u32", "ushort": "u32"}
_NT = r"(?:unsigned\s+char|signed\s+char|unsigned\s+short|u8|s8|u16|s16|bool|char|short|uchar|ushort)"
# a definition / declaration head at the start of a line
_HEAD = re.compile(r"^(?P<pre>[ \t]*(?:extern\s+\"[ C]\"\s+)?(?:(?:static|inline|__inline)\s+)*)"
                   r"(?P<t>" + _NT + r")(?P<sp>\s+)(?P<n>[A-Za-z_]\w*_[0-9a-fA-F]{6}\w*)\s*\(", re.M)
_IDENT = re.compile(r"\b[A-Za-z_]\w*_[0-9a-fA-F]{6}\w*\b")


def _code(text: str) -> str:
    return X.blank_pp(X.blank(text))


def _close_paren(code: str, i: int) -> int:
    depth = 0
    for k in range(i, len(code)):
        c = code[k]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return k
    return -1


def heads(code: str):
    """(match, kind 'def'|'decl', body_open, body_close) for every narrow head in code"""
    out = []
    for m in _HEAD.finditer(code):
        lp = m.end() - 1
        rp = _close_paren(code, lp)
        if rp < 0:
            continue
        k = rp + 1
        while k < len(code) and code[k] in " \t\r\n":
            k += 1
        if k < len(code) and code[k] == "{":
            close = X.match_close(code, k)
            out.append((m, "def", k, close))
        elif k < len(code) and code[k] == ";":
            out.append((m, "decl", k, k))
    return out


def narrow_defs(files: dict) -> dict:
    """{name: relpath} of narrow-return definitions over the corpus"""
    defs = {}
    for rel, data in files.items():
        if not rel.endswith((".c", ".cpp")):
            continue
        code = _code(data.decode("utf-8", "replace"))
        for m, kind, _, _ in heads(code):
            if kind == "def":
                defs[m.group("n")] = rel
    return defs


def address_taken(files: dict, names: set) -> set:
    """names used other than as `F(` or in a narrow head of their own"""
    out = set()
    for rel, data in files.items():
        if not rel.endswith((".c", ".cpp")):
            continue
        code = _code(data.decode("utf-8", "replace"))
        for m in _IDENT.finditer(code):
            n = m.group(0)
            if n not in names or n in out:
                continue
            k = m.end()
            while k < len(code) and code[k] in " \t\r\n":
                k += 1
            if k < len(code) and code[k] == "(":
                continue
            out.add(n)
    return out


def rewrite(text: str, targets: set) -> tuple[str, int, list]:
    code = _code(text)
    rws = []          # (a, b, new)
    done = []
    for m, kind, bo, bc in heads(code):
        n = m.group("n")
        if n not in targets:
            continue
        t = re.sub(r"\s+", " ", m.group("t"))
        rws.append((m.start("t"), m.end("t"), WIDE[t]))
        if kind == "def":
            done.append(n)
            for r in re.finditer(r"\breturn\b", code[bo:bc]):
                a = bo + r.end()
                depth, k = 0, a
                while k < bc:
                    c = code[k]
                    if c in "([{":
                        depth += 1
                    elif c in ")]}":
                        depth -= 1
                    elif c == ";" and depth == 0:
                        break
                    k += 1
                expr = text[a:k]
                if not expr.strip():
                    continue
                lead = expr[:len(expr) - len(expr.lstrip())]
                rws.append((a, k, f"{lead or ' '}({t})({expr.strip()})"))
    if not rws:
        return text, 0, done
    rws.sort()
    out, pos = [], 0
    for a, b, new in rws:
        out.append(text[pos:a])
        out.append(new)
        pos = b
    out.append(text[pos:])
    return "".join(out), len(done), done


class RetWidenStage:
    def __init__(self):
        self.targets: set = set()
        self.rows: list = []
        self.errors: list = []

    def prepare(self, files: dict) -> None:
        if os.environ.get("RG_PROTOS_NO_RETWIDEN"):
            self.targets = set()
            return
        defs = narrow_defs(files)
        self.targets = address_taken(files, set(defs))

    def apply(self, rel: str, data: bytes) -> tuple[bytes, int]:
        if not self.targets or not rel.endswith((".c", ".cpp")):
            return data, 0
        text = data.decode("utf-8", "surrogateescape")
        new, n, done = rewrite(text, self.targets)
        if not n and new == text:
            return data, 0
        self.rows += [(rel, d) for d in done]
        return new.encode("utf-8", "surrogateescape"), n

    def report(self) -> str:
        return f"retwiden: {len(self.rows)} definitions widened ({len(self.targets)} address-taken narrow)"


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--file", help="print the rewrite of one file (relative to --game)")
    a = ap.parse_args(argv)
    root = Path(a.game)
    files = {p.relative_to(root).as_posix(): p.read_bytes()
             for p in root.rglob("*") if p.suffix in (".c", ".cpp")}
    st = RetWidenStage()
    st.prepare(files)
    if a.file:
        print(st.apply(a.file, files[a.file])[0].decode("utf-8", "replace"))
        return 0
    n = 0
    for rel in sorted(files):
        new, k = st.apply(rel, files[rel])
        n += k
    print(st.report(), f"; {len({r for r, _ in st.rows})} files")
    if a.list:
        for rel, d in st.rows:
            print(f"{d}\t{rel}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
