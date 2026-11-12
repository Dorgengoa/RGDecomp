#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Is the map drawn?  Automatic detector for the "missing map geometry" class of regression
(docs/BRINGUP.md 2026-10-18 (f)/(g), docs/TEST-FIXTURES.md "Map check").

    python tools/fixtures/mapcheck.py [CARD ...] --exe EXE [--out DIR] [--ref-dir D]
                                      [--env K=V ...] [--min-ratio 0.6] [--tsv F]

For each library card (default: the four cards that lost their map, ch06_vedan,
ch09_labyrinth, ch12_mariglenn, ch13_mariglenn, plus control ch08c_zerard): one power-on run
with bootcheck's pass-1 script (CONTINUE -> load -> recap presses) to field 4,700 with
RG_STATUS_EVERY=10 and a screenshot every 50 fields from 3,700.  The shot taken >= 40 fields
after field control starts (first ovl=3 gamemode=6/100) is scored by its DETAIL fraction: the
share of 8x8 blocks (at 640 wide) whose luminance standard deviation is > 1.5 (flat sky, black void and the
fog-free clear colour score ~0; map geometry is textured).  The verdict compares it with the
reference shot of the same card (default out/retail/cb1/<card>_control.png, the retail
CONTINUE shots of tools/trace/cardboot.py): ratio >= --min-ratio = DRAWN, else MISSING.
`--battle` adds a second run (bootcheck's box walk from control) scored 250 fields after the
first random encounter.  Calibrated on the 15:03 exe / exe3 / retail shots: missing map = ratio 0.18-0.48, drawn = 0.95-1.1.  One rg-game at a time; ~30 s per
card.  Exit 1 if any card is MISSING.  `--score PNG [PNG...]` just prints scores.
"""
from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import bootcheck  # noqa: E402
import fxlib  # noqa: E402

PORT = HERE.parents[1]
DEFAULT = ["ch06_vedan", "ch09_labyrinth", "ch12_mariglenn", "ch13_mariglenn", "ch08c_zerard"]


def detail(png: Path) -> float:
    import numpy as np
    from PIL import Image
    im = Image.open(png).convert("L")
    if im.width > 640:      # retail shots are 640 wide; normalise the port's to the same scale
        im = im.resize((640, int(im.height * 640 / im.width)))
    a = np.asarray(im, dtype=np.float32)
    h, w = (a.shape[0] // 8) * 8, (a.shape[1] // 8) * 8
    b = a[:h, :w].reshape(h // 8, 8, w // 8, 8).std(axis=(1, 3))
    return float((b > 1.5).mean())


def check(card, exe, out, ref_dir, env, min_ratio, battle=False):
    out.mkdir(parents=True, exist_ok=True)
    fields = list(range(3700, 4701, 50))
    extra = []
    for f in fields:
        extra += ["--shot", f"{f}:{out / f'{card}_{f}.png'}"]
    t0 = time.time()
    rc, log, st = bootcheck.run_status(card, bootcheck.lib_script(None), exe, 4710, 10, extra,
                                       env, card + "_mapcheck", out / "logs")
    ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v == (3, "6/100")), None)
    crash = fxlib.crash_report(log, exe)
    if ctl is None:
        return dict(card=card, verdict="NOCTL", score=0, ref=0, ratio=0, shot="", ctl=None,
                    crash=crash, secs=time.time() - t0)
    f = next((f for f in fields if f >= ctl + 40), fields[-1])
    shot = out / f"{card}_{f}.png"
    s = detail(shot) if shot.exists() else 0.0
    ref = ref_dir / f"{card}_control.png"
    r = detail(ref) if ref.exists() else None
    ratio = s / r if r else None
    verdict = "?" if ratio is None else ("DRAWN" if ratio >= min_ratio else "MISSING")
    res = dict(card=card, verdict=verdict, score=s, ref=r or 0, ratio=ratio or 0, shot=str(shot),
               ctl=ctl, crash=crash, secs=time.time() - t0)
    if battle:
        res["battle"] = check_battle(card, exe, out, env, ctl, r, min_ratio)
    return res


def check_battle(card, exe, out, env, ctl, ref, min_ratio):
    """bootcheck's pass-2 script (menu, walk, box walk) from control; the shot 250 fields
    after the first battle mode (7/*) is scored like the field one (same reference)."""
    fields = list(range(ctl + 700, ctl + 3501, 100))     # rg-game takes at most 32 --shot
    extra = []
    for f in fields:
        extra += ["--shot", f"{f}:{out / f'{card}_b{f}.png'}"]
    rc, log, st = bootcheck.run_status(card, bootcheck.lib_script(ctl), exe, ctl + 3520, 10, extra,
                                       env, card + "_mapcheck_battle", out / "logs")
    enc = next((k for k, v in sorted(st.items()) if k >= ctl + 700 and v[1].startswith("7/")), None)
    if enc is None:
        return dict(verdict="NOBATTLE", score=0, ratio=0, shot="", field=None)
    f = next((f for f in fields if f >= enc + 250), fields[-1])
    shot = out / f"{card}_b{f}.png"
    s = detail(shot) if shot.exists() else 0.0
    ratio = s / ref if ref else None
    return dict(verdict="?" if ratio is None else ("DRAWN" if ratio >= min_ratio else "MISSING"),
                score=s, ratio=ratio or 0, shot=str(shot), field=enc)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("cards", nargs="*")
    ap.add_argument("--exe")
    ap.add_argument("--out", default=str(PORT / "out" / "mapcheck"))
    ap.add_argument("--ref-dir", default=str(PORT / "out" / "retail" / "cb1"))
    ap.add_argument("--env", action="append", default=[], help="K=V for the game process")
    ap.add_argument("--min-ratio", type=float, default=0.6)
    ap.add_argument("--tsv")
    ap.add_argument("--battle", action="store_true",
                    help="also a battle: bootcheck's box walk from control, scored 250 fields "
                         "after the first random encounter (cards that meet one)")
    ap.add_argument("--score", nargs="+", help="only print the detail score of these PNGs")
    a = ap.parse_args(argv)
    if a.score:
        for p in a.score:
            print(f"{detail(Path(p)):.3f}  {p}")
        return 0
    if not a.exe:
        ap.error("--exe required")
    env = dict(kv.split("=", 1) for kv in a.env)
    exe, out, ref_dir = Path(a.exe).resolve(), Path(a.out), Path(a.ref_dir)
    bad = 0
    for c in a.cards or DEFAULT:
        r = check(c, exe, out, ref_dir, env, a.min_ratio, a.battle)
        bad += r["verdict"] != "DRAWN"
        line = (f"{c:16s} {r['verdict']:8s} detail {r['score']:.3f} ref {r['ref']:.3f} "
                f"ratio {r['ratio']:.2f} ctl {r['ctl']} ({r['secs']:.0f} s) {Path(r['shot']).name}")
        print(line, flush=True)
        if "battle" in r:
            b = r["battle"]
            bad += b["verdict"] not in ("DRAWN", "NOBATTLE")
            print(f"{'':16s} battle {b['verdict']:8s} detail {b['score']:.3f} ratio {b['ratio']:.2f} "
                  f"encounter at {b['field']} {Path(b['shot']).name if b['shot'] else ''}", flush=True)
        for x in r["crash"]:
            print("    " + x)
        if a.tsv:
            with open(a.tsv, "a", encoding="utf-8") as fh:
                fh.write("\t".join(str(v) for v in (exe, " ".join(a.env), c, r["verdict"],
                                                     f"{r['score']:.3f}", f"{r['ratio']:.2f}")) + "\n")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
