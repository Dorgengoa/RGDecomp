#!/usr/bin/env python3
"""Score a compiled function in BYTES against the retail image, without linking.

    bytecheck.py                 every symbol in config/units.txt
    bytecheck.py <symbol>...     just these
    bytecheck.py --verbose <sym> list every differing instruction

objdiff's percentage is a diff score, not an acceptance test. The acceptance
test is now the LINK -- config/cunits.txt, scripts/link.py -- and a function is
only allowed in once its compiled bytes ARE retail's bytes. But a link is a
four-minute round trip to the build host, which is far too slow to iterate on.

This does the same comparison locally and instantly: take the object mwcc
produced, resolve its relocations at the address the function really lives at,
and compare the result word for word with SCUS_974.90 itself.

⚠ It is a MODEL of the link, not the link. `scripts/link.py` stays the thing
that decides -- this only says which function to spend the next hour on.
Calibrated against the 28 functions the link already proves byte-identical:
all 28 must read 0 here, and `--calibrate` checks exactly that.
"""
from __future__ import annotations

import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import rgd
import textsplit

RETAIL = __import__("rgd").RETAIL_DIR / "SCUS_974.90"
VRAM0 = 0x00100000
FILE0 = 0x180
GP = 0x00485170

R_MIPS_16, R_MIPS_32, R_MIPS_26 = 5, 2, 4
R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 = 5, 6, 7
# ⚠ THE QUANTIFIER IS A WINDOW.  This is the last-resort resolver: it
# reads a splat-generated name's own address out of the name when
# config/main.symbols.txt does not carry it.  It wanted EXACTLY eight
# hex digits until pass 28, and the lcf spells the same class of name
# with six digits 213 times and seven 3 times -- so `func_4EC3E0` read
# as `unresolved symbol` for a name with its address written in it.
# 216 such names are referenced by 171 functions, 168 of them unclaimed.
# Widening cannot manufacture a false MATCH: a wrong address encodes a
# different word than retail's, so the byte comparison still arbitrates.
# Negative control: build/p28_addrctl.py -- every name the 8-digit form
# resolved resolves to the SAME address under {6,8}.
NAME_ADDR = re.compile(r"^(?:D|func|jtbl|jpt|L)_?([0-9A-Fa-f]{6,8})$")


class Obj:
    """Just enough ELF to relocate one .text section."""

    def __init__(self, path: Path):
        d = self.d = path.read_bytes()
        shoff, = struct.unpack_from("<I", d, 32)
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
        self.sh = [struct.unpack_from("<10I", d, shoff + i * shentsize)
                   for i in range(shnum)]
        strtab = self.sh[shstrndx][4]

        def sname(i):
            off = strtab + self.sh[i][0]
            return d[off:d.index(b"\0", off)].decode()

        self.names = [sname(i) for i in range(shnum)]
        self.symtab = self.names.index(".symtab")
        symstr = self.sh[self.sh[self.symtab][6]][4]
        self.syms = []
        base, size = self.sh[self.symtab][4], self.sh[self.symtab][5]
        for off in range(base, base + size, 16):
            nm, val, sz, info, other, shndx = struct.unpack_from("<IIIBBH", d, off)
            end = d.index(b"\0", symstr + nm)
            self.syms.append((d[symstr + nm:end].decode(), val, info >> 4, shndx))

    def section(self, name: str):
        if name not in self.names:
            return None
        i = self.names.index(name)
        _, _, _, _, off, size, _, _, _, _ = self.sh[i]
        return bytearray(self.d[off:off + size])

    def relocs(self, name: str):
        rel = ".rel" + name
        if rel not in self.names:
            return []
        i = self.names.index(rel)
        off, size = self.sh[i][4], self.sh[i][5]
        out = []
        for p in range(off, off + size, 8):
            where, info = struct.unpack_from("<II", self.d, p)
            out.append((where, info & 0xFF, info >> 8))
        return out


def symbol_addresses() -> dict:
    table = {n: v for n, (v, _) in textsplit.symbol_table().items()}
    table["_gp"] = GP
    # compiler-runtime aliases (config/aliases.txt), never overriding a real symbol
    ali = rgd.ROOT / "config" / "aliases.txt"
    if ali.exists():
        for ln in ali.read_text().splitlines():
            f = ln.split("#")[0].split()
            if len(f) >= 2 and f[0] not in table:
                table[f[0]] = int(f[1], 16)
    return table


