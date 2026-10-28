#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""rva2sym.py MAP RVA [RVA ..]: name exe RVAs (BRK / BRKSTACK lines, crash reports) through
an lld-link map, i686 or x64 (preferred base 0x400000).  `-` reads RVAs from stdin."""
import bisect, re, sys
ROW = re.compile(r"\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)")
rows = []
for ln in open(sys.argv[1], errors="replace"):
    m = ROW.match(ln)
    if m:
        rows.append((int(m.group(4), 16), m.group(3), m.group(5)))
rows.sort()
keys = [r[0] for r in rows]
args = sys.argv[2:] if sys.argv[2:] != ["-"] else sys.stdin.read().split()
for s in args:
    v = int(s.split(":")[-1], 16)
    a = 0x400000 + v
    i = bisect.bisect_right(keys, a) - 1
    print(f"{s}\t{rows[i][1]}+0x{a - rows[i][0]:x}\t{rows[i][2]}" if i >= 0 else f"{s}\t?")
