#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Smoothness of a presented frame sequence (docs/NATIVE-RENDER.md "Interpolated presentation").

  python tools/native/interp_smooth.py DIR [DIR2 ...] [--csv OUT.tsv] [--crop X0,Y0,X1,Y1]

--crop measures the shift in a sub-rectangle (fractions of the image): a background band
without the HUD and the camera-followed character (e.g. 0,0,1,0.3), where a camera pan is
the dominant motion.

DIR holds the PNGs one run presented in order (rg-game headless with RG_INTERP_SIM=hz and
RG_INTERP_DUMP=DIR: sNNNNNN_fFFFFF.png, sequence number first).  Per consecutive pair:

  mad     mean absolute difference (0..255, RGB)
  shift   global image motion (phase correlation of the luma, pixels; the camera's pan)

and per run:

  changed    presents that differ from the previous one (a 144 Hz run of 30 Hz logic without
             interpolation repeats each image ~4.8 times: ~21 % changed)
  judder     coefficient of variation of the shift magnitude over the presents while the view
             moves (|shift| > 0.25 px over a 5-present window): 0 = every present moves the same
             distance; the snap control (no interpolation) shows 0 0 0 0 X steps, ~2
  step judder  the same coefficient over the per-present change (mad) in 5-present windows
             with change: local motion counts (a character part that snaps once per game frame
             while the scene around it moves every present); snap control ~2
  pops       presents that differ from both neighbours while the neighbours agree with each
             other (mad(k-1,k) + mad(k,k+1) > 2.5 mad(k-1,k+1) + 1): a frame out of sequence,
             a ghost, a wrong pose for one present; should be 0
"""
import argparse
import sys
from pathlib import Path

import numpy as np
from PIL import Image


def load(p, size=None):
    im = Image.open(p).convert("RGB")
    a = np.asarray(im, dtype=np.float32)
    return a


def luma(a):
    return 0.299 * a[..., 0] + 0.587 * a[..., 1] + 0.114 * a[..., 2]


def phase_shift(a, b):
    """global translation b relative to a (pixels), by phase correlation with sub-pixel peak"""
    h, w = a.shape
    win = np.outer(np.hanning(h), np.hanning(w)).astype(np.float32)
    fa = np.fft.rfft2(a * win)
    fb = np.fft.rfft2(b * win)
    r = fa * np.conj(fb)
    r /= np.abs(r) + 1e-6
    c = np.fft.irfft2(r, s=a.shape)
    y, x = np.unravel_index(np.argmax(c), c.shape)

    def sub(cm, c0, cp):
        d = cm - 2 * c0 + cp
        return 0.5 * (cm - cp) / d if abs(d) > 1e-9 else 0.0

    dy = y + sub(c[(y - 1) % h, x], c[y, x], c[(y + 1) % h, x])
    dx = x + sub(c[y, (x - 1) % w], c[y, x], c[y, (x + 1) % w])
    if dy > h / 2:
        dy -= h
    if dx > w / 2:
        dx -= w
    return -dx, -dy


def analyse(d, crop=None):
    files = sorted(Path(d).glob("s*.png"))
    if len(files) < 3:
        return None
    imgs = [load(f) for f in files]
    lum = [luma(i)[::2, ::2] for i in imgs]
    if crop:
        h, w = lum[0].shape
        x0, y0, x1, y1 = crop
        lum = [x[int(y0 * h):int(y1 * h), int(x0 * w):int(x1 * w)] for x in lum]
    n = len(imgs)
    mad = [float(np.mean(np.abs(imgs[k] - imgs[k - 1]))) for k in range(1, n)]
    shift = [phase_shift(lum[k - 1], lum[k]) for k in range(1, n)]
    mag = [float(np.hypot(*s)) * 2.0 for s in shift]   # (luma at half resolution)
    changed = sum(1 for m in mad if m > 0.0)
    # judder over moving stretches
    cv = []
    for k in range(0, len(mag) - 4):
        w = mag[k:k + 5]
        if np.mean(w) > 0.25:
            cv.append(float(np.std(w) / np.mean(w)))
    # step judder: the same over the per-present change (mad), so local motion counts too (a
    # character part that snaps once per game frame while the rest moves every present)
    cvm = []
    for k in range(0, len(mad) - 4):
        w = mad[k:k + 5]
        if np.mean(w) > 0.05:
            cvm.append(float(np.std(w) / np.mean(w)))
    pops = []
    for k in range(1, n - 1):
        a = mad[k - 1]
        b = mad[k]
        ac = float(np.mean(np.abs(imgs[k + 1] - imgs[k - 1])))
        if a + b > 2.5 * ac + 1.0:
            pops.append((files[k].name, a, b, ac))
    return dict(files=files, mad=mad, mag=mag, changed=changed, judder=float(np.median(cv)) if cv else 0.0,
                moving=len(cv), pops=pops, n=n, mjudder=float(np.median(cvm)) if cvm else 0.0, mwin=len(cvm))


ap = argparse.ArgumentParser()
ap.add_argument("dirs", nargs="+")
ap.add_argument("--csv")
ap.add_argument("--crop")
a = ap.parse_args()
crop = [float(v) for v in a.crop.split(",")] if a.crop else None
rows = []
for d in a.dirs:
    r = analyse(d, crop)
    if not r:
        print(f"{d}: fewer than 3 frames")
        continue
    print(f"{d}: {r['n']} presents, changed {r['changed']} ({100.0 * r['changed'] / (r['n'] - 1):.1f} %), "
          f"judder {r['judder']:.2f} over {r['moving']} moving windows, mean |shift| {np.mean(r['mag']):.2f} px, "
          f"pops {len(r['pops'])}, step judder {r['mjudder']:.2f} over {r['mwin']} windows")
    for p in r["pops"][:10]:
        print(f"  pop {p[0]}: mad {p[1]:.2f} / {p[2]:.2f}, neighbours {p[3]:.2f}")
    for k in range(len(r["mad"])):
        rows.append((d, r["files"][k + 1].name, r["mad"][k], r["mag"][k]))
if a.csv:
    with open(a.csv, "w") as f:
        f.write("run\tframe\tmad\tshift_px\n")
        for row in rows:
            f.write("%s\t%s\t%.3f\t%.3f\n" % row)
