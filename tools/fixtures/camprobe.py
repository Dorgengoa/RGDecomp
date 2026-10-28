#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Field camera of library cards at bootcheck's control / field milestones (the camera
collision check of docs/BRINGUP.md 2026-10-18 (f); retail values from tools/trace/cardboot.py
logs, e.g. ch01_salgin control eye (-3328.2, 97.0, -1894.9), ch05_factory (6589.3, -644.1,
5831.6)).

    python tools/fixtures/camprobe.py --exe EXE CARD [CARD ...]

Two runs per card (bootcheck pass 1 to find control C, then the pass-2 script to C+360 with
RG_STATUS_DUMP of the six camera objects at 0x4B5660 + k*0x2F0 + 0x50: look-at xyz, eye xyz).
Prints one JSON line per card: {milestone: {field, cams: [[look x,y,z, eye x,y,z], ..]}}.
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import bootcheck  # noqa: E402

DUMP = ",".join(f"0x{0x4B5660 + k * 0x2F0 + 0x50:X}:0x20" for k in range(6))


def probe(card: str, exe: Path) -> tuple[int | None, dict]:
    rc, log, st = bootcheck.run_status(card, bootcheck.lib_script(None), exe, 4700, 10, [], {},
                                       card + "_cam1", None)
    ctl = next((k for k, v in sorted(st.items()) if k >= 3700 and v == (3, "6/100")), None)
    if ctl is None:
        return None, {}
    rc, log, st = bootcheck.run_status(card, bootcheck.lib_script(ctl), exe, ctl + 360, 10, [],
                                       {"RG_STATUS_DUMP": DUMP}, card + "_cam2", None)
    res = {}
    for ms, f in (("control", ctl + 40), ("field", ctl + 340)):
        f = f // 10 * 10
        cams = []
        for ln in log.splitlines():
            if ln.startswith(f"DUMP field={f} "):
                v = struct.unpack("<8f", bytes.fromhex("".join(ln.split()[4:])))
                cams.append([round(x, 1) for x in v[0:3] + v[4:7]])
        res[ms] = {"field": f, "cams": [c for c in cams if any(c[:3])]}
    return ctl, res


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("cards", nargs="+")
    ap.add_argument("--exe", required=True)
    a = ap.parse_args(argv)
    for c in a.cards:
        ctl, res = probe(c, Path(a.exe).resolve())
        print(c, ctl, json.dumps(res), flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
