#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Identity-coverage census of interpolated presentation (docs/NATIVE-RENDER.md "Interpolated
presentation"): summarises the per-frame TSV an rg-game run writes with RG_INTERP=1
RG_INTERP_CENSUS=path (tools/native/interp_run.sh writes out/interp/runs/NAME_census.tsv).

  python tools/native/interp_census.py CENSUS.tsv [CENSUS2.tsv ...] [--worst N]

Per file: frames with mesh items, mesh items and how a pass draws them (interpolated = matched
with the previous frame: object, camera and bones lerp/slerp; camera only = new or jumped
items; exact = Z-scale composites and cut frames), unmatched items, immediate (2D / effect)
records and the share repeated exactly from the previous frame (static 2D, shown as the latest),
and the N frames with the lowest matched share.
"""
import argparse

COLS = ["frame", "T", "items", "full", "cam", "exact", "unmatched", "far", "zscale", "skin",
        "overlap", "cut", "ims", "ims_static", "recs", "bytes"]


def load(p):
    rows = []
    for line in open(p, encoding="utf-8"):
        if line.startswith("#") or not line.strip():
            continue
        v = line.split("\t")
        rows.append({k: int(x) for k, x in zip(COLS, v)})
    return rows


ap = argparse.ArgumentParser()
ap.add_argument("files", nargs="+")
ap.add_argument("--worst", type=int, default=5)
a = ap.parse_args()
for f in a.files:
    rows = load(f)
    mesh = [r for r in rows if r["items"]]
    S = lambda k, rr=rows: sum(r[k] for r in rr)
    it = S("items") or 1
    ims = S("ims") or 1
    print(f"{f}: {len(rows)} frames, {len(mesh)} with mesh items, cut frames {S('cut')}")
    print(f"  mesh items {S('items')}: interpolated {100.0 * S('full') / it:.1f} %, camera only "
          f"{100.0 * S('cam') / it:.1f} % (jumped {S('far')}), exact {100.0 * S('exact') / it:.1f} % "
          f"(Z-scale composites {S('zscale')}), unmatched {100.0 * S('unmatched') / it:.1f} %; "
          f"skinned {S('skin')}")
    print(f"  immediate records {S('ims')}: repeated exactly {100.0 * S('ims_static') / ims:.1f} % "
          f"(the rest: 2D / effects that change, shown as the latest frame)")
    if mesh and a.worst:
        mesh.sort(key=lambda r: r["full"] / r["items"])
        for r in mesh[:a.worst]:
            print(f"  low frame {r['frame']}: items {r['items']} interpolated {r['full']} camera {r['cam']} "
                  f"exact {r['exact']} unmatched {r['unmatched']} cut {r['cut']}")
