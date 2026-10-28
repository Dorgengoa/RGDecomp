#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Symbolise an rg-game crash report (stderr "rg-game: EXCEPTION ..." block, or the
rg-game-crash.txt the crash handler writes beside the saves) with the exe's link map.

    python tools/native/crashsym.py MAP [LOG]      (LOG default: stdin)

Prints the faulting function (eip rva) and every "stack words in the image" rva that falls in
a function (return-address candidates: the call chain, plus stale words; read top-down).
MAP = the rg-game.map of the SAME build (build dir, or out/playtest build's
build/pt<TAG>-i686/rg-game.map).
"""
from __future__ import annotations

import bisect
import re
import sys


def load_map(path: str):
    syms = []
    for line in open(path, encoding="latin-1"):
        m = re.match(r"\s*0001:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8,16})\s+\S*\s*(\S*)", line)
        if m:
            syms.append((int(m.group(2), 16), m.group(1), m.group(3)))
    syms.sort()
    return syms


def name(syms, keys, va: int) -> str:
    i = bisect.bisect_right(keys, va) - 1
    if i < 0:
        return "?"
    a, n, obj = syms[i]
    return f"{n} + 0x{va - a:X}  ({obj})" if obj else f"{n} + 0x{va - a:X}"


def main(argv=None) -> int:
    argv = sys.argv[1:] if argv is None else argv
    if not argv:
        print(__doc__)
        return 2
    syms = load_map(argv[0])
    keys = [s[0] for s in syms]
    txt = open(argv[1], encoding="utf-8", errors="replace").read() if len(argv) > 1 else sys.stdin.read()
    base = 0x400000
    m = re.search(r"image base 0x([0-9A-Fa-f]+), rva 0x([0-9A-Fa-f]+)", txt)
    if m:
        base = int(m.group(1), 16)
        print(f"fault: rva 0x{int(m.group(2), 16):X} = {name(syms, keys, 0x400000 + int(m.group(2), 16))}")
    m = re.search(r"stack words in the image \(rva\):([0-9A-Fa-f\s]+)", txt)
    if m:
        for w in m.group(1).split():
            rva = int(w, 16)
            print(f"  {w}  {name(syms, keys, 0x400000 + rva)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
