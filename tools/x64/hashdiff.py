#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare two RG_HASH_LOG files (src/runtime/runtime.c: one row per field with the run
hash and its parts) and name where they part: the first field each column differs, and
the run-hash spans (equal / different) over the whole log.

    python tools/x64/hashdiff.py A.tsv B.tsv [--at F,F..]

Used for the x64 bring-up (docs/X64-PLAN.md 0.6): run the i686 and x64 exe with
RG_HASH_LOG on the same input, then this; the first differing field and part (pad /
audio / ktrace) is where to start the state trace.
"""
from __future__ import annotations

import argparse
import sys


def load(path: str):
    with open(path, encoding="utf-8") as f:
        hdr = f.readline().rstrip("\n").split("\t")
        rows = {}
        for ln in f:
            c = ln.rstrip("\n").split("\t")
            if len(c) == len(hdr):
                rows[int(c[0])] = c
    return hdr, rows


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--at", default="", help="also print both rows at these fields")
    a = ap.parse_args()
    ha, ra = load(a.a)
    hb, rb = load(a.b)
    if ha != hb:
        print(f"hashdiff: headers differ: {ha} vs {hb}")
        return 2
    common = sorted(set(ra) & set(rb))
    print(f"fields: A {min(ra, default=0)}..{max(ra, default=0)}, B {min(rb, default=0)}..{max(rb, default=0)}, common {len(common)}")
    first = {}
    for f in common:
        for i, h in enumerate(ha[1:], 1):
            if h not in first and ra[f][i] != rb[f][i]:
                first[h] = f
    for h in ha[1:]:
        print(f"  {h:10} {'first differs at field %d' % first[h] if h in first else 'equal'}")
    spans, cur, start = [], None, None
    for f in common:
        eq = ra[f][1] == rb[f][1]
        if eq != cur:
            if cur is not None:
                spans.append((start, prev, cur))
            cur, start = eq, f
        prev = f
    if cur is not None:
        spans.append((start, prev, cur))
    print("run_hash spans: " + ", ".join(f"{s}-{e} {'equal' if q else 'DIFF'}" for s, e, q in spans[:12]))
    shown = [int(x) for x in a.at.split(",") if x] + ([first["run_hash"]] if "run_hash" in first else [])
    for f in shown:
        if f in ra and f in rb:
            print(f"field {f}:")
            for i, h in enumerate(ha[1:], 1):
                mark = "" if ra[f][i] == rb[f][i] else "  <--"
                print(f"  {h:10} {ra[f][i]:>18} {rb[f][i]:>18}{mark}")
    return 1 if first else 0


if __name__ == "__main__":
    sys.exit(main())
