#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Field navigation probes for route work (docs/TEST-FIXTURES.md "Navigation").

Reads, at the end of a short rg-game segment from a save state:

- the field leader's position and yaw: RG_BREAK on the return address of the
  ActionMgrFindById_233b50 call in PlayerControlUpdateMaybe_1fc4a0 (the per-tick
  leader lookup; eax = the leader Chara: SRT at +0x50, rot +0x60 (yaw +0x64),
  pos +0x70, CharaGetPos_2388a0 / SrtGetPos_1c7430);
- the active camera (6 static camera objects Camera0..5 at 0x4B5660 + k*0x2F0,
  +0x50 look-at = leader + 25 y, +0x60 eye; the active one is the one whose
  look-at is near the leader);
- the objective markers the minimap draws (yellow star): RG_BREAK on the return
  of StateBlockCollectMapMarkers_3cc390 in MinimapDrawEntry_325720, dumping its
  out array (arg 1: vec4 x, y, z, 1 each; eax = count).  Source of the list:
  GameData(0x4B8B30)->+0x10 state block, ids at +0x34C, filtered by the current
  map id D_004838C0->+0x18->+4;
- the current map id (`p<RVA of D_004838C0>/0x18+4:2` STATUS_DUMP) and game mode.

RVAs come from the exe's own map + llvm-objdump (cached next to the map as
navprobe.json), so any build works.  A camera-relative stick: the game rotates
the move stick by the camera yaw (PlayerControlUpdateMaybe_1fc4a0), so
`stick_for(heading, cam)` turns a world heading into stick bytes.

    python tools/trace/navprobe.py where  --from STATE [--input F] [--exe EXE]
    python tools/trace/navprobe.py marker --from STATE [--input F] [--exe EXE]
