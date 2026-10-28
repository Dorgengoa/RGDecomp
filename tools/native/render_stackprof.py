#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Callers of a function in an rgprof sample file (docs/NATIVE-RENDER.md "Tools").

    python tools/native/render_stackprof.py PROF.tsv MAP FUNC [--tid TID] [--depth N]

For every sample whose stack (leaf + candidate return addresses, rgprof rows)
contains FUNC (a substring of a link-map symbol), counts the chain of the next
N named frames above it (callers), most frequent first.  Answers "who calls
the drain that waits" without a debugger."""
import argparse, bisect, collections

ap = argparse.ArgumentParser()
ap.add_argument("prof"); ap.add_argument("map"); ap.add_argument("func")
ap.add_argument("--tid", type=int, default=0)
ap.add_argument("--depth", type=int, default=3)
ap.add_argument("--top", type=int, default=20)
a = ap.parse_args()

syms = []
for ln in open(a.map, errors="replace"):
    p = ln.split()
    if len(p) == 4 and p[0].startswith("0001:"):
        try:
            syms.append((int(p[2], 16), p[1]))
        except ValueError:
            pass
syms.sort()
sva = [s[0] for s in syms]


def name(va):
    i = bisect.bisect_right(sva, va) - 1
    return syms[i][1] if i >= 0 else "?"


lo, hi = (syms[0][0], syms[-1][0] + 0x100000) if syms else (0, 0)
chains = collections.Counter()
total = 0
for ln in open(a.prof):
    if ln.startswith("#"):
        continue
    p = ln.split()
    if len(p) < 3 or (a.tid and int(p[1]) != a.tid):
        continue
    frames = [int(x, 16) for x in p[2:]]
    names = []
    for va in frames:
        if lo <= va < hi:
            n = name(va)
            if not names or names[-1] != n:
                names.append(n)
    for i, n in enumerate(names):
        if a.func in n:
            total += 1
            chains[" <- ".join(names[i:i + 1 + a.depth])] += 1
            break
print("%d samples with %s" % (total, a.func))
for c, n in chains.most_common(a.top):
    print("%6d %5.1f%%  %s" % (n, 100.0 * n / max(total, 1), c))
