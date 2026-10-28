#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""vramrect.py - write a PSMCT32 rectangle of a GS local-memory dump (fNNNNN.vram from
RG_GS_DUMP_DIR / RG_GS_DUMP_FIELDS) as two PNGs: RGB and alpha (x2 for visibility).

  python tools/shadow/vramrect.py f03850.vram BP BW W H OUT_PREFIX [--zoom N]

Used by the shadow-bands lane (docs/NATIVE-RENDER.md "Shadow map at the internal resolution")
to look at the shadow-map work buffers the GS / the 1x mirror hold.
"""
import argparse
import os
import sys
from PIL import Image

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'prompts'))
from vram_gaiji import read_rect  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('vram'); ap.add_argument('bp', type=int); ap.add_argument('bw', type=int)
    ap.add_argument('w', type=int); ap.add_argument('h', type=int); ap.add_argument('out')
    ap.add_argument('--zoom', type=int, default=4)
    a = ap.parse_args()
    v = open(a.vram, 'rb').read()
    px = read_rect(v, a.bp, a.bw, a.w, a.h)
    im = Image.frombytes('RGBA', (a.w, a.h), px)
    z = (a.w * a.zoom, a.h * a.zoom)
    im.convert('RGB').resize(z, Image.NEAREST).save(a.out + '_rgb.png')
    al = bytes(min(255, b * 2) for b in px[3::4])
    Image.frombytes('L', (a.w, a.h), al).resize(z, Image.NEAREST).save(a.out + '_a.png')


if __name__ == '__main__':
    main()
