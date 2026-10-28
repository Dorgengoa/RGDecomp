#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare the game heap of two rg-game runs (i686 vs x64, docs/X64-PLAN.md section 0.7)
from one RG_STATUS_DUMP line each, with host pointers normalised.

    RG_STATUS_EVERY=F RG_STATUS_DUMP=0x528200:0x1AD7E00 rg-game ... --fields F  (both exes)
    python tools/x64/heapdiff.py A_ERR.txt B_ERR.txt [--field F] [--max N] [--gap 64]

Each log's "game heap at HOSTADDR" line gives the RAM block base (host address of PS2
0x528200); a word inside the block [base, base+32 MB) is replaced by its PS2 address, a
word that looks like an image address (0x400000..0x1800000) by "IMG" (the two exes'
images differ; read those through the maps when they matter).  Prints the differing
words grouped into ranges (PS2 addresses; words closer than --gap bytes join a range).
"""
from __future__ import annotations

import argparse
import re
import sys

HEAP0 = 0x528200
RAM = 32 << 20


def load(path: str, field: int | None):
    base = None
    words = None
    start = None
    with open(path, encoding="utf-8", errors="replace") as f:
        for ln in f:
            if base is None:
                m = re.search(r"game heap at ([0-9A-Fa-f]+)", ln)
                if m:
                    base = int(m.group(1), 16) - HEAP0
            m = re.match(r"^DUMP field=(\d+) vbl=\d+ ([0-9A-Fa-fx]+): (.*)$", ln.rstrip("\n"))
            if m and (field is None or int(m.group(1)) == field):
                start = int(m.group(2), 16)
                words = m.group(3).split()
    if words is None:
        sys.exit(f"{path}: no DUMP line")
    return base, start, words


def norm(w: str, base: int) -> str:
    v = int.from_bytes(bytes.fromhex(w), "little") if len(w) == 8 and w[:2] != "0x" else int(w, 16)
    if base is not None and base <= v < base + RAM:
        return f"P{v - base:08X}"
    if 0x400000 <= v < 0x1800000:
        return "IMG"
    return w


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--field", type=int)
    ap.add_argument("--max", type=int, default=60)
    ap.add_argument("--gap", type=int, default=64)
    a = ap.parse_args()
    ba, sa, wa = load(a.a, a.field)
    bb, sb, wb = load(a.b, a.field)
    if sa != sb:
        sys.exit("different dump start addresses")
    print(f"A base {ba:#x}, B base {bb:#x}, {len(wa)} words from {sa:#x}")
    diffs = [i for i in range(min(len(wa), len(wb))) if wa[i] != wb[i] and norm(wa[i], ba) != norm(wb[i], bb)]
    ranges = []
    for i in diffs:
        if ranges and (i - ranges[-1][1]) * 4 <= a.gap:
            ranges[-1][1] = i
            ranges[-1][2] += 1
        else:
            ranges.append([i, i, 1])
    print(f"{len(diffs)} words differ in {len(ranges)} ranges")
    for lo, hi, n in ranges[:a.max]:
        ex = " ".join(f"{wa[i]}/{wb[i]}" for i in range(lo, min(hi + 1, lo + 4)))
        print(f"  {sa + lo * 4:#010x}..{sa + hi * 4 + 4:#010x} ({n} words): {ex}")
    return 1 if diffs else 0


if __name__ == "__main__":
    sys.exit(main())
