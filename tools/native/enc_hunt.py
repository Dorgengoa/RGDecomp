#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Find a box-walk shift that meets a wanted enemy (lane ptbugs1108).  Runs card_shots.py on a
library card with the box walk started N fields later for each N, a memory dump every 10 fields
(autobattle.dump_spec), and names the enemies of the first battle from the enemy records
(monster_param_EN ids found in each 0x410-byte record).

    python tools/native/enc_hunt.py CARD EXE OUT --control C --shifts 0,15,30 [--want 'Blue Thunder']
        [--fields N] [--env K=V ..] [--nrm]

Prints one line per shift: encounter field, fight field, enemy names.  Stops at the first shift
whose battle has --want.  Per-shift logs: OUT/sN/run.log."""
from __future__ import annotations

import argparse
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "fixtures"))
import autobattle  # noqa: E402
import bootcheck  # noqa: E402
import rgdata  # noqa: E402


def monster_names():
    names = {}
    for kind, r in rgdata.table("monster_param_EN.cfg.bin"):
        if kind == 4 and len(r) > 3 and isinstance(r[3], str) and r[3]:
            names[r[0]] = r[3]
    return names


def enemies(log: str, names: dict):
    """(encounter field, fight field, [names]) of the first battle in a run.log."""
    st = bootcheck.parse_status(log)
    enc = next((k for k, v in sorted(st.items()) if v[1].startswith("7/")), None)
    fight = next((k for k, v in sorted(st.items()) if enc and k >= enc and v[1] == "7/201"), None)
    if fight is None:
        return enc, fight, []
    blocks = {}
    for ln in log.splitlines():
        if ln.startswith("DUMP field="):
            f = int(ln.split()[1].split("=")[1])
            blocks.setdefault(f, []).append(ln)
    f = min((k for k in blocks if k >= fight + 20), default=None)
    if f is None:
        return enc, fight, []
    w = blocks[f][2].split()
    if len(w) < 5 or w[3] == "NULL":
        return enc, fight, []
    b = bytes.fromhex("".join(w[4:]))
    found = []
    for k in range(15):
        rec = b[k * 0x410:(k + 1) * 0x410]
        if len(rec) < 0x20 or struct.unpack_from("<i", rec, 0xC)[0] < 128:
            continue
        hits = sorted({names[v] + f"@{o:#x}" for o in range(0, len(rec) - 3, 2)
                       for v in [struct.unpack_from("<i", rec, o)[0]] if v in names})
        found.append("|".join(hits[:3]) or "?")
    return enc, fight, found


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("card")
    ap.add_argument("exe")
    ap.add_argument("out")
    ap.add_argument("--control", type=int, required=True)
    ap.add_argument("--shifts", default="0")
    ap.add_argument("--want")
    ap.add_argument("--fields", type=int)
    ap.add_argument("--env", action="append", default=[], help="K=V for the runs (e.g. RG_NR_DEBUG=1)")
    ap.add_argument("--nrm", action="store_true",
                    help="RG_NR_DEBUG=1 and print the meshes kept on the VU program for missing normals")
    a = ap.parse_args()
    if a.nrm:
        a.env.append("RG_NR_DEBUG=1")
    names = monster_names()
    exe = Path(a.exe).resolve()
    spec = autobattle.dump_spec(exe)
    for sh in [int(s) for s in a.shifts.split(",")]:
        o = Path(a.out) / f"s{sh}"
        cmd = [sys.executable, str(ROOT / "tools" / "native" / "card_shots.py"), a.card, str(exe), str(o),
               "--control", str(a.control), "--shift", str(sh), "--fields", str(a.fields or a.control + 3400),
               "--env", "RG_STATUS_EVERY=10", "--env", f"RG_STATUS_DUMP={spec}"]
        for kv in a.env:
            cmd += ["--env", kv]
        subprocess.run(cmd, capture_output=True)
        log = (o / "run.log").read_text(encoding="utf-8", errors="replace")
        enc, fight, found = enemies(log, names)
        print(f"shift {sh}: encounter {enc} fight {fight}: {', '.join(found)}", flush=True)
        if a.nrm:
            for ln in log.splitlines():
                m = re.search(r"mesh (\w+) variant (\w+) stays emulated: arrays missing (\w+) \(needs (\w+)\).*frame (\d+)", ln)
                if m and int(m.group(4), 16) & 1:
                    print(f"  missing normals: mesh {m.group(1)} variant {m.group(2)} frame {m.group(5)}", flush=True)
        if a.want and any(a.want in x for x in found):
            return 0
    return 1


if __name__ == "__main__":
    sys.exit(main())
