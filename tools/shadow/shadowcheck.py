#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""shadowcheck.py - regression check for the shadow bands (BRINGUP-HISTORY "2026-10-26 (shadow
bands)", docs/NATIVE-RENDER.md "Shadow maps at the internal resolution"): boots save2 to field
3,850 (the Hooded Man's shadow-map shadow at the transporter) at internal res x1 and at each
SCALE, and compares the shadow map the full-screen shadow sprite decodes (a 192x192 CT32 work
buffer at TBP 14336, whose alpha the game makes by a CT16 channel shuffle) in the 4 MB mirror at
that draw (RG_NR_RTDUMP + RG_NR_RTDUMP_TBP, nr_dev.cpp) against x1; then the displayed shadow
region (PSNR vs x1).

  python tools/shadow/shadowcheck.py --exe build/X/rg-game.exe [--scales 3,5] [--out DIR]
      [--max-bad 8] [--min-psnr 28]

FAIL when any scale has more than --max-bad map texels whose alpha differs from their own red by
more than 16 (the shuffle copies red/green into alpha; the bands: texels in columns 8k at x3
before the fix) or the shadow region's PSNR is
below --min-psnr.  Exit 0 PASS, 1 FAIL, 2 could not run, 77 (--skip-missing) no data / card.
--control (or RG_SHCHECK_FAULT=1) runs the scaled exes with RG_NR_UV16=0 (the old snap without
the 1/16 rounding): the check must FAIL at x3 (exit 0 when it does).  ctests fixtures.shadowbands
and fixtures.shadowbands_control (tests/fixtures/CMakeLists.txt).
"""
import argparse
import math
import os
import shutil
import subprocess
import sys

PORT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(PORT, 'tools', 'prompts'))
from vram_gaiji import read_rect  # noqa: E402

FIELD, FRAME = 3850, 2288          # field dumped / EE frame of the shadow draw in it
TBP, TBW, W = 14336, 3, 192
BOX = (380, 330, 480, 383)         # shadow region, native pixels


def run(exe, scale, out, env_extra):
    d = os.path.join(out, 'x%d' % scale)
    shutil.rmtree(d, ignore_errors=True)
    os.makedirs(d)
    wd = os.path.abspath(d)
    env = dict(os.environ)
    env.update(env_extra)
    env['RG_NR_RTDUMP_TBP'] = str(TBP)
    env['RG_NR_RTDUMP'] = '0:%d:1:%s' % (FRAME, wd.replace('\\', '/'))
    name = 'shchk_%s_x%d' % (os.path.basename(os.path.abspath(out)), scale)
    sh = shutil.which('sh') or 'sh'
    subprocess.run([sh, os.path.join(PORT, 'tools', 'native', 'render_fx.sh'), name, 'native', exe, 'boot:save2',
                    str(scale), '100', str(FIELD)], env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    mem = os.path.join(d, 'rt_%05d_0000_mem.vram' % FRAME)
    png = os.path.join(PORT, 'out', 'nrender', 'runs', name, 'f%05d_display.png' % FIELD)
    if not os.path.exists(mem) or not os.path.exists(png):
        return None, None
    return read_rect(open(mem, 'rb').read(), TBP, TBW, W, W), png


def region(png):
    from PIL import Image
    im = Image.open(png).convert('RGB')
    s = max(1, im.size[0] // 512)
    return im.crop(tuple(v * s for v in BOX)).resize((BOX[2] - BOX[0], BOX[3] - BOX[1]), Image.BOX)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--exe', required=True)
    ap.add_argument('--scales', default='3,5')
    ap.add_argument('--out', default=os.path.join(PORT, 'out', 'shadow', 'check'))
    ap.add_argument('--max-bad', type=int, default=2)
    ap.add_argument('--min-psnr', type=float, default=28.0)
    ap.add_argument('--api', choices=['d3d11', 'vulkan'], help='RG_GPU_API for the runs')
    ap.add_argument('--control', action='store_true',
                    help='RG_NR_UV16=0 on the scaled runs (the pre-fix snap): exit 0 when the check FAILS')
    ap.add_argument('--skip-missing', action='store_true', help='exit 77 without the game data / save2 card')
    a = ap.parse_args()
    fault = a.control or os.environ.get('RG_SHCHECK_FAULT') == '1'
    if a.api:
        os.environ['RG_GPU_API'] = a.api
    card = os.path.join(PORT, 'out', 'fixtures', 'cards', 'save2')
    if not os.path.isdir(card) or not os.path.isdir(os.path.join(PORT, 'data')):
        print('shadowcheck: no save2 card / game data')
        return 77 if a.skip_missing else 2
    os.makedirs(a.out, exist_ok=True)
    ref, refpng = run(a.exe, 1, a.out, {})
    if ref is None:
        print('shadowcheck: x1 run produced no dump (exe without RG_NR_RTDUMP, or no save2 card)')
        return 2
    rr = region(refpng)
    x1bad = sum(1 for i in range(W * W) if abs(ref[i * 4 + 3] - ref[i * 4]) > 16)
    print('shadowcheck x1: map texels whose alpha is not their red (+-16): %d' % x1bad)
    ok = True
    for s in [int(v) for v in a.scales.split(',') if v]:
        m, png = run(a.exe, s, a.out, {'RG_NR_UV16': '0'} if fault else {})
        if m is None:
            print('shadowcheck x%d: no dump' % s)
            return 2
        # the shuffle copies each texel's own red/green into its alpha: a band texel's alpha
        # no longer follows its red (x1: 0 such texels)
        bad = cols = 0
        hit = set()
        for i in range(W * W):
            if abs(m[i * 4 + 3] - m[i * 4]) > 16:
                bad += 1
                hit.add(i % W)
        r = region(png)
        px = [abs(x - y) for p, q in zip(rr.getdata(), r.getdata()) for x, y in zip(p, q)]
        mse = sum(v * v for v in px) / len(px)
        psnr = 99.0 if mse == 0 else 10 * math.log10(255 * 255 / mse)
        cols = sum(1 for c in hit if c % 8 == 0)
        good = bad <= a.max_bad and psnr >= a.min_psnr
        ok &= good
        print('shadowcheck x%d: map texels whose alpha is not their red (+-16): %d (%d columns 8k), shadow region PSNR %.2f dB vs x1: %s'
              % (s, bad, cols, psnr, 'PASS' if good else 'FAIL'))
    ok &= x1bad <= a.max_bad
    print('shadowcheck: %s%s' % ('PASS' if ok else 'FAIL', ' (control: must FAIL)' if a.control else ''))
    if a.control:
        return 0 if not ok else 1
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
