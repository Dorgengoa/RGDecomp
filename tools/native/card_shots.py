#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Shots of a library card's first box-walk battle (or any input) from power-on, for native vs
oracle comparisons (lane ptbugs1108; docs/NATIVE-RENDER.md "Mesh-partitioned enemies").

    python tools/native/card_shots.py CARD EXE OUT --control C --shots F1,F2,.. [--fields N]
        [--input EXTRA.txt] [--env K=V ..] [-- extra rg-game args, e.g. --set graphics.aspect=16:9]

Boots the card with the bootcheck.py card-library script for field control C (autobattle prep's
`control`: ch02_juraika 3830 meets Horrorwood x2 + Blue Thunder at 5220) plus EXTRA lines
(appended; e.g. an autobattle route.txt; --cut F ends the box walk's stick at F), shots OUT/fNNNNN.png, log OUT/run.log.  No save states:
any exe with the same run hash (native rg-game, the oracle twin with RG_RENDER=emu) reaches the
same fields.  Prints the run.log's 'run hash' / composite lines."""
from __future__ import annotations

import argparse
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "fixtures"))
import bootcheck  # noqa: E402
import fxlib  # noqa: E402


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]
    extra = []
    if "--" in argv:
        i = argv.index("--")
        argv, extra = argv[:i], argv[i + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("card")
    ap.add_argument("exe")
    ap.add_argument("out")
    ap.add_argument("--control", type=int, required=True)
    ap.add_argument("--shots", default="")
    ap.add_argument("--fields", type=int)
    ap.add_argument("--input")
    ap.add_argument("--env", action="append", default=[])
    ap.add_argument("--cut", type=int, help="end the box walk's stick lines before this field")
    ap.add_argument("--shift", type=int, default=0,
                    help="start the box walk N fields later (another random encounter)")
    a = ap.parse_args(argv)
    out = Path(a.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    script = bootcheck.lib_script(a.control)
    if a.shift:
        L = []
        for ln in script.splitlines():
            t = ln.split()
            if ln.startswith("#!stick") and len(t) >= 5 and t[1] != "1" and int(t[1]) >= a.control + 340:
                ln = " ".join(["#!stick", str(int(t[1]) + a.shift), str(int(t[2]) + a.shift)] + t[3:])
            L.append(ln)
        script = "\n".join(L) + "\n"
    if a.cut:
        keep = []
        for ln in script.splitlines():
            t = ln.split()
            if ln.startswith("#!stick") and len(t) >= 5 and t[1] != "1":
                f0, f1 = int(t[1]), int(t[2])
                if f0 >= a.cut:
                    continue
                if f1 >= a.cut:
                    ln = " ".join(["#!stick", t[1], str(a.cut - 1)] + t[3:5])
            keep.append(ln)
        script = "\n".join(keep) + "\n"
    if a.input:
        extra_lines = Path(a.input).read_text(encoding="utf-8").splitlines()
        if "#!stick 1 0" in script.splitlines():   # the version line may appear once
            extra_lines = [ln for ln in extra_lines if ln.split("#")[1:2] != ["!stick 1 0"]
                           and not ln.startswith("#!stick 1 0")]
        script += "\n".join(extra_lines) + "\n"
    sp = out / "input.txt"
    sp.write_text(script, encoding="utf-8")
    shots = [int(s) for s in a.shots.split(",") if s]
    end = a.fields or (max(shots) + 2 if shots else a.control + 2000)
    args = []
    for f in shots:
        args += ["--shot", f"{f}:{out / f'f{f:05d}.png'}"]
    env = fxlib.game_env(dict(kv.split("=", 1) for kv in a.env))
    cmd = [sys.executable, str(ROOT / "tools" / "fixtures" / "run_from.py"), "--boot-save", a.card,
           "--input", str(sp), "--exe", str(Path(a.exe).resolve()), "--fields", str(end), "--"] + args + extra
    p = subprocess.run(cmd, env=env, capture_output=True, text=True, errors="replace")
    log = p.stdout + p.stderr
    (out / "run.log").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    for ln in log.splitlines():
        if "run hash" in ln or "native render composite (" in ln:
            print(ln)
    print(f"exit {p.returncode}; shots {sum((out / f'f{f:05d}.png').exists() for f in shots)}/{len(shots)}")
    return p.returncode


if __name__ == "__main__":
    sys.exit(main())
