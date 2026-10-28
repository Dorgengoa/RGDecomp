#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""One image per screen state of a stage3shots.py dir, every aspect side by side AS PRESENTED
(the -view.png, at its own shape, same height), labelled: the quick look at one screen.

    python tools/wide/aspectrow.py DIR STATE[,STATE...] [--aspects 4x3,21x9] [--h 300]
                                   [--out FILE]
Writes DIR/row_<state>.png per state (or one stacked FILE with --out).
"""
import argparse
from pathlib import Path

from PIL import Image, ImageDraw


def row(d: Path, st: str, aspects, h: int):
    ims = []
    for a in aspects:
        p = d / f"{st}_{a}-view.png"
        if not p.exists():
            p = d / f"{st}_{a}.png"
        if not p.exists():
            continue
        im = Image.open(p).convert("RGB")
        im = im.resize((max(1, round(im.width * h / im.height)), h), Image.BILINEAR)
        ImageDraw.Draw(im).text((4, 2), f"{st} {a}", fill="yellow")
        ims.append(im)
    if not ims:
        return None
    out = Image.new("RGB", (sum(i.width for i in ims) + 4 * (len(ims) - 1), h), "gray")
    x = 0
    for i in ims:
        out.paste(i, (x, 0))
        x += i.width + 4
    return out


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("dir")
    ap.add_argument("states")
    ap.add_argument("--aspects", default="4x3,21x9")
    ap.add_argument("--h", type=int, default=300)
    ap.add_argument("--out")
    a = ap.parse_args(argv)
    d = Path(a.dir)
    rows = [(s, row(d, s, a.aspects.split(","), a.h)) for s in a.states.split(",")]
    rows = [(s, r) for s, r in rows if r is not None]
    if a.out:
        w = max(r.width for _, r in rows)
        sheet = Image.new("RGB", (w, sum(r.height + 4 for _, r in rows)), "black")
        y = 0
        for _, r in rows:
            sheet.paste(r, (0, y))
            y += r.height + 4
        sheet.save(a.out)
        print(a.out)
    else:
        for s, r in rows:
            r.save(d / f"row_{s}.png")
            print(d / f"row_{s}.png")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
