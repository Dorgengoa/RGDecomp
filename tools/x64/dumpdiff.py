#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare the RG_STATUS_DUMP / RG_BREAK_SPEC lines (DUMP / SDUMP) of two rg-game logs,
e.g. the i686 and the x64 exe on the same input (docs/X64-PLAN.md section 0.7).

    python tools/x64/dumpdiff.py A_ERR.txt B_ERR.txt [--tag DUMP] [--words N] [--first]

For each (field, item) present in both logs: the 4-byte words that differ, as
item+offset: A B.  --first stops after the first field with a difference; --words
limits the words printed per item (default 16).  Words that hold host pointers differ
between the two exes by construction (different image layouts): read those through
the maps, or look for the first non-pointer word.
"""
from __future__ import annotations

import argparse
import re
import sys

LINE = re.compile(r"^(\w+) field=(\d+) vbl=(\d+) (\S+): (.*)$")


def load(path: str, tag: str):
    out = {}
    order = []
    with open(path, encoding="utf-8", errors="replace") as f:
        for ln in f:
            m = LINE.match(ln.rstrip("\n"))
            if not m or m.group(1) != tag:
                continue
            k = (int(m.group(2)), m.group(4))
            if k not in out:
                order.append(k)
            out[k] = m.group(5).split()
    return out, order


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--tag", default="DUMP")
    ap.add_argument("--words", type=int, default=16)
    ap.add_argument("--first", action="store_true")
    a = ap.parse_args()
    A, order = load(a.a, a.tag)
    B, _ = load(a.b, a.tag)
    nd = 0
    last_field = None
    for k in order:
        if k not in B:
            continue
        wa, wb = A[k], B[k]
        diffs = [(i, x, y) for i, (x, y) in enumerate(zip(wa, wb)) if x != y]
        if len(wa) != len(wb):
            diffs.append((min(len(wa), len(wb)), f"len{len(wa)}", f"len{len(wb)}"))
        if not diffs:
            continue
        if a.first and last_field is not None and k[0] != last_field:
            break
        last_field = k[0]
        nd += 1
        print(f"field {k[0]} {k[1]}: {len(diffs)} words differ")
        for i, x, y in diffs[:a.words]:
            try:
                off = f"+0x{i * 4:X}"
            except TypeError:
                off = str(i)
            print(f"   {k[1]}{off}: {x} {y}")
    print(f"{nd} (field, item) pairs differ")
    return 1 if nd else 0


if __name__ == "__main__":
    sys.exit(main())
