#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Diff the game state of two rg-game save states taken at the same field by two
DIFFERENT exes (the i686 and the x64 build: docs/X64-PLAN.md section 0.7).

    rg-game ... --save-state F:a.rgstate   (RG_SS=1; each exe, same input)
    python tools/x64/ssdiff.py A.rgstate A_EXE.map B.rgstate B_EXE.map [--max N] [--gap 64]
                               [--sections ram,statics]

Sections compared:
  ram      the game heap allocation, word by word (both are the same size);
  statics  the captured .data/.bss ranges (statics.map), aligned by SYMBOL through each
           exe's link map (the two images lay statics out differently).
Every 32-bit word is normalised before comparing: a word inside the ram section ->
"R+offset", a word inside the exe image -> "symbol+offset" (through that exe's map).
Differing words are grouped into ranges (ram: by offset; statics: by symbol) and printed
with both raw values.  Exit 1 when anything differs.
"""
from __future__ import annotations

import argparse
import bisect
import re
import struct
import sys

ROW = re.compile(r"\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)")
HDR = struct.Struct("<8sII40sIIIIIIIIIII4xQII")  # up to nsect, pad (meta follows); 4x = C alignment of init_fp
SHDR = struct.Struct("<32sIIIIQ")
PAGE = 4096


class Map:
    def __init__(self, path):
        rows = []
        for ln in open(path, encoding="utf-8", errors="replace"):
            m = ROW.match(ln)
            if m:
                rows.append((int(m.group(4), 16), m.group(3)))
        rows.sort()
        # i686 COFF decorates C names with '_' (x64 does not): compare undecorated
        if sum(1 for r in rows if r[1].startswith("_")) > len(rows) // 2:
            rows = [(a, n[1:] if n.startswith("_") else n) for a, n in rows]
        self.keys = [r[0] for r in rows]
        self.rows = rows

    def sym(self, a):
        i = bisect.bisect_right(self.keys, a) - 1
        if i < 0:
            return None, 0
        return self.rows[i][1], a - self.rows[i][0]


def read_state(path):
    d = open(path, "rb").read()
    if d[:8] != b"RGSTATE1":
        sys.exit(f"{path}: not a save state")
    hdr_bytes = struct.unpack_from("<I", d, 12)[0]
    f = HDR.unpack_from(d, 0)
    image_base, size_of_image = f[6], f[5]
    nsect = f[16]
    o = hdr_bytes
    secs = []
    for _ in range(nsect):
        name, addr, size, enc, stored, h = SHDR.unpack_from(d, o)
        o += SHDR.size
        name = name.split(b"\0")[0].decode()
        payload = d[o:o + stored]
        o += stored
        npages = (size + PAGE - 1) // PAGE
        bm = (npages + 7) // 8
        out = bytearray(size)
        p = bm
        for i in range(npages):
            if payload[i // 8] & (1 << (i % 8)):
                n = min(PAGE, size - i * PAGE)
                out[i * PAGE:i * PAGE + n] = payload[p:p + n]
                p += n
        secs.append((name, addr, bytes(out)))
    return {"base": image_base, "size": size_of_image, "secs": secs}


def norm_fn(st, mp, ram_addr, ram_size):
    lo, hi = st["base"], st["base"] + st["size"]

    def norm(v):
        if ram_addr <= v < ram_addr + ram_size:
            return f"R+{v - ram_addr:X}"
        if lo <= v < hi:
            s, off = mp.sym(v)
            return f"{s}+{off:X}" if s else f"img{v - lo:X}"
        return v
    return norm


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("a")
    ap.add_argument("amap")
    ap.add_argument("b")
    ap.add_argument("bmap")
    ap.add_argument("--max", type=int, default=80)
    ap.add_argument("--gap", type=int, default=64)
    ap.add_argument("--sections", default="ram,statics")
    a = ap.parse_args()
    A, B = read_state(a.a), read_state(a.b)
    MA, MB = Map(a.amap), Map(a.bmap)
    sa = {n: (ad, b) for n, ad, b in A["secs"]}
    sb = {n: (ad, b) for n, ad, b in B["secs"]}
    ra, rb = sa["ram"], sb["ram"]
    na = norm_fn(A, MA, ra[0], len(ra[1]))
    nb = norm_fn(B, MB, rb[0], len(rb[1]))
    total = 0
    want = a.sections.split(",")
    if "ram" in want:
        x, y = ra[1], rb[1]
        n = min(len(x), len(y)) // 4
        wx = struct.unpack_from(f"<{n}I", x)
        wy = struct.unpack_from(f"<{n}I", y)
        def same(x, y):
            if x == y or na(x) == nb(y):
                return True
            # a host image pointer whose low byte(s) a byte store overwrote (strcpy of
            # an empty name over a vptr): the two exes' images differ, the bytes agree
            for m in (0xFF, 0xFFFF):
                if (x & m) == (y & m) and not isinstance(na(x & ~m), int) and not isinstance(nb(y & ~m), int):
                    return True
            return False
        diffs = [i for i in range(n) if wx[i] != wy[i] and not same(wx[i], wy[i])]
        ranges = []
        for i in diffs:
            if ranges and (i - ranges[-1][1]) * 4 <= a.gap:
                ranges[-1][1] = i
                ranges[-1][2] += 1
            else:
                ranges.append([i, i, 1])
        total += len(diffs)
        print(f"ram: {len(x)} bytes (A at {ra[0]:#x}, B at {rb[0]:#x}); {len(diffs)} words differ in {len(ranges)} ranges")
        for lo, hi, c in ranges[:a.max]:
            ex = " ".join(f"{wx[i]:08x}/{wy[i]:08x}" for i in range(lo, min(hi + 1, lo + 4)))
            print(f"  R+{lo * 4:07X}..+{hi * 4 + 4:07X} ({c} words): {ex}")
    if "statics" in want:
        def statics(s, mp):
            """{symbol: bytes} for every map symbol inside the captured ranges, each cut at
            the next symbol (so a 2-byte object is compared as 2 bytes)"""
            tab = s["statics.map"][1]
            nr = struct.unpack_from("<I", tab, 0)[0]
            data = s["statics"][1]
            out = {}
            o = 0
            for i in range(nr):
                lo, hi = struct.unpack_from("<II", tab, 4 + 8 * i)
                j = bisect.bisect_left(mp.keys, lo)
                while j < len(mp.keys) and mp.keys[j] < hi:
                    a0 = mp.keys[j]
                    a1 = mp.keys[j + 1] if j + 1 < len(mp.keys) else hi
                    a1 = min(a1, hi)
                    if a1 > a0:
                        out[mp.rows[j][1]] = data[o + (a0 - lo):o + (a1 - lo)]
                    j += 1
                o += hi - lo
            return out
        PA, PB = statics(sa, MA), statics(sb, MB)
        keys = [k for k in PA if k in PB]
        bad = {}
        for k in keys:
            x, y = PA[k], PB[k]
            n = min(len(x), len(y))
            for off in range(0, n, 4):
                wx, wy = x[off:min(off + 4, n)], y[off:min(off + 4, n)]
                if wx == wy:
                    continue
                if len(wx) == 4:
                    vx, vy = struct.unpack("<I", wx)[0], struct.unpack("<I", wy)[0]
                    if na(vx) == nb(vy):
                        continue
                else:
                    vx, vy = int.from_bytes(wx, "little"), int.from_bytes(wy, "little")
                bad.setdefault(k, []).append((off, vx, vy))
        nbad = sum(len(v) for v in bad.values())
        total += nbad
        print(f"statics: {len(keys)} symbols aligned (A {len(PA)}, B {len(PB)}); "
              f"{nbad} words differ in {len(bad)} symbols")
        for s_, lst in list(bad.items())[:a.max]:
            ex = " ".join(f"+{o:X}:{x:08x}/{y:08x}" for o, x, y in sorted(lst)[:4])
            print(f"  {s_} ({len(lst)} words): {ex}")
    return 1 if total else 0


if __name__ == "__main__":
    sys.exit(main())
