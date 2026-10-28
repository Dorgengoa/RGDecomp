#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Derive the x64 source tree from the generated i686 tree (P7 strategy A,
docs/X64-PLAN.md steps 2-4).

    python tools/x64/derive.py [--out build/x64-src] [-j 8] [--only REGEX]

Input: game/ (tools/ingest.py output, every ingest stage applied), overrides/
and missing/.  Output: <out>/game, <out>/overrides, <out>/missing with the
same relative paths, written only when their bytes change (stale files are
removed), plus <out>/game/PTR32.tsv and <out>/DERIVE.txt (counts).  An x64
build points at it: `-DRG_X64_SRC=<out>` (CMakeLists.txt, RG_ARCH=x64; the
default is <build dir>/../x64-src is NOT assumed: configure stops if the
tree is missing).

The x64 stages, in order (none of them runs for i686, so the i686 build is
unchanged by construction):
  ptr32    tools/stages/ptr32.py: pointers stored in game memory -> 4 bytes
  addr32   tools/x64/addr32.py: data-layer objects holding pointer words ->
           top-level asm with ADDR32 relocations
  vthunk   protos rule def-vthunk-naked: the naked i686 forwarder
           `movl 4(%esp),%eax; movl V(%eax),%eax; jmp *S(%eax)` -> the Win64
           form `movl V(%rcx),%eax; movl S(%rax),%eax; jmp *%rax` (this = rcx;
           vptr and slot are 4-byte words)
  dalign   data-layer arrays keep their i686 alignment (x86-64 clang 16-aligns
           arrays >= 16 bytes; the layer is laid out back to back: datalayout.py)
  xalign   extern data declarations of game code: aligned(1) (x86-64 clang assumes
           16-byte alignment for extern objects >= 16 bytes; retail addresses are not)
  narrowabi caller declarations whose 1/2-byte integer argument or 32-bit return
           disagrees with the definition (i686 extends small integers, Win64 does
           not: tools/x64/narrowabi.py)
  (also vcmwiden, libc below)
