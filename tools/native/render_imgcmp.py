#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Image comparison for the native renderer (docs/NATIVE-RENDER.md "Verification").

  python tools/native/render_imgcmp.py REF_DIR TEST_DIR [--fields a,b,..] [--out DIR]
                                       [--psnr DB] [--bad PCT] [--ssim S]

Compares fNNNNN_display.png of two runs (the emulated oracle and the native
renderer) field by field.  The native renderer is not bit-exact by design
(no 1/16-pixel vertex snapping, float interpolation, hardware blending and
filtering), so the metric tolerates sub-pixel edge shifts and +-few LSB
colour differences but catches wrong geometry, textures, colours or state:

  PSNR    over RGB, whole frame                         pass: >= --psnr (30 dB)
  bad%    pixels whose largest channel differs by > 48  pass: <= --bad (2.0 %)
          after a 3x3 tolerance: a test pixel counts as matching when any
          reference pixel of its 3x3 neighbourhood is within 48 (sub-pixel
          edge shifts move edges by one pixel)
  SSIM    mean structural similarity of 8x8 luma blocks  pass: >= --ssim (0.95)

A field passes when all three pass.  --out writes side-by-side and amplified
difference images.  Exit 0 when every compared field passes.
"""
import argparse, math, sys
from pathlib import Path

import numpy as np
from PIL import Image


def load(p):
    return np.asarray(Image.open(p).convert('RGB'), dtype=np.int16)


def psnr(a, b):
    mse = np.mean((a.astype(np.float64) - b.astype(np.float64)) ** 2)
    return 99.0 if mse == 0 else 10.0 * math.log10(255.0 * 255.0 / mse)


def bad_pct(a, b, thr=48):
    h, w, _ = a.shape
    pad = np.pad(a, ((1, 1), (1, 1), (0, 0)), mode='edge')
    best = None
    for dy in range(3):
        for dx in range(3):
            d = np.abs(pad[dy:dy + h, dx:dx + w] - b).max(axis=2)
            best = d if best is None else np.minimum(best, d)
    return 100.0 * np.count_nonzero(best > thr) / (h * w), best


def ssim(a, b, k=8):
    def luma(x):
        return 0.299 * x[..., 0] + 0.587 * x[..., 1] + 0.114 * x[..., 2]
    x, y = luma(a.astype(np.float64)), luma(b.astype(np.float64))
    h, w = x.shape
    h, w = h - h % k, w - w % k
    x = x[:h, :w].reshape(h // k, k, w // k, k).transpose(0, 2, 1, 3).reshape(-1, k * k)
    y = y[:h, :w].reshape(h // k, k, w // k, k).transpose(0, 2, 1, 3).reshape(-1, k * k)
    mx, my = x.mean(1), y.mean(1)
    vx, vy = x.var(1), y.var(1)
    cxy = ((x - mx[:, None]) * (y - my[:, None])).mean(1)
    c1, c2 = (0.01 * 255) ** 2, (0.03 * 255) ** 2
    s = ((2 * mx * my + c1) * (2 * cxy + c2)) / ((mx * mx + my * my + c1) * (vx + vy + c2))
    return float(s.mean())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('ref')
    ap.add_argument('test')
    ap.add_argument('--fields')
    ap.add_argument('--out')
    ap.add_argument('--psnr', type=float, default=30.0)
    ap.add_argument('--bad', type=float, default=2.0)
    ap.add_argument('--ssim', type=float, default=0.95)
    a = ap.parse_args()
    ref, test = Path(a.ref), Path(a.test)
    if a.fields:
        fields = [int(x) for x in a.fields.split(',')]
    else:
        fields = sorted(int(p.name[1:6]) for p in ref.glob('f?????_display.png') if (test / p.name).exists())
    if not fields:
        print('no common fNNNNN_display.png')
        return 2
    out = Path(a.out) if a.out else None
    if out:
        out.mkdir(parents=True, exist_ok=True)
    ok_all = True
    print('%6s %7s %6s %6s %s' % ('field', 'PSNR', 'bad%', 'SSIM', 'verdict'))
    for f in fields:
        pa, pb = ref / ('f%05d_display.png' % f), test / ('f%05d_display.png' % f)
        if not pa.exists() or not pb.exists():
            print('%6d missing' % f)
            ok_all = False
            continue
        A, B = load(pa), load(pb)
        if A.shape != B.shape:
            print('%6d size %s vs %s' % (f, A.shape, B.shape))
            ok_all = False
            continue
        p = psnr(A, B)
        bp, best = bad_pct(A, B)
        s = ssim(A, B)
        ok = p >= a.psnr and bp <= a.bad and s >= a.ssim
        ok_all &= ok
        print('%6d %7.2f %6.2f %6.3f %s' % (f, p, bp, s, 'pass' if ok else 'FAIL'))
        if out:
            h, w, _ = A.shape
            side = np.zeros((h, w * 3, 3), dtype=np.uint8)
            side[:, :w] = A
            side[:, w:2 * w] = B
            amp = np.clip(np.abs(A - B).max(axis=2) * 4, 0, 255).astype(np.uint8)
            side[:, 2 * w:] = np.stack([amp, (best > 48) * 255, np.zeros_like(amp)], axis=2)
            Image.fromarray(side).save(out / ('cmp_f%05d.png' % f))
    print('PASS' if ok_all else 'FAIL')
    return 0 if ok_all else 1


if __name__ == '__main__':
    sys.exit(main())
