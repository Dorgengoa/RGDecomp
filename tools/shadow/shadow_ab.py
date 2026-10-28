#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""shadow_ab.py - A/B runs of the shadow-bands case (docs/NATIVE-RENDER.md "Shadow map at the
internal resolution"): each VARIANT is one render_fx.sh run from a card (default boot:save2,
field 3,850: the Hooded Man's shadow-map shadow at the transporter) with its own exe / scale /
mode / env; the crops of the same region are stacked into one PNG and each variant's crop is
compared with the first one (PSNR, max diff).

  python tools/shadow/shadow_ab.py OUT.png NAME=EXE,SCALE[,MODE][,ENV=V;ENV=V] ...
      [--fx boot:save2] [--field 3850] [--box x0,y0,x1,y1 (native pixels)] [--zoom 3] [--reuse]

--reuse: skip runs whose out/nrender/runs/sha_NAME/fFIELD_display.png exists.
"""
import argparse
import math
import os
import shutil
import subprocess
import sys
from PIL import Image, ImageChops

PORT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RUNS = os.path.join(PORT, 'out', 'nrender', 'runs')
SH = shutil.which('sh') or 'sh'


def run(name, exe, scale, mode, env, fx, field, reuse):
    d = os.path.join(RUNS, 'sha_' + name)
    png = os.path.join(d, 'f%05d_display.png' % field)
    if reuse and os.path.exists(png):
        return png
    e = dict(os.environ)
    e.update(env)
    fields = 100 if (fx == 'boot:save2' and field <= 3850) else field   # (boot: fields after the boot script's end)
    subprocess.run([SH, os.path.join(PORT, 'tools', 'native', 'render_fx.sh'), 'sha_' + name, mode, exe, fx,
                    str(scale), str(fields), str(field)], env=e, check=False, stdout=subprocess.DEVNULL)
    return png


def crop(png, box, zoom):
    im = Image.open(png).convert('RGB')
    s = im.size[0] // 512 if im.size[0] >= 512 else 1
    c = im.crop(tuple(v * s for v in box))
    w, h = (box[2] - box[0]) * zoom * 3, (box[3] - box[1]) * zoom * 3
    return c.resize((w, h), Image.NEAREST), c.resize((box[2] - box[0], box[3] - box[1]), Image.BOX)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('out')
    ap.add_argument('variants', nargs='+')
    ap.add_argument('--fx', default='boot:save2')
    ap.add_argument('--field', type=int, default=3850)
    ap.add_argument('--box', default='380,330,480,383')
    ap.add_argument('--zoom', type=int, default=1)
    ap.add_argument('--reuse', action='store_true')
    a = ap.parse_args()
    box = [int(v) for v in a.box.split(',')]
    tiles, ref = [], None
    for v in a.variants:
        name, spec = v.split('=', 1)
        parts = spec.split(',')
        exe, scale = parts[0], int(parts[1])
        mode = parts[2] if len(parts) > 2 and parts[2] else 'native'
        env = {}
        if len(parts) > 3:
            for kv in ','.join(parts[3:]).split(';'):
                if kv:
                    k, val = kv.split('=', 1)
                    env[k] = val
        png = run(name, exe, scale, mode, env, a.fx, a.field, a.reuse)
        if not os.path.exists(png):
            print('%-14s no image (%s)' % (name, png))
            continue
        big, small = crop(png, box, a.zoom)
        if ref is None:
            ref = small
            print('%-14s reference' % name)
        else:
            d = ImageChops.difference(ref, small)
            px = list(d.getdata())
            mse = sum(c * c for p in px for c in p) / (3.0 * len(px))
            print('%-14s PSNR %6.2f dB  max %3d' % (name, 99.0 if mse == 0 else 10 * math.log10(255 * 255 / mse),
                                                 max(max(p) for p in px)))
        tiles.append(big)
    if tiles:
        W = max(t.size[0] for t in tiles)
        H = sum(t.size[1] + 6 for t in tiles)
        o = Image.new('RGB', (W, H), (255, 0, 0))
        y = 0
        for t in tiles:
            o.paste(t, (0, y))
            y += t.size[1] + 6
        o.save(a.out)


if __name__ == '__main__':
    sys.exit(main())
