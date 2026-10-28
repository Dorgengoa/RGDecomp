#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Find an interaction (shop, NPC, transporter) next to a card's spawn: for each of 8
stick directions x walk lengths, boot the card, walk, press CROSS a few times and report
the game modes seen after the walk (docs/TEST-FIXTURES.md "Card library").

    python tools/fixtures/talksweep.py CARD --exe EXE --control C [--walks 10,25,45]
                                       [--out out/talksweep] [--boot-input FILE]

CARD is a fixture under out/fixtures/cards/ (e.g. one made with saveedit.py patch
--spawn-jump N).  C = field where control starts (bootcheck.py prints it).  The boot
part of the input is the card library's (CONTINUE .. recap CROSS at 3700) unless
--boot-input gives another.  Each trial writes <out>/<dir>_<walk>.input.txt + .log;
a trial whose modes leave 6/* is the hit to reuse.  ~11 s per trial (RG_GPU=hw).
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BOOT = """1900 1905 CROSS
2150 2155 CROSS
2350 2355 CROSS
2450 2455 CROSS
2650 2655 CROSS
3700 3703 CROSS
"""
DIRS = {"N": (128, 0), "NE": (255, 0), "E": (255, 128), "SE": (255, 255),
        "S": (128, 255), "SW": (0, 255), "W": (0, 128), "NW": (0, 0)}


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("card")
    ap.add_argument("--exe", required=True)
    ap.add_argument("--control", type=int, required=True)
    ap.add_argument("--walks", default="10,25,45")
    ap.add_argument("--dirs", default=",".join(DIRS))
    ap.add_argument("--out", default="out/talksweep")
    ap.add_argument("--boot-input")
    a = ap.parse_args(argv)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    boot = Path(a.boot_input).read_text() if a.boot_input else BOOT
    env = dict(os.environ, RG_GPU=os.environ.get("RG_GPU", "hw"), RG_STATUS_EVERY="10")
    for d in a.dirs.split(","):
        lx, ly = DIRS[d]
        for w in (int(x) for x in a.walks.split(",")):
            s0 = a.control + 20
            s1 = s0 + w
            c = s1 + 15
            txt = boot + f"#!stick 1 0\n#!stick {s0} {s1} {lx} {ly}\n"
            for k in range(4):
                txt += f"{c + 40 * k} {c + 40 * k + 3} CROSS\n"
            inp = out / f"{d}_{w}.input.txt"
            inp.write_text(txt)
            log = out / f"{d}_{w}.log"
            end = c + 200
            with open(log, "w") as f:
                subprocess.run([sys.executable, str(ROOT / "tools/fixtures/run_from.py"), "--boot-save", a.card,
                                "--exe", a.exe, "--input", str(inp), "--fields", str(end)],
                               stdout=f, stderr=subprocess.STDOUT, env=env, cwd=ROOT)
            modes = []
            for m in re.finditer(r"STATUS field=(\d+) .*?gamemode=(\S+)", log.read_text(errors="replace")):
                if int(m.group(1)) >= s1 and (not modes or modes[-1][1] != m.group(2)):
                    modes.append((int(m.group(1)), m.group(2)))
            hit = any(not g.startswith("6/") for _, g in modes)
            print(f"{d:>2} walk {w:3}: {' '.join(f'{f}:{g}' for f, g in modes)}{'  <-- HIT' if hit else ''}",
                  flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
