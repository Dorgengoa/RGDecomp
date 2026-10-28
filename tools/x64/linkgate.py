#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Linker launcher for the x64 build (CMAKE_<LANG>_LINKER_LAUNCHER, set by
cmake/x64.cmake): runs the link command it is given, then checks the PE
headers of the executable it wrote with tools/x64/pecheck.py.  A link without
the low-address flags (/LARGEADDRESSAWARE:NO /DYNAMICBASE:NO
/HIGHENTROPYVA:NO, a base below 2 GB) FAILS and its exe is deleted: lld-link
silently writes a crashing exe otherwise (docs/X64-PLAN.md section 4, R2).

    python tools/x64/linkgate.py <link command ...>
"""
from __future__ import annotations

import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import pecheck  # noqa: E402


def outputs(cmd: list[str]) -> list[str]:
    out = []
    args = list(cmd)
    # response files (@file): CMake uses them for long object lists
    exp = []
    for a in args:
        if a.startswith("@") and Path(a[1:]).is_file():
            exp += Path(a[1:]).read_text(encoding="utf-8", errors="replace").split()
        else:
            exp.append(a)
    for i, a in enumerate(exp):
        if a == "-o" and i + 1 < len(exp):
            out.append(exp[i + 1])
        elif a.startswith("-o") and len(a) > 2 and not a.startswith("-O"):
            out.append(a[2:])
        elif a.lower().startswith(("/out:", "-out:")):
            out.append(a[5:])
    return [o.strip('"') for o in out if o.strip('"').lower().endswith(".exe")]


def main(argv: list[str]) -> int:
    if not argv:
        print(__doc__)
        return 2
    rc = subprocess.call(argv)
    if rc != 0:
        return rc
    exes = outputs(argv)
    if not exes:
        return 0
    return pecheck.main(exes + ["--delete-on-fail", "--quiet"])


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
