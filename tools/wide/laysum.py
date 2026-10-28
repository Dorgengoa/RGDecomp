#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Summarize an RG_LAYOUT_LOG (docs/WIDESCREEN.md "Stage 2"): per field, the packets grouped
by (task, calling function) with symbol names from the exe's map, rectangles and decisions.

    python tools/wide/laysum.py LOG --exe EXE [--field N] [--all]
"""
import argparse
import bisect
import re
import sys
from collections import defaultdict


def syms(mp):
    out = []
    for line in open(mp, encoding="latin-1"):
        m = re.match(r"\s*0001:[0-9a-f]+\s+_?(\S+)\s+([0-9a-f]{16})", line)
        if m:
            out.append((int(m.group(2), 16) - 0x400000, m.group(1)))
    out.sort()
    return out


def name(tab, keys, rva):
    if rva == 0:
        return "-"
    i = bisect.bisect_right(keys, rva) - 1
    return tab[i][1] if i >= 0 else hex(rva)


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("log")
    ap.add_argument("--exe", required=True)
    ap.add_argument("--field", type=int)
    a = ap.parse_args(argv)
    tab = syms(a.exe.rsplit(".", 1)[0] + ".map")
    keys = [k for k, _ in tab]
    rows = defaultdict(list)
    fields = set()
    for ln in open(a.log, errors="replace"):
        m = re.match(r"(\d+) pk task=(\w+) caller=(\w+) x=(\S+)\.\.(\S+) y=(\S+)\.\.(\S+) n=(\d+)(?: psm=(-?\d+))?(?: fbp=(\S+))? (.*)", ln)
        if not m:
            continue
        f = int(m.group(1))
        fields.add(f)
        if a.field is not None and f != a.field:
            continue
        rows[f].append(m.groups())
    if a.field is None:
        a.field = max(fields) if fields else None
    for g in rows.get(a.field, []):
        _, t, c, x0, x1, y0, y1, n, psm, fbp, dec = g
        print(f"{name(tab, keys, int(t, 16)):34s} {name(tab, keys, int(c, 16)):34s} x {float(x0):6.1f}..{float(x1):6.1f}"
              f" y {float(y0) - 1824:6.1f}..{float(y1) - 1824:6.1f} n={n:>3} psm={psm} fbp={fbp} {dec}")


if __name__ == "__main__":
    sys.exit(main())
