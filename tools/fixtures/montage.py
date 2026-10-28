#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Contact sheet of a play.py run's screenshots (one image to look at), or a side-by-side
sheet of port vs retail milestone shots.

    python tools/fixtures/montage.py OUTDIR [--cols 4] [--scale 0.5] [--from F] [--to F]
    python tools/fixtures/montage.py --pairs PORT_DIR RETAIL_DIR [--names a,b] [--out F]
                                     [--scale 0.5] [--match REGEX]
    python tools/fixtures/montage.py --grid DIR --rows a,b --cols x,y [--out F] [--scale 0.5]

Default mode: reads OUTDIR/sNNNNN.png (not the -view variants), writes OUTDIR/montage.png
with the field number printed on each tile.

--pairs: one row per image name found in both dirs (`<card>_<milestone>.png`: bootcheck.py
--shots on the port, tools/trace/cardboot.py on retail), port left, retail right, each
scaled to the same height and labelled; --match filters names (regex).  Writes --out
(default RETAIL_DIR/pairs.png).  Comparison is by content: the milestones are events
(field control, menu open), not equal frame numbers.
"""
import argparse
import re
import sys
from pathlib import Path

from PIL import Image, ImageDraw


def pairs(a):
    pd, rd = Path(a.pairs[0]), Path(a.pairs[1])
    names = sorted(p.name for p in rd.glob("*.png") if (pd / p.name).exists()
                   and not p.name.startswith("pairs") and "-view" not in p.name)
    if a.match:
        names = [n for n in names if re.search(a.match, n)]
    if not names:
        raise SystemExit("montage: no image name in both dirs")
    h = int(448 * a.scale)
    rows = []
    for n in names:
        tiles = []
        for lab, d in (("port", pd), ("retail", rd)):
            im = Image.open(d / n).convert("RGB")
            im = im.resize((max(1, int(im.width * h / im.height)), h))
            ImageDraw.Draw(im).text((4, 4), f"{lab}: {n[:-4]}", fill=(255, 255, 0))
            tiles.append(im)
        rows.append(tiles)
    w = max(sum(t.width for t in r) + 8 for r in rows)
    m = Image.new("RGB", (w, h * len(rows)), (40, 40, 40))
    for i, r in enumerate(rows):
        x = 0
        for t in r:
            m.paste(t, (x, i * h))
            x += t.width + 8
    out = Path(a.out) if a.out else rd / "pairs.png"
    m.save(out)
    print(out)


def grid(a):
    """--grid DIR: rows x columns of DIR/<row>_<col>-view.png (the picture as presented; the
    native frame <row>_<col>.png when there is no -view), each tile scaled to the same
    height and labelled, missing ones grey (tools/wide/stage2shots.py: states x aspects)."""
    d = Path(a.grid)
    rows, cols = a.rows.split(","), a.grid_cols.split(",")
    h = int(448 * a.scale)
    tiles = {}
    widths = {c: 0 for c in cols}
    for r in rows:
        for c in cols:
            p = d / f"{r}_{c}-view.png"
            if not p.exists():
                p = d / f"{r}_{c}.png"
            if not p.exists():
                continue
            im = Image.open(p).convert("RGB")
            im = im.resize((max(1, int(im.width * h / im.height)), h))
            ImageDraw.Draw(im).text((4, 4), f"{r} {c}", fill=(255, 255, 0))
            tiles[(r, c)] = im
            widths[c] = max(widths[c], im.width)
    for c in cols:
        widths[c] = widths[c] or int(h * 4 / 3)
    W = sum(widths.values()) + 6 * len(cols)
    m = Image.new("RGB", (W, (h + 6) * len(rows)), (40, 40, 40))
    for i, r in enumerate(rows):
        x = 0
        for c in cols:
            if (r, c) in tiles:
                m.paste(tiles[(r, c)], (x, i * (h + 6)))
            x += widths[c] + 6
    out = Path(a.out) if a.out else d / "grid.png"
    m.save(out)
    print(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dir", nargs="?")
    ap.add_argument("--cols", type=int, default=4)
    ap.add_argument("--scale", type=float, default=0.5)
    ap.add_argument("--from", dest="f0", type=int, default=0)
    ap.add_argument("--to", dest="f1", type=int, default=1 << 30)
    ap.add_argument("--out")
    ap.add_argument("--pairs", nargs=2, metavar=("PORT_DIR", "RETAIL_DIR"))
    ap.add_argument("--match")
    ap.add_argument("--grid", metavar="DIR")
    ap.add_argument("--rows", help="--grid: row names")
    ap.add_argument("--grid-cols", "--gcols", dest="grid_cols", help="--grid: column names")
    a, rest = ap.parse_known_args()
    if a.grid:
        if not a.grid_cols and "--cols" in sys.argv:
            a.grid_cols = sys.argv[sys.argv.index("--cols") + 1]
        return grid(a)
    a = ap.parse_args()
    if a.pairs:
        return pairs(a)
    d = Path(a.dir)
    fs = []
    for p in sorted(d.glob("s*.png")):
        m = re.fullmatch(r"s(\d+)\.png", p.name)
        if m and a.f0 <= int(m.group(1)) <= a.f1:
            fs.append((int(m.group(1)), p))
    if not fs:
        raise SystemExit("montage: no shots")
    ims = []
    for f, p in fs:
        im = Image.open(p).convert("RGB")
        im = im.resize((int(im.width * a.scale), int(im.height * a.scale)))
        ImageDraw.Draw(im).text((4, 4), str(f), fill=(255, 255, 0))
        ims.append(im)
    w, h = ims[0].size
    rows = (len(ims) + a.cols - 1) // a.cols
    m = Image.new("RGB", (w * a.cols, h * rows))
    for i, im in enumerate(ims):
        m.paste(im, ((i % a.cols) * w, (i // a.cols) * h))
    out = Path(a.out) if a.out else d / "montage.png"
    m.save(out)
    print(out)


if __name__ == "__main__":
    main()
