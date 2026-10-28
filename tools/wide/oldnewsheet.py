#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Old-exe vs new-exe widescreen shots (two stage3shots.py dirs), as presented (-view.png):
one contact sheet per aspect (rows = screen states, OLD left | NEW right) plus a table of
per-shot numbers, so a renderer / layout change can be judged at a glance.

    python tools/wide/oldnewsheet.py OLD_DIR NEW_DIR OUT_DIR [--aspects 16x9,21x9,32x9]
                                     [--h 224] [--states a,b,...]
Writes OUT_DIR/sheet_<aspect>[_N].png (at most 12 rows each) and OUT_DIR/edges.tsv:
state, aspect, diff% (pixels differing by > 24 levels, whole frame), and for the side
regions outside the centred 4:3 (the edge strips) the near-black share (max channel < 12)
in OLD and NEW: "black parts" left by an old device show as old_black >> new_black.
"""
import argparse
from pathlib import Path

from PIL import Image, ImageChops, ImageDraw


def view(d: Path, st: str, a: str):
    p = d / f"{st}_{a}-view.png"
    return Image.open(p).convert("RGB") if p.exists() else None


def side_black(im: Image.Image) -> float:
    w, h = im.size
    cw = round(h * 4 / 3)
    if cw >= w - 4:
        return 0.0
    x0 = (w - cw) // 2
    tot = blk = 0
    g = im.convert("RGB")
    for box in ((0, 0, x0, h), (x0 + cw, 0, w, h)):
        reg = g.crop(box)
        px = reg.getdata()
        tot += len(px)
        blk += sum(1 for p in px if max(p) < 12)
    return 100.0 * blk / max(1, tot)


def diffpct(a: Image.Image, b: Image.Image) -> float:
    if a.size != b.size:
        b = b.resize(a.size)
    d = ImageChops.difference(a, b).convert("L").point(lambda v: 255 if v > 24 else 0)
    return 100.0 * sum(1 for v in d.getdata() if v) / (a.width * a.height)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("old")
    ap.add_argument("new")
    ap.add_argument("out")
    ap.add_argument("--aspects", default="16x9,21x9,32x9")
    ap.add_argument("--h", type=int, default=224)
    ap.add_argument("--states")
    a = ap.parse_args()
    old, new, out = Path(a.old), Path(a.new), Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    rows = ["state\taspect\tdiff_pct\told_side_black_pct\tnew_side_black_pct"]
    for asp in a.aspects.split(","):
        if a.states:
            states = a.states.split(",")
        else:
            states = sorted({p.name[: -len(f"_{asp}-view.png")]
                             for p in new.glob(f"*_{asp}-view.png")})
        tiles = []
        for st in states:
            o, n = view(old, st, asp), view(new, st, asp)
            if n is None:
                continue
            dp = diffpct(o, n) if o is not None else -1
            ob = side_black(o) if o is not None else -1
            nb = side_black(n)
            rows.append(f"{st}\t{asp}\t{dp:.2f}\t{ob:.1f}\t{nb:.1f}")
            tiles.append((st, o, n, dp, ob, nb))
        for k in range(0, len(tiles), 12):
            chunk = tiles[k:k + 12]
            w1 = max(round(t[2].width * a.h / t[2].height) for t in chunk)
            sheet = Image.new("RGB", (2 * w1 + 8, len(chunk) * (a.h + 4)), "gray")
            dr = ImageDraw.Draw(sheet)
            for r, (st, o, n, dp, ob, nb) in enumerate(chunk):
                y = r * (a.h + 4)
                for c, im in enumerate((o, n)):
                    if im is None:
                        continue
                    im = im.resize((round(im.width * a.h / im.height), a.h), Image.BILINEAR)
                    sheet.paste(im, (c * (w1 + 8), y))
                dr.text((4, y + 2), f"OLD {st} {asp} sideblack {ob:.0f}%", fill="yellow")
                dr.text((w1 + 12, y + 2), f"NEW {st} {asp} sideblack {nb:.0f}% diff {dp:.1f}%",
                        fill="yellow")
            name = f"sheet_{asp}" + (f"_{k // 12 + 1}" if len(tiles) > 12 else "") + ".png"
            sheet.save(out / name)
            print(out / name)
    (out / "edges.tsv").write_text("\n".join(rows) + "\n")
    print(out / "edges.tsv")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
