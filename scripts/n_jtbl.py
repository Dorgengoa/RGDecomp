#!/usr/bin/env python3
"""Move a compiled `switch`'s JUMP TABLE out of the object and onto retail's.

FACTORY namespace only (scripts/f_*.py).  Nothing here edits a shared file.

THE PROBLEM.  mwcc compiles a dense `switch` into a real jump table and emits
that table in the OBJECT'S `.rodata`, addressed by an internal `@N` label.  The
overlay's own data assembly ALREADY carries the identical table at a fixed
address (`jtbl_0050CAC0` and friends), and olink's lcf collects `*(.rodata)`
into `.data` -- so the overlay would carry the table TWICE and every byte after
it would shift.  The overlay pipeline notes recorded this as "a linker-plumbing
problem, not a matching problem" and declined to build the tool for insmenu,
where the class is 2 functions and 1.59% of the text.

WHY IT IS BUILT HERE.  In factory the same class is **19 functions and 35,028
bytes = 26.21% of the text**, including four of the six largest functions.  The
price was measured before the tool was written, which is the recorded rule.

WHAT IT DOES, and every step is a check rather than an assumption:

  1. read the object's `.rodata` and its R_MIPS_32 relocations, and turn each
     word into the ABSOLUTE address it will have once the function is placed;
  2. find that exact word sequence in RETAIL's own .BIN.  It must occur
     EXACTLY ONCE, and the address it occurs at must carry a `jtbl_` label in
     the overlay's data assembly.  Either failing is a hard error -- a table
     that is not retail's must never be silently redirected;
  3. patch the `lui`/`addiu` pair in `.text` to %hi/%lo of retail's address and
     DROP their two relocations;
  4. empty `.rodata` (size 0, align 1) and its relocation section, so the
     object contributes no data at all.

The `.text` is untouched apart from those two immediates, so this cannot turn a
wrong compile into a passing one: olink still compares every byte.
"""
from __future__ import annotations

import re
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LOAD = 0x004E9E80
REF_BIN = __import__("rgd").RETAIL_DIR / "BIN"

SHT_SYMTAB, SHT_REL = 2, 9
SHN_ABS = 0xFFF1
R_32, R_HI16, R_LO16 = 2, 5, 6


def _u32(d, o):
    return struct.unpack_from("<I", d, o)[0]


def _sections(d):
    shoff, = struct.unpack_from("<I", d, 32)
    shent, shnum, shstr = struct.unpack_from("<HHH", d, 46)
    out = []
    for i in range(shnum):
        o = shoff + i * shent
        f = struct.unpack_from("<10I", d, o)
        out.append({"hdr": o, "name": f[0], "type": f[1], "flags": f[2],
                    "addr": f[3], "offset": f[4], "size": f[5], "link": f[6],
                    "info": f[7], "align": f[8], "entsize": f[9]})
    base = out[shstr]["offset"]
    for s in out:
        e = d.index(b"\0", base + s["name"])
        s["sname"] = d[base + s["name"]:e].decode("latin1")
    return out


