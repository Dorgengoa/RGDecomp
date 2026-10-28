#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Walk the game's malloc heap (src/crt/crt_heap.c: newlib chunks, 4-byte prev_size /
size|PREV_INUSE headers, 16-byte alignment) in the ram section of save states and
compare two exes' chunk sequences (docs/X64-PLAN.md section 0.7): the first chunk whose
size differs is the allocation that moved everything after it.

    python tools/x64/heapwalk.py A.rgstate B.rgstate [--around N] [--start OFF]
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ssdiff import read_state  # noqa: E402


def walk(ram: bytes, start: int):
    out = []
    o = start
    while o + 8 <= len(ram):
        size = struct.unpack_from("<I", ram, o + 4)[0]
        sz = size & ~7
        if sz < 16 or o + sz > len(ram):
            out.append((o, size, "end"))
            break
        out.append((o, size, ""))
        o += sz
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--around", type=int, default=6)
    ap.add_argument("--start", type=lambda s: int(s, 0))
    a = ap.parse_args()
    ra = {n: b for n, ad, b in read_state(a.a)["secs"]}["ram"]
    rb = {n: b for n, ad, b in read_state(a.b)["secs"]}["ram"]
    start = a.start if a.start is not None else ((0x200 + 8 + 15) & ~15) - 8
    wa, wb = walk(ra, start), walk(rb, start)
    print(f"chunks: A {len(wa)}, B {len(wb)} (start R+{start:X})")
    for i, (x, y) in enumerate(zip(wa, wb)):
        if x[:2] != y[:2]:
            print(f"first differing chunk #{i}:")
            for j in range(max(0, i - a.around), min(len(wa), len(wb), i + a.around)):
                ca, cb = wa[j], wb[j]
                mark = "  <--" if ca[:2] != cb[:2] else ""
                print(f"  #{j}: A R+{ca[0]:07X} size {ca[1]:#x}   B R+{cb[0]:07X} size {cb[1]:#x}{mark}")
            return 1
    print("chunk sequences equal")
    return 0


if __name__ == "__main__":
    sys.exit(main())
