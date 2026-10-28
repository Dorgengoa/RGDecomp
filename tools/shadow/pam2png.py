#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""pam2png.py - convert RG_NR_RTDUMP target dumps (nr_dev.cpp, RGBA .pam) to PNGs: RGB and the
alpha channel (x2, GS 0x80 = 1.0 shown as 255) side by side, optionally cropped / zoomed.

  python tools/shadow/pam2png.py DUMP.pam [DUMP.pam ...] [--crop x0,y0,x1,y1] [--zoom N] [--out DIR]
"""
import argparse
import os
from PIL import Image


def load(p):
    b = open(p, 'rb').read()
    hdr, _, data = b.partition(b'ENDHDR\n')
    kv = dict(l.split(' ', 1) for l in hdr.decode().splitlines()[1:] if ' ' in l)
    w, h = int(kv['WIDTH']), int(kv['HEIGHT'])
    return Image.frombytes('RGBA', (w, h), data[:w * h * 4])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('pam', nargs='+')
    ap.add_argument('--crop')
    ap.add_argument('--zoom', type=int, default=1)
    ap.add_argument('--out')
    a = ap.parse_args()
    for p in a.pam:
        im = load(p)
        if a.crop:
            im = im.crop(tuple(int(v) for v in a.crop.split(',')))
        rgb = im.convert('RGB')
        al = im.getchannel('A').point(lambda v: min(255, v * 2)).convert('RGB')
        o = Image.new('RGB', (im.size[0] * 2 + 4, im.size[1]), (255, 0, 0))
        o.paste(rgb, (0, 0))
        o.paste(al, (im.size[0] + 4, 0))
        if a.zoom > 1:
            o = o.resize((o.size[0] * a.zoom, o.size[1] * a.zoom), Image.NEAREST)
        d = a.out or os.path.dirname(p)
        o.save(os.path.join(d, os.path.basename(p)[:-4] + '.png'))


if __name__ == '__main__':
    main()
