#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Widescreen stage 3 screenshots: every menu / tutorial / shop / save / factory / insect
screen the cards reach, at chosen aspects, + the aspect log (docs/WIDESCREEN.md "Stage 3").

    python tools/wide/stage3shots.py --exe EXE --out out/wide3/after [--aspects 4:3,16:9]
                                     [--only menu,item] [--log] [--extra --set k=v ...]

Scenarios (game-save fixtures from out/fixtures/cards, no save state, so any build works):
  menu     save2 + TRIANGLE 3800    field 3790, menu opening 3812, main menu 3910
  save     save2 + CROSS 3800, 4000 transporter menu 3990, save screen 4150
  item     late_game, item_use     main menu 3860, Items 3990, context 4040, target 4110
  shop     zshop2, out/shopcheck   shop 4050, shop closed 4380
  pause    save2 + battle2 + START  tutorial 4640, battle 5000, pause 5240
  battle2  save2 + battle2 script   results 7300, map help 7550, field2 7690 (retimed 10-24)
  factory  factory                 factory menu 4400, blueprints 4700
  insect   insectron               INSMENU 3500, team select 6000, INSECT battle 11500
  (2026-10-24, the stage 3 gaps)
  worldmap save2 + battle2 + SELECT area map (full-screen map) 7712 / 7800, closed 7990
  allies   late_game, row 2        Allies 4150, member commands 4320
  strategy late_game, row 3        Strategy 4150, 4320
  menurows late_game, rows 5/6/8   Battle Recorder 4150, Frog Log 4430, System 4730
  revel    late_game, revelation   Revelation board 4250, stone list 4500, abilities 5050
  btlmenu  save2 + battle2 + TRIANGLE  battle command menu 4950, Items 5100, 5200
  dorg     ch02_dorgenark          bridge 3880, main menu 3990, galaxy map (planet select) 4290..4590