def _symbols(d, secs):
    st = next((s for s in secs if s["type"] == SHT_SYMTAB), None)
    if st is None:
        return []
    strs = secs[st["link"]]["offset"]
    out = []
    for i in range(st["size"] // 16):
        o = st["offset"] + i * 16
        nm, val, sz, info, other, shndx = struct.unpack_from("<IIIBBH", d, o)
        e = d.index(b"\0", strs + nm)
        out.append({"ent": o, "name": d[strs + nm:e].decode("latin1"),
                    "value": val, "shndx": shndx})
    return out


def _rels(d, secs, target_idx):
    for s in secs:
        if s["type"] == SHT_REL and s["info"] == target_idx:
            n = s["size"] // 8
            return s, [(_u32(d, s["offset"] + i * 8),
                        _u32(d, s["offset"] + i * 8 + 4)) for i in range(n)]
    return None, []


def _jtbl_labels(overlay: str) -> set:
    p = ROOT / "asm" / "overlays" / overlay / "data" / f"{overlay}_data.data.s"
    return {int(m, 16) for m in re.findall(
        r"^glabel jtbl_([0-9A-Fa-f]{6,8})", p.read_text(errors="replace"), re.M)}


_REF_CACHE = {}


def _ref(overlay: str) -> bytes:
    if overlay not in _REF_CACHE:
        _REF_CACHE[overlay] = (REF_BIN / f"{overlay.upper()}.BIN").read_bytes()
    return _REF_CACHE[overlay]


def _find_unique(ref: bytes, pat: bytes) -> int:
    hits, i = [], ref.find(pat)
    while i >= 0:
        if i % 4 == 0:
            hits.append(i)
        i = ref.find(pat, i + 1)
    if len(hits) != 1:
        raise SystemExit("f_jtbl: the compiled table occurs %d times in "
                         "retail's image -- refusing to guess" % len(hits))
    return LOAD + hits[0]


def _listing_tables(overlay: str, sym: str):
    """The jtbl addresses a function's reference listing names, in the order
    they appear.  Used ONLY by the scoring fallback below."""
    p = (ROOT / "asm" / "overlays" / overlay / "matchings" / overlay
         / f"{sym}.s")
    out = []
    for m in re.findall(r"jtbl_([0-9A-Fa-f]{6,8})", p.read_text(errors="replace")):
        a = int(m, 16)
        if a not in out:
            out.append(a)
    return out


def retarget(data: bytes, vram: int, overlay: str, sym: str = None,
             fallback: bool = False):
    """Returns (newbytes, [(section, jtbl_addr, nentries)]).

    A no-op (and an empty list) for an object with no `.rodata`.

    An object with TWO switches has TWO SECTIONS BOTH NAMED `.rodata`, each
    holding one table and each with its own `@N` label at value 0.  Keying
    anything here on the section NAME collapses them, and the second switch
    then gets the first table's address -- right length, ONE bad word, which
    is the shape that passes every guard except the byte compare.  Everything
    below is keyed on the section INDEX.
    """
    d = bytearray(data)
    secs = _sections(d)
    ro_idx = [i for i, s in enumerate(secs)
              if s["sname"] == ".rodata" and s["size"]]
    if not ro_idx:
        return bytes(d), []
    syms = _symbols(d, secs)

    abs_at = {}
    for i in ro_idx:
        ro = secs[i]
        _, rorels = _rels(d, secs, i)
        for off, info in rorels:
            rtype, symi = info & 0xFF, info >> 8
            if rtype != R_32:
                raise SystemExit("f_jtbl: .rodata carries relocation type %d, "
                                 "which is not a jump table" % rtype)
            s = syms[symi]
            if secs[s["shndx"]]["sname"] != ".text":
                raise SystemExit("f_jtbl: .rodata entry points at %s, not "
                                 ".text" % secs[s["shndx"]]["sname"])
            abs_at[(i, off)] = (vram + s["value"]
                                + _u32(d, ro["offset"] + off)) & 0xFFFFFFFF

    tidx = next(i for i, s in enumerate(secs) if s["sname"] == ".text")
    tsec, trels = _rels(d, secs, tidx)
    text_off = secs[tidx]["offset"]
    labels = _jtbl_labels(overlay)
    ref = _ref(overlay)

    drop, found = set(), []
    for i, (off, info) in enumerate(trels):
        rtype, symi = info & 0xFF, info >> 8
        if rtype != R_HI16:
            continue
        s = syms[symi]
        sec = s["shndx"]
        if sec not in ro_idx:
            continue
        lo = next(((j, o2) for j, (o2, n2) in enumerate(trels)
                   if j > i and (n2 & 0xFF) == R_LO16 and (n2 >> 8) == symi),
                  None)
        if lo is None:
            raise SystemExit("f_jtbl: HI16 into .rodata with no matching LO16")
        j, lo_off = lo
        hi_insn = _u32(d, text_off + off)
        lo_insn = _u32(d, text_off + lo_off)
        addend = ((hi_insn & 0xFFFF) << 16) + struct.unpack(
            "<h", struct.pack("<H", lo_insn & 0xFFFF))[0]
        startoff = s["value"] + addend

        n = 0
        while (sec, startoff + 4 * n) in abs_at:
            n += 1
        if n == 0:
            raise SystemExit("f_jtbl: no relocated table at .rodata+%#x"
                             % startoff)
        pat = b"".join(struct.pack("<I", abs_at[(sec, startoff + 4 * k)])
                       for k in range(n))
        if fallback:
            # SCORING ONLY.  While a unit is still being written its blocks sit
            # at the wrong addresses, so the compiled table cannot match
            # retail's and the strict search refuses -- which would leave the
            # text unscorable.  Take the table the reference listing names, in
            # .rodata order, and let the caller print that it did.
            cand = _listing_tables(overlay, sym)
            addr = cand[len(found)] if len(found) < len(cand) else cand[-1]
        else:
            addr = _find_unique(ref, pat)
        if addr not in labels:
            raise SystemExit("f_jtbl: the table matches retail at 0x%08X, "
                             "which carries no jtbl_ label -- refusing" % addr)
        struct.pack_into("<I", d, text_off + off,
                         (hi_insn & 0xFFFF0000)
                         | (((addr + 0x8000) >> 16) & 0xFFFF))
        struct.pack_into("<I", d, text_off + lo_off,
                         (lo_insn & 0xFFFF0000) | (addr & 0xFFFF))
        drop |= {i, j}
        found.append((sec, addr, n))
        # mwld refuses to link a symbol that lives in a section it never
        # writes ("@14(.rodata) ... is referenced but has not been written"),
        # so the internal label becomes an ABSOLUTE symbol at retail's table.
        struct.pack_into("<I", d, s["ent"] + 4, addr)
        struct.pack_into("<H", d, s["ent"] + 14, SHN_ABS)

    if len(found) != len(ro_idx):
        raise SystemExit("f_jtbl: %d .rodata section(s) but %d reached from "
                         ".text -- refusing to drop data nothing claims"
                         % (len(ro_idx), len(found)))

    keep = [r for k, r in enumerate(trels) if k not in drop]
    for k, (off, info) in enumerate(keep):
        struct.pack_into("<II", d, tsec["offset"] + k * 8, off, info)
    struct.pack_into("<I", d, tsec["hdr"] + 20, len(keep) * 8)

    for i in ro_idx:
        for s in syms:
            if s["shndx"] == i:
                struct.pack_into("<H", d, s["ent"] + 14, SHN_ABS)
        struct.pack_into("<I", d, secs[i]["hdr"] + 20, 0)
        struct.pack_into("<I", d, secs[i]["hdr"] + 32, 1)
        rosec, _ = _rels(d, secs, i)
        if rosec is not None:
            struct.pack_into("<I", d, rosec["hdr"] + 20, 0)
    return bytes(d), found
