#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Regression for the 1025b shop-close crash (docs/bringup/BRINGUP-HISTORY.md "shop-close
crash"): boot card zuser1025 (the user's play-test card, Salgin "Near the Item Shop"), walk
into the item shop, talk to Shihawa, Buy -> Grand Edge -> x1 -> Yes, close the shop with
CIRCLE, then run on in the field to 5,100.  1025b died at the second CIRCLE (field ~4,750)
with 0xC0000005 in nr_const_apply: the light packet the field's draw requests name (the light
record's "emitted" pointer, set at frame ~2,488 before the shop) was walked after the shop
menu had reused that memory (docs/NATIVE-RENDER.md "Constants from the game").

    python tools/fixtures/shopcrash.py --exe EXE [--api d3d11|vulkan] [--out DIR] [--fields N]
                                       [--stale] [--skip-missing]

PASS = exit 0, no exception, the shop menu seen (mode 12/1) and the game back in the field
(mode 6/100) after the close.  Shots of the buy list, the bought item (money 863 -> 543) and
the field after the close go to DIR.  --stale adds RG_NR_STALE=1 (counts and prints the
uses of remembered packets whose game memory changed; the fixed exe applies its copies).
--skip-missing: exit 77 without the card / data (ctest fixtures.shopcrash).
Input: tools/trace/goldens/shopcrash_buyclose.input.txt (made with cardwhere.py + shots).
~15 s per run.  Exit 0 PASS, 1 FAIL.  The card is a copy of the user's card
(out/fixtures/cards/zuser1025; the original in out/playtest/saves is never touched).
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INPUT = ROOT / "tools/trace/goldens/shopcrash_buyclose.input.txt"
CARD = "zuser1025"
CLOSE_FIELD = 4830   # last CIRCLE of the script


def run(exe: Path, api: str, out: Path, fields: int, stale: bool) -> tuple[bool, str]:
    out.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, RG_GPU=os.environ.get("RG_GPU", "hw"), RG_STATUS_EVERY="10", RG_GPU_API=api)
    if stale:
        env["RG_NR_STALE"] = "1"
    log = out / f"shopcrash_{api}.log"
    cmd = [sys.executable, str(ROOT / "tools/fixtures/run_from.py"), "--boot-save", CARD, "--exe", str(exe),
           "--input", str(INPUT), "--fields", str(fields), "--",
           "--shot", f"4300:{out / f'{api}_buylist.png'}", "--shot", f"4620:{out / f'{api}_bought.png'}",
           "--shot", f"{fields - 10}:{out / f'{api}_after.png'}"]
    p = subprocess.run(cmd, env=env, capture_output=True, text=True, errors="replace", cwd=ROOT)
    txt = p.stdout + p.stderr
    log.write_text(txt, encoding="utf-8")
    modes = [(int(f), m) for f, m in re.findall(r"STATUS field=(\d+) .*?gamemode=(\S+)", txt)]
    exc = re.search(r"rg-game: EXCEPTION .*", txt)
    shop = any(m == "12/1" for f, m in modes if 4250 <= f <= 4700)
    back = any(m == "6/100" for f, m in modes if f > CLOSE_FIELD)
    stale = re.search(r"native render constants notes: .*", txt)
    ok = p.returncode == 0 and not exc and shop and back
    why = (f"rc {p.returncode}, shop menu {'seen' if shop else 'NOT seen'}, field after close "
           f"{'yes' if back else 'NO'}, last field {modes[-1][0] if modes else '-'}"
           + (f"; {exc.group(0)}" if exc else "") + (f"; {stale.group(0)}" if stale else ""))
    return ok, why


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--api", default="d3d11,vulkan", help="comma list (default both)")
    ap.add_argument("--out", default="out/shopcrash/check")
    ap.add_argument("--fields", type=int, default=5100)
    ap.add_argument("--stale", action="store_true")
    ap.add_argument("--skip-missing", action="store_true",
                    help="exit 77 (ctest skip) when the card or the game data is missing")
    a = ap.parse_args(argv)
    if a.skip_missing:
        data = Path(os.environ.get("RG_DATA", ROOT / "data"))
        card = ROOT / "out/fixtures/cards" / CARD / "card1"
        if not card.is_dir() or not data.is_dir():
            print(f"shopcrash: SKIP (card {card} or data {data} missing)")
            return 77
    bad = 0
    for api in a.api.split(","):
        ok, why = run(Path(a.exe).resolve(), api, Path(a.out).resolve(), a.fields, a.stale)
        print(f"shopcrash {api}: {'PASS' if ok else 'FAIL'} ({why})", flush=True)
        bad += not ok
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
