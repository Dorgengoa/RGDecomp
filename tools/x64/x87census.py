#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""x87 census of an i686 rg-game (docs/X64-PLAN.md section 0.7): where the i686 build
computes with the x87 unit, whose rounding (control word: round to nearest, the CRT
default) is NOT the guest MXCSR (round toward zero since 2026-10-24).  The x64 build
does every float op in SSE under the MXCSR, so each such site is a place where i686 and
x64 can round differently.

    python tools/x64/x87census.py EXE_I686 [--map MAP] [--dis FILE] [--all]

Disassembles EXE (llvm-objdump; or reads --dis) and, through the link map, reports
  - x87 arithmetic in the port's own objects (fild/fadd/fmul/fdiv/fsqrt/fistp/...;
    plain fld/fstp moves of float/double values are exact and not counted),
  - calls from the port's objects into CRT objects (libucrt / libcpmt / libvcruntime):
    per CRT function the number of call sites and calling objects (e.g. sqrtf =
    libcpmt xfprec = x87 fsqrt + fstps: round to nearest).
--all lists every site instead of the per-object summary.
"""
from __future__ import annotations

import argparse
import bisect
import collections
import re
import subprocess
import sys
from pathlib import Path

OBJDUMP = r"../tools\llvm\bin\llvm-objdump.exe"
ROW = re.compile(r"\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8,16})\s+(?:f\s+)?(?:i\s+)?(\S+)")
INS = re.compile(r"^\s*([0-9a-f]+):\s+(\S+)\s*(.*)$")
# rounding-sensitive x87 ops (moves fld/fst/fstp/fxch/fchs/fabs/fcom are exact)
X87 = re.compile(r"^f(i?add|i?sub|i?subr|i?mul|i?div|i?divr|sqrt|ild|istp|ist|prem1?|scale|2xm1|yl2x|yl2xp1|patan|sin|cos|sincos|ptan|rndint|addp|subp|subrp|mulp|divp|divrp)[a-z]*$")
CRT = ("libucrt", "libcpmt", "libvcruntime", "libcmt", "msvcrt", "ucrt", "oldnames")


def load_map(path: Path):
    rows = []
    for ln in path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = ROW.match(ln)
        if m:
            rows.append((int(m.group(4), 16), m.group(3), m.group(5)))
    rows.sort()
    return rows


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("exe")
    ap.add_argument("--map")
    ap.add_argument("--dis")
    ap.add_argument("--all", action="store_true")
    a = ap.parse_args()
    exe = Path(a.exe)
    rows = load_map(Path(a.map) if a.map else exe.with_suffix(".map"))
    keys = [r[0] for r in rows]

    def where(addr):
        i = bisect.bisect_right(keys, addr) - 1
        return rows[i] if i >= 0 else (0, "?", "?")

    text = Path(a.dis).read_text(errors="replace") if a.dis else subprocess.run(
        [OBJDUMP, "-d", "--no-show-raw-insn", str(exe)], capture_output=True, text=True).stdout
    is_crt = lambda obj: obj.lower().startswith(CRT) or ":" in obj and obj.split(":")[0].lower().startswith(CRT)
    x87 = collections.Counter()
    x87_sites = []
    calls = collections.defaultdict(lambda: [0, set()])
    for ln in text.splitlines():
        m = INS.match(ln)
        if not m:
            continue
        addr = int(m.group(1), 16)
        mn, ops = m.group(2), m.group(3)
        if mn[0] != "f" and mn != "calll" and mn != "callq":
            continue
        _, fn, obj = where(addr)
        if is_crt(obj):
            continue
        if X87.match(mn):
            x87[(obj, fn, mn)] += 1
            x87_sites.append((addr, fn, obj, mn, ops))
        elif mn in ("calll", "callq"):
            t = re.match(r"0x([0-9a-f]+)", ops)
            if not t:
                continue
            ta, tfn, tobj = where(int(t.group(1), 16))
            if is_crt(tobj):
                c = calls[(tfn, tobj)]
                c[0] += 1
                c[1].add(obj)
    print("# x87 arithmetic in port objects:", sum(x87.values()), "instructions,",
          len({k[0] for k in x87}), "objects")
    if a.all:
        for s in x87_sites:
            print(f"X87\t{s[0]:x}\t{s[1]}\t{s[2]}\t{s[3]}\t{s[4]}")
    else:
        per = collections.defaultdict(collections.Counter)
        for (obj, fn, mn), n in x87.items():
            per[(obj, fn)][mn] += n
        for (obj, fn), c in sorted(per.items()):
            print("X87\t%s\t%s\t%s" % (obj, fn, " ".join(f"{k}={v}" for k, v in sorted(c.items()))))
    print("# calls into CRT objects:", len(calls), "functions")
    for (tfn, tobj), (n, objs) in sorted(calls.items(), key=lambda kv: -kv[1][0]):
        ex = ", ".join(sorted(objs)[:4]) + (" .." if len(objs) > 4 else "")
        print(f"CRT\t{tfn}\t{tobj}\t{n} sites\t{len(objs)} objects\t{ex}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
