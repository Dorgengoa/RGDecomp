#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Character pose smoothness of presented frame sequences (docs/NATIVE-RENDER.md "Interpolated
presentation", checkpoint 13: composite poses).

  python tools/native/interp_pose.py DIR [DIR2 ...] [--crop X0,Y0,X1,Y1] [--per N]
         [--montage OUT.png --from K --count M] [--csv OUT.tsv]

DIR holds the PNGs one run presented in order (rg-game headless, RG_INTERP_SIM=hz,
RG_INTERP_DUMP=DIR: sNNNNNN_fFFFFF.png), e.g. out/interp/fight/NAME_dump from
tools/native/interp_fight.sh.  Everything is measured inside --crop (fractions of the image;
default 0.25,0.3,0.7,0.85 = the battle characters of the ch07_rosa route), so the change between
presents is the characters' (pose, place) plus whatever moves behind them.

Per run:

  crop mad      mean absolute difference of the crop between consecutive presents (0..255)
  peak share    in each window of --per presents (default: presents per game frame, 144 Hz over
                30 Hz logic = 5) the largest single change over the window's total, averaged over
                windows with change: a pose that steps once per game frame puts the whole change
                into one present (snap control ~1.0, placement-only composites ~0.6-0.8 because
                the pose still steps); an even motion over 4.8 presents ~0.2-0.35
  step judder   coefficient of variation of the crop mad over 5-present windows (interp_smooth.py's
                step judder, restricted to the crop)
  pose peak share  the same over the residual: the crop mad after the best whole-crop
                translation between the two presents (phase correlation), so a character that only
                travels (placement) changes little and a pose that steps once per game frame shows as
                one large residual per window; snap ~1.0
  switch ratio  (--switches REF) at each game-frame switch (where REF's crop changes) the change
                over the mean change of the two presents before and after: ~1 an even motion, the
                pose stepping once per game frame shows as >> 1 (placement only: ~2)
  still         presents whose crop equals the previous one exactly (a 144 Hz run of 30 Hz logic
                without interpolation repeats each image: ~79 %)

--montage writes the crops of presents K .. K+M-1 of every DIR side by side, one row per DIR
(the visual evidence: the in-between poses)."""
import argparse
from pathlib import Path

import numpy as np
from PIL import Image


def crops(d, crop):
    files = sorted(Path(d).glob("s*.png"))
    out = []
    for f in files:
        im = Image.open(f).convert("RGB")
        w, h = im.size
        x0, y0, x1, y1 = crop
        out.append((f.name, im.crop((int(x0 * w), int(y0 * h), int(x1 * w), int(y1 * h)))))
    return out


def shift_of(a, b):
    """integer translation of luma b against a (phase correlation)"""
    h, w = a.shape
    win = np.outer(np.hanning(h), np.hanning(w)).astype(np.float32)
    r = np.fft.rfft2(a * win) * np.conj(np.fft.rfft2(b * win))
    r /= np.abs(r) + 1e-6
    c = np.fft.irfft2(r, s=a.shape)
    y, x = np.unravel_index(np.argmax(c), c.shape)
    if y > h // 2:
        y -= h
    if x > w // 2:
        x -= w
    return int(y), int(x)


def residual(a, b):
    """mad of b against a after the best whole-crop translation: what is not rigid motion"""
    la = a @ np.float32([0.299, 0.587, 0.114])
    lb = b @ np.float32([0.299, 0.587, 0.114])
    dy, dx = shift_of(la, lb)
    h, w = la.shape
    if abs(dy) > h // 4 or abs(dx) > w // 4:
        dy = dx = 0
    ya, yb = max(0, dy), max(0, -dy)
    xa, xb = max(0, dx), max(0, -dx)
    hh, ww = h - abs(dy), w - abs(dx)
    return float(np.mean(np.abs(a[ya:ya + hh, xa:xa + ww] - b[yb:yb + hh, xb:xb + ww])))


def shares(v, per):
    sh = []
    for k in range(0, len(v) - per + 1):
        w = v[k:k + per]
        s = sum(w)
        if s > 0.5:
            sh.append(max(w) / s)
    return float(np.mean(sh)) if sh else 0.0, len(sh)


def analyse(cs, per):
    a = [np.asarray(c, dtype=np.float32) for _, c in cs]
    mad = [float(np.mean(np.abs(a[k] - a[k - 1]))) for k in range(1, len(a))]
    res = [residual(a[k - 1], a[k]) for k in range(1, len(a))]
    share, nwin = shares(mad, per)
    rshare, rwin = shares(res, per)
    cvm = []
    for k in range(0, len(mad) - 4):
        w = mad[k:k + 5]
        if np.mean(w) > 0.05:
            cvm.append(float(np.std(w) / np.mean(w)))
    still = sum(1 for m in mad if m == 0.0)
    return dict(n=len(a), mad=mad, res=res, share=share, nwin=nwin, rshare=rshare, rwin=rwin,
                judder=float(np.median(cvm)) if cvm else 0.0, still=still)


ap = argparse.ArgumentParser()
ap.add_argument("dirs", nargs="+")
ap.add_argument("--crop", default="0.25,0.3,0.7,0.85")
ap.add_argument("--per", type=int, default=5)
ap.add_argument("--montage")
ap.add_argument("--from", dest="k0", type=int, default=0)
ap.add_argument("--count", type=int, default=10)
ap.add_argument("--csv")
ap.add_argument("--switches", help="reference run (e.g. the composites-exact RG_INTERP_ZSCALE=0 isolated run, or the snap "
                "control): the presents where its crop changes are the game-frame switches")
a = ap.parse_args()
crop = [float(v) for v in a.crop.split(",")]
rows = []
strips = []
sw = None
if a.switches:
    rc = [np.asarray(c, dtype=np.float32) for _, c in crops(a.switches, crop)]
    sw = set(k for k in range(1, len(rc)) if float(np.mean(np.abs(rc[k] - rc[k - 1]))) > 0.05)
for d in a.dirs:
    cs = crops(d, crop)
    if len(cs) < a.per + 2:
        print(f"{d}: {len(cs)} presents, too few")
        continue
    r = analyse(cs, a.per)
    print(f"{d}: {r['n']} presents, crop mad mean {np.mean(r['mad']):.2f}, peak share {r['share']:.2f} over {r['nwin']} "
          f"windows, pose peak share {r['rshare']:.2f} (residual mean {np.mean(r['res']):.2f}), step judder {r['judder']:.2f}, still {r['still']} ({100.0 * r['still'] / (r['n'] - 1):.1f} %)")
    if sw:
        # switch ratio: the change at a game-frame switch over the mean change of the presents
        # around it (k-2, k-1, k+1, k+2); ~1 when the pose moves evenly, >> 1 when it steps
        rat = []
        for k in sorted(sw):
            j = k - 1   # (mad index of the step into present k)
            nb = [r["mad"][i] for i in (j - 2, j - 1, j + 1, j + 2) if 0 <= i < len(r["mad"])]
            if len(nb) == 4 and np.mean(nb) > 0.05:
                rat.append(r["mad"][j] / float(np.mean(nb)))
        print(f"  switch ratio {float(np.median(rat)) if rat else 0.0:.2f} (median over {len(rat)} game-frame switches)")
    for k, m in enumerate(r["mad"]):
        rows.append((d, cs[k + 1][0], m, r["res"][k]))
    if a.montage:
        strips.append([c for _, c in cs[a.k0:a.k0 + a.count]])
if a.montage and strips:
    cw, ch = strips[0][0].size
    n = max(len(s) for s in strips)
    sheet = Image.new("RGB", (cw * n + 2 * (n - 1), ch * len(strips) + 2 * (len(strips) - 1)), (255, 0, 255))
    for j, s in enumerate(strips):
        for i, c in enumerate(s):
            sheet.paste(c, (i * (cw + 2), j * (ch + 2)))
    sheet.save(a.montage)
    print(f"montage {a.montage}: {len(strips)} rows x {n} presents from {a.k0}")
if a.csv:
    with open(a.csv, "w") as f:
        f.write("run\tframe\tcrop_mad\tresidual\n")
        for row in rows:
            f.write("%s\t%s\t%.3f\t%.3f\n" % row)
