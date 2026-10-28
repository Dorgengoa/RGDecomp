#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""s64param_census.py [GAME_SRC]: definitions taking an 8-byte integer BY VALUE that a data
table (vtable / command table) points at.

On the EE every 32-bit value sits sign-extended in a 64-bit GPR, so a callee declared with an
s64 parameter sees the right value even when its callers think in 32 bits.  On i686 a caller
that passes 4 bytes (a VCM slot thunk typed `(void *, s32)`, a `rgp_a1..a3` forward) leaves
the parameter's high word to a stale stack slot.  A definition is only at risk if it reads
the high word (a full compare / shift); one that casts the parameter down to s16/s32 is fine.
Fixed so far: CharaStatusTimeLeft_3b6d00 (override, 2026-10-27: boss monograph platforms
vanished at once).  Prints: in-table flag, function, wide parameter indexes, file, override.
"""
import re
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
root = Path(sys.argv[1]) if len(sys.argv) > 1 else PORT / "game" / "src"
ov = PORT / "overrides" / "src"
data = "".join(p.read_text(errors="replace") for p in (root / "main_data").glob("data2c_*.c"))
in_table = set(re.findall(r"\(u32\)&(\w+)", data))
defn = re.compile(r"^(?:extern \"C\" )?[\w \*]+?\b(\w+_[0-9a-f]{6})\s*\(([^)]*)\)\s*\{", re.M)
wide = re.compile(r"(?:s64|u64|(?:un)?signed long long|long long)\b(?![^,]*\*)")
rows = []
for p in root.rglob("*.c*"):
    if "main_data" in p.parts:
        continue
    q = ov / p.relative_to(root)
    t = (q if q.exists() else p).read_text(errors="replace")
    for m in defn.finditer(t):
        ps = [x.strip() for x in m.group(2).split(",")]
        w = [i for i, x in enumerate(ps) if wide.match(x)]
        if w:
            rows.append((m.group(1) in in_table, m.group(1), w, p.relative_to(root).as_posix(), q.exists()))
rows.sort(key=lambda r: (not r[0], r[1]))
for r in rows:
    print("table" if r[0] else "-", r[1], ",".join(map(str, r[2])), r[3], "override" if r[4] else "", sep="\t")
print(f"{len(rows)} definitions with by-value 8-byte int parameters, "
      f"{sum(r[0] for r in rows)} reached from data tables", file=sys.stderr)
