#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Initial data-image parity of the game's data layer between an i686 and an x64 rg-game
(docs/X64-PLAN.md 0.6): every D_xxxxxxxx object of the two exes, word by word.

    python tools/x64/dataparity.py I686_EXE X64_EXE [--limit 40] [--only REGEX]

The data layer is generated twice (i686: data2c C; x64: the same C, or tools/x64/addr32.py
asm with ADDR32 words), so the bytes the game starts from must agree.  A 4-byte word is
EQUAL when the bytes match, or POINTER-EQUAL when both words resolve, through the exes'
maps, to the same symbol + offset (addresses differ between the two links).  Anything
else is listed (object, offset, both words, what each resolves to).  Object size = the
distance to the next symbol in each map (the smaller of the two).  Exit 1 on a difference.
"""
from __future__ import annotations

import argparse
import bisect
import re
import sys
from pathlib import Path

import pefile

ROW = re.compile(r"\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)")
DSYM = re.compile(r"^D_[0-9A-F]{8}$")


def load_map(exe: Path):
    rows = []
    for ln in exe.with_suffix(".map").read_text(encoding="utf-8", errors="replace").splitlines():
        r = ROW.match(ln)
        if r and int(r.group(1), 16) > 0:
            name = r.group(3)
            if name.startswith("_") and not name.startswith("__"):
                name = name[1:]          # i686 C names carry the `_` prefix
            rows.append((int(r.group(4), 16), name))
    rows.sort()
    return rows


class Image:
    def __init__(self, exe: Path):
        self.pe = pefile.PE(str(exe), fast_load=True)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.rows = load_map(exe)
        self.addrs = [a for a, _ in self.rows]
        self.by_name = {}
        for i, (a, n) in enumerate(self.rows):
            self.by_name.setdefault(n, i)

    def size_of(self, i: int) -> int:
        a = self.rows[i][0]
        j = bisect.bisect_right(self.addrs, a)
        return (self.addrs[j] - a) if j < len(self.addrs) else 0

    def read(self, va: int, n: int) -> bytes:
        rva = va - self.base
        for s in self.pe.sections:
            if s.VirtualAddress <= rva < s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData):
                off = rva - s.VirtualAddress
                raw = s.get_data()[off:off + n] if off < s.SizeOfRawData else b""
                return raw + bytes(n - len(raw))
        return bytes(n)

    def resolve(self, v: int):
        i = bisect.bisect_right(self.addrs, v) - 1
        if i < 0 or v < self.base:
            return None
        a, n = self.rows[i]
        if v - a > 0x100000:
            return None
        return n, v - a


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("i686")
    ap.add_argument("x64")
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--only", default="")
    a = ap.parse_args()
    A, B = Image(Path(a.i686)), Image(Path(a.x64))
    only = re.compile(a.only) if a.only else None
    objs = ndiff = nbytes = nptr = 0
    shown = 0
    bad_objs = []
    for name, ia in A.by_name.items():
        if not DSYM.match(name) or (only and not only.search(name)) or name not in B.by_name:
            continue
        ib = B.by_name[name]
        size = min(A.size_of(ia), B.size_of(ib))
        if size <= 0 or size > (8 << 20):
            continue
        objs += 1
        nbytes += size
        da, db = A.read(A.rows[ia][0], size), B.read(B.rows[ib][0], size)
        if da == db:
            continue
        diffs = []
        for off in range(0, size - size % 4, 4):
            wa, wb = da[off:off + 4], db[off:off + 4]
            if wa == wb:
                continue
            ra = A.resolve(int.from_bytes(wa, "little"))
            rb = B.resolve(int.from_bytes(wb, "little"))
            if ra and rb and ra == rb:
                nptr += 1
                continue
            diffs.append((off, wa.hex(), wb.hex(), ra, rb))
        tail = size % 4
        if tail and da[-tail:] != db[-tail:]:
            diffs.append((size - tail, da[-tail:].hex(), db[-tail:].hex(), None, None))
        if diffs:
            ndiff += len(diffs)
            bad_objs.append(name)
            for d in diffs:
                if shown < a.limit:
                    print(f"  {name}+0x{d[0]:x}: i686 {d[1]} ({d[3]}) x64 {d[2]} ({d[4]})")
                    shown += 1
    print(f"dataparity: {objs} objects, {nbytes} bytes; {nptr} pointer words equal by symbol; "
          f"{ndiff} differing words in {len(bad_objs)} objects")
    if bad_objs:
        print("objects: " + " ".join(bad_objs[:60]) + (" ..." if len(bad_objs) > 60 else ""))
    return 1 if bad_objs else 0


if __name__ == "__main__":
    sys.exit(main())
