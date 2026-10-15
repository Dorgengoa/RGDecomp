#!/usr/bin/env python3
"""Split asm/main.s into several text objects so a C unit can take one slot.

The whole main .text is one assembly file. To put a COMPILED function into the
byte-identical link, the assembly around it has to be cut out and the compiled
object placed at exactly that address -- which means the link stops being one
text object and becomes a list of them, in address order.

Boundaries are chosen so that every part starts on the address a function
starts on, and the trailing 16-byte padding after a function belongs to the
part that FOLLOWS it. That matters: gas gives .text sh_addralign 4, mwcc gives
it 16, so the only alignment mwld ever has to apply is the C unit's own -- and
link.py lowers that to what the function's address actually needs before the
link, because a library function is only 8-aligned. Nothing in the layout then depends on
what the linker decides to pad.
"""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MAIN_S = ROOT / "asm" / "main.s"
SYMBOLS = ROOT / "config" / "main.symbols.txt"

# "    /* 04A310 0014A190 0000A678 */  lq   $6, 0x0($5)"
LINE_RE = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8})(?: [0-9A-F]{8})? \*/")
SYM_RE = re.compile(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$")

PROLOGUE = """.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

"""


def symbol_table() -> dict:
    """name -> (vram, size) for every func line in config/main.symbols.txt."""
    out = {}
    for ln in SYMBOLS.read_text().splitlines():
        m = SYM_RE.match(ln)
        if not m:
            continue
        attrs = m.group(3)
        size = re.search(r"size:(0x[0-9A-Fa-f]+)", attrs)
        out[m.group(1)] = (int(m.group(2), 16),
                           int(size.group(1), 16) if size else None)
    return out


def load_main() -> tuple:
    """The lines of asm/main.s and a vram -> line-index map over them."""
    lines = MAIN_S.read_text().splitlines()
    index = {}
    for i, ln in enumerate(lines):
        marker = re.match(r"^# DATA2C (0x[0-9A-Fa-f]+) (0x[0-9A-Fa-f]+) (0x[0-9A-Fa-f]+)", ln)
        if marker:
            address, size = int(marker[1], 16), int(marker[2], 16)
            index[address] = i
            index[int(marker[3], 16)] = i
        m = LINE_RE.match(ln)
        if m:
            index[int(m.group(1), 16)] = i
    return lines, index


def cut_points(symbols: list, table: dict, index: dict, lines: list) -> list:
    """[(symbol, vram, size, first_line, end_line)] in address order.

    first_line is the `glabel <symbol>` line; end_line is ONE PAST the last
    instruction line of the function. Everything between end_line and the next
    function's glabel -- the blank line, the 16-byte padding -- therefore falls
    to the part that FOLLOWS, which is the point: mwcc's object stops at the
    last instruction and the padding has to come from somewhere that is not
    linker discretion.

    ⚠ Do NOT spell end_line as `index[vram + size]`. For a function with no
    padding after it that address is the NEXT function's first instruction, so
    the slot would swallow the next function's `glabel` line and the link would
    lose the symbol.
    """
    cuts = []
    for s in symbols:
        if s not in table:
            raise SystemExit(f"textsplit: {s} is not in config/main.symbols.txt")
        vram, size = table[s]
        if size is None:
            raise SystemExit(f"textsplit: {s} has no size: attribute")
        # The real requirement is 4 (a MIPS instruction), not 16. mwcc gives
        # .text sh_addralign 16, so an 8-aligned function used to be refused
        # here -- mwld would have bumped its slot to the next 16 boundary and
        # shifted every byte after it. link.py now lowers the compiled
        # object's .text alignment to what the function's own address
        # actually needs, so only 4 is left to enforce.
        # ⚠ This is a LIBRARY-CODE case and it is not rare: RG pads its own
        # functions to 16 everywhere, but the prebuilt archives are 8-aligned,
        # so ALL FIVE of the library units in scope tripped it.
        if vram % 4:
            raise SystemExit(f"textsplit: {s} at 0x{vram:08X} is not 4-aligned")
        if vram not in index:
            raise SystemExit(f"textsplit: no line for {s} at 0x{vram:08X}")
        last = index.get(vram + size - 4)
        if last is None:
            raise SystemExit(f"textsplit: no line at 0x{vram + size - 4:08X} "
                             f"(last instruction of {s})")
        try:
            first = lines.index(f"glabel {s}", max(0, index[vram] - 8), index[vram])
        except ValueError:
            raise SystemExit(f"textsplit: no `glabel {s}` above 0x{vram:08X}")
        cuts.append((s, vram, size, first, last + 1))
    cuts.sort(key=lambda c: c[1])
    for a, b in zip(cuts, cuts[1:]):
        if a[1] + a[2] > b[1]:
            raise SystemExit(f"textsplit: {a[0]} and {b[0]} overlap")
    return cuts


def rodata_cuts(slots: list, index: dict) -> list:
    """[(symbol, vram, size, first_line, end_line)] for .rodata slots.

    A compiled unit that contains a `switch` emits its jump table into its OWN
    `.rodata`, and admission condition 3 refuses that -- because until now the
    only place a C object's rodata could land was the lcf's trailing
    `*(.rodata)` wildcard, i.e. past the end of everything, which shifts the
    whole image.  Retail's tables are not in a separate segment: spimdisasm
    puts them inside `asm/main.s` (`jtbl_0045FE80` sits at line 988631, in the
    middle of the listing), so they cut out of the text exactly the way a
    function does and the compiled `.rodata` takes the hole.

    Unlike a function slot there is no `glabel` to find: the entry is named by
    ADDRESS in `config/crodata.txt` and the cut runs from the table's first
    word to its last.  ⚠ The `glabel jtbl_XXXXXXXX` line above the first word
    is deliberately LEFT in the preceding part -- that part now ends at the
    table's address, so the label still lands exactly where it did, and any
    other reference to the table still resolves.
    """
    cuts = []
    for sym, vram, size in slots:
        if vram % 4:
            raise SystemExit(f"textsplit: rodata slot {sym} at 0x{vram:08X} "
                             f"is not 4-aligned")
        if vram not in index:
            raise SystemExit(f"textsplit: no line at 0x{vram:08X} for {sym}'s "
                             f"rodata slot")
        last = index.get(vram + size - 4)
        if last is None:
            raise SystemExit(f"textsplit: no line at 0x{vram + size - 4:08X} "
                             f"(last word of {sym}'s rodata slot)")
        cuts.append((sym, vram, size, index[vram], last + 1))
    return cuts


def split(symbols: list, out_dir: Path, cunit_slots: bool = True,
          rodata_slots: list = (), data_slots: list = ()) -> list:
    """Write the part files. Returns the ordered object-name list for the lcf.

    cunit_slots=False writes the function's own assembly into its slot instead
    of leaving it for a compiled object -- the control arm that proves the
    splitting itself moves no bytes.  It also suppresses the rodata slots, for
    the same reason: the control arm must be all-assembly.

    rodata_slots is [(symbol, vram, size)] from config/crodata.txt; each one
    becomes an `(symbol, "rodata")` entry in the returned order, which link.py
    turns into a `<symbol>.o (.rodata)` line in the lcf.
    """
    lines, index = load_main()
    table = symbol_table()
    # ⚠ The kind travels IN the tuple, never in a dict keyed by symbol: a unit
    # appears TWICE here, once for its .text and once for its .rodata, and the
    # two entries are the same name at different addresses.  A `{sym: kind}`
    # map silently marks both of them "rodata" and the function's own code
    # never reaches the image.
    cuts = [c + ("c",) for c in cut_points(symbols, table, index, lines)]
    if cunit_slots and rodata_slots:
        cuts += [c + ("rodata",) for c in rodata_cuts(list(rodata_slots), index)]
        # Sort the two families together: a table can sit either side of the
        # function that uses it, and the lcf's order IS the address order.
        cuts.sort(key=lambda c: c[1])
        for a, b in zip(cuts, cuts[1:]):
            if a[1] + a[2] > b[1]:
                raise SystemExit(f"textsplit: {a[0]} and {b[0]} overlap")

    # Generated data definitions own the label as well as its bytes.
    if cunit_slots and data_slots:
        for sym, vram, size, last_address in data_slots:
            first = index[vram]
            while first and (not lines[first-1].strip() or
                    re.match(r"^(?:glabel|dlabel|alabel)\s+", lines[first-1])):
                first -= 1
            cuts.append((sym, vram, size, first, index[last_address]+1, "data"))
        cuts.sort(key=lambda c: c[1])
        for a, b in zip(cuts, cuts[1:]):
            if a[1]+a[2] > b[1]:
                raise SystemExit("data2c: overlapping slots: " + a[0] + " / " + b[0])

    out_dir.mkdir(parents=True, exist_ok=True)
    order = []
    pos = 0
    part = 0

    def emit_part(body: list) -> None:
        nonlocal part
        # No bytes, labels, or unknown directives: there is no input section
        # to place. In particular, don't align a zero-byte .text between
        # adjacent two-byte data objects. Register masks remain pinned.
        payload = [re.sub(r"/\*.*?\*/", "", line).strip() for line in body]
        if all(not line or line.startswith(
                ("#", ".include", ".set", ".section")) for line in payload):
            return
        name = f"main_text_{part:03d}"
        (out_dir / f"{name}.s").write_text(PROLOGUE + "\n".join(body) + "\n")
        order.append((name, "asm"))
        part += 1

    for sym, vram, size, first, end, kind in cuts:
        emit_part(lines[pos:first])
        if cunit_slots:
            order.append((sym, kind))
        else:
            (out_dir / f"{sym}_asm.s").write_text(
                PROLOGUE + "\n".join(lines[first:end]) + "\n")
            order.append((f"{sym}_asm", "asm"))
        pos = end
    emit_part(lines[pos:])
    return order


if __name__ == "__main__":
    import sys
    for name, kind in split(sys.argv[1:], ROOT / "build" / "link" / "parts"):
        print(f"{kind:4} {name}")