Aspects: 4:3, 16:9, 16:10, 21:9 and 32:9 (= graphics.aspect=auto on a 3840x1080 display).
Look at one screen at every aspect: tools/wide/aspectrow.py OUT STATE[,STATE].
Per run: OUT/<state>_<aspect>.png (+ -view.png as presented), OUT/<run>_<aspect>.log, and
OUT/<run>_<aspect>.aspect.log (RG_ASPECT_LOG: one line per content-shape change, so
"no aspect switch" = one line per run after the title).  Sheet: OUT/sheet.png.  One rg-game
at a time.  Prints the run hash per run (must be equal across aspects).
"""
from __future__ import annotations

import argparse
import os
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
GOLD = PORT / "tools" / "trace" / "goldens"
RUN_FROM = PORT / "tools" / "fixtures" / "run_from.py"
MONTAGE = PORT / "tools" / "fixtures" / "montage.py"
SHOP = PORT / "out" / "shopcheck" / "shop.input.txt"

ASPECTS = {"4:3": "4x3", "16:9": "16x9", "16:10": "16x10", "21:9": "21x9", "32:9": "32x9"}


def aspect_args(asp: str):
    """32:9 is graphics.aspect=auto on a 3840x1080 display (the auto clamp's widest shape)"""
    if asp == "32:9":
        return ["--set", "graphics.aspect=auto", "--set", "display.width=3840",
                "--set", "display.height=1080"]
    return ["--set", f"graphics.aspect={asp}"]


def scenarios(out: Path):
    """(name, card, input script, end field, {state: field})"""
    b2 = (GOLD / "boot_save2.input.txt").read_text()
    bb = (GOLD / "boot_save2_battle2.input.txt").read_text()
    # library-card boot (bootcheck.py pass 1: CONTINUE .. recap) and late_game + main menu
    LGB = ("1900 1905 CROSS\n2150 2155 CROSS\n2350 2355 CROSS\n2450 2455 CROSS\n"
           "2650 2655 CROSS\n3700 3703 CROSS\n")
    LG = LGB + "3790 3793 TRIANGLE  # main menu\n"

    def w(name, text):
        p = out / f"s3_{name}.input.txt"
        p.write_text(text)
        return p
    return [
        ("menu", "save2", w("menu", b2 + "3800 3803 TRIANGLE  # main menu\n"), 3920,
         {"field": 3790, "menuopen": 3812, "menu": 3910}),
        ("save", "save2", w("save", b2 + "3800 3803 CROSS  # transporter\n4000 4003 CROSS  # Save\n"), 4160,
         {"trans": 3990, "save": 4150}),
        ("item", "late_game", GOLD / "item_use.input.txt", 4120,
         {"mainmenu": 3860, "items": 3990, "context": 4040, "target": 4110}),
        ("shop", "zshop2", SHOP, 4390, {"shop": 4050, "shopclosed": 4380}),
        ("pause", "save2", w("pause", bb + "5200 5203 START  # pause menu\n"), 5250,
         {"tutorial": 4640, "battle": 5000, "pause": 5240}),
        ("battle2", "save2", GOLD / "boot_save2_battle2.input.txt", 7700,
         {"results": 7300, "maphelp": 7550, "field2": 7690}),
        ("factory", "factory", GOLD / "boot_factory.input.txt", 4710, {"factory": 4400, "blueprints": 4700}),
        ("insect", "insectron", GOLD / "boot_insectron.input.txt", 11510,
         {"insmenu": 3500, "teamsel": 6000, "insbattle": 11500}),
        # 2026-10-24 (stage 3 gaps): world map, main-menu sub-screens, battle command menu,
        # the Dorgenark
        ("worldmap", "save2", w("worldmap", bb + "7700 7705 SELECT  # full-screen map\n"
                                "7900 7905 SELECT  # close\n"), 8000,
         {"mapopen": 7712, "map": 7800, "mapclosed": 7990}),
        ("allies", "late_game", w("allies", LG + "3960 3963 DOWN\n4010 4015 CROSS  # Allies\n"
                                  "4220 4225 CROSS  # first member\n"), 4330,
         {"allies": 4150, "ally1": 4320}),
        ("strategy", "late_game", w("strategy", LG + "3960 3963 DOWN\n3975 3978 DOWN\n"
                                    "4010 4015 CROSS  # Strategy\n4220 4225 CROSS\n"), 4330,
         {"strategy": 4150, "strat1": 4320}),
        ("menurows", "late_game", w("menurows", LG + "3960 3963 DOWN\n3975 3978 DOWN\n3990 3993 DOWN\n"
                                    "4005 4008 DOWN\n4030 4035 CROSS  # Battle Recorder\n"
                                    "4200 4205 CIRCLE\n4280 4283 DOWN\n4310 4315 CROSS  # Frog Log\n"
                                    "4480 4485 CIRCLE\n4560 4563 DOWN\n4580 4583 DOWN\n"
                                    "4610 4615 CROSS  # System\n"), 4740,
         {"recorder": 4150, "froglog": 4430, "system": 4730}),
        ("revel", "late_game", GOLD / "revelation.input.txt", 5060,
         {"revboard": 4250, "revstones": 4500, "revlearn": 5050}),
        ("btlmenu", "save2", w("btlmenu", bb.split("4940 4942")[0] +
                               "4900 4905 TRIANGLE  # battle command menu\n"
                               "4960 4965 DOWN\n4990 4995 DOWN  # Items\n5030 5035 CROSS\n"), 5210,
         {"btlcmd": 4950, "btlitems": 5100, "btlitems2": 5200}),
        ("dorg", "ch02_dorgenark", w("dorg", LGB + "3800 3803 CROSS  # recap\n"
                                     "3890 3893 TRIANGLE  # main menu\n4000 4005 CIRCLE\n"
                                     "#!stick 1 0\n#!stick 4100 4160 128 0  # toward the helm\n"
                                     "4200 4205 CROSS\n4300 4305 CROSS\n4450 4455 DOWN\n"), 4600,
         {"dorgfield": 3880, "dorgmenu": 3990, "dorgtalk1": 4290, "dorgtalk2": 4390,
          "dorgtalk3": 4590}),
    ]


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--exe", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--aspects", default="4:3,16:9")
    ap.add_argument("--only", help="comma list of run names")
    ap.add_argument("--log", action="store_true", help="RG_LAYOUT_LOG per run")
    ap.add_argument("--extra", nargs=argparse.REMAINDER, default=[], help="more rg-game args")
    a = ap.parse_args(argv)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    aspects = a.aspects.split(",")
    states = []
    for name, card, script, end, shots in scenarios(out):
        if a.only and name not in a.only.split(","):
            continue
        states += list(shots)
        for asp in aspects:
            tag = ASPECTS.get(asp, asp.replace(":", "x"))
            cmd = [sys.executable, str(RUN_FROM), "--boot-save", card, "--input", str(script),
                   "--exe", str(Path(a.exe).resolve()), "--fields", str(end), "--"] +                 aspect_args(asp) + a.extra
            for st, f in shots.items():
                cmd += ["--shot", f"{f}:{out / f'{st}_{tag}.png'}"]
            env = dict(os.environ, RG_ASPECT_LOG=str(out / f"{name}_{tag}.aspect.log"))
            if a.log:
                env["RG_LAYOUT_LOG"] = str(out / f"{name}_{tag}.layout.log")
            p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env)
            (out / f"{name}_{tag}.log").write_text(p.stdout + p.stderr, encoding="utf-8")
            hashes = [ln for ln in (p.stdout + p.stderr).splitlines() if "run_hash=" in ln]
            alog = out / f"{name}_{tag}.aspect.log"
            nsw = len(alog.read_text().splitlines()) if alog.exists() else -1
            print(f"  {name:8s} {asp:6s} exit {p.returncode} aspect-changes {nsw} "
                  f"{hashes[-1].strip() if hashes else ''}", flush=True)
    cols = ",".join(ASPECTS.get(x, x.replace(":", "x")) for x in aspects)
    subprocess.run([sys.executable, str(MONTAGE), "--grid", str(out), "--rows", ",".join(states),
                    "--grid-cols", cols, "--out", str(out / "sheet.png")])
    print(f"stage3shots: sheet {out / 'sheet.png'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
