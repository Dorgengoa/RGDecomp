#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare two directories of same-named --shot PNGs (e.g. two replays of one route under
different env knobs: RG_NR_TEXCACHE_MB=8 vs default).

    python tools/native/shotdiff.py DIR_A DIR_B [--out D] [--thresh 24]

Per shot: changed-pixel count (max channel delta > thresh), mean abs delta, bbox of change,
and a high-frequency ratio B/A inside the bbox (sum |dx|+|dy|; < 1 means B is blurrier /
lower-res there).  --out writes side-by-side crops (A | B | diff) of every changed shot.
"""
import argparse
from pathlib import Path

import numpy as np
from PIL import Image


def hf(a):
    a = a.astype(np.int32).sum(axis=2)
    return float(np.abs(np.diff(a, axis=0)).sum() + np.abs(np.diff(a, axis=1)).sum())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("a"); ap.add_argument("b")
    ap.add_argument("--out"); ap.add_argument("--thresh", type=int, default=24)
    o = ap.parse_args()
    A, B = Path(o.a), Path(o.b)
    if o.out: Path(o.out).mkdir(parents=True, exist_ok=True)
    nsame = 0
    for pa in sorted(A.glob("*.png")):
        pb = B / pa.name
        if not pb.exists(): print(pa.name, "missing in B"); continue
        x = np.asarray(Image.open(pa).convert("RGB")); y = np.asarray(Image.open(pb).convert("RGB"))
        if x.shape != y.shape: print(pa.name, "size", x.shape, y.shape); continue
        d = np.abs(x.astype(np.int16) - y.astype(np.int16)).max(axis=2)
        m = d > o.thresh
        n = int(m.sum())
        if n == 0: nsame += 1; continue
        ys, xs = np.nonzero(m)
        x0, x1, y0, y1 = xs.min(), xs.max() + 1, ys.min(), ys.max() + 1
        ca, cb = x[y0:y1, x0:x1], y[y0:y1, x0:x1]
        r = hf(cb) / max(hf(ca), 1.0)
        print(f"{pa.name}: {n} px changed, mean {d.mean():.3f}, bbox {x0},{y0}-{x1},{y1}, hf B/A {r:.3f}")
        if o.out:
            dv = np.repeat((m * 255).astype(np.uint8)[y0:y1, x0:x1, None], 3, axis=2)
            Image.fromarray(np.concatenate([ca, cb, dv], axis=1)).save(Path(o.out) / pa.name)
    print(f"{nsame} shots identical (thresh {o.thresh})")


if __name__ == "__main__":
    main()