"""
from __future__ import annotations

import argparse
import hashlib
import multiprocessing as mp
import os
import re
import sys
import time
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PORT = Path(os.environ.get("RG_PORT_ROOT", ROOT))
sys.path.insert(0, str(ROOT / "tools" / "stages"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import ptr32  # noqa: E402
import addr32  # noqa: E402
import narrowabi  # noqa: E402

SRC_EXT = (".c", ".cpp", ".h", ".hpp")
VTHUNK = re.compile(
    r'__asm__ volatile\("movl 4\(%esp\), %eax\\n\\t" "movl (?P<v>-?(?:0x)?[0-9A-Fa-f]+)\(%eax\), %eax\\n\\t"'
    r' "jmp \*(?P<s>-?(?:0x)?[0-9A-Fa-f]+)\(%eax\)"\);')

_STAGE: ptr32.Ptr32Stage | None = None
_DEFS: dict = {}


def _init(state, defs=None):
    global _STAGE, _DEFS
    _STAGE = ptr32.Ptr32Stage()
    _STAGE.glob, _STAGE.hdr_fn_members = state
    _DEFS = defs or {}


def vthunk(text: str) -> tuple[str, int]:
    n = 0

    def sub(m):
        nonlocal n
        n += 1
        return ('__asm__ volatile("movl ' + m.group("v") + '(%rcx), %eax\\n\\t" "movl '
                + m.group("s") + '(%rax), %eax\\n\\t" "jmp *%rax");')
    return VTHUNK.sub(sub, text), n


# libc: a size argument declared 32-bit is read as 64-bit size_t by the real
# function (Win64: the upper half of the register is undefined).  The game's own
# redeclarations (`extern void *memset(void *, s32, u32);`, 789 of them) keep
# their other parameter types; only the size parameter becomes size_t, so every
# call converts its 32-bit value to 64 bits.  `operator new(u32, ..)` likewise
# (C++ requires size_t: a hard error on x64).
LIBC_SIZE = {"memset": (2,), "memcpy": (2,), "memmove": (2,), "memcmp": (2,), "strncpy": (2,),
             "strncmp": (2,), "strncat": (2,), "malloc": (0,), "calloc": (0, 1), "realloc": (1,),
             "memchr": (2,)}
LIBC_DECL = re.compile(r"(?m)^([ \t]*(?:extern\s+(?:\"C\"\s+)?)?[A-Za-z_][\w \t]*?[\s*]"
                       r"(" + "|".join(LIBC_SIZE) + r")\s*\()([^()]*)(\)\s*;)")
INT32_T = re.compile(r"^\s*(?:const\s+)?(?:unsigned\s+long|unsigned\s+int|signed\s+int|u32|s32|int|"
                     r"unsigned|signed|uint|long)\b")
OPNEW = re.compile(r"\boperator\s+new(\s*\[\s*\])?\s*\(\s*(?:u32|unsigned\s+int|unsigned|s32|int)\b")


def libc(text: str) -> tuple[str, int]:
    n = 0

    def sub(m):
        nonlocal n
        ps = m.group(3).split(",")
        changed = False
        for k in LIBC_SIZE[m.group(2)]:
            if k < len(ps) and INT32_T.match(ps[k]):
                ps[k] = INT32_T.sub(" __SIZE_TYPE__", ps[k], count=1)
                changed = True
        if not changed:
            return m.group(0)
        n += 1
        return m.group(1) + ",".join(ps) + m.group(4)
    text = LIBC_DECL.sub(sub, text)

    def sub2(m):
        nonlocal n
        n += 1
        return "operator new" + (m.group(1) or "") + "(__SIZE_TYPE__"
    text = OPNEW.sub(sub2, text)
    return text, n


# vcmwiden: a devirt slot call's view of an integer parameter is widened to 64 bits
# (sign- or zero-extended as its type says).  The slot function's own declaration may
# differ from the view (the EE passed every argument extended in a 64-bit register, i686
# cdecl in an extended 4-byte stack word): with a narrower view Win64 leaves the upper
# bits undefined -- a register argument's above 8/16 bits (WorldSubsysLinkTree_419e60:
# view (void *, s16), the function reads s32: garbage ids), a stack argument's (5th on)
# upper 4 bytes when the function reads a pointer or an 8-byte integer.  A function
# that reads a narrower integer reads the same low part.
VCM_MAC = re.compile(r"\b(VCMQ?(?:_FN)?|VCMQ0|VCALL(?:_THIS|_BOOL)?)\s*\(")
_S64, _U64 = "long long", "unsigned long long"
NARROW = {"s16": _S64, "u16": _U64, "s8": _S64, "u8": _U64, "bool": _U64, "short": _S64,
          "unsigned short": _U64, "char": _S64, "signed char": _S64, "unsigned char": _U64,
          "s32": _S64, "int": _S64, "signed": _S64, "signed int": _S64, "u32": _U64,
          "unsigned": _U64, "unsigned int": _U64, "uint": _U64, "vc_u32": _U64}


def _split_top(s: str) -> list[tuple[int, int]]:
    out, d, st = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        elif ch == "," and d == 0:
            out.append((st, i))
            st = i + 1
    out.append((st, len(s)))
    return out


def vcmwiden(text: str) -> tuple[str, int]:
    n = 0
    out = []
    last = 0
    for m in VCM_MAC.finditer(text):
        if m.start() < last:
            continue
        i, d = m.end(), 1
        while i < len(text) and d:
            d += {"(": 1, ")": -1}.get(text[i], 0)
            i += 1
        args = text[m.end():i - 1]
        for a, b in _split_top(args):
            arg = args[a:b].strip()
            if not (arg.startswith("(") and arg.endswith(")")):
                continue
            inner = arg[1:-1]
            ps = [inner[x:y] for x, y in _split_top(inner)]
            if not ps or not re.match(r"\s*(const\s+)?void\s*\*", ps[0]):
                continue
            new = []
            for p in ps:
                core = " ".join(p.split())
                if core in NARROW:
                    new.append(p.replace(p.strip(), NARROW[core]))
                    n += 1
                else:
                    new.append(p)
            if new != ps:
                s0 = m.end() + a + args[a:b].index("(") + 1
                out.append(text[last:s0])
                out.append(",".join(new))
                last = s0 + len(inner)
            break
    out.append(text[last:])
    return "".join(out), n


# dalign: x86-64 clang gives every global ARRAY of 16 bytes or more a 16-byte alignment
# (the target's "large array" rule; i686 keeps the element type's).  The data layer is
# one object per retail address in `.data$rgXXXXXXXX` sections laid out back to back, and
# game code indexes across object boundaries (FontGetCharWidth_26f4c0 reads the width
# table D_0044E851 + 4 * code through 0044E852 / 0044E854...: 340 objects moved on x64,
# tools/x64/datalayout.py), so every data-layer definition without an explicit
# alignment gets `aligned(__alignof__(TYPE))` = its i686 alignment.
DALIGN = re.compile(r"(?m)^(?P<type>(?:const\s+|volatile\s+)*[A-Za-z_][\w ]*?(?:\s*\*\s*(?:RG_P32\s*)?)*)\s*"
                    r"\b(?P<name>[A-Za-z_]\w*)\s*(?P<dims>(?:\[[^\]\r\n]*\]\s*)+)"
                    r"__attribute__\(\((?P<attrs>[^\r\n]*?)\)\)(?=\s*[=;])")


def dalign(text: str) -> tuple[str, int]:
    n = 0

    def sub(m):
        nonlocal n
        attrs = m.group("attrs")
        if "section(" not in attrs or "aligned" in attrs:
            return m.group(0)
        ty = re.sub(r"\b(?:static|extern)\b", "", m.group("type")).strip()
        n += 1
        return m.group(0)[:-2] + f", aligned(__alignof__({ty}))" + "))"
    return DALIGN.sub(sub, text), n


# xalign: x86-64 clang also ASSUMES the 16-byte alignment for an extern object of 16
# bytes or more (struct or array) and copies it with movaps; the data layer keeps
# retail addresses, so D_004E9084 (a 108-byte struct at ...084) faulted in
# SaveSysMsgGet_373840 (every card boot of bootcheck).  Every extern DATA declaration of
# game code gets `__attribute__((aligned(1)))`: no alignment beyond what the code itself
# guarantees is assumed (only a weaker assumption: always correct).
XEXTERN = re.compile(r'(?m)^[ \t]*extern\b(?![ \t]*"C"[ \t]*\{)')


def xalign(text: str) -> tuple[str, int]:
    code = ptr32.blank(text)
    edits = []
    for m in XEXTERN.finditer(code):
        e = m.end()
        depth = 0
        while e < len(code):
            ch = code[e]
            if ch in "([{":
                depth += 1
            elif ch in ")]}":
                depth -= 1
            elif ch == ";" and depth == 0:
                break
            elif ch == "{" and depth == 0:
                break
            e += 1
        if e >= len(code) or code[e] != ";":
            continue
        stmt = code[m.end():e]
        body = ptr32.strip_attrs(stmt)
        if "=" in body or "typedef" in body:
            continue
        # declarators: split at top-level commas
        parts = ptr32.split_top(stmt, ",")
        for a, b in parts:
            d = ptr32.strip_attrs(stmt[a:b])
            # a function declarator `name(..)` (not `(*name)(..)`) is skipped
            fm = re.search(r"([A-Za-z_]\w*)\s*\(", d)
            if fm and not re.search(r"\(\s*\*\s*[A-Za-z_]\w*\s*\)\s*\(", d) and \
                    not re.search(r"\(\s*\*", d[:fm.start()]):
                continue
            if not re.search(r"[A-Za-z_]\w*", d):
                continue
            edits.append(m.end() + b)
    for p in sorted(edits, reverse=True):
        text = text[:p] + " __attribute__((aligned(1)))" + text[p:]
    return text, len(edits)


def is_data(rel: str) -> bool:
    return bool(re.search(r"(^|/)src/(?:[^/]+/)*[^/]*_data/", rel))


def work(item):
    tree, rel, src = item
    data = Path(src).read_bytes()
    if not rel.endswith(SRC_EXT):
        return tree, rel, data, {}, [], []
    text = data.decode("utf-8", "surrogateescape")
    cnt = Counter()
    probs = []
    rows = []
    if is_data(rel) and rel.endswith(".c"):
        text, n, p = addr32.convert(text)
        cnt["addr32-objects"] += n
        text, n = dalign(text)
        cnt["dalign"] += n
        probs += [f"{tree}/{rel}: {x}" for x in p]
    else:
        st = _STAGE
        st.rows = []
        st.stats = Counter()
        text, n = st.rewrite(f"{tree}/{rel}", text)
        cnt.update({"ptr32-" + k: v for k, v in st.stats.items()})
        rows = st.rows
        text, n = vthunk(text)
        cnt["vthunk"] += n
        text, n = libc(text)
        cnt["libc"] += n
        text, n = vcmwiden(text)
        cnt["vcmwiden"] += n
        text, n = xalign(text)
        cnt["xalign"] += n
        if rel.endswith((".c", ".cpp")) and _DEFS:
            text, n, _ = narrowabi.rewrite(text, _DEFS, rel.endswith(".cpp"))
            cnt["narrowabi"] += n
        if "movl 4(%esp)" in text:
            probs.append(f"{tree}/{rel}: i686 asm left (movl 4(%esp))")
    return tree, rel, text.encode("utf-8", "surrogateescape"), dict(cnt), probs, rows


def collect(a) -> list[tuple[str, str, str]]:
    items = []
    game = PORT / "game"
    rows = [ln.split("\t") for ln in (game / "MANIFEST.tsv").read_text(encoding="utf-8").splitlines()[1:]]
    for r in rows:
        rel, kind = r[0], r[3]
        if kind == "config":
            continue
        items.append(("game", rel, str(game / rel)))
    items.append(("game", "MANIFEST.tsv", str(game / "MANIFEST.tsv")))
    items.append(("game", "SNAPSHOT.txt", str(game / "SNAPSHOT.txt")))
    for tree in ("overrides", "missing"):
        base = PORT / tree
        for f in sorted(base.rglob("*")):
            if f.is_file():
                items.append((tree, f.relative_to(base).as_posix(), str(f)))
    if a.only:
        rx = re.compile(a.only)
        items = [i for i in items if rx.search(f"{i[0]}/{i[1]}") or not i[1].endswith(SRC_EXT)
                 or "/include/" in f"/{i[1]}"]
    return items


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--out", default=str(PORT / "build" / "x64-src"))
    ap.add_argument("-j", "--jobs", type=int, default=max(1, (os.cpu_count() or 4) // 2))
    ap.add_argument("--only", default="", help="debug: only rewrite matching paths")
    a = ap.parse_args()
    out = Path(a.out)
    t0 = time.time()
    # shared headers: the game include tree and the port include tree
    hdr = {}
    for d in (PORT / "game" / "include", PORT / "include"):
        for h in d.rglob("*.h"):
            hdr[str(h)] = h.read_text(encoding="utf-8", errors="replace")
    st = ptr32.Ptr32Stage()
    st.prepare_headers(hdr)
    items = collect(a)
    # narrowabi: every game definition's signature (caller declarations are matched
    # against it; tools/x64/narrowabi.py)
    defs = narrowabi.definitions(src for _t, rel, src in items if rel.endswith((".c", ".cpp")))
    tot = Counter()
    probs: list[str] = []
    rows: list[str] = []
    written = 0
    keep: set[Path] = set()
    with mp.Pool(a.jobs, initializer=_init, initargs=((st.glob, st.hdr_fn_members), defs)) as pool:
        for tree, rel, data, cnt, p, r in pool.imap_unordered(work, items, chunksize=64):
            tot.update(cnt)
            probs += p
            rows += r
            dst = out / tree / rel
            keep.add(dst)
            if not dst.exists() or dst.read_bytes() != data:
                dst.parent.mkdir(parents=True, exist_ok=True)
                dst.write_bytes(data)
                written += 1
    rows.sort()
    tsv = ("tree/relpath\tline\trule\ttext\n" + "\n".join(rows) + "\n").encode()
    pt = out / "game" / "PTR32.tsv"
    keep.add(pt)
    if not pt.exists() or pt.read_bytes() != tsv:
        pt.write_bytes(tsv)
    removed = 0
    for tree in ("game", "overrides", "missing"):
        for f in sorted((out / tree).rglob("*"), reverse=True) if (out / tree).is_dir() else []:
            if f.is_file() and f not in keep:
                f.unlink()
                removed += 1
            elif f.is_dir() and not any(f.iterdir()):
                f.rmdir()
    rep = [f"derive: {len(items)} files, {written} written, {removed} removed, "
           f"{time.time() - t0:.0f} s",
           "counts: " + ", ".join(f"{k}={v}" for k, v in sorted(tot.items())),
           f"problems: {len(probs)}"] + [f"  {p}" for p in probs[:200]]
    (out / "DERIVE.txt").write_text("\n".join(rep) + "\n", encoding="utf-8")
    print("\n".join(rep[:3 + min(len(probs), 30)]))
    return 1 if probs else 0


if __name__ == "__main__":
    sys.exit(main())
