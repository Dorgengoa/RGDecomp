#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Compare two stage3shots.py / stage2shots.py output dirs made by two exes (docs/WIDESCREEN.md
"Stage 3"): the run hash of every <run>_<aspect>.log and the pixels of every shot PNG.
"Original / 4:3 unchanged" = every line SAME.

    python tools/wide/idcheck.py DIR_A DIR_B
Exit 0 when everything matches.
"""
import hashlib
import re
import sys
from pathlib import Path


def run_hash(p: Path):
    m = re.findall(r"run_hash=([0-9a-f]+)", p.read_text(errors="replace"))
    return m[-1] if m else None


def pix(p: Path):
    try:
        from PIL import Image
        im = Image.open(p)
        return hashlib.sha256(im.convert("RGBA").tobytes()).hexdigest()
    except ImportError:
        return hashlib.sha256(p.read_bytes()).hexdigest()


def main(argv=None) -> int:
    a, b = (Path(x) for x in (argv or sys.argv[1:])[:2])
    bad = 0
    for pa in sorted(a.glob("*.log")):
        if pa.name.endswith((".layout.log", ".aspect.log")):
            continue
        pb = b / pa.name
        if not pb.exists():
            continue
        ha, hb = run_hash(pa), run_hash(pb)
        ok = ha is not None and ha == hb
        bad += not ok
        print(f"{'SAME' if ok else 'DIFF'} run_hash {pa.stem}: {ha} {hb}")
    n = 0
    for pa in sorted(a.glob("*.png")):
        pb = b / pa.name
        if not pb.exists() or pa.name.startswith("sheet"):
            continue
        n += 1
        if pix(pa) != pix(pb):
            bad += 1
            print(f"DIFF pixels {pa.name}")
    print(f"idcheck: {n} shots compared, {bad} differences")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
