#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Per-shot difference of two shot directories (play.py --shots / render_fx dumps): for each
PNG name present in both, the pixels that differ, the mean and max absolute difference and the
PSNR; a summary line (docs/NATIVE-RENDER.md checkpoint 12: A/B of renderer knobs on the same
run, e.g. RG_NR_REINT=0 vs 1).

    python tools/native/shotset_diff.py DIR_A DIR_B [--glob 's*.png'] [--quiet]
"""
import argparse
import math
from pathlib import Path

import numpy as np
from PIL import Image

ap = argparse.ArgumentParser()
ap.add_argument("a")
ap.add_argument("b")
ap.add_argument("--glob", default="s*.png")
ap.add_argument("--quiet", action="store_true")
o = ap.parse_args()
names = sorted(set(p.name for p in Path(o.a).glob(o.glob)) & set(p.name for p in Path(o.b).glob(o.glob)))
tot_px = tot_same = 0
worst = None
for n in names:
    x = np.asarray(Image.open(Path(o.a) / n).convert("RGB"), dtype=np.int16)
    y = np.asarray(Image.open(Path(o.b) / n).convert("RGB"), dtype=np.int16)
    if x.shape != y.shape:
        print(f"{n}: sizes differ {x.shape} {y.shape}")
        continue
    d = np.abs(x - y)
    px = int((d.max(axis=2) > 0).sum())
    mse = float((d.astype(np.float64) ** 2).mean())
    psnr = 99.0 if mse == 0 else 10 * math.log10(255 * 255 / mse)
    tot_px += 1
    tot_same += px == 0
    if worst is None or psnr < worst[1]:
        worst = (n, psnr)
    if not o.quiet:
        print(f"{n}: {px} px differ, mean {d.mean():.3f}, max {int(d.max())}, PSNR {psnr:.2f} dB")
print(f"{len(names)} shots, {tot_same} identical" + (f", lowest PSNR {worst[1]:.2f} dB ({worst[0]})" if worst else ""))
