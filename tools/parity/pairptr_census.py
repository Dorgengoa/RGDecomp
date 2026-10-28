#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""pairptr_census.py: data words the data layer turned into POINTERS that are really packed
small integers (s16 pairs / byte quads), a link-layout-dependent bug class.

Found 2026-10-24 (BRINGUP-HISTORY "Revelation flashing slot"): the Revelation board sprite
table D_004539F0 (s16 x/y/w/h quads) holds the words 0x00400040 (= 64, 64) and 0x004C008A
(= 138, 76); data2c symbolised the first as `(u32)&DataTableCompareThunk_400040` and the
datareloc stage the second as `data2c_main_bss + 0x3F00A`, so on the host they hold HOST
addresses and the sprite's UVs change with every relink.

Scans game/src/main_data/*.c (or its overrides/src/main_data replacement) for initialiser elements that are not numeric literals (pointer
expressions), reads the retail word at that address from the ELF, and scores it:
  pair   the word's low half is a small signed s16 (|v| < 0x1000) -- true of 1/16 of real
         pointers, of almost every packed (x, y) pair;
  ctx    fraction of the object's NUMERIC words that are packed pairs (high half a small
         NONZERO s16, low half small): >= 0.5 scores 2;
  dens   pointer words / all words <= 0.25 scores 1 (real pointer tables are dense);
  unal   the target is not 4-aligned (1).
Prints rows sorted by suspicion; --all prints every pointer word.  Verdicts need the code's
access width (listing.py: lh/lhu on the table = packed, lw + deref = pointer).
Earlier fixes of the same class: overrides/src/main_data (2026-10-13, every DATARELOC
`main-bss` row; out/render-bringup/tools/mk_datafix_overrides.py).

    python tools/parity/pairptr_census.py [--game game] [--elf ../work/SCUS_974.90] [--all]
"""
from __future__ import annotations

import argparse
import re
import struct
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
DEF = re.compile(r'^(?:const\s+)?(\w+)\s+(\w+)\[(\d+)\]\s+__attribute__\(\(section\("\.data\$rg([0-9A-F]{8})"\)[^;]*?\)\)\s*=\s*\{(.*?)\};',
                 re.S | re.M)


def elf_reader(path):
    b = Path(path).read_bytes()
    phoff, = struct.unpack_from("<I", b, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", b, 0x2A)
    segs = []
    for i in range(phnum):
        _, off, vaddr, _, filesz, _, _, _ = struct.unpack_from("<8I", b, phoff + i * phentsize)
        segs.append((vaddr, off, filesz))

    def word(a):
        for v, o, n in segs:
            if v <= a < v + n:
                return struct.unpack_from("<I", b, o + a - v)[0]
        return None
    return word


def split_top(s):
    out, depth, cur = [], 0, []
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur).strip())
    return out


def small(h):
    return h < 0x1000 or h >= 0xF000


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game", default=str(PORT / "game"))
    ap.add_argument("--elf", default="../work/SCUS_974.90")
    ap.add_argument("--all", action="store_true")
    a = ap.parse_args()
    word = elf_reader(a.elf)
    rows = []
    ovr = PORT / "overrides" / "src" / "main_data"
    for f in sorted((Path(a.game) / "src" / "main_data").glob("*.c")):
        if (ovr / f.name).exists():          # the override is what links
            f = ovr / f.name
        t = f.read_text(errors="replace")
        for m in DEF.finditer(t):
            typ, name, n, base, body = m.group(1), m.group(2), int(m.group(3)), int(m.group(4), 16), m.group(5)
            if typ not in ("u32", "s32"):
                continue
            el = split_top(re.sub(r"/\*.*?\*/", "", body, flags=re.S))
            num = [e for e in el if re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)u?", e)]
            ptr = [(i, e) for i, e in enumerate(el) if e not in num]
            if not ptr:
                continue
            nv = [int(e.rstrip("u"), 0) & 0xFFFFFFFF for e in num]
            # packed-pair evidence: numeric words whose HIGH half is a small NONZERO s16
            # (x/y, w/h pairs); plain small ints (hi == 0) and flags say nothing
            ctx = sum(1 for v in nv if (v >> 16) and small(v >> 16) and small(v & 0xFFFF)) / len(nv) if nv else 0.0
            dens = len(ptr) / len(el)
            for i, e in ptr:
                ad = base + 4 * i
                w = word(ad)
                if w is None:
                    continue
                pair = small(w & 0xFFFF)
                unal = w & 3 != 0
                score = ((2 if pair else 0) + (2 if ctx >= 0.5 and len(nv) >= 3 else 0)
                         + (1 if dens <= 0.25 else 0) + (1 if unal else 0))
                rows.append((score, ad, w, f.name, name, len(el), ctx, e))
    rows.sort(key=lambda r: (-r[0], r[1]))
    shown = 0
    for s, ad, w, fn, name, n, ctx, e in rows:
        if not a.all and s < 4:
            continue
        shown += 1
        print(f"{s} 0x{ad:08X} word=0x{w:08X} ({w & 0xFFFF:#x},{w >> 16:#x}) {name}[{n}] ctx={ctx:.2f} {e[:70]}  [{fn}]")
    print(f"pairptr_census: {len(rows)} pointer words, {shown} shown (score >= 4 unless --all)")


if __name__ == "__main__":
    main()
