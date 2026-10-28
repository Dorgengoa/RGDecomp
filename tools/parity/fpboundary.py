#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Game -> host call boundary census for the EE FPU mode (docs/BRINGUP.md "Retail parity").

    python tools/parity/fpboundary.py EXE [--tsv F] [--top N]

With RG_EE_FPU=chop the kernel step (game flows, handlers, alarms, driven steps) runs with
MXCSR = round toward zero + FTZ + DAZ.  Host code reached from game code inside the step
runs under it too.  This lists every host function called directly from a game function
(map object column: the game units *_xxxxxx.c(pp).obj and data2c), with the float work in
its transitive host call closure (SSE arithmetic / conversions that depend on MXCSR, x87
arithmetic, which MXCSR does not touch), so the boundaries that need a round-to-nearest
scope can be picked (and the rest shown to be float-free).  Static: indirect calls from
host code are not followed (listed as `indirect` counts).
"""
from __future__ import annotations

import argparse
import bisect
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from fpcensus import OBJDUMP, SINGLE, DOUBLE_RND, X87, load_map  # noqa: E402

GAME = re.compile(r"(_[0-9a-f]{5,6}\.(c|cpp)\.obj$|^data2c)")
MXCSR_DEP = (SINGLE | DOUBLE_RND | {"cvtss2si", "cvtsd2si", "cvtps2dq", "cvtpd2dq", "roundss", "roundsd"})


def build(exe: Path):
    syms = load_map(exe.with_suffix(".map"))
    addrs = [s[0] for s in syms]
    fn = lambda a: bisect.bisect_right(addrs, a) - 1   # noqa: E731
    calls = defaultdict(set)
    fp = defaultdict(int)
    x87 = defaultdict(int)
    ind = defaultdict(int)
    p = subprocess.Popen([OBJDUMP, "-d", "--no-show-raw-insn", str(exe)], stdout=subprocess.PIPE,
                         text=True, errors="replace")
    for line in p.stdout:
        m = re.match(r"\s*([0-9a-f]+):\s+(\S+)\s*(\S*)", line)
        if not m:
            continue
        a, op, arg = int(m.group(1), 16), m.group(2), m.group(3)
        i = fn(a)
        if i < 0:
            continue
        if op in MXCSR_DEP:
            fp[i] += 1
        elif op in X87:
            x87[i] += 1
        elif op in ("calll", "jmp") and arg.startswith("0x"):
            j = fn(int(arg, 16))
            if j >= 0 and j != i:
                calls[i].add(j)
        elif op == "calll":
            ind[i] += 1
    p.wait()
    return syms, calls, fp, x87, ind


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("exe")
    ap.add_argument("--tsv")
    ap.add_argument("--top", type=int, default=60)
    a = ap.parse_args(argv)
    syms, calls, fp, x87, ind = build(Path(a.exe))
    game = {i for i, s in enumerate(syms) if GAME.search(s[2])}
    roots = defaultdict(int)
    for g in game:
        for t in calls.get(g, ()):
            if t not in game:
                roots[t] += 1
    rows = []
    for r in roots:
        seen, stack = {r}, [r]
        while stack:
            u = stack.pop()
            for v in calls.get(u, ()):
                if v not in seen and v not in game:
                    seen.add(v)
                    stack.append(v)
        rows.append((sum(fp[u] for u in seen), sum(x87[u] for u in seen), sum(ind[u] for u in seen),
                     len(seen), roots[r], syms[r][1], syms[r][2]))
    rows.sort(reverse=True)
    withfp = [r for r in rows if r[0]]
    print(f"host functions called from game code: {len(rows)}; with MXCSR-dependent float work in "
          f"their static closure: {len(withfp)}")
    for r in rows[:a.top]:
        print(f"  fp {r[0]:5d} x87 {r[1]:3d} indirect {r[2]:3d} closure {r[3]:4d} callers {r[4]:4d}  {r[5]}  ({r[6]})")
    if a.tsv:
        with open(a.tsv, "w", encoding="utf-8") as f:
            f.write("host_function\tobj\tgame_call_sites\tclosure_fns\tmxcsr_fp_ops\tx87_ops\tindirect_calls\n")
            for r in rows:
                f.write(f"{r[5]}\t{r[6]}\t{r[4]}\t{r[3]}\t{r[0]}\t{r[1]}\t{r[2]}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
