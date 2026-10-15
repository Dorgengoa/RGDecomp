#!/usr/bin/env python3
# TITLE session namespace (t_*).
"""Slot-SPAN override for title, wrapped around the shared `otextsplit`.

WHY THIS IS A WRAPPER AND NOT A COPY.  `otextsplit.py` is shared by all five
overlay link paths; copying its cut rule into a sixth file is how two copies
drift, which this tree has already paid for twice (the copied screen in
factory, the copied scorer that kept another overlay's context).  Everything
here delegates -- the only thing added is the size override, and the shared
module is monkey-patched only for the duration of one `split()` call inside
this process.

WHAT THE OVERRIDE IS FOR.  `0x004EF940`-`0x004EFB8C` is ONE multi-entry
function: a single prologue, a dense `switch` through `jtbl_004F1600`, ten
case bodies and one shared tail and epilogue.  Ghidra listed each jump-table
target as a separate function, so `config/title.symbols.txt` carries ELEVEN
`size:` attributes across it and the splitter would cut eleven slots.  One
compiled unit fills all eleven, so `title_TitleOptionsCursorMoveCb_4ef940`'s slot is widened to
the whole span and the ten interior `glabel`s fall inside the cut.

★ The ten swallowed labels are still REFERENCED, by `jtbl_004F1600` in the
overlay's data assembly.  Nothing extra is needed for them: `olink.unresolved`
already reads an absolute address off the tail of a symbol's own name, and
`title_FUN_004ef990` ends in eight hex digits.  The link resolves all ten that
way, which is the same mechanism the split already relies on for splat's
`alabel` locals.
"""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import otextsplit                                            # noqa: E402

# overlay -> {symbol: slot size in bytes}
SPAN = {
    "title": {
        # 0x004EF940 .. 0x004EFB8C inclusive of the shared epilogue.
        "title_TitleOptionsCursorMoveCb_4ef940": 0x250,
    },
}

# The symbols each span swallows, kept explicit so a reader can see that they
# are deliberately absent from the link's own text rather than lost.
COVERED = {
    "title": {
        "title_TitleOptionsCursorMoveCb_4ef940": [
            "title_FUN_004ef990", "title_FUN_004ef9c0", "title_FUN_004ef9ec",
            "title_FUN_004efa14", "title_FUN_004efa40", "title_FUN_004efa6c",
            "title_FUN_004efa98", "title_FUN_004efac8", "title_FUN_004efaf8",
            "title_FUN_004efb24",
        ],
    },
}

load_text = otextsplit.load_text
real_size = otextsplit.real_size
# Bind the ORIGINAL before anything can patch the attribute: split() swaps
# otextsplit.symbol_table for this wrapper, and a wrapper that re-reads the
# attribute it replaced calls itself forever.
_symbol_table = otextsplit.symbol_table


def symbol_table(name: str) -> dict:
    t = dict(_symbol_table(name))
    for sym, size in SPAN.get(name, {}).items():
        if sym in t:
            t[sym] = (t[sym][0], size)
    return t


def covers(name: str, sym: str) -> list:
    return COVERED.get(name, {}).get(sym, [])


def split(name: str, symbols: list, out_dir: Path, cunit_slots: bool = True):
    original = otextsplit.symbol_table
    otextsplit.symbol_table = symbol_table
    try:
        return otextsplit.split(name, symbols, out_dir, cunit_slots)
    finally:
        otextsplit.symbol_table = original
