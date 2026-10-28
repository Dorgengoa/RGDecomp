#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Floating-point rounding census of a built rg-game.exe (docs/BRINGUP.md "Retail parity",
EE FPU rounding).

    python tools/parity/fpcensus.py EXE [--tsv F] [--top N] [--objfilter REGEX]

Disassembles the exe once (llvm-objdump) and attributes every instruction to its function
through rg-game.map.  Per function: single-precision SSE arithmetic (affected by the EE
FPU mode: round toward zero + FTZ/DAZ under RG_EE_FPU=chop), double-precision arithmetic
whose result depends on the MXCSR rounding mode (addsd subsd mulsd divsd sqrtsd cvtsd2ss
and packed forms; retail does double math in gcc soft-float = round to nearest, so these
sites need round to nearest), and x87 arithmetic (never affected by MXCSR).
Only functions from game objects (map object column matches --objfilter, default: the
game's units *_xxxxxx.c(pp).obj and data2c) are listed as game sites.
"""
from __future__ import annotations

import argparse
import bisect
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

OBJDUMP = r"../tools/llvm/bin/llvm-objdump.exe"
SINGLE = {"addss", "subss", "mulss", "divss", "sqrtss", "addps", "subps", "mulps", "divps", "sqrtps",
          "rcpss", "rsqrtss", "cvtsi2ss", "cvtsd2ss", "minss", "maxss"}
DOUBLE_RND = {"addsd", "subsd", "mulsd", "divsd", "sqrtsd", "addpd", "subpd", "mulpd", "divpd", "sqrtpd",
              "cvtsd2ss", "cvtpd2ps", "cvtsi2sd"}
X87 = {"fadd", "faddp", "fsub", "fsubp", "fsubr", "fsubrp", "fmul", "fmulp", "fdiv", "fdivp", "fdivr",
       "fdivrp", "fsqrt", "fiadd", "fimul", "fidiv", "fisub", "fild", "fistp", "fist"}


def load_map(mp: Path):
    syms = []
    for line in open(mp, encoding="latin-1"):
        m = re.match(r"\s*0001:[0-9a-f]+\s+_?(\S+)\s+([0-9a-f]{16})\s+(?:f\s+)?(?:i\s+)?(\S+)", line)
        if m:
            syms.append((int(m.group(2), 16), m.group(1), m.group(3)))
    syms.sort()
    return syms


def census(exe: Path, objfilter: str):
    syms = load_map(exe.with_suffix(".map"))
    addrs = [s[0] for s in syms]
    rx = re.compile(objfilter)
    per = defaultdict(lambda: {"single": 0, "double": 0, "x87": 0, "dops": defaultdict(int), "obj": ""})
    p2 = subprocess.Popen([OBJDUMP, "-d", "--no-show-raw-insn", str(exe)], stdout=subprocess.PIPE,
                          text=True, errors="replace")
    for line in p2.stdout:
        m = re.match(r"\s*([0-9a-f]+):\s+(\S+)", line)
        if not m:
            continue
        op = m.group(2)
        kind = "double" if op in DOUBLE_RND else "single" if op in SINGLE else "x87" if op in X87 else None
        if not kind:
            continue
        a = int(m.group(1), 16)
        i = bisect.bisect_right(addrs, a) - 1
        if i < 0:
            continue
        _, name, obj = syms[i]
        if not rx.search(obj):
            continue
        d = per[name]
        d["obj"] = obj
        d[kind] += 1
        if kind == "double":
            d["dops"][op] += 1
    p2.wait()
    return per


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("exe")
    ap.add_argument("--tsv")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--objfilter", default=r"(_[0-9a-f]{5,6}\.(c|cpp)\.obj$|^data2c)")
    a = ap.parse_args(argv)
    per = census(Path(a.exe), a.objfilter)
    fs = [n for n, d in per.items() if d["single"]]
    fd = [n for n, d in per.items() if d["double"]]
    fx = [n for n, d in per.items() if d["x87"]]
    print(f"game functions with single-precision SSE arithmetic: {len(fs)} "
          f"({sum(per[n]['single'] for n in fs)} instructions)")
    print(f"game functions with rounding-sensitive double arithmetic: {len(fd)} "
          f"({sum(per[n]['double'] for n in fd)} instructions)")
    print(f"game functions with x87 arithmetic: {len(fx)}")
    for n in sorted(fd, key=lambda n: -per[n]["double"])[:a.top]:
        d = per[n]
        print(f"  {n:50s} double {d['double']:4d} single {d['single']:4d}  "
              + " ".join(f"{k}:{v}" for k, v in sorted(d["dops"].items())))
    if a.tsv:
        with open(a.tsv, "w", encoding="utf-8") as f:
            f.write("function\tobj\tsingle\tdouble\tx87\tdouble_ops\n")
            for n, d in sorted(per.items()):
                f.write(f"{n}\t{d['obj']}\t{d['single']}\t{d['double']}\t{d['x87']}\t"
                        + ",".join(f"{k}:{v}" for k, v in sorted(d["dops"].items())) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