def resolve(obj: Obj, symidx: int, table: dict, base: int):
    name, value, bind, shndx = obj.syms[symidx]
    if shndx not in (0, 0xFFF1) and name in ("", None):
        return None, "section-relative symbol"
    if shndx not in (0, 0xFFF1):
        # Defined inside this object. Only .text is placed at a known address;
        # a function carrying its OWN .rodata (a jump table) has nowhere to go
        # until that section is placed too, and saying so is the point.
        if obj.names[shndx] == ".text":
            return base + value, None
        return None, f"defined in this object's {obj.names[shndx]}"
    if name in table:
        return table[name], None
    m = NAME_ADDR.match(name)
    if m:
        return int(m.group(1), 16), None
    return None, f"unresolved symbol {name}"


def relocate(obj: Obj, base: int, table: dict):
    text = obj.section(".text")
    if text is None:
        return None, ["no .text"]
    rels = obj.relocs(".text")
    notes = []
    i = 0
    while i < len(rels):
        where, rtype, symidx = rels[i]
        addr, why = resolve(obj, symidx, table, base)
        if addr is None:
            notes.append(why)
            i += 1
            continue
        field, = struct.unpack_from("<I", text, where)
        if rtype == R_MIPS_32:
            struct.pack_into("<I", text, where, (field + addr) & 0xFFFFFFFF)
        elif rtype == R_MIPS_26:
            a = (field & 0x03FFFFFF) << 2
            struct.pack_into("<I", text, where,
                             (field & 0xFC000000) | (((addr + a) >> 2) & 0x03FFFFFF))
        elif rtype == R_MIPS_HI16:
            # HI16 carries only the top half of the addend; the matching LO16
            # carries the bottom, signed. Pair them or every %hi is off by one
            # wherever the low half is negative.
            lo = next((r for r in rels[i + 1:] if r[1] == R_MIPS_LO16), None)
            if lo is None:
                notes.append("HI16 with no following LO16")
                i += 1
                continue
            lofield, = struct.unpack_from("<I", text, lo[0])
            ahl = ((field & 0xFFFF) << 16) + struct.unpack("<h", struct.pack(
                "<H", lofield & 0xFFFF))[0]
            v = addr + ahl
            hi = ((v - struct.unpack("<h", struct.pack("<H", v & 0xFFFF))[0])
                  >> 16) & 0xFFFF
            struct.pack_into("<I", text, where, (field & 0xFFFF0000) | hi)
        elif rtype == R_MIPS_LO16:
            a = struct.unpack("<h", struct.pack("<H", field & 0xFFFF))[0]
            struct.pack_into("<I", text, where,
                             (field & 0xFFFF0000) | ((addr + a) & 0xFFFF))
        elif rtype == R_MIPS_GPREL16:
            a = struct.unpack("<h", struct.pack("<H", field & 0xFFFF))[0]
            struct.pack_into("<I", text, where,
                             (field & 0xFFFF0000) | ((addr + a - GP) & 0xFFFF))
        else:
            notes.append(f"relocation type {rtype} not handled")
        i += 1
    return text, notes


def check(sym: str, table: dict, retail: bytes, verbose: bool = False):
    obj = rgd.OBJ_DIR / f"{sym}.o"
    if not obj.exists():
        return None
    vram, size = table.get(sym), textsplit.symbol_table().get(sym, (None, None))[1]
    if vram is None or size is None:
        return None
    o = Obj(obj)
    text, notes = relocate(o, vram, table)
    if text is None:
        return (sym, vram, None, None, notes)
    want = retail[vram - VRAM0 + FILE0: vram - VRAM0 + FILE0 + size]
    if len(text) != len(want):
        return (sym, vram, len(text), None, notes + [f"length 0x{len(text):X} "
                                                     f"vs retail 0x{len(want):X}"])
    bad = [w for w in range(0, len(want), 4)
           if text[w:w + 4] != want[w:w + 4]]
    if verbose:
        for w in bad:
            print(f"  0x{vram + w:08X}  retail {struct.unpack_from('<I', want, w)[0]:08X}"
                  f"   ours {struct.unpack_from('<I', text, w)[0]:08X}")
    return (sym, vram, len(text), bad, notes)


