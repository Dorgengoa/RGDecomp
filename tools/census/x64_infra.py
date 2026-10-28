#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""x64 infra census (P7, docs/X64-PLAN.md): port code, build files and tools that
assume a 32-bit (i686) target.  Text patterns only; one row per (class, file)
with the hit count and the first matching line.

    python tools/census/x64_infra.py [--out build/x64-probe]

Writes <out>/infra_sites.tsv and prints a per-class summary.  Classes:
  arch-guard     `__i386__` / `_M_IX86` conditionals (code that is i686-only or
                 silently disabled elsewhere: fiber arena, save-state heap,
                 overlay trampolines, VU JIT)
  x86-asm        inline asm naming 32-bit registers (%esp, %eax, pushl, ...)
  wow64          WOW64 thread-context APIs (samplers that read a 32-bit target)
  ctx32          CONTEXT Eip/Esp/Ebp fields (crash handler, samplers)
  m32-flag       -m32 / i686 triples / i386 sysroots in build files and tools
  ptrsize-guard  CMAKE_SIZEOF_VOID_P / sizeof(void *) == 4 assertions
  sym-underscore leading-underscore C symbol handling (i686 COFF decorates C
                 names with `_`; x64 COFF does not)
  u32-addr       a host address stored as uint32_t (`(uint32_t)(uintptr_t)p`,
                 save-state headers) -- fine below 4 GB, must stay there
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ROOTS = ["src", "include", "tests", "tools", "cmake", "CMakeLists.txt"]
SUFFIX = {".c", ".h", ".cpp", ".hpp", ".py", ".cmake", ".txt", ".ps1", ".sh", ".S", ".s"}
PATS = {
    "arch-guard": re.compile(r"__i386__|_M_IX86\b"),
    "x86-asm": re.compile(r"%%?e(?:sp|bp|ax|bx|cx|dx|si|di)\b|\bpushl\b|\bpopl\b|\bmovl\b.*%"),
    "wow64": re.compile(r"Wow64|WOW64"),
    "ctx32": re.compile(r"(?:->|\.)(?:Eip|Esp|Ebp)\b"),
    "m32-flag": re.compile(r"(?<![\w-])-m32\b|i686-|i386-linux|\bi686\b"),
    "ptrsize-guard": re.compile(r"CMAKE_SIZEOF_VOID_P|sizeof\s*\(\s*void\s*\*\s*\)\s*==\s*4"),
    "sym-underscore": re.compile(r"__USER_LABEL_PREFIX__|lstrip\(\s*['\"]_['\"]\s*\)|"
                                 r"startswith\(\s*['\"]_['\"]\s*\)|\[1:\]\s*if\s*\w+\.startswith\(['\"]_"),
    "u32-addr": re.compile(r"\(\s*uint32_t\s*\)\s*\(\s*uintptr_t\s*\)|\(\s*uint32_t\s*\)\s*\w+->base\b"),
}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", default="build/x64-probe")
    a = ap.parse_args()
    out = Path(a.out)
    out = out if out.is_absolute() else ROOT / out
    out.mkdir(parents=True, exist_ok=True)
    me = Path(__file__).resolve()
    rows = []
    for r in ROOTS:
        base = ROOT / r
        files = [base] if base.is_file() else sorted(base.rglob("*"))
        for p in files:
            if not p.is_file() or p.suffix not in SUFFIX or "__pycache__" in p.parts:
                continue
            if p.resolve() == me or p.name.startswith("x64_"):
                continue
            try:
                txt = p.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            for cls, rx in PATS.items():
                hits = [ln for ln in txt.splitlines() if rx.search(ln)]
                if hits:
                    rows.append((cls, str(p.relative_to(ROOT)).replace("\\", "/"), len(hits),
                                 hits[0].strip()[:90].replace("\t", " ")))
    with open(out / "infra_sites.tsv", "w", encoding="utf-8") as fo:
        fo.write("class\tfile\thits\tfirst\n")
        for r in rows:
            fo.write("\t".join(str(x) for x in r) + "\n")
    byc = Counter()
    byf = Counter()
    top = {"src": Counter(), "tools": Counter(), "tests": Counter(), "other": Counter()}
    for cls, f, n, _ in rows:
        byc[cls] += n
        byf[cls] += 1
        k = f.split("/")[0]
        top[k if k in top else "other"][cls] += 1
    print("x64 infra census (files / hits):")
    for cls in PATS:
        print(f"  {cls:15s} {byf[cls]:5d} files {byc[cls]:6d} hits   "
              + ", ".join(f"{k}={v[cls]}" for k, v in top.items() if v[cls]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
