#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Data-layer layout check (docs/X64-PLAN.md section 0.7): the datareloc data layer
places every retail data object in its own `.data$rgXXXXXXXX` (/ .bss / .sdata ..)
section so the linker lays them out in retail address order, back to back.  Game code
indexes ACROSS object boundaries (a table addressed from its first entry's symbol), so
the host layout must keep retail's relative offsets.  For every symbol named after its
retail address (D_XXXXXXXX, data2c_*_XXXXXXXX), host address - retail address must be
constant along each run of the layer.

    python tools/x64/datalayout.py MAP [MAP2] [--show N]

Prints the runs (constant delta) with their retail ranges and the symbols where the
delta jumps (a gap or overlap the retail layout does not have).  With two maps (i686,
x64) also lists retail addresses where the two exes' runs break differently.
"""
from __future__ import annotations

import argparse
import re
import sys

ROW = re.compile(r"\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)")
NAME = re.compile(r"^_?(?:D|data2c_\w+?)_([0-9A-Fa-f]{8})$")


def load(path):
    out = []
    for ln in open(path, encoding="utf-8", errors="replace"):
        m = ROW.match(ln)
        if not m:
            continue
        n = NAME.match(m.group(3))
        if not n:
            continue
        sec = int(m.group(1), 16)
        out.append((int(n.group(1), 16), int(m.group(4), 16), m.group(3).lstrip("_"), sec))
    out.sort()
    return out


def breaks(rows):
    """retail address -> (prev symbol, delta change) where the host delta changes"""
    res = {}
    prev = None
    for ra, ha, nm, sec in rows:
        d = ha - ra
        if prev is not None and prev[3] == sec and d != prev[1]:
            res[ra] = (prev[2], nm, d - prev[1])
        prev = (ra, d, nm, sec)
    return res


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("maps", nargs="+")
    ap.add_argument("--show", type=int, default=30)
    a = ap.parse_args()
    allb = []
    for m in a.maps:
        rows = load(m)
        b = breaks(rows)
        allb.append(b)
        print(f"{m}: {len(rows)} retail-named data symbols, {len(b)} delta changes within a section")
        for ra, (p, n, dd) in list(sorted(b.items()))[:a.show]:
            print(f"  at {ra:08X} {n} (after {p}): delta {dd:+#x}")
    if len(allb) == 2:
        only = sorted(set(allb[1]) - set(allb[0]))
        print(f"breaks only in {a.maps[1]}: {len(only)}")
        for ra in only[:a.show]:
            p, n, dd = allb[1][ra]
            print(f"  at {ra:08X} {n} (after {p}): delta {dd:+#x}")
        return 1 if only else 0
    return 0


if __name__ == "__main__":
    sys.exit(main())
