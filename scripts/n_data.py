#!/usr/bin/env python3
"""Move a compiled LOCAL-ARRAY INITIALISER TEMPLATE out of the object and onto
retail's copy of it.  NORMAL namespace only (scripts/n_*.py).

THE PROBLEM, and it is the exact twin of scripts/n_jtbl.py's.  A local array
with a brace initialiser -- `u16 base[9] = {6, 0, ...};` -- is not built with
stores: mwcc emits the initial bytes once as a TEMPLATE in the object's own
`.data` under an internal `@N` label and copies from it, addressing the
template with a `lui`/`addiu` pair.  The overlay's own data assembly ALREADY
carries the identical bytes at a fixed address (`glabel D_00524D60` and
friends), and olink's lcf collects `*(.data)` into `.data` on top of it -- so
the overlay would carry each template TWICE and every byte after it would
shift.  Meanwhile scripts/bytecheck.py refuses to resolve a symbol defined
outside `.text`, so the two words of every such pair score BAD however right
the source is: `normal_FieldHudPartyPanelsRefresh_4f7d00` (688 words, 1.16% of NORMAL's text) sat on
a floor of exactly 6 = three templates x two words.

WHAT IT DOES.  Every step is a check, not an assumption:

  1. read each non-empty `.data` section.  It must carry NO relocations -- a
     template holding a POINTER is a different animal and is refused rather
     than silently redirected;
  2. find its bytes in RETAIL's own .BIN.  They must occur EXACTLY ONCE, at a
     4-byte-aligned offset, and the address must carry a `glabel D_xxxxxxxx`
     in the overlay's data assembly.  Any of those failing is a hard error;
  3. patch the `lui`/`addiu` pair in `.text` to %hi/%lo of retail's address and
     DROP their two relocations;
  4. empty the section (size 0, align 1) and its relocation section, and make
     the internal label an ABSOLUTE symbol at retail's address -- mwld refuses
     to link a symbol living in a section it never writes.

The `.text` is untouched apart from those immediates, so this cannot turn a
wrong compile into a passing one: olink still compares every byte.
"""
from __future__ import annotations

import re
import struct
from pathlib import Path

import n_jtbl
from n_jtbl import _sections, _symbols, _rels, _ref, _u32, SHN_ABS, R_HI16, R_LO16

ROOT = Path(__file__).resolve().parent.parent
LOAD = 0x004E9E80


def _data_labels(overlay: str) -> set:
    p = ROOT / "asm" / "overlays" / overlay / "data" / f"{overlay}_data.data.s"
    return {int(m, 16) for m in re.findall(
        r"^glabel D_([0-9A-Fa-f]{6,8})", p.read_text(errors="replace"), re.M)}


def _find_unique(ref: bytes, pat: bytes) -> int:
    hits, i = [], ref.find(pat)
    while i >= 0:
        if i % 4 == 0:
            hits.append(i)
        i = ref.find(pat, i + 1)
    if len(hits) != 1:
        raise SystemExit("n_data: the compiled template occurs %d times in "
                         "retail's image -- refusing to guess" % len(hits))
    return LOAD + hits[0]


def retarget(data: bytes, vram: int, overlay: str, slots: dict = None):
    """Returns (newbytes, [(section_index, address, nbytes)]).

    A no-op (and an empty list) for an object with no `.data`.  `slots` maps a
    section INDEX to a forced address, for scoring a unit whose text is not yet
    right (the pattern search cannot fire then).  Keyed on the section INDEX,
    never the name: an object with three templates has THREE sections all named
    `.data` (n_jtbl's own recorded trap).
    """
    d = bytearray(data)
    secs = _sections(d)
    di = [i for i, s in enumerate(secs) if s["sname"].startswith(".data")
          and s["size"]]
    if not di:
        return bytes(d), []
    syms = _symbols(d, secs)
    labels = _data_labels(overlay)
    ref = _ref(overlay)

    addr_of = {}
    for i in di:
        _, drels = _rels(d, secs, i)
        if drels:
            raise SystemExit("n_data: .data section %d carries %d relocation(s) "
                             "-- a template holding a pointer is not handled"
                             % (i, len(drels)))
        if slots and i in slots:
            addr_of[i] = slots[i]
            continue
        sec = secs[i]
        a = _find_unique(ref, bytes(d[sec["offset"]:sec["offset"] + sec["size"]]))
        if a not in labels:
            raise SystemExit("n_data: the template matches retail at 0x%08X, "
                             "which carries no D_ label in the overlay's data "
                             "assembly -- refusing" % a)
        addr_of[i] = a

    tidx = next(i for i, s in enumerate(secs) if s["sname"] == ".text")
    tsec, trels = _rels(d, secs, tidx)
    text_off = secs[tidx]["offset"]

    drop, found = set(), []
    for i, (off, info) in enumerate(trels):
        rtype, symi = info & 0xFF, info >> 8
        if rtype != R_HI16:
            continue
        s = syms[symi]
        if s["shndx"] not in addr_of:
            continue
        lo = next(((j, o2) for j, (o2, n2) in enumerate(trels)
                   if j > i and (n2 & 0xFF) == R_LO16 and (n2 >> 8) == symi),
                  None)
        if lo is None:
            raise SystemExit("n_data: HI16 into .data with no matching LO16")
        j, lo_off = lo
        hi_insn = _u32(d, text_off + off)
        lo_insn = _u32(d, text_off + lo_off)
        addend = ((hi_insn & 0xFFFF) << 16) + struct.unpack(
            "<h", struct.pack("<H", lo_insn & 0xFFFF))[0]
        a = addr_of[s["shndx"]] + s["value"] + addend
        struct.pack_into("<I", d, text_off + off,
                         (hi_insn & 0xFFFF0000) | (((a + 0x8000) >> 16) & 0xFFFF))
        struct.pack_into("<I", d, text_off + lo_off,
                         (lo_insn & 0xFFFF0000) | (a & 0xFFFF))
        drop |= {i, j}
        found.append((s["shndx"], a, secs[s["shndx"]]["size"]))

    reached = {sec for sec, _, _ in found}
    if reached != set(addr_of):
        raise SystemExit("n_data: %d .data section(s) but %d reached from "
                         ".text -- refusing to drop data nothing claims"
                         % (len(addr_of), len(reached)))

    keep = [r for k, r in enumerate(trels) if k not in drop]
    for k, (off, info) in enumerate(keep):
        struct.pack_into("<II", d, tsec["offset"] + k * 8, off, info)
    struct.pack_into("<I", d, tsec["hdr"] + 20, len(keep) * 8)

    for i in addr_of:
        for s in syms:
            if s["shndx"] == i:
                struct.pack_into("<I", d, s["ent"] + 4, addr_of[i] + s["value"])
                struct.pack_into("<H", d, s["ent"] + 14, SHN_ABS)
        struct.pack_into("<I", d, secs[i]["hdr"] + 20, 0)
        struct.pack_into("<I", d, secs[i]["hdr"] + 32, 1)
        dsec, _ = _rels(d, secs, i)
        if dsec is not None:
            struct.pack_into("<I", d, dsec["hdr"] + 20, 0)
    return bytes(d), sorted(found)
