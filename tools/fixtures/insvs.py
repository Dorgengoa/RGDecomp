#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Insectron versus (title INSECTRON -> INSMENU) probe driver (lane insvs 2026-11-12;
docs/INSECTRON-VERSUS.md).

    python tools/fixtures/insvs.py cards [--out DIR]
    python tools/fixtures/insvs.py run SCRIPT --out DIR [--exe EXE] [--saves DIR] [--fields N]
                                   [--shots A-B/STEP,F,..] [--env K=V ..] [--load-state S]
                                   [-- extra rg-game args, e.g. --save-state F:FILE (needs --env RG_SS=1)]
    python tools/fixtures/insvs.py text

cards: a two-card saves dir (default out/insvs/saves_base):
  card1 = cards/insect_final_s6_s (15 strong caged insects, Insectron rank var 5 = 6, so the
          title shows INSECTRON) + two registered teams ALPHA / BRAVO (--insect-formation);
  card2 = cards/insect_final (15 caged insects, var 5 set to 3) = "player 2's memory card".
run: one headless power-on run of rg-game with a COPY of the saves dir (the original is never
  written), the input SCRIPT (rg-game --input format: "FIRST LAST KEYS # comment"), shots at
  the listed fields (DIR/sNNNNN.png) and a contact sheet DIR/montage.png (montage.py).
  RG_STATUS_EVERY=100 goes to DIR/run.log.
text: print the INSMENU message tables from the disc (event/ev_ins_vs_en.txt and the
  cmd_*.txt members of menu/rc/insect_vs_rc_en.pac), via gamedata.py.
"""
from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402
import gamedata  # noqa: E402

PORT = fxlib.PORT
OUT = PORT / "out" / "insvs"


def cards(out: Path) -> Path:
    src1 = fxlib.CARDS / "insect_final_s6_s"
    src2 = fxlib.CARDS / "insect_final"
    for s in (src1, src2):
        if not s.is_dir():
            subprocess.run([sys.executable, str(HERE / "saveedit.py"), "make", s.name], check=True)
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    shutil.copytree(src1 / "card1", out / "card1")
    shutil.copy2(src1 / "card1.card", out / "card1.card")
    shutil.copytree(src2 / "card1", out / "card2")
    shutil.copy2(src2 / "card1.card", out / "card2.card")
    se = [sys.executable, str(HERE / "saveedit.py"), "patch"]
    subprocess.run(se + [str(out / "card1"), "--insect-formation", "--insect-team", "0:ALPHA:0,1,2,3,4",
                         "--insect-team", "1:BRAVO:5,6,7,8,9"], check=True)
    subprocess.run(se + [str(out / "card2"), "--var", "5=3"], check=True)
    return out


def shot_fields(spec: str) -> list[int]:
    fs: list[int] = []
    for part in filter(None, spec.split(",")):
        if "-" in part:
            rng, _, step = part.partition("/")
            a, b = (int(x) for x in rng.split("-"))
            fs += list(range(a, b + 1, int(step or 100)))
        else:
            fs.append(int(part))
    return sorted(set(fs))


def run(a) -> int:
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    base = Path(a.saves) if a.saves else OUT / "saves_base"
    if not base.is_dir():
        cards(base)
    saves = out / "saves"
    shutil.rmtree(saves, ignore_errors=True)
    shutil.copytree(base, saves)
    fs = shot_fields(a.shots) if a.shots else []
    end = a.fields or ((max(fs) + 2) if fs else 4000)
    exe = Path(a.exe) if a.exe else OUT / "exe" / "rg-game.exe"
    for old in out.glob("s*.png"):
        old.unlink()
    cmd = [str(exe), "--headless", "--fields", str(end), "--saves", str(saves), "--input", str(Path(a.script).resolve())]
    if a.load_state:
        cmd += ["--load-state", str(Path(a.load_state).resolve())]
    for f in fs:
        cmd += ["--shot", f"{f}:{out / f's{f:05d}.png'}"]
    cmd += a.extra
    env = fxlib.game_env({"RG_STATUS_EVERY": "100", **({"RG_SS": "1"} if a.load_state else {})})
    for kv in a.env:
        k, _, v = kv.partition("=")
        env[k] = v
    with open(out / "run.log", "w", encoding="utf-8", errors="replace") as log:
        rc = subprocess.call(cmd, env=env, stdout=log, stderr=subprocess.STDOUT)
    print(f"insvs: exit {rc}, {len(fs)} shots, log {out / 'run.log'}")
    if fs:
        subprocess.call([sys.executable, str(HERE / "montage.py"), str(out), "--cols", str(a.cols),
                         "--scale", str(a.scale)])
    return rc


def text() -> int:
    ar = gamedata.Archive()
    print(gamedata.text(ar.get("event/ev_ins_vs_en.txt")))
    b = ar.get("menu/rc/insect_vs_rc_en.pac")
    for nm, off, size in gamedata.pac_members(b):
        if nm.lower().endswith(".txt"):
            print(f"==== {nm}")
            print(gamedata.text(b[off:off + size]))
    return 0


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    c = sp.add_parser("cards"); c.add_argument("--out", default=str(OUT / "saves_base"))
    r = sp.add_parser("run")
    r.add_argument("script"); r.add_argument("--out", required=True); r.add_argument("--exe")
    r.add_argument("--saves"); r.add_argument("--fields", type=int, default=0)
    r.add_argument("--shots", default=""); r.add_argument("--env", action="append", default=[])
    r.add_argument("--cols", type=int, default=6); r.add_argument("--scale", type=float, default=0.4)
    r.add_argument("--load-state", help="start from a save state of the same exe (RG_SS=1 is set)")
    sp.add_parser("text")
    argv = list(sys.argv[1:] if argv is None else argv)
    extra = argv[argv.index("--") + 1:] if "--" in argv else []
    a = ap.parse_args(argv[:argv.index("--")] if "--" in argv else argv)
    a.extra = extra
    if a.cmd == "cards":
        print(cards(Path(a.out)))
        return 0
    if a.cmd == "text":
        return text()
    return run(a)


if __name__ == "__main__":
    sys.exit(main())
