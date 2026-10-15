#!/usr/bin/env python3
"""Split an OVERLAY's text assembly so a C unit can take one slot.

Overlay twin of scripts/textsplit.py.  Same cut rule, parameterised on the
overlay name:

    asm/overlays/<n>/<n>.s      the text unit splat wrote
    config/<n>.symbols.txt      name = addr; // type:func size:0x..

This is a NEW FILE on purpose.  scripts/textsplit.py and scripts/link.py are
the main image's acceptance path; a second session grinding main units may be
running them at any moment, so nothing here edits them.

The cut rule is copied deliberately, not re-derived:

  * a slot ends at the function's LAST INSTRUCTION.  The 16-byte padding after
    it, the blank line and the next glabel all belong to the FOLLOWING part.
    gas gives .text sh_addralign 4 and mwcc gives it 16, so with ALIGNALL(1)
    the only alignment mwld ever applies is the C object's own -- and olink.py
    lowers that to what the address actually needs.  Nothing in the layout is
    then left to linker discretion.

  * do NOT spell the slot's end as index[vram + size].  For a function with no
    padding after it that address is the NEXT function's first instruction, so
    the slot swallows the next glabel and the symbol vanishes from the link.
    Use index[vram + size - 4] + 1, and test overlap on ADDRESSES.
"""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

LINE_RE = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/")
SYM_RE = re.compile(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$")

JR_RA = 0x03E00008
J_OPCODE = 2

PROLOGUE = """.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

"""


def text_path(name: str) -> Path:
    return ROOT / "asm" / "overlays" / name / f"{name}.s"


def symbols_path(name: str) -> Path:
    return ROOT / "config" / f"{name}.symbols.txt"


def symbol_table(name: str) -> dict:
    """symbol -> (vram, size) for every func line in the overlay's symbols."""
    out = {}
    for ln in symbols_path(name).read_text(errors="replace").splitlines():
        m = SYM_RE.match(ln)
        if not m:
            continue
        attrs = m.group(3)
        size = re.search(r"size:(0x[0-9A-Fa-f]+)", attrs)
        out[m.group(1)] = (int(m.group(2), 16),
                           int(size.group(1), 16) if size else None)
    return out


def load_text(name: str) -> tuple:
    """lines, vram -> line index, vram -> instruction word.

    The listing prints the word byte-reversed (`0800E003` is 0x03E00008), so
    read it as little-endian, which is what it literally is in the file.
    """
    lines = text_path(name).read_text(errors="replace").splitlines()
    index, words = {}, {}
    for i, ln in enumerate(lines):
        m = LINE_RE.match(ln)
        if m:
            v = int(m.group(1), 16)
            index[v] = i
            words[v] = int.from_bytes(bytes.fromhex(m.group(2)), "little")
    return lines, index, words


def real_size(vram: int, size: int, words: dict) -> int:
    """The recorded size minus any TRAILING PADDING it swallowed.

    The overlay symbol files have TWO different size provenances, measured
    2026-08-24 over all five non-trivial overlays:

        title                     sizes CLAMPED to the next symbol -- the pad
                                  is INSIDE the size, 74 of 107 functions
        insmenu/normal/factory/   the pad lies in the GAPS between symbols,
        insect                    0 of 2,000 affected

    So a splitter that trusts `size:` cuts 74 of title's 107 slots too long,
    the compiled object comes out shorter than the slot, and link.py's length
    guard reads it as "the structure is missing or doubled" -- the same false
    `len` verdict `scripts/padsize.py` exists to stop in the main image.  This
    trims locally instead of rewriting a shared symbols file.

    The rule is padsize.py's, and it scans FORWARD on purpose: walking BACK
    over zero words consumes the `jr $31` DELAY-SLOT nop and then misreads the
    instruction before it, which is the documented trap that manufactured a
    clean-looking bucket of false boundaries the first time it was tried.
    Find the LAST terminator, keep it and its delay slot, and only call the
    remainder padding if every word of it is zero.
    """
    end = vram + size
    last = None
    for v in range(vram, end, 4):
        w = words.get(v)
        if w is None:
            return size
        if w == JR_RA or (w >> 26) == J_OPCODE:
            last = v
    if last is None:
        return size
    real = min(last + 8, end)
    tail = [words.get(v) for v in range(real, end, 4)]
    if tail and all(t == 0 for t in tail):
        return real - vram
    return size


def cut_points(name, symbols, table, index, lines, words) -> list:
    cuts = []
    for s in symbols:
        if s not in table:
            raise SystemExit(f"otextsplit: {s} is not in {symbols_path(name).name}")
        vram, size = table[s]
        if size is None:
            raise SystemExit(f"otextsplit: {s} has no size: attribute")
        trimmed = real_size(vram, size, words)
        if trimmed != size:
            print(f"otextsplit: {s} size 0x{size:X} includes 0x{size - trimmed:X} "
                  f"bytes of trailing padding -- slot is 0x{trimmed:X}")
            size = trimmed
        if vram % 4:
            raise SystemExit(f"otextsplit: {s} at 0x{vram:08X} is not 4-aligned")
        if vram not in index:
            raise SystemExit(f"otextsplit: no line for {s} at 0x{vram:08X}")
        last = index.get(vram + size - 4)
        if last is None:
            raise SystemExit(f"otextsplit: no line at 0x{vram + size - 4:08X} "
                             f"(last instruction of {s})")
        try:
            first = lines.index(f"glabel {s}", max(0, index[vram] - 8), index[vram])
        except ValueError:
            raise SystemExit(f"otextsplit: no `glabel {s}` above 0x{vram:08X}")
        cuts.append((s, vram, size, first, last + 1))
    cuts.sort(key=lambda c: c[1])
    for a, b in zip(cuts, cuts[1:]):
        if a[1] + a[2] > b[1]:
            raise SystemExit(f"otextsplit: {a[0]} and {b[0]} overlap")
    return cuts


def split(name: str, symbols: list, out_dir: Path,
          cunit_slots: bool = True) -> list:
    """Write the part files.  Returns the ordered (object, kind) list.

    cunit_slots=False writes the function's own assembly into its slot -- the
    control arm that proves the splitting itself moves no bytes.
    """
    lines, index, words = load_text(name)
    table = symbol_table(name)
    cuts = cut_points(name, symbols, table, index, lines, words)

    out_dir.mkdir(parents=True, exist_ok=True)
    order = []
    pos = 0
    part = 0

    def emit_part(body: list) -> None:
        nonlocal part
        pname = f"{name}_text_{part:03d}"
        (out_dir / f"{pname}.s").write_text(PROLOGUE + "\n".join(body) + "\n")
        order.append((pname, "asm"))
        part += 1

    for sym, vram, size, first, end in cuts:
        emit_part(lines[pos:first])
        if cunit_slots:
            order.append((sym, "c"))
        else:
            (out_dir / f"{sym}_asm.s").write_text(
                PROLOGUE + "\n".join(lines[first:end]) + "\n")
            order.append((f"{sym}_asm", "asm"))
        pos = end
    emit_part(lines[pos:])
    return order


if __name__ == "__main__":
    import sys
    n = sys.argv[1]
    for nm, kind in split(n, sys.argv[2:], ROOT / "build" / "overlay-c" / "parts"):
        print(f"{kind:4} {nm}")
