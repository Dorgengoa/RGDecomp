# SPDX-License-Identifier: CC0-1.0
"""bestmatch.py REF.png DIR [N] -- rank the native frames in DIR (f*.png, not -view)
by similarity to REF (e.g. a PCSX2 window shot), both scaled to 128x112 grey; prints the
N best (mean absolute difference, 0 = identical).  Used to line up port frames with a
PCSX2 run whose timeline is offset (docs/WIDESCREEN.md "Stage 1", PCSX2 reference)."""
import sys, os
from PIL import Image, ImageChops, ImageStat


def small(p):
    return Image.open(p).convert('L').resize((128, 112), Image.BILINEAR)


ref = small(sys.argv[1])
n = int(sys.argv[3]) if len(sys.argv) > 3 else 5
res = []
for f in os.listdir(sys.argv[2]):
    if f.endswith('.png') and not f.endswith('-view.png'):
        d = ImageStat.Stat(ImageChops.difference(ref, small(os.path.join(sys.argv[2], f)))).mean[0]
        res.append((d, f))
for d, f in sorted(res)[:n]:
    print('%7.2f  %s' % (d, f))
