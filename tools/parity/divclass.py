#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""divclass.py: classify the first divergences of a parity sweep (sweep.py OUT) by kind.

    python tools/parity/divclass.py OUT [--ulps 4]

Reads OUT/<scenario>/compare.txt (the "frame N (...) OBJ: field port/retail, ..." lines: the
first divergence of every object) and puts each field into a class:
  ulp      float, |port - retail| <= --ulps units in the last place (EE rounding: add / sub /
           div / libm; the known open class, docs/TEST-FIXTURES.md "Retail parity")
  float    float, further apart (a grown ulp difference or a different code path)
  int      integer / flag / hex field (logic: collision flags, action state, command masks)
  rng      the newlib RNG state
  timing   frametime (retail's long frames: loads, menu opening; not a game-logic divergence)
`after-rng` marks lines compare.txt prints after the RNG has already diverged (downstream).
Prints one row per scenario: first frame per class (and the field), then the totals.
"""
from __future__ import annotations

import argparse
import re
import struct
from pathlib import Path

LINE = re.compile(r"^  frame +(\d+) \([^)]*\) (\w+): (.*?)( \(after rng\))?$")


def f2i(x):
    i = struct.unpack("<i", struct.pack("<f", x))[0]
    return i if i >= 0 else -(i & 0x7FFFFFFF)


def classify(name, a, b, ulps):
    if name == "rng":
        return "rng"
    if name == "frametime":
        return "timing"
    try:
        if a.lower().startswith("0x") or b.lower().startswith("0x"):
            return "int"
        if re.fullmatch(r"-?\d+", a) and re.fullmatch(r"-?\d+", b):
            return "int"
        fa, fb = float(a), float(b)
    except ValueError:
        return "int"
    return "ulp" if abs(f2i(fa) - f2i(fb)) <= ulps else "float"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("out")
    ap.add_argument("--ulps", type=int, default=4)
    a = ap.parse_args()
    tot = {}
    for d in sorted(p for p in Path(a.out).iterdir() if (p / "compare.txt").exists()):
        first = {}
        for ln in (d / "compare.txt").read_text(encoding="utf-8", errors="replace").splitlines():
            m = LINE.match(ln)
            if not m:
                continue
            fr, obj, rest, after = int(m.group(1)), m.group(2), m.group(3), bool(m.group(4))
            rest = re.sub(r" \(\+\d+ more\)$", "", rest)
            for item in rest.split(", "):
                mm = re.match(r"(\w+) (\S+)/(\S+)$", item)
                if not mm:
                    continue
                c = classify(mm.group(1), mm.group(2), mm.group(3), a.ulps)
                tot[c] = tot.get(c, 0) + 1
                if c not in first:
                    first[c] = f"{fr}{'*' if after else ''} {obj}.{mm.group(1)} {mm.group(2)}/{mm.group(3)}"
        print(f"{d.name:22s} " + " | ".join(f"{k}: {first[k]}" for k in ("ulp", "float", "int", "rng", "timing") if k in first))
    print("totals (first-divergence fields): " + ", ".join(f"{k} {v}" for k, v in sorted(tot.items())))
    print("(* = after the rng diverged)")


if __name__ == "__main__":
    main()
