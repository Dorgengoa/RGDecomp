#!/usr/bin/env python3
"""Summarise an RG_UBSAN census log (src/game/ubsan_census.c) into a sorted TSV
(docs/UB-AUDIT.md):  python tools/ubaudit/ubsum.py LOG OUT.tsv"""
import re
import sys
from collections import Counter

rows, det = {}, {}


def norm(f):
    return re.sub(r"^.*?port[\\/]", "", f).replace("\\", "/")


for line in open(sys.argv[1], encoding="utf-8", errors="replace"):
    p = line.rstrip("\n").split("\t")
    if p[0] == "NEW":
        det[(p[1], p[2], norm(p[3]), p[4], p[5])] = p[6]
    elif p[0] == "COUNT":
        rows[(p[1], p[2], norm(p[3]), p[4], p[5])] = int(p[6])
with open(sys.argv[2], "w", newline="\n", encoding="utf-8") as o:
    o.write("kind\tsub\tfile\tline\tcol\thits\tfirst_detail\n")
    for k in sorted(rows, key=lambda k: (k[0], k[1], k[2], int(k[3]))):
        o.write("\t".join(k) + f"\t{rows[k]}\t{det.get(k, '')}\n")
c = Counter((k[0], k[1]) for k in rows)
for (a, b), n in c.most_common():
    print(f"{n:5d} sites {sum(v for k, v in rows.items() if (k[0], k[1]) == (a, b)):9d} hits  {a} {b}")
