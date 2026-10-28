#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Brute-force short stick taps from a state (docs/TEST-FIXTURES.md "Route").

    python tools/fixtures/tapsearch.py --from STATE --input BASE.txt --at F \\
        --lens 2,4,8 [--dirs all|8] [--then "F0 F1 CROSS" ...] --to T \\
        --out D [--want-mode 20] [--exe EXE] [--stop]

For every stick direction (8 corners/edges of the stick bytes) and length L in
--lens, plays BASE + `#!stick F F+L-1 LX LY` + the --then lines (fields
relative to F: "+40 +43 CROSS") from STATE to field T with play.py and reports
the game mode at T and the leader's position (RG_STATUS_DUMP of the field
leader, Chara at 0x0AA3A3E0: pos +0x10/+0x18, yaw +4; valid in Salgin after the
first battle) and the input file of each try.  --want-mode M marks tries whose
last STATUS line has game mode M; --stop ends at the first such try.
F must be after the state's field (play.py rule).  One rg-game at a time.
"""
from __future__ import annotations

import argparse
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
DIRS = [(128, 0), (255, 0), (255, 128), (255, 255), (128, 255), (0, 255), (0, 128), (0, 0)]
NAMES = ["U", "UR", "R", "DR", "D", "DL", "L", "UL"]
LEADER = 0x0AA3A3E0


def rel(line: str, f: int) -> str:
    p = line.split()
    for i in (0, 1):
        if p[i].startswith("+"):
            p[i] = str(f + int(p[i][1:]))
    return " ".join(p)


def run(a, base: str, extra: list[str], tag: str):
    out = Path(a.out) / tag
    inp = Path(a.out) / f"{tag}.txt"
    inp.write_text(base.rstrip("\n") + "\n" + "\n".join(extra) + "\n", encoding="utf-8")
    env = dict(os.environ, RG_STATUS_DUMP=f"h0x{LEADER:08X}:32")
    cmd = [sys.executable, str(HERE / "play.py"), "--from", a.frm, "--to", str(a.to), "--input", str(inp),
           "--out", str(out), "--status", "10"]
    if a.exe:
        cmd += ["--exe", a.exe]
    subprocess.run(cmd, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    mode, pos = None, None
    for ln in (out / "log.txt").read_text(errors="replace").splitlines():
        m = re.match(r"STATUS .*gamemode=(\S+)", ln)
        if m:
            mode = m.group(1)
        if ln.startswith("DUMP") and f"{LEADER:08X}:" in ln:
            b = bytes.fromhex("".join(ln.split()[4:]))
            pos = (struct.unpack_from("<f", b, 0x10)[0], struct.unpack_from("<f", b, 0x18)[0])
    return mode, pos, inp


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="frm", required=True)
    ap.add_argument("--input", required=True)
    ap.add_argument("--at", type=int, required=True)
    ap.add_argument("--lens", default="2,4,8")
    ap.add_argument("--then", action="append", default=[])
    ap.add_argument("--to", type=int, required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--want-mode")
    ap.add_argument("--exe")
    ap.add_argument("--stop", action="store_true")
    a = ap.parse_args(argv)
    Path(a.out).mkdir(parents=True, exist_ok=True)
    base = Path(a.input).read_text(encoding="utf-8")
    then = [rel(t, a.at) for t in a.then]
    mode, pos, _ = run(a, base, then, "none")
    print(f"none        mode={mode} pos={pos}", flush=True)
    for L in (int(x) for x in a.lens.split(",")):
        for (lx, ly), nm in zip(DIRS, NAMES):
            line = f"#!stick {a.at} {a.at + L - 1} {lx} {ly}"
            mode, pos, inp = run(a, base, [line] + then, f"{nm}{L}")
            hit = a.want_mode and mode and mode.split("/")[0] == a.want_mode
            ps = "(%.1f %.1f)" % pos if pos else "-"
            print(f"{nm:>2} x{L:<3}    mode={mode} pos={ps} {'HIT ' + str(inp) if hit else ''}", flush=True)
            if hit and a.stop:
                return 0
    return 0


if __name__ == "__main__":
    sys.exit(main())
