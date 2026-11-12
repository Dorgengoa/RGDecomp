#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Widescreen stage 2 screenshots: the milestone screens at every aspect, one contact sheet
(docs/WIDESCREEN.md "Stage 2").

    python tools/wide/stage2shots.py --exe EXE --out out/play2/wide/s2 [--aspects 4:3,16:9,16:10,21:9]
                                     [--only field,menu] [--extra --set k=v ...]

Scenarios (game-save fixtures, no save state, so any build works; scripts written to OUT):
  save2 boot (CONTINUE)      title 1950 (title menu), field 3790 (field HUD + prompt + minimap
                             + compass), menu 3910 (TRIANGLE: main menu, pillarboxed)
  save2 + CROSS 3800         trans 3990 (transporter menu)
  save2_battle2 + START      tutorial 4640 ("The Lock-On Function" help window), battle 5000
                             (battle HUD), pause 5240 (START: pause menu)
  save2_battle2              results 6320 (battle results), maphelp 6720 ("The Map
                             Display" help), field2 6820
Shots: OUT/<state>_<aspect>-view.png (as presented) + the native frame; the sheet
OUT/sheet.png (rows = states, columns = aspects; tools/fixtures/montage.py --grid).
RG_LAYOUT_LOG per run when --log.  One rg-game at a time.
"""
from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
GOLD = PORT / "tools" / "trace" / "goldens"
RUN_FROM = PORT / "tools" / "fixtures" / "run_from.py"
MONTAGE = PORT / "tools" / "fixtures" / "montage.py"

ASPECTS = {"4:3": "4x3", "16:9": "16x9", "16:10": "16x10", "21:9": "21x9"}


def scripts(out: Path) -> list[tuple[str, Path, int, dict]]:
    """(name, input script, end field, {state: field})"""
    b2 = (GOLD / "boot_save2.input.txt").read_text()
    bb = (GOLD / "boot_save2_battle2.input.txt").read_text()
    s_menu = out / "s2_menu.input.txt"
    s_menu.write_text(b2 + "3800 3803 TRIANGLE  # main menu\n")
    s_trans = out / "s2_trans.input.txt"
    s_trans.write_text(b2 + "3800 3803 CROSS  # Use transporter\n")
    s_pause = out / "s2_pause.input.txt"
    s_pause.write_text(bb + "5200 5203 START  # pause menu\n")
    return [
        ("menu", s_menu, 3920, {"title": 1950, "field": 3790, "menu": 3910}),
        ("trans", s_trans, 4000, {"trans": 3990}),
        ("pause", s_pause, 5250, {"tutorial": 4640, "battle": 5000, "pause": 5240}),
        ("battle2", GOLD / "boot_save2_battle2.input.txt", 6830, {"results": 6320, "maphelp": 6720,
                                                                   "field2": 6820}),
    ]


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--exe", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--aspects", default="4:3,16:9,16:10,21:9")
    ap.add_argument("--only", help="comma list of run names (menu,trans,pause,battle2)")
    ap.add_argument("--log", action="store_true", help="RG_LAYOUT_LOG per run")
    ap.add_argument("--extra", nargs=argparse.REMAINDER, default=[], help="more rg-game args")
    a = ap.parse_args(argv)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    aspects = a.aspects.split(",")
    states = []
    for name, script, end, shots in scripts(out):
        states += list(shots)
        if a.only and name not in a.only.split(","):
            continue
        card = "save2"
        for asp in aspects:
            tag = ASPECTS.get(asp, asp.replace(":", "x"))
            cmd = [sys.executable, str(RUN_FROM), "--boot-save", card, "--input", str(script),
                   "--exe", str(Path(a.exe).resolve()), "--fields", str(end), "--",
                   "--set", f"graphics.aspect={asp}"] + a.extra
            for st, f in shots.items():
                cmd += ["--shot", f"{f}:{out / f'{st}_{tag}.png'}"]
            env = None
            if a.log:
                import os
                env = dict(os.environ, RG_LAYOUT_LOG=str(out / f"{name}_{tag}.layout.log"))
            p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env)
            (out / f"{name}_{tag}.log").write_text(p.stdout + p.stderr, encoding="utf-8")
            hashes = [ln for ln in (p.stdout + p.stderr).splitlines() if "run_hash=" in ln]
            print(f"  {name:8s} {asp:6s} exit {p.returncode} {hashes[-1].strip() if hashes else ''}", flush=True)
    cols = ",".join(ASPECTS.get(x, x.replace(":", "x")) for x in aspects)
    subprocess.run([sys.executable, str(MONTAGE), "--grid", str(out), "--rows", ",".join(states),
                    "--grid-cols", cols, "--out", str(out / "sheet.png")])
    print(f"stage2shots: sheet {out / 'sheet.png'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