def ref_lines(sym: str) -> dict:
    """vram -> the reference's own disassembly line, for readable output."""
    out = {}
    p = rgd.ASM_DIR / f"{sym}.s"
    if not p.exists():
        return out
    for ln in p.read_text().splitlines():
        m = re.match(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s*(.*)$", ln)
        if m:
            out[int(m.group(1), 16)] = m.group(2).strip()
    return out


def align(sym: str, table: dict, retail: bytes) -> int:
    """Line up the two instruction streams and show where they diverge.

    A function of the WRONG LENGTH is a different kind of defect from one that
    is merely wrong: the structure is missing or doubled, not misallocated. A
    plain word-for-word compare is useless there -- everything after the first
    insertion shifts and reads as a total mismatch -- so align first.

    Alignment runs over a LOOSE fingerprint with the low 16 bits masked off,
    because a branch's own offset changes when the instructions around it move
    and would otherwise defeat the very comparison meant to find the move.
    """
    import difflib
    obj = rgd.OBJ_DIR / f"{sym}.o"
    vram, size = table.get(sym), textsplit.symbol_table().get(sym, (None, None))[1]
    if vram is None or not obj.exists():
        print(f"{sym}: no object or no address")
        return 1
    ours, notes = relocate(Obj(obj), vram, table)
    want = retail[vram - VRAM0 + FILE0: vram - VRAM0 + FILE0 + size]
    a = [struct.unpack_from("<I", want, i)[0] for i in range(0, len(want), 4)]
    b = [struct.unpack_from("<I", ours, i)[0] for i in range(0, len(ours), 4)]
    def kind(w: int):
        """Instruction KIND only -- no registers, no immediates.

        ⚠ Masking just the low 16 bits is not enough here. A function whose
        residue is pervasive register renaming (QuatSlerp_13c270: `mfc1 $8` against
        `mfc1 $4`, 8 times) then fails to align at all, and every rename gets
        reported as an insert+delete pair -- which is precisely the signal the
        length mismatch was supposed to isolate. Align on kind, report on bytes.
        """
        op = w >> 26
        return (op, w & 0x3F) if op in (0, 0x11, 0x12, 0x13, 0x1C, 0x1F) else (op,)

    loose = lambda ws: [kind(w) for w in ws]
    src = ref_lines(sym)

    print(f"{sym}: retail {len(a)} words, ours {len(b)} words"
          + (f"   [{'; '.join(sorted(set(notes)))}]" if notes else ""))
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(
            None, loose(a), loose(b), autojunk=False).get_opcodes():
        if tag == "equal":
            continue
        print(f"\n  {tag} at retail 0x{vram + i1 * 4:08X} "
              f"({i2 - i1} word(s)) vs ours +0x{j1 * 4:X} ({j2 - j1} word(s))")
        for k in range(i1, i2):
            print(f"    retail 0x{vram + k * 4:08X} {a[k]:08X}  "
                  f"{src.get(vram + k * 4, '')}")
        for k in range(j1, j2):
            print(f"    ours   +0x{k * 4:<8X} {b[k]:08X}")
    return 0


def main() -> int:
    verbose = "--verbose" in sys.argv
    if "--align" in sys.argv:
        table = symbol_addresses()
        retail = RETAIL.read_bytes()
        rc = 0
        for s in [a for a in sys.argv[1:] if not a.startswith("--")]:
            rc |= align(s, table, retail)
        return rc
    calibrate = "--calibrate" in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    table = symbol_addresses()
    retail = RETAIL.read_bytes()

    if calibrate:
        args = [ln.split("#")[0].strip()
                for ln in (rgd.ROOT / "config" / "cunits.txt").read_text().splitlines()
                if ln.split("#")[0].strip()]
    syms = args or rgd.registered()

    rows = []
    for s in syms:
        r = check(s, table, retail, verbose and len(syms) == 1)
        if r is None:
            print(f"{s:<26} no object -- run scripts/hostbuild.py {s}")
            continue
        rows.append(r)

    rows.sort(key=lambda r: (r[3] is None, -(len(r[3]) if r[3] else 0)))
    print(f"{'function':<26} {'words':>6} {'bad':>5}  notes")
    for sym, vram, n, bad, notes in rows:
        words = n // 4 if n else 0
        cell = "?" if bad is None else ("MATCH" if not bad else str(len(bad)))
        note = "; ".join(sorted(set(notes)))
        print(f"{sym:<26} {words:>6} {cell:>5}  {note}")

    if calibrate:
        broken = [r[0] for r in rows if r[3] is None or r[3]]
        print(f"\ncalibration: {len(rows) - len(broken)}/{len(rows)} of the linked "
              f"C units read MATCH here")
        if broken:
            print("MISCALIBRATED -- the link proves these byte-identical and this "
                  "does not: " + " ".join(broken))
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
