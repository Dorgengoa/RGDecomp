# SPDX-License-Identifier: CC0-1.0
"""pairsheet.py OUT.png LABEL_A:IMG_A LABEL_B:IMG_B [...] -- every argument after OUT
is a row of LABEL=IMAGE items separated by ','; each image resized to 512x448 and labelled
(side-by-side checks: port vs PCSX2, aspect vs aspect)."""
import sys
from PIL import Image, ImageDraw

rows = [r.split(',') for r in sys.argv[2:]]
W, H = 512, 448
cols = max(len(r) for r in rows)
sheet = Image.new('RGB', (cols * W, len(rows) * (H + 16)), 'black')
d = ImageDraw.Draw(sheet)
for y, r in enumerate(rows):
    for x, item in enumerate(r):
        lab, path = item.split('=', 1)
        im = Image.open(path).convert('RGB').resize((W, H), Image.BILINEAR)
        sheet.paste(im, (x * W, y * (H + 16) + 16))
        d.text((x * W + 4, y * (H + 16) + 2), lab, fill='white')
sheet.save(sys.argv[1])
