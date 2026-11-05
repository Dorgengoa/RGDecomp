#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Interior-label macros vs x64 pointer width (docs/X64-PLAN.md 0.15).

The ingest stage `interior` (tools/stages/interior.py, docs/LINUX.md "Linux ABI differences";
since aliasfix 11-02, replacing linuxrun's tools/linux/interiorfix.py overrides) spells an
interior label as an lvalue of its container:

    #define D_x (*(__typeof__(D_x) *)((u8 *)&D_y + off))     /* rg-interior */   (typeof form)
    #define D_x (*(T * (*)[N])((u8 *)&D_y + off))                                (explicit form)

On x64 the game table behind D_x holds 4-byte pointer words.  The typeof form is safe when the
file's own `extern T *D_x[N];` was rewritten by ptr32 (`T * RG_P32 D_x[N]`); the explicit form
needs ptr32's `ptrarr` rule (`T * RG_P32 (*)[N]`).  An 8-byte pointer element left in either is
the x64e 11-02 fault (NpcCfgCmdSelectDef_2fd6e0, field 2,114).  This check reads a DERIVED tree
(tools/x64/derive.py output) and fails on:
  explicit  a cast `(*(TYPE (*)[N]) ..)` / `(*(TYPE *) ..)` in a #define whose element TYPE has a
            pointer star without RG_P32
  typeof    `__typeof__(D_x)` where the file's declaration of D_x has a pointer star without
            RG_P32 (or no declaration is found)
  fnptr     an element that is a function pointer (ptr32 rejects `R (*(*)[N])(A)` itself)

    python tools/x64/interiorcheck.py [--root build/x64-src] [--all]   # exit 1 on a FAIL row
    python tools/x64/interiorcheck.py --control    # the raw explicit form must FAIL, ptr32's
                                                   # rewrite of it must PASS
Macros are found by the `rg-interior` tag and by any object-like #define whose body is
`(*(<type> ...)((u8 *)&SYM + off))`.
"""
from __future__ import annotations

import argparse
import re
import sys
import tempfile
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
ID = r"[A-Za-z_]\w*"
DEF = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+(" + ID + r")[ \t]+\(\*\((.*?)\)\s*\(\s*\(\s*(?:u8|char|unsigned char|s8)\s*\*\s*\)\s*&\s*(" + ID + r")")
TYPEOF = re.compile(r"^\s*__typeof__\s*\(\s*(" + ID + r")\s*\)\s*\*\s*$")


ATTR = re.compile(r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)")


def decl_of(text: str, name: str) -> str | None:
    """the file's (extern) declaration of `name` (not the #define), reduced to the one
    declarator `<base type> <declarator of name>` (attributes dropped, comma lists split)"""
    for m in re.finditer(r"(?m)^[ \t]*(?!#)([^;{}\n]*\b" + re.escape(name) + r"\b[^;{}]*);", text):
        st = ATTR.sub("", m.group(1))
        parts, depth, cur = [], 0, ""
        for ch in st:
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
            if ch == "," and depth == 0:
                parts.append(cur)
                cur = ""
            else:
                cur += ch
        parts.append(cur)
        for i, part in enumerate(parts):
            if not re.search(r"\b" + re.escape(name) + r"\s*(\[|$|=|\))", part):
                continue
            if "(" in part.split(name)[0] and "(*" not in part:
                break           # a function prototype / call naming it
            if i == 0:
                return part.strip()
            # `extern T a[4], *b[4];`: the base type of the first declarator + this one
            d0 = re.search(r"[\s*]*\(?\s*\*?\s*" + ID + r"\s*(\[[^\]]*\]\s*)*$", parts[0])
            base = parts[0][:d0.start()] if d0 else parts[0]
            return (base + " " + part.strip()).strip()
    return None


def classify(text: str):
    """[(line, name, form, verdict, detail)] for every interior-style macro of one file"""
    rows = []
    for m in DEF.finditer(text):
        name, ty, base = m.group(1), m.group(2), m.group(3)
        ln = text.count("\n", 0, m.start()) + 1
        tm = TYPEOF.match(ty)
        if tm:
            d = decl_of(text, tm.group(1))
            if d is None:
                rows.append((ln, name, "typeof", "FAIL", "no declaration of the typeof name"))
                continue
            elem = d.split(tm.group(1))[0]
            if re.search(r"\(\s*\*", d) and re.search(r"\)\s*\(", d):
                rows.append((ln, name, "typeof", "FAIL", f"function pointer element: {d.strip()}"))
            elif "*" in elem and "RG_P32" not in elem:
                rows.append((ln, name, "typeof", "FAIL", f"8-byte pointer element: {d.strip()}"))
            else:
                rows.append((ln, name, "typeof", "ok", d.strip()))
            continue
        # explicit: `T * (*)[N]` (pointer to array) or `T *` (scalar pointer slot = `T **`
        # after the outer star; ptr32's ptrptr / dptr rules)
        arr = re.match(r"^(.*?)\(\s*\*\s*\)\s*(\[.*)$", ty)
        elem = arr.group(1) if arr else re.sub(r"\*\s*$", "", ty)
        if re.search(r"\(\s*\*", elem):
            rows.append((ln, name, "explicit", "FAIL", f"function pointer element: {ty.strip()}"))
        elif "*" in elem and "RG_P32" not in elem:
            rows.append((ln, name, "explicit", "FAIL", f"8-byte pointer element: {ty.strip()}"))
        else:
            rows.append((ln, name, "explicit", "ok", ty.strip()))
    return rows


def run(root: Path, show_all: bool) -> int:
    n = bad = 0
    files = 0
    for tree in ("overrides", "missing", "game"):
        base = root / tree
        if not base.is_dir():
            continue
        for f in base.rglob("*"):
            if f.suffix not in (".c", ".cpp", ".h"):
                continue
            t = f.read_text(encoding="utf-8", errors="replace")
            if "#" not in t or "(u8 *)&" not in t.replace("(u8 *) &", "(u8 *)&"):
                continue
            rows = classify(t)
            if not rows:
                continue
            files += 1
            for ln, name, form, v, det in rows:
                n += 1
                if v == "FAIL":
                    bad += 1
                if v == "FAIL" or show_all:
                    print(f"{f.relative_to(root).as_posix()}:{ln}\t{name}\t{form}\t{v}\t{det}")
    print(f"# interiorcheck {root}: {n} interior macros in {files} files, {bad} FAIL")
    return 1 if bad else 0


CONTROL = """#include "types.h"
typedef struct Ctx { s32 a; } Ctx;
extern u8 D_00FFF000[0x400];
extern Ctx *D_00FFF010[0x10];
#define D_00FFF008 (*(Ctx * (*)[0x100])((u8 *)&D_00FFF000 + 0x8))   /* rg-interior */
#define D_00FFF010 (*(__typeof__(D_00FFF010) *)((u8 *)&D_00FFF000 + 0x10))   /* rg-interior */
s32 f(s32 i) { return D_00FFF008[i]->a + D_00FFF010[i]->a; }
"""


def control() -> int:
    sys.path.insert(0, str(PORT / "tools" / "stages"))
    import ptr32
    raw = classify(CONTROL)
    if [r[3] for r in raw] != ["FAIL", "FAIL"]:
        print(f"control: FAIL, the raw forms were not both flagged: {raw}")
        return 1
    st = ptr32.Ptr32Stage()
    hdr = {str(h): h.read_text(encoding="utf-8", errors="replace")
           for h in (PORT / "game" / "include").glob("types.h")}
    st.prepare_headers(hdr)
    out, _n = st.rewrite("src/ctl.c", CONTROL)
    got = classify(out)
    if [r[3] for r in got] != ["ok", "ok"] or st.stats.get("ptrarr") != 1:
        print(f"control: FAIL, after ptr32: {got} (stats {dict(st.stats)})\n{out}")
        return 1
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / "overrides" / "ctl.c"
        p.parent.mkdir(parents=True)
        p.write_text(CONTROL, encoding="utf-8")
        if run(Path(td), False) == 0:
            print("control: FAIL, the tree check passed the raw forms")
            return 1
    print("control: PASS (raw explicit + typeof forms FAIL; ptr32's ptrarr / global rewrite passes)")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=str(PORT / "build" / "x64-src"))
    ap.add_argument("--all", action="store_true", help="print ok rows too")
    ap.add_argument("--control", action="store_true")
    a = ap.parse_args()
    if a.control:
        return control()
    return run(Path(a.root).resolve(), a.all)


if __name__ == "__main__":
    sys.exit(main())
