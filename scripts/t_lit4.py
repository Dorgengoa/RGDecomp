#!/usr/bin/env python3
# TITLE session namespace (t_*).  Sandbox tag "ti", objects build/obj-ti.
"""Resolve mwcc's `.lit4` FLOAT LITERAL POOL against retail's small-data pool.

    t_lit4.py title <symbol>...      patch build/obj-ti/<sym>.o IN PLACE
    t_lit4.py title --all            every object in build/obj-ti
    t_lit4.py title --verify <sym>   print every patch site, write nothing
    t_lit4.py title tiprobe --ref <sym>
                                     patch a PROBE TU, taking the
                                     candidate pool addresses from <sym>

WHY THIS EXISTS -- the finding it implements (session 12)
--------------------------------------------------------
`D_0047D3B8`, `D_0047D574`, `D_0047D56C`, `D_0047D1FC`, `D_0047D248` ... are
NOT global variables.  0x0047D1FC-0x0047D7FF is mwcc's float LITERAL POOL:
every entry is a hand-typed decimal (3.1415927, 0.0785398, -0.1, 0.4, 0.7,
0.05, 1e-4) and splat labelled only the ones something referenced.  Retail's
source wrote a LITERAL; every draft in this tree wrote `extern f32 D_0047Dxxx`
and read it as a variable.

That one spelling difference is the whole "gp-float prologue rotation" class:
mwcc pins a load of an EXTERN GLOBAL at its use, but a `.lit4` pool entry is a
known constant with no alias hazard, so it hoists freely -- which is exactly
retail's schedule (the gp `lwc1` issued before the callee-saved `sq`).  Five
sessions measured that residue as a scheduler tie-break and called it negative
on five axes; every one of those sweeps held the extern spelling fixed, so the
axis that mattered was uniform across the entire search.  See
[[title-float-const-operand]] step 2 -- same failure mode, same overlay.

WHAT THE PATCH DOES
-------------------
Writing the literal makes mwcc emit a `.lit4` section per distinct constant
with an `@N` symbol, and a GPREL16 relocation against it.  Those four bytes
already exist in MAIN's image at the retail pool address, and the overlay
cannot reach its own data through main's $gp anyway (title's data sits 0x64000
past gp's +/-32KB window), so the section must NOT be emitted into TITLE.BIN.
This pre-relocates the instruction to the retail pool address and neutralises
the relocation (R_MIPS_NONE), leaving `.lit4` unreferenced; the overlay lcf
names its input sections explicitly and never collects `.lit4`, so mwld drops
it the same way it already drops `.mwcats`.

HOW THE ADDRESS IS CHOSEN -- and why it cannot silently pick a wrong one
-----------------------------------------------------------------------
Candidates are the gp-relative addresses the UNIT'S OWN reference listing
actually touches, intersected with the addresses in main's data whose word
equals the `.lit4` content.  Exactly one match is required; zero or several is
a hard error, never a silent skip (probe-traps TRAP 28).  And the choice is
arbitrated downstream regardless: a wrong address encodes a different
immediate, so t_obytecheck's byte comparison still decides.
"""
from __future__ import annotations

import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
GP = 0x00485170
R_MIPS_GPREL16, R_MIPS_LITERAL = 7, 8

_DATA_WORD = re.compile(
    r"^/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/")
# `lwc1 $f0, -0x7DB8($28)` / `swc1 ... ($28)` -- any gp-relative operand.
_GPREF = re.compile(r"(-?0x[0-9A-Fa-f]+)\(\$28\)")


def retail_words() -> dict:
    """vram -> the 4 little-endian bytes at that address in main's data."""
    out = {}
    for p in (ROOT / "asm" / "data").glob("*.s"):
        for ln in p.read_text(errors="replace").splitlines():
            m = _DATA_WORD.match(ln.strip())
            if m:
                out[int(m.group(1), 16)] = bytes.fromhex(m.group(2))
    if out:
        return out
    # MAIN's data is C now (data2c) and asm/data/ is gone: read the words
    # straight out of the retail ELF's loadable segments instead.
    import bytecheck
    elf = Path(bytecheck.RETAIL).read_bytes()
    phoff, = struct.unpack_from("<I", elf, 28)
    phentsize, phnum = struct.unpack_from("<HH", elf, 42)
    for i in range(phnum):
        p_type, off, vaddr, _, filesz = struct.unpack_from("<IIIII", elf, phoff + i * phentsize)
        if p_type != 1:
            continue
        for a in range(0, filesz - 3, 4):
            out[vaddr + a] = elf[off + a:off + a + 4]
    return out


