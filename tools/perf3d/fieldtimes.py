#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""fieldtimes.py TIMES.tsv RANGE... : mean ms per field of each RG_FIELD_TIMES column
(wall, step, read, present, gs_wait) over each range a-b, as a markdown table."""
import sys

d = {}
cols = ["wall", "step", "read", "present", "gs_wait"]
for l in open(sys.argv[1]):
    p = l.split()
    if p and p[0].isdigit():
        d[int(p[0])] = [float(x) for x in p[1:]]
print("| fields | n | " + " | ".join(c + " ms" for c in cols) + " |")
print("| --- | --- |" + " --- |" * len(cols))
for r in sys.argv[2:]:
    a, b = map(int, r.split("-"))
    v = [d[f] for f in range(a, b + 1) if f in d]
    if not v:
        print("| %s | 0 |" % r)
        continue
    k = min(len(x) for x in v)
    m = [sum(x[i] for x in v) / len(v) for i in range(k)]
    print("| %s | %d | " % (r, len(v)) + " | ".join("%.2f" % x for x in m) + " |")
