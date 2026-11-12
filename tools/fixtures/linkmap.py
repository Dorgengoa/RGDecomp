#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""The exe's link map, both formats (docs/TEST-FIXTURES.md "Scenarios", "Rosencaster and Linux").

One reader for the fixture tools that look up globals / functions by name (autobattle.py,
areaplace.py, soak.py, fdump.py, cardwhere.py via tools/trace/navprobe.py):

  MSVC /MAP (rg-game.exe -> rg-game.map):
      ' 0003:000xxxxx       _D_004837C0      0000000000883bc0 ...'   (Rva+Base = VA)
      i686 C names carry a leading '_', x64 names do not.
  lld -Map (Linux rg-game -> rg-game.map, beside the exe):
      '     VMA      LMA     Size Align Out     In      Symbol'       (header)
      '  99d440   99d440     11bc     1                 PlayerControlUpdateMaybe_1fc4a0'
      symbol rows start in the header's "Symbol" column; output / input section rows start
      further left.

Both link at 0x400000 (/DYNAMICBASE:NO; Linux -no-pie), so RVA = VA - 0x400000.

    python tools/fixtures/linkmap.py EXE_OR_MAP NAME [NAME ..]      # print VA / RVA of names
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

IMAGE_BASE = 0x400000
_MSVC = re.compile(r"\s*(000[0-9a-f]):[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8,16})\s+")
_LLD_NUMS = re.compile(r"\s*([0-9a-f]+)\s+[0-9a-f]+\s+[0-9a-f]+\s+\d+\s*$")
_LLD_OSEC = re.compile(r"\s*[0-9a-f]+\s+[0-9a-f]+\s+[0-9a-f]+\s+\d+ (\S+)")

_cache: dict = {}


def map_path(exe) -> Path:
    """rg-game.exe -> rg-game.map (MSVC); rg-game (ELF, no suffix) -> rg-game.map (lld);
    a .map path is returned as is."""
    exe = Path(exe)
    if exe.suffix.lower() == ".map":
        return exe
    return exe.with_suffix(".map") if exe.suffix.lower() == ".exe" else exe.with_name(exe.name + ".map")


def symbols(exe, msvc_sections: str | None = None) -> list[tuple[int, str, str]]:
    """[(VA, raw name, section)] in map order.  MSVC: section = '0001'.. ('0003' = .data);
    msvc_sections ('13' = 0001 + 0003) keeps only those.  lld: section = the output section
    (.text, .data, ..); every symbol row, local symbols included."""
    mp = map_path(exe)
    key = (str(mp), mp.stat().st_mtime_ns, msvc_sections)
    if key in _cache:
        return _cache[key]
    out = []
    sym_col = None
    osec = ""
    with open(mp, encoding="latin-1") as f:
        for n, line in enumerate(f):
            line = line.rstrip("\r\n")
            if n < 4 and sym_col is None and "VMA" in line and line.rstrip().endswith("Symbol"):
                sym_col = line.index("Symbol")
                continue
            if sym_col is not None:
                if (len(line) > sym_col and line[sym_col] != " " and line[sym_col - 1] == " "
                        and _LLD_NUMS.match(line[:sym_col])):
                    out.append((int(line[:sym_col].split()[0], 16), line[sym_col:].rstrip(), osec))
                    continue
                m = _LLD_OSEC.match(line)       # output-section row (input rows are indented)
                if m:
                    osec = m.group(1)
                continue
            m = _MSVC.match(line)
            if m and (msvc_sections is None or m.group(1)[-1] in msvc_sections):
                out.append((int(m.group(3), 16), m.group(2), m.group(1)))
    _cache[key] = out
    return out


def _norm(name: str) -> str:
    """MSVC i686 C decoration: one leading '_' (x64 and lld names have none)."""
    return name[1:] if name.startswith("_") else name


def sym_vas(exe, names, tool: str = "linkmap") -> dict:
    """{name: VA} for the given undecorated names (first definition in map order wins).
    A missing name -> SystemExit naming the map."""
    want = set(names)
    out = {}
    for va, raw, _ in symbols(exe):
        for cand in (raw, _norm(raw)):
            if cand in want and cand not in out:
                out[cand] = va
                break
    missing = want - set(out)
    if missing:
        raise SystemExit(f"{tool}: {', '.join(sorted(missing))} not in {map_path(exe)}")
    return out


def sym_rvas(exe, names, tool: str = "linkmap") -> dict:
    return {k: v - IMAGE_BASE for k, v in sym_vas(exe, names, tool).items()}


def sym_rva(exe, name: str, tool: str = "linkmap") -> int:
    return sym_rvas(exe, [name], tool)[name]


def main(argv=None) -> int:
    argv = sys.argv[1:] if argv is None else argv
    if len(argv) < 2:
        print(__doc__)
        return 2
    for k, v in sym_vas(argv[0], argv[1:]).items():
        print(f"{k}\tVA 0x{v:X}\tRVA 0x{v - IMAGE_BASE:X}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