def gp_sites(overlay: str, sym: str) -> list:
    """Every distinct gp-relative address the reference listing touches."""
    return _listing_refs(overlay, sym, "gp")

def _listing_refs(overlay: str, sym: str, kind: str) -> list:
    """Addresses a function's retail listing referenced, frozen into
    config/listing_refs.json (the listings themselves are not shipped)."""
    import json
    global _REFS
    try:
        _REFS
    except NameError:
        _REFS = json.loads((ROOT / "config" / "listing_refs.json").read_text())
    return [int(a, 16) for a in _REFS.get(overlay, {}).get(sym, {}).get(kind, [])]


class Elf:
    def __init__(self, path: Path):
        self.path = path
        self.d = bytearray(path.read_bytes())
        self.shoff, = struct.unpack_from("<I", self.d, 32)
        self.shentsize, self.shnum, shstrndx = struct.unpack_from(
            "<HHH", self.d, 46)
        self.sh = [list(struct.unpack_from(
            "<10I", self.d, self.shoff + i * self.shentsize))
            for i in range(self.shnum)]
        st = self.sh[shstrndx][4]

        def nm(i):
            o = st + self.sh[i][0]
            return self.d[o:self.d.index(b"\0", o)].decode()

        self.names = [nm(i) for i in range(self.shnum)]
        si = self.symsect = self.names.index(".symtab")
        symstr = self.sh[self.sh[si][6]][4]
        off, size = self.sh[si][4], self.sh[si][5]
        self.symoff = off
        self.syms = []
        for p in range(off, off + size, 16):
            n, val, sz, info, other, shndx = struct.unpack_from(
                "<IIIBBH", self.d, p)
            e = self.d.index(b"\0", symstr + n)
            self.syms.append((self.d[symstr + n:e].decode(), val, shndx))

    def body(self, i):
        return self.sh[i][4], self.sh[i][5]


