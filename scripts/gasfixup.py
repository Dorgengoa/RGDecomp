#!/usr/bin/env python3
"""Make a GNU-as object acceptable to mwldps2, and correct for the one place
the two toolchains disagree.

    gasfixup.py in.o out.o

Two edits, both measured on the full main image (2026-08-22):

1. DROP THE ZERO-SIZE .data/.bss THAT GNU as ALWAYS EMITS. mwld refuses the
   object outright with

       .data(.data) in file X.o is referenced but has not been written.
       Check your linker command file.

   which reads like an lcf mistake and is not one -- naming the sections
   explicitly in the lcf does NOT satisfy it. Removing the two empty sections
   is both necessary and sufficient; .MIPS.abiflags and .gnu.attributes are
   tolerated and can stay.

2. BIAS EVERY R_MIPS_PC16 ADDEND BY +1 INSTRUCTION. gas resolves a branch to a
   LOCAL label itself, but a branch to a GLOBAL one is left as an R_MIPS_PC16
   for the linker, and gas and mwld disagree by exactly one instruction about
   what the in-field addend means (gas: target - (PC + 4); mwld: target - PC).
   Uncorrected, each such branch lands 4 bytes early. This is the disagreement
   already noted in include/macro.inc, which is why splat's `alabel` deliberately
   keeps branch targets local -- but three targets in the main image are real
   `glabel` functions that a branch also reaches, so they cannot be made local.

   In the main ELF there are exactly THREE R_MIPS_PC16 relocations, and before
   this fixup they were exactly the THREE differing bytes in an otherwise
   byte-identical 0x381080-byte image. The correction is therefore fully
   scoped: it cannot touch anything else, because nothing else uses that type.
"""
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OBJCOPY = __import__("rgd").binutil("objcopy")

R_MIPS_PC16 = 10
SHT_REL = 9


def sections(d):
    (e_shoff,) = struct.unpack_from("<I", d, 32)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", d, 46)
    shs = [struct.unpack_from("<IIIIIIIIII", d, e_shoff + i * e_shentsize)
           for i in range(e_shnum)]
    stro = shs[e_shstrndx][4]

    def name(sh):
        end = d.index(b"\0", stro + sh[0])
        return d[stro + sh[0]:end].decode()

    return shs, name


def bias_pc16(path):
    """Add one instruction to every R_MIPS_PC16 in-field addend. Returns count.

    ⚠ Elf32_Shdr field order is name/type/flags/addr/offset/size/link/info/
    addralign/entsize, so sh_link is index 6 and sh_info is index 7. Reading
    sh_info as index 8 lands on sh_addralign, which here is a plausible small
    integer (4) that indexes a real section -- so the scan silently matched
    nothing instead of failing. It reports "biased 0" and looks like a
    correct no-op.
    """
    d = bytearray(path.read_bytes())
    shs, name = sections(d)
    fixed = 0
    for sh in shs:
        if sh[1] != SHT_REL:
            continue
        target = shs[sh[7]]          # sh_info -> the section the relocs apply to
        if not name(target).startswith(".text"):
            continue
        for off in range(sh[4], sh[4] + sh[5], 8):
            r_offset, r_info = struct.unpack_from("<II", d, off)
            if (r_info & 0xFF) != R_MIPS_PC16:
                continue
            at = target[4] + r_offset
            (insn,) = struct.unpack_from("<I", d, at)
            struct.pack_into("<I", d, at, (insn & 0xFFFF0000) | ((insn + 1) & 0xFFFF))
            fixed += 1
    path.write_bytes(bytes(d))
    return fixed


def main() -> int:
    src, dst = Path(sys.argv[1]), Path(sys.argv[2])
    # Only the EMPTY ones. The data object's .data is the payload; removing it
    # unconditionally silently produces a valid-looking object with no data in
    # it, and the link still succeeds.
    d = src.read_bytes()
    shs, name = sections(d)
    drop = [name(sh) for sh in shs
            if name(sh) in (".data", ".bss", ".text") and sh[5] == 0]
    # asm/reginfo_pin.s's scratch section: it exists only so gas records the
    # registers in .reginfo, and must never reach the image.
    drop += [name(sh) for sh in shs
             if name(sh) in (".reginfo_pin", ".rel.reginfo_pin")]
    # objcopy first: it rewrites the file wholesale, so biasing before it would
    # be undone by the section renumbering.
    r = subprocess.run([str(OBJCOPY)] + [f"--remove-section={s}" for s in drop] +
                       [str(src), str(dst)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stderr.strip())
        return 1
    n = bias_pc16(dst)
    print(f"{src.name} -> {dst.name}: dropped empty {drop or None}, "
          f"biased {n} R_MIPS_PC16 addend(s)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
