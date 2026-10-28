#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""cardrepro.py: run a play-test repro (power-on on a library card + an input script).

    python tools/bringup/cardrepro.py --exe build/play-i686/rg-game.exe --card late_game \\
        --input tools/trace/goldens/item_use.input.txt --fields 4320 --out out/rep \\
        --shot 4100 --shot 4300

Copies out/fixtures/cards/<card> to <out>/saves (fresh each run), runs rg-game headless
with fxlib.game_env (RG_DATA, RG_GPU=hw), writes <out>/s<field>.png per --shot and
<out>/run.log, prints the exit code and any EXCEPTION / fault lines.  The item 6/7 repros
in BRINGUP.md (2026-10-23) were run this way.
"""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fxlib  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--exe", required=True)
    ap.add_argument("--card", default="late_game")
    ap.add_argument("--input", required=True)
    ap.add_argument("--fields", type=int, required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--shot", type=int, action="append", default=[])
    a = ap.parse_args()
    out = Path(a.out).resolve()
    saves = out / "saves"
    if saves.exists():
        shutil.rmtree(saves)
    out.mkdir(parents=True, exist_ok=True)
    shutil.copytree(PORT / "out" / "fixtures" / "cards" / a.card, saves)
    cmd = [str(Path(a.exe).resolve()), "--headless", "--fields", str(a.fields),
           "--saves", str(saves), "--input", str(Path(a.input).resolve())]
    for f in a.shot:
        cmd += ["--shot", f"{f}:{out / f's{f}.png'}"]
    with open(out / "run.log", "w", encoding="utf-8", errors="replace") as log:
        rc = subprocess.run(cmd, cwd=PORT, env=fxlib.game_env(), stdout=log,
                            stderr=subprocess.STDOUT).returncode
    bad = [l.rstrip() for l in open(out / "run.log", encoding="utf-8", errors="replace")
           if any(k in l for k in ("EXCEPTION", "fault", "FAULT", "panic"))]
    print(f"cardrepro: rc={rc} fields={a.fields} log={out / 'run.log'}")
    for l in bad[:10]:
        print("  " + l)
    for f in a.shot:
        p = out / f"s{f}.png"
        print(f"  shot {f}: {'ok' if p.exists() else 'MISSING'} {p}")
    return rc


if __name__ == "__main__":
    sys.exit(main())