"""
from __future__ import annotations

import argparse
import bisect
import json
import math
import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import fxlib  # noqa: E402

OBJDUMP = os.environ.get("RG_OBJDUMP", r"../tools\llvm\bin\llvm-objdump.exe")
CAMS = [0x4B5660 + k * 0x2F0 for k in range(6)]
MAPID_SYM = "D_004838C0"


def _syms(mp: Path):
    syms = []
    for line in open(mp, encoding="latin-1"):
        m = re.match(r"\s*000[13]:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8,16})\s+", line)
        if m:
            syms.append((int(m.group(2), 16), m.group(1).lstrip("_")))
    syms.sort()
    return syms


def _ret_sites(exe: Path, syms, caller: str, callee: str) -> list[int]:
    text = [(a, n) for a, n in syms]
    keys = [a for a, _ in text]
    byname = {n: a for a, n in text}
    start = byname[caller]
    end = keys[bisect.bisect_right(keys, start)]
    tgt = byname[callee]
    out = subprocess.run([OBJDUMP, "-d", "--no-show-raw-insn", "--start-address=%#x" % start,
                          "--stop-address=%#x" % end, str(exe)], capture_output=True, text=True).stdout
    lines = [ln for ln in out.splitlines() if re.match(r"\s+[0-9a-f]+:", ln)]
    res = []
    for i, ln in enumerate(lines):
        m = re.match(r"\s+([0-9a-f]+):\s+call[l]?\s+(0x[0-9a-f]+)", ln)
        if m and int(m.group(2), 16) == tgt and i + 1 < len(lines):
            res.append(int(lines[i + 1].split(":")[0], 16) - 0x400000)
    return res


def rvas(exe: Path) -> dict:
    """{leader: [ret rva], marker: [ret rvas], mapid_rva: rva} for this exe."""
    exe = Path(exe).resolve()
    mp = exe.with_suffix(".map")
    cache = exe.parent / "navprobe.json"
    eid = fxlib.exe_id(exe)
    if cache.exists():
        c = json.loads(cache.read_text())
        if c.get("exe_id") == eid:
            return c
    syms = _syms(mp)
    byname = {n: a for a, n in syms}
    c = {
        "exe_id": eid,
        "leader": _ret_sites(exe, syms, "PlayerControlUpdateMaybe_1fc4a0", "ActionMgrFindById_233b50")[:1],
        "marker": _ret_sites(exe, syms, "MinimapDrawEntry_325720", "StateBlockCollectMapMarkers_3cc390"),
        "mapid_rva": byname[MAPID_SYM] - 0x400000,
    }
    cache.write_text(json.dumps(c, indent=1))
    return c


def heading(dx: float, dz: float) -> float:
    """World heading of a step (radians, atan2(x, z): the game's yaw convention)."""
    return math.atan2(dx, dz)


def stick_for(h: float, cam: tuple | None, cal: float = 0.0, mag: float = 1.0) -> tuple[int, int]:
    """Stick bytes (LX, LY) that move the leader along world heading h with the
    camera cam = (eye, look): stick up = away from the eye.  `cal` is an extra
    offset (radians, learned by Steer).  Full deflection on the DS2 square
    (corners for diagonals: the run band needs |stick| >= 0.9)."""
    cy = heading(cam[1][0] - cam[0][0], cam[1][2] - cam[0][2]) if cam else 0.0
    r = h - cy + cal                     # heading relative to camera forward
    sx, sy = math.sin(r), math.cos(r)    # right, forward
    # camera right is forward rotated by -90 deg in this yaw convention (verified
    # by navprobe calibrate: stick right moves along heading cy - pi/2)
    sx = -sx
    k = mag / max(abs(sx), abs(sy))
    lx = int(round(128 + 127 * sx * k))
    ly = int(round(128 - 127 * sy * k))
    return max(0, min(255, lx)), max(0, min(255, ly))


def run_probe(exe: Path, state: Path, inp_text: str, to: int, out: Path, save: int | None = None,
              marker: bool = False, shots: list[int] | None = None, env_extra: dict | None = None,
              saves: Path | None = None) -> dict:
    """One rg-game segment from `state` to field `to` with the input text;
    returns {pos, yaw, cam, mode, mapid, markers, log, state}."""
    exe = Path(exe).resolve()
    r = rvas(exe)
    out.mkdir(parents=True, exist_ok=True)
    inp = out / "input.txt"
    inp.write_text(inp_text, encoding="utf-8")
    vbl_from = max(0, to - 33 - 6)
    dump = ",".join(f"0x{c + 0x40:X}:0x30" for c in CAMS) + f",p0x{r['mapid_rva']:X}/0x18+4:2"
    env = {
        "RG_STATUS_EVERY": "2", "RG_STATUS_DUMP": dump,
        "RG_BREAK": ",".join(f"0x{x:X}" for x in (r["marker"] if marker else r["leader"])),
        "RG_BREAK_MAX": "3", "RG_BREAK_FROM_VBL": str(vbl_from),
        "RG_BREAK_DUMP": "0x40" if marker else "0x80",
    }
    if marker:
        env["RG_BREAK_DUMPARG"] = "1"
    if env_extra:
        env.update(env_extra)
    sv = saves or (out / "saves")
    sv.mkdir(parents=True, exist_ok=True)
    cmd = [str(exe), "--headless", "--fields", str(to), "--saves", str(sv), "--input", str(inp),
           "--load-state", str(Path(state).resolve())]
    st = None
    if save:
        st = out / f"f{save}.rgstate"
        cmd += ["--save-state", f"{save}:{st}"]
    for f in shots or []:
        cmd += ["--shot", f"{f}:{out / f's{f:05d}.png'}"]
    p = subprocess.run(cmd, env=fxlib.game_env(env), capture_output=True, text=True, errors="replace")
    log = p.stdout + p.stderr
    (out / "log.txt").write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    res = {"rc": p.returncode, "pos": None, "yaw": None, "cam": None, "mode": None, "mapid": None,
           "markers": [], "state": st, "log": out / "log.txt", "field": None}
    cams = {}
    last_brk = None
    for ln in log.splitlines():
        if ln.startswith("STATUS"):
            m = re.search(r"field=(\d+).*gamemode=(\S+)", ln)
            if m:
                res["field"], res["mode"] = int(m.group(1)), m.group(2)
        elif ln.startswith("DUMP"):
            w = ln.split()
            if len(w) < 5:
                continue
            addr = int(w[3].rstrip(":"), 16)
            b = bytes.fromhex("".join(w[4:]))
            if len(b) == 2:
                res["mapid"] = struct.unpack("<h", b)[0]
            elif len(b) == 0x30:
                f = struct.unpack("<12f", b)
                cams[addr] = (f[8:11], f[4:7])      # (eye +0x60, look +0x50)
        elif ln.startswith("BRK "):
            last_brk = ln
        elif ln.startswith("BRKDUMP"):
            b = bytes.fromhex("".join(ln.split()[1:]))
            if marker:
                n = int(re.search(r"eax=([0-9A-F]+)", last_brk).group(1), 16)
                res["markers"] = [struct.unpack_from("<3f", b, 16 * i) for i in range(min(n, 4))]
            else:
                res["pos"] = struct.unpack_from("<3f", b, 0x70)
                res["yaw"] = struct.unpack_from("<f", b, 0x64)[0]
    if res["pos"] and cams:
        best = min(cams.values(), key=lambda c: math.dist(c[1], (res["pos"][0], res["pos"][1] + 25, res["pos"][2])))
        if math.dist(best[1], best[0]) > 1:
            res["cam"] = best
    elif cams:
        live = [c for c in cams.values() if math.dist(c[1], c[0]) > 1]
        res["cam"] = live[0] if live else None
    return res


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("what", choices=["where", "marker"])
    ap.add_argument("--from", dest="frm", required=True, help=".rgstate")
    ap.add_argument("--input", help="input script (default: none)")
    ap.add_argument("--exe", help="exe that wrote the state (default $RG_FIXTURES_EXE)")
    ap.add_argument("--fields", type=int, default=4)
    ap.add_argument("--out", default=str(Path(tempfile.gettempdir()) / "navprobe"))
    a = ap.parse_args(argv)
    exe = fxlib.exe_path(a.exe)
    f0 = fxlib.peek(Path(a.frm))["field"]
    txt = Path(a.input).read_text(encoding="utf-8") if a.input else "#!stick 1 0\n"
    r = run_probe(exe, Path(a.frm), txt, f0 + a.fields, Path(a.out), marker=(a.what == "marker"))
    print(json.dumps({k: (str(v) if isinstance(v, Path) else v) for k, v in r.items()}, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