def patch(overlay: str, sym: str, words: dict, verify: bool = False,
          ref: str = None, objdir=None):
    # objdir defaults to TITLE's sandbox for backward compatibility; every
    # other overlay must pass its own (insmenu build/obj-im, normal obj-nm...).
    # It was hardcoded here, which is why this could not be borrowed as-is.
    obj = (Path(objdir) if objdir else ROOT / "build" / "obj-ti") / f"{sym}.o"
    if not obj.exists():
        return "no object", 0, []
    e = Elf(obj)
    lit = {i for i, n in enumerate(e.names) if n == ".lit4"}
    if not lit:
        return "no .lit4", 0, []
    sites = gp_sites(overlay, ref or sym)

    target = {}                      # .lit4 section index -> retail pool vram
    for i in sorted(lit):
        off, _ = e.body(i)
        content = bytes(e.d[off:off + 4])
        hits = [a for a in sites if words.get(a) == content]
        if len(hits) != 1:
            v = struct.unpack("<f", content)[0]
            return (f"AMBIGUOUS {content.hex().upper()} ({v!r}): {len(hits)} of "
                    f"{len(sites)} gp sites match {[hex(a) for a in hits]}"), 0, []
        target[i] = hits[0]

    log, n = [], 0
    for ri, rn in enumerate(e.names):
        if rn != ".rel.text":
            continue
        toff = e.sh[e.sh[ri][7]][4]
        roff, rsize = e.body(ri)
        keep = []
        for p in range(roff, roff + rsize, 8):
            where, info = struct.unpack_from("<II", e.d, p)
            rtype, symidx = info & 0xFF, info >> 8
            shndx = e.syms[symidx][2] if symidx < len(e.syms) else -1
            if (rtype not in (R_MIPS_GPREL16, R_MIPS_LITERAL)
                    or shndx not in target):
                keep.append((where, info))
                continue
            name, value, _ = e.syms[symidx]
            addr = target[shndx]
            field, = struct.unpack_from("<I", e.d, toff + where)
            a = struct.unpack("<h", struct.pack("<H", field & 0xFFFF))[0]
            new = (field & 0xFFFF0000) | ((addr + a + value - GP) & 0xFFFF)
            log.append(f"    {name:>6} -> 0x{addr:08X}   text+0x{where:04X}   "
                       f"{field:08X} -> {new:08X}")
            if not verify:
                struct.pack_into("<I", e.d, toff + where, new)
            n += 1
        # DROP the satisfied entries rather than blanking them: a
        # R_MIPS_NONE/sym-0 stub still reads as `unresolved symbol` in
        # t_obytecheck's notes, and cosmetic noise there would mask a REAL
        # unresolved symbol next time.  Shrinking sh_size is enough -- the
        # trailing bytes stop being part of the section.
        if not verify and len(keep) * 8 != rsize:
            for k, (where, info) in enumerate(keep):
                struct.pack_into("<II", e.d, roff + k * 8, where, info)
            for k in range(len(keep) * 8, rsize):
                e.d[roff + k] = 0
            e.sh[ri][5] = len(keep) * 8
            struct.pack_into("<10I", e.d, e.shoff + ri * e.shentsize,
                             *e.sh[ri])
    if n and not verify:
        # mwld rejects a DEFINED symbol living in a section the lcf does not
        # place: `@9(.lit4) ... is referenced but has not been written`, even
        # with every relocation against it already gone.  Retarget the symbol
        # to SHN_ABS at the retail pool address -- which is what it now
        # genuinely is -- and empty the section so nothing can be emitted into
        # the overlay image.
        for si, (nm, val, shndx) in enumerate(e.syms):
            if shndx in target:
                q = e.symoff + si * 16
                struct.pack_into("<I", e.d, q + 4, target[shndx] + val)
                struct.pack_into("<H", e.d, q + 14, 0xFFF1)          # SHN_ABS
        for i in sorted(target):
            e.sh[i][5] = 0
            struct.pack_into("<10I", e.d, e.shoff + i * e.shentsize, *e.sh[i])
        obj.write_bytes(bytes(e.d))
    # Idempotency: after a patch no LITERAL reloc survives, so a second run
    # legitimately finds nothing.  That is reported as `already` and is NOT
    # an error -- but it deliberately does not weaken the TRAP-28 guard,
    # because the arbiter is downstream and runs every time: an unfired
    # patch leaves the gp immediate at 0 and t_obytecheck reads a bad word.
    status = "ok" if n else "already"
    return status, n, log


def main():
    overlay = sys.argv[1]
    verify = "--verify" in sys.argv
    ref = None
    if "--ref" in sys.argv:
        ref = sys.argv[sys.argv.index("--ref") + 1]
    objdir = None
    if "--objdir" in sys.argv:
        objdir = Path(sys.argv[sys.argv.index("--objdir") + 1])
    args = [a for a in sys.argv[2:] if not a.startswith("--")]
    if ref:
        args = [a for a in args if a != ref]
    if objdir:
        args = [a for a in args if a != str(objdir)]
    if "--all" in sys.argv:
        args = sorted(p.stem for p in
                      (objdir or ROOT / "build" / "obj-ti").glob("*.o"))
    words = retail_words()
    print(f"t_lit4: {len(words)} retail data words, {len(args)} candidate "
          f"object(s){'  [VERIFY ONLY]' if verify else ''}")
    seen = fired = bad = 0
    for s in args:
        status, n, log = patch(overlay, s, words, verify, ref, objdir)
        if status in ("no object", "no .lit4"):
            continue
        seen += 1
        fired += 1 if n else 0
        bad += 0 if status in ("ok", "already") else 1
        print(f"  {s:30} {n} site(s)  {status}")
        for ln in log:
            print(ln)
    print(f"t_lit4: {fired} of {seen} object(s) carrying .lit4 patched, "
          f"{bad} error(s)")
    return 1 if bad else 0


if __name__ == "__main__":
    raise SystemExit(main())
