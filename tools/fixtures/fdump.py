#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""FACTORY state dump (docs/TEST-FIXTURES.md "Widened soak", factory production): plays a
segment from a save state and prints the factory object at its end field, read live through
RG_STATUS_DUMP pointer chains (exe + its rg-game.map; no game code changes).

    python tools/fixtures/fdump.py EXE STATE [--input IN] [--to FIELD] [--grid] [--defs] [--json OUT]

Factory object = *D_004830E8 (GetFactoryObj_367f30):
  +0x004 s32 running, +0x008 s32 result code (FactoryProduceRun_505e00: 1 produced, 4 route
         broken, 8 / 9 / 0xA / 0xB / 0xC / 0xD wrong material in the Disassembler / Grinder /
         Athanor / Washer / Smelter / Form Press, 0xE unprocessed material at the assembler,
         0x10 / 0x11 metal not cooled / not pressed, 0x13 inputs do not match the plan, 0x15 not
         all inputs at the assembler in the same tick, 0x12 stopped by the player)
  +0x0E0 4 material slots x 0x40 (+0 item def, +4 s16 item id, +0xA / +0xC source cell,
         +0xE part group, +0x10 part, +0x12 path, +0x30 s16 processing state (0 raw, 1
         disassembled, 2 smelted, 3 pressed, 4 cooled, 5 athanor, 6 ground, 7 washed, 8
         assembled), +0x32 s16 tick in the part, +0x34 s16 ticks since start)
  +0x0D4 part groups (0x68 each, +0xD8 count): +4 s16 type (0 Disassembler, 1 Grinder,
         2 Athanor, 3 Washer, 4 Smelter, 5 Form Press, 6 Cooler, 0xA..0xC Assembler I..III
         (inputs = type - 9), 0xD Source Table, 0xE Completion Table, 0xF..0x11 I / L / X tube,
         0x12 Power Cord), +6 s16 length (a material spends length x 30 ticks in a part and is
         processed at length x 15), +0xC s16 count, +0x10 parts (0x40 each: +0x25 s8 state (3
         placed, 4 powered, 5/6 running), +0x26 dir, +0x30 / +0x32 s16 coarse cell); +0x20 /
         +0x24 power points (ptr, n), +0x38 / +0x3C footprint rects, +0x60 / +0x64 routes
  +0x294 fine cell grid (6 bytes: s16 group, s16 part, u16 flags), +0x298 / +0x29A w / h;
  +0x2A0 coarse grid (same cells), +0x2A4 / +0x2A6 w / h
