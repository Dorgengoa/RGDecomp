#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Where is the leader after an input script, booted from a card (no save states needed, so
play-test exes work too).  navprobe.py's probes (RG_BREAK on the per-tick leader lookup +
the camera objects) on a run_from.py --boot-save run (docs/TEST-FIXTURES.md "Navigation").

    python tools/fixtures/cardwhere.py CARD --exe EXE --input F --to FIELD [--shots A,B,..]
                                       [--out DIR]

Prints field, game mode, leader position (x, y, z), yaw and the camera-relative stick bytes
for the 8 world headings (navprobe.stick_for), so the next walk can be aimed in world terms.
The exe needs its .map beside it (build dirs have one; out/playtest exes: pass the build
dir's copy, e.g. build/pt1025b-i686/rg-game.exe, byte-identical to rg-game-1025b.exe).
"""
from __future__ import annotations

import argparse
import math
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "trace"))
import navprobe  # noqa: E402


def probe(card: str, exe: Path, inp: Path, to: int, out: Path, shots=()) -> dict:
    r = navprobe.rvas(exe)
    dump = ",".join(f"0x{c + 0x40:X}:0x30" for c in navprobe.CAMS) + f",p0x{r['mapid_rva']:X}/0x18+4:2"
    env = dict(os.environ, RG_GPU=os.environ.get("RG_GPU", "hw"), RG_STATUS_EVERY="2", RG_STATUS_DUMP=dump,
               RG_BREAK=",".join(f"0x{x:X}" for x in r["leader"]), RG_BREAK_MAX="3",
               RG_BREAK_FROM_VBL=str(max(0, to - 39)), RG_BREAK_DUMP="0x80")
    out.mkdir(parents=True, exist_ok=True)
    extra = []
    for f in shots:
        extra += ["--shot", f"{f}:{out / f'{inp.stem}-{f}.png'}"]
    cmd = [sys.executable, str(ROOT / "tools/fixtures/run_from.py"), "--boot-save", card, "--exe", str(exe),
           "--input", str(inp), "--fields", str(to), "--"] + extra
    p = subprocess.run(cmd, env=env, capture_output=True, text=True, errors="replace", cwd=ROOT)
    log = p.stdout + p.stderr
    (out / f"{inp.stem}.log").write_text(log, encoding="utf-8")
    res = {"rc": p.returncode, "pos": None, "yaw": None, "cam": None, "mode": None, "mapid": None, "modes": []}
    cams = {}
    for ln in log.splitlines():
        if ln.startswith("STATUS"):
            m = re.search(r"field=(\d+).*gamemode=(\S+)", ln)
            if m:
                res["mode"] = m.group(2)
                if not res["modes"] or res["modes"][-1][1] != m.group(2):
                    res["modes"].append((int(m.group(1)), m.group(2)))
        elif ln.startswith("DUMP"):
            w = ln.split()
            if len(w) < 5:
                continue
            try:
                addr = int(w[3].rstrip(":"), 16)
            except ValueError:
                continue
            b = bytes.fromhex("".join(w[4:]))
            if len(b) == 2:
                res["mapid"] = struct.unpack("<h", b)[0]
            elif len(b) == 0x30:
                f = struct.unpack("<12f", b)
                cams[addr] = (f[8:11], f[4:7])
        elif ln.startswith("BRKDUMP"):
            b = bytes.fromhex("".join(ln.split()[1:]))
            res["pos"] = struct.unpack_from("<3f", b, 0x70)
            res["yaw"] = struct.unpack_from("<f", b, 0x64)[0]
    if res["pos"] and cams:
        best = min(cams.values(), key=lambda c: math.dist(c[1], (res["pos"][0], res["pos"][1] + 25, res["pos"][2])))
        if math.dist(best[1], best[0]) > 1:
            res["cam"] = best
    return res


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("card")
    ap.add_argument("--exe", required=True)
    ap.add_argument("--input", required=True)
    ap.add_argument("--to", type=int, required=True)
    ap.add_argument("--shots", default="")
    ap.add_argument("--out", default="out/cardwhere")
    a = ap.parse_args(argv)
    shots = [int(x) for x in a.shots.split(",") if x]
    res = probe(a.card, Path(a.exe).resolve(), Path(a.input).resolve(), a.to, Path(a.out).resolve(), shots)
    pos = res["pos"]
    print(f"rc {res['rc']} mode {res['mode']} map {res['mapid']} modes {' '.join(f'{f}:{m}' for f, m in res['modes'][-6:])}")
    if pos:
        print(f"leader x {pos[0]:.1f} y {pos[1]:.1f} z {pos[2]:.1f} yaw {math.degrees(res['yaw']):.0f}")
    if res["cam"]:
        print("stick for world heading (deg, atan2(dx, dz)): " +
              " ".join(f"{h}:{navprobe.stick_for(math.radians(h), res['cam'])}" for h in range(0, 360, 45)))
    return 0 if pos else 1


if __name__ == "__main__":
    sys.exit(main())
