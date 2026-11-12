#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""PSNR (RGB, whole frame or a crop) of card_shots.py shot dirs against a reference dir (lane
missnrm3; docs/NATIVE-RENDER.md "Leftover normals natively").

    python tools/native/shotpsnr.py REF_DIR DIR [DIR ..] [--crop x0,y0,x1,y1] [--fields a,b,..]

One row per field (fNNNNN.png present in REF and every DIR), one column per DIR: dB (inf =
identical), and the share of pixels whose largest channel differs by more than 24."""
import argparse
import math
import re
import sys
from pathlib import Path

import numpy as np
from PIL import Image


def shots(d):
    out = {}
    for p in Path(d).glob("f*.png"):
        if p.name.endswith("-view.png"):
            continue
        m = re.match(r"f(\d+)\.png$", p.name)
        if m:
            out[int(m.group(1))] = p
    return out


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("ref")
    ap.add_argument("dirs", nargs="+")
    ap.add_argument("--crop")
    ap.add_argument("--fields")
    a = ap.parse_args(argv)
    ref = shots(a.ref)
    ds = [shots(d) for d in a.dirs]
    fs = sorted(set(ref).intersection(*[set(d) for d in ds]))
    if a.fields:
        want = {int(x) for x in a.fields.split(",")}
        fs = [f for f in fs if f in want]
    crop = tuple(int(x) for x in a.crop.split(",")) if a.crop else None
    print("field  " + "  ".join("%-22s" % Path(d).name[-22:] for d in a.dirs))
    for f in fs:
        r = Image.open(ref[f]).convert("RGB")
        if crop:
            r = r.crop(crop)
        R = np.asarray(r, dtype=np.int32)
        cells = []
        for d in ds:
            t = Image.open(d[f]).convert("RGB")
            if t.size != Image.open(ref[f]).size:
                t = t.resize(Image.open(ref[f]).size)
            if crop:
                t = t.crop(crop)
            T = np.asarray(t, dtype=np.int32)
            mse = float(((R - T) ** 2).mean())
            db = 99.0 if mse == 0 else 10 * math.log10(255 * 255 / mse)
            bad = float((np.abs(R - T).max(axis=2) > 24).mean()) * 100
            cells.append("%6.2f dB %6.3f %%   " % (db, bad))
        print("%5d  %s" % (f, "  ".join(cells)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
