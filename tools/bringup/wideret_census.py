#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Wide-return census: game definitions typed with a 4-byte integer return whose retail
$v0 at `jr $31` is a 64-bit value (asmflow.wide_flow taint: `ld`/`lq`/`dsll32` results,
8-byte call results, copies and logical ops), iterated to a fixpoint (a function found
wide makes its callers' $v0 wide too).  On the EE mwcc never narrows a register for a C
conversion to 4 bytes, so `s32 r; r |= F64();  return r;` returns all 64 bits; the port's
s32 cuts the high word (play-test 2: the ActCfg *pending* prmt / cmnd mask chain dropped
bits 32-63, so a SQUARE / CROSS press during an action's recovery was never buffered).

    python tools/bringup/wideret_census.py [--tsv out/bringup-checkpoint/wideret.tsv]

Prints one row per candidate: name, C return type, file, the labels that reach $v0.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
PORT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(PORT / "tools" / "stages"))
import listings  # noqa: E402
import asmflow  # noqa: E402

WIDE_T = r"(?:long\s+long|unsigned\s+long\s+long|s64|u64)"
NARROW_T = r"(?:s32|u32|int|unsigned\s+int|unsigned|signed\s+int|long|unsigned\s+long)"
HEAD = re.compile(r"^(?:extern\s+\"C\"\s+)?(?:static\s+)?(?:inline\s+)?(?P<t>" + WIDE_T + "|" + NARROW_T +
                  r")\s+(?P<n>[A-Za-z_]\w*_[0-9a-f]{6})\s*\(", re.M)


def c_returns():
    out = {}
    for p in (PORT / "game" / "src").rglob("*"):
        if p.suffix not in (".c", ".cpp"):
            continue
        s = p.read_text(encoding="utf-8", errors="replace")
        for m in HEAD.finditer(s):
            k = m.end()
            depth, i = 1, k
            while i < len(s) and depth:
                depth += {"(": 1, ")": -1}.get(s[i], 0)
                i += 1
            if s[i:i + 40].lstrip().startswith("{"):
                out[m.group("n")] = (re.sub(r"\s+", " ", m.group("t")), p.relative_to(PORT).as_posix())
    return out


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--tsv")
    a = ap.parse_args(argv)
    rets = c_returns()
    wide = {n for n, (t, _) in rets.items() if re.fullmatch(WIDE_T, t)}
    lst = {fn: tx for img, fn, tx in listings.all_listings()}
    cfgs = {}
    found = {}
    changed = True
    rounds = 0
    while changed and rounds < 10:
        changed = False
        rounds += 1
        for fn, (t, rel) in rets.items():
            if fn in wide or fn not in lst:
                continue
            if fn not in cfgs:
                try:
                    cfgs[fn] = asmflow.CFG(asmflow.parse_listing(lst[fn])[0])
                except Exception:   # noqa: BLE001
                    cfgs[fn] = None
            cfg = cfgs[fn]
            if cfg is None:
                continue
            ev = asmflow.wide_flow(cfg, {}, gen_ret=lambda tgt: f"call:{tgt}" if tgt in wide else None)
            labs = set()
            for e in ev:
                if e[0] == "ret":
                    labs |= set(e[2])
            if labs:
                wide.add(fn)
                found[fn] = (t, rel, sorted(labs))
                changed = True
    rows = [f"{fn}\t{t}\t{rel}\t{','.join(l)}" for fn, (t, rel, l) in sorted(found.items())]
    print(f"wideret: {len(rows)} 4-byte definitions return a 64-bit $v0 ({rounds} rounds)")
    for r in rows:
        print(r)
    if a.tsv:
        Path(a.tsv).write_text("name\tc_type\tfile\tlabels\n" + "\n".join(rows) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
