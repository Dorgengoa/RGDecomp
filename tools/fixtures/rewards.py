#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Battle rewards probe: party EXP and money over a run (docs/BRINGUP.md "User play-test 2").

    python tools/fixtures/rewards.py --exe EXE --boot-save save2 \
        --input tools/trace/goldens/boot_save2_battle2.input.txt --fields 7700 --every 100
    python tools/fixtures/rewards.py --exe EXE --state S.rgstate --input route.txt --fields N
    python tools/fixtures/rewards.py --log LOG          # parse a kept log again

Reads, with one RG_STATUS_DUMP per STATUS line (RG_SS=1, fixed RAM block):
  CharaSys D_004837C0 +0x18 -> party object: +0x160 s64 money (PartySetMoney_3c9720);
  +0x14 -> party record manager +0x8 pool +0x8 base: 10 Chara records x 0x4C8.
Record layout (object = save payload + 4, docs/SAVE-FORMAT.md "Characters"): +0x4 data id,
+0xC chara id, +0x10 level, +0x14 HP, +0x4B8 s32 EXP (CharaAddExp_3ac740 / CharaGetExp_29ea40).
--state runs the exe directly (the state's own exe; fields absolute).
Prints one row per change of (mode, money, EXP) with the game mode; exit 0.
Retail counterpart: tools/trace/cardboot.py --plan rewards (same fields over PINE).
"""
from __future__ import annotations

import argparse
import re
import struct
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import fxlib  # noqa: E402

STRIDE = 0x4C8
NREC = 10


def _rva(exe: Path, name: str) -> int:
    for line in open(Path(exe).with_suffix(".map"), encoding="latin-1"):
        m = re.match(r"\s*0003:[0-9a-f]+\s+_?(\w+)\s+([0-9a-f]{16})\s", line)
        if m and m.group(1) == name:
            return int(m.group(2), 16) - 0x400000
    raise SystemExit(f"rewards: {name} not in the map of {exe}")


def dump_spec(exe: Path) -> str:
    cs = _rva(exe, "D_004837C0")
    return f"p0x{cs:X}/0x18+0x160:0x8,p0x{cs:X}/0x14/0x8/0x8+0:0x{STRIDE * NREC:X}"


def parse(log: str):
    modes, rows = {}, []
    blocks: dict[int, list[str]] = {}
    for ln in log.splitlines():
        m = re.match(r"STATUS field=(\d+) .*?gamemode=(\S+)", ln)
        if m:
            modes[int(m.group(1))] = m.group(2)
        m = re.match(r"DUMP field=(\d+) ", ln)
        if m:
            blocks.setdefault(int(m.group(1)), []).append(ln)

    def data(ln):
        w = ln.split()
        if len(w) < 5 or w[3] == "NULL" or w[-1] == "NULL":
            return None
        return bytes.fromhex("".join(w[4:]))

    for f in sorted(blocks):
        bl = blocks[f]
        if len(bl) < 2:
            continue
        mb, rb = data(bl[0]), data(bl[1])
        money = struct.unpack_from("<q", mb)[0] if mb else None
        party = []
        if rb:
            for k in range(NREC):
                o = k * STRIDE
                if o + STRIDE > len(rb):
                    break
                did, cid, lv, hp = struct.unpack_from("<4xi4xiii", rb, o)
                exp = struct.unpack_from("<i", rb, o + 0x4B8)[0]
                if 11001 <= did <= 11010:
                    party.append((cid, lv, exp, hp))
        rows.append((f, modes.get(f, "?"), money, party))
    return rows


def show(rows) -> None:
    last = None
    for f, mode, money, party in rows:
        key = (mode, money, tuple((c, lv, e) for c, lv, e, _ in party))
        if key == last:
            continue
        last = key
        p = " ".join(f"{c}:L{lv}/{e}" for c, lv, e, _ in party)
        print(f"{f:6d} {mode:>8} money={money} exp[{p}]")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--exe")
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--boot-save")
    g.add_argument("--state")
    g.add_argument("--log", help="parse this log instead of running")
    ap.add_argument("--input")
    ap.add_argument("--fields", type=int, default=7700)
    ap.add_argument("--every", type=int, default=100)
    ap.add_argument("--keep", help="write the rg-game log here")
    a = ap.parse_args(argv)
    if a.log:
        show(parse(Path(a.log).read_text(errors="replace")))
        return 0
    exe = fxlib.exe_path(a.exe)
    env = fxlib.game_env({"RG_STATUS_EVERY": str(a.every), "RG_STATUS_DUMP": dump_spec(exe), "RG_SS": "1"})
    if a.boot_save:
        cmd = [sys.executable, str(HERE / "run_from.py"), "--boot-save", a.boot_save, "--exe", str(exe),
               "--fields", str(a.fields)]
        if a.input:
            cmd += ["--input", str(Path(a.input).resolve())]
    else:
        sv = Path(a.keep or "rewards.log").resolve().parent / "rewards_saves"
        sv.mkdir(parents=True, exist_ok=True)
        cmd = [str(exe), "--headless", "--fields", str(a.fields), "--saves", str(sv),
               "--load-state", str(Path(a.state).resolve())]
        if a.input:
            cmd += ["--input", str(Path(a.input).resolve())]
    p = subprocess.run(cmd, env=env, capture_output=True, text=True, errors="replace")
    log = p.stdout + p.stderr
    if a.keep:
        Path(a.keep).write_text(" ".join(cmd) + "\n" + log, encoding="utf-8")
    rows = parse(log)
    if not rows:
        print(log[-3000:])
        print(f"rewards: no DUMP rows (exit {p.returncode})")
        return 1
    show(rows)
    return 0


if __name__ == "__main__":
    sys.exit(main())
