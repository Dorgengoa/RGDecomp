#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Disassemble the game's compiled config files (.cfg.bin, CfgVm byte code).

    python tools/fixtures/cfgdump.py PAC_OR_FILE [MEMBER] [--grep RX] [--ids]
    e.g. cfgdump.py rc/param/param_2_en.pac phase_param_EN.cfg.bin

Format (CfgVmLoad_42fac0, CfgVmStep_42f6e0, CfgVmGetString_42f3d0):
header u32 command count, u32 string pool offset (from the header), u32 pool
size, u32 ?; commands from +0x10: u16 id, u8 argc, ceil(argc*2/8) type bytes
(2 bits per argument, low bits first: 0 string = pool offset, -1 = "",
1 int, 2 float, 3 none), padded to 4, then one 32-bit value per argument
(type 3 consumes none).  The ids are the table's own command numbers (the
loader registers its handlers with CfgVmRegisterCmds_42fb00); the dump prints
them as `#id`.  The first string arguments usually name the row.

PAC_OR_FILE: an archive name (gamedata.py) or a file on disk.
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gamedata  # noqa: E402

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")


def parse(b: bytes):
    """Yield (id, [args]) where args are str / int / float."""
    n, pool, pool_n = struct.unpack_from("<III", b, 0)
    pos = 0x10

    def s(i):
        if i == -1:
            return ""
        if i < 0 or i >= pool_n:
            return None
        return b[pool + i:b.index(b"\0", pool + i)].decode("cp932", "replace")

    for _ in range(n):
        if pos + 4 > len(b):
            break
        cid, argc = struct.unpack_from("<HB", b, pos)
        nflag = argc * 2 // 8 + (1 if argc * 2 % 8 else 0)
        flags = b[pos + 3:pos + 3 + nflag]
        vals = pos + ((nflag + 3 + 3) // 4) * 4
        args = []
        v = vals
        for i in range(argc):
            t = (flags[i // 4] >> (2 * (i % 4))) & 3
            if t == 3:
                continue
            (w,) = struct.unpack_from("<i", b, v)
            if t == 0:
                args.append(s(w))
            elif t == 1:
                args.append(w)
            else:
                args.append(round(struct.unpack_from("<f", b, v)[0], 4))
            v += 4
        yield cid, args
        pos = vals + 4 * argc


def load(name: str, member: str | None) -> bytes:
    p = Path(name)
    b = p.read_bytes() if p.exists() else gamedata.Archive().get(name)
    if member:
        for nm, off, size in gamedata.pac_members(b):
            if nm.lower() == member.lower() or nm.lower().startswith(member.lower()):
                return b[off:off + size]
        raise SystemExit(f"cfgdump: no member {member} in {name}")
    return b


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("file")
    ap.add_argument("member", nargs="?")
    ap.add_argument("--grep")
    ap.add_argument("--ids", action="store_true", help="only count rows per command id")
    a = ap.parse_args(argv)
    b = load(a.file, a.member)
    rx = re.compile(a.grep, re.I) if a.grep else None
    counts = {}
    for cid, args in parse(b):
        counts[cid] = counts.get(cid, 0) + 1
        if a.ids:
            continue
        line = f"#{cid:<4d} " + ", ".join(repr(x) if isinstance(x, str) else str(x) for x in args)
        if rx is None or rx.search(line):
            print(line)
    if a.ids:
        for k in sorted(counts):
            print(f"#{k}: {counts[k]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