--grid prints the coarse grid (one char per cell: group type in hex, '.' empty), --defs the raw
point / rect / route tables of every group (part geometry).
"""
from __future__ import annotations

import argparse
import json
import struct
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402

NAMES = {0: "Disassembler", 1: "Grinder", 2: "Athanor", 3: "Washer", 4: "Smelter", 5: "Form Press",
         6: "Cooler", 0xA: "Assembler", 0xB: "Assembler II", 0xC: "Assembler III", 0xD: "Source Table",
         0xE: "Completion Table", 0xF: "I tube", 0x10: "L tube", 0x11: "X tube", 0x12: "Power Cord"}
# --grid characters: machines by initial, tubes | L X, tables S / E, assemblers 1..3
GRID_CH = {0: "D", 1: "G", 2: "A", 3: "W", 4: "M", 5: "P", 6: "C", 0xA: "1", 0xB: "2", 0xC: "3", 0xD: "S",
           0xE: "E", 0xF: "|", 0x10: "L", 0x11: "X", 0x12: "c"}
RESULTS = {1: "produced", 4: "route broken", 8: "wrong material: Disassembler", 9: "wrong material: Grinder",
           0xA: "wrong material: Athanor", 0xB: "wrong material: Washer", 0xC: "wrong material: Smelter",
           0xD: "wrong material: Form Press", 0xE: "improperly processed (raw) material at the assembler",
           0x10: "overheated metal (not cooled)", 0x11: "misshapen metal (not pressed)",
           0x12: "stopped", 0x13: "materials don't fit (plan)", 0x15: "not all materials arrived on time"}


def sym_rva(exe: Path, name: str) -> int:
    for ln in open(exe.with_suffix(".map"), encoding="latin-1"):
        w = ln.split()
        if len(w) >= 3 and w[1] == name:
            return int(w[2], 16) - 0x400000
    raise SystemExit(f"fdump: {name} not in {exe.with_suffix('.map')}")


def dump(exe: Path, state: Path, inp: Path | None, to: int, defs=False, saves=None):
    rva = sym_rva(exe, "_D_004830E8")
    base = f"p0x{rva:X}"
    items = [f"{base}+0:0x300",                              # the object head (slots, counts)
             f"{base}/0xD4+0:0x{0x68 * 20:X}",                # part group headers
             f"{base}/0x2A0+0:0x{6 * 30 * 30:X}"]             # coarse grid (w x h <= 30 x 30)
    items += [f"{base}/0xD4/0x{0x68 * i + 0x10:X}+0:0x500" for i in range(20)]
    if defs:
        for i in range(20):
            items += [f"{base}/0xD4/0x{0x68 * i + o:X}+0:0x80" for o in (0x20, 0x38, 0x60)]
    sv = Path(saves) if saves else Path(state).parent / "fdump_saves"
    sv.mkdir(parents=True, exist_ok=True)
    cmd = [str(exe), "--headless", "--fields", str(to), "--load-state", str(state), "--saves", str(sv)]
    if inp:
        cmd += ["--input", str(inp)]
    p = subprocess.run(cmd, env=fxlib.game_env({"RG_SS": "1", "RG_STATUS_EVERY": str(to),
                                                "RG_STATUS_DUMP": ",".join(items)}),
                       capture_output=True, text=True, errors="replace")
    blocks = []
    for ln in (p.stdout + p.stderr).splitlines():
        if ln.startswith("DUMP"):
            w = ln.split()
            blocks.append(None if len(w) < 5 or w[4] == "NULL" else bytes.fromhex("".join(w[4:])))
    if len(blocks) < 3 or blocks[0] is None:
        raise SystemExit("fdump: no factory object at the end field\n" + (p.stdout + p.stderr)[-1500:])
    head, groups, grid = blocks[0], blocks[1], blocks[2]
    parts = blocks[3:23]
    out = {"field": to, "running": struct.unpack_from("<i", head, 4)[0],
           "result": struct.unpack_from("<i", head, 8)[0], "phase": struct.unpack_from("<i", head, 0x2D4)[0]}
    out["result_text"] = RESULTS.get(out["result"], "")
    out["slots"] = []
    for k in range(4):
        o = 0xE0 + 0x40 * k
        item, marker, sx, sy, grp, prt, path = struct.unpack_from("<h2xhhhhhh", head, o + 4)
        st, tick, total = struct.unpack_from("<hhh", head, o + 0x30)
        out["slots"].append({"item": item, "src": (sx, sy), "group": grp, "part": prt, "path": path,
                             "state": st, "tick": tick, "ticks": total})
    ng = struct.unpack_from("<i", head, 0xD8)[0]
    out["groups"] = []
    for i in range(min(ng, 20)):
        g = groups[0x68 * i:0x68 * i + 0x68]
        typ, ln_, fl, n = struct.unpack_from("<hhH2xh", g, 4)
        ps = []
        pb = parts[i] or b""
        for k in range(n):
            if 0x40 * k + 0x40 <= len(pb):
                q = pb[0x40 * k:0x40 * k + 0x40]
                ps.append({"state": q[0x25], "dir": q[0x26], "cell": struct.unpack_from("<hh", q, 0x30)})
        gi = {"index": i, "type": typ, "name": NAMES.get(typ, "?"), "len": ln_, "flags": fl, "n": n,
              "s14": g[0x14], "s15": g[0x15], "f18": struct.unpack_from("<ff", g, 0x18),
              "npoints": struct.unpack_from("<i", g, 0x24)[0], "nrects": struct.unpack_from("<i", g, 0x3C)[0],
              "nroutes": struct.unpack_from("<i", g, 0x64)[0], "parts": ps, "raw": g.hex()}
        out["groups"].append(gi)
    if defs:
        d = blocks[23:]
        for i, gi in enumerate(out["groups"]):
            gi["points_raw"], gi["rects_raw"], gi["routes_raw"] = [(x.hex() if x else None) for x in d[3 * i:3 * i + 3]]
    out["grid"] = grid.hex()
    out["grid_wh"] = struct.unpack_from("<hh", head, 0x2A4)
    out["log_tail"] = (p.stdout + p.stderr)[-400:]
    return out


def grid_text(res, w=None, h=None):
    g = bytes.fromhex(res["grid"])
    w = w or res["grid_wh"][0]
    h = h or res["grid_wh"][1]
    h = h or len(g) // (6 * w)
    rows = []
    for y in range(h):
        r = ""
        for x in range(w):
            o = (y * w + x) * 6
            if o + 6 > len(g):
                break
            gid, _, _ = struct.unpack_from("<hhH", g, o)
            if gid < 0:
                r += "."
            else:
                typ = next((x_["type"] for x_ in res["groups"] if x_["index"] == gid), gid)
                r += GRID_CH.get(typ, "?")
        rows.append(f"{y:2d} {r}")
    return "\n".join(rows)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("exe")
    ap.add_argument("state")
    ap.add_argument("--input")
    ap.add_argument("--to", type=int, help="end field (default: the state's field + 2, from its name fNNNN)")
    ap.add_argument("--grid", action="store_true")
    ap.add_argument("--defs", action="store_true")
    ap.add_argument("--json")
    a = ap.parse_args(argv)
    st = Path(a.state).resolve()
    to = a.to
    if to is None:
        import re
        m = re.search(r"f(\d+)\.rgstate$", st.name)
        to = int(m.group(1)) + 2 if m else None
    res = dump(Path(a.exe).resolve(), st, Path(a.input).resolve() if a.input else None, to, defs=a.defs)
    print(f"field {res['field']} running {res['running']} result {res['result']:#x} {res['result_text']} phase {res['phase']}")
    for k, s in enumerate(res["slots"]):
        if s["item"] >= 0:
            print(f"  slot {k}: {s}")
    for gi in res["groups"]:
        print(f"  group {gi['index']:2d} {gi['name']:16s} type {gi['type']:#x} len {gi['len']} flags {gi['flags']:#x} "
              f"n {gi['n']} pts {gi['npoints']} rects {gi['nrects']} routes {gi['nroutes']} "
              + " ".join(f"{p['cell']}d{p['dir']}s{p['state']}" for p in gi["parts"]))
        if a.defs:
            print(f"      head {gi['raw']}\n      points {gi['points_raw']}\n      rects {gi['rects_raw']}\n      routes {gi['routes_raw']}")
    if a.grid:
        print(grid_text(res))
    if a.json:
        Path(a.json).write_text(json.dumps(res, indent=1), encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
