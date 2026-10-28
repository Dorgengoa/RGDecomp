# SPDX-License-Identifier: CC0-1.0
"""Retail listing of a MAIN function (R5900 disassembly) for writing C from it.

    python tools/parity/eediv/listing.py KernelTanf_127ae0 [more names...]
    python tools/parity/eediv/listing.py --words 0x447850 13     # data words (hex + float)

Uses the decomp's symbol table (config/main.symbols.txt: address + size) and its
mips-ps2 objdump on the retail ELF.  Paths: --decomp (default ../RGDecomp),
--elf (default ../work/SCUS_974.90).  Used for src/crt/crt_eelibm.c (2026-10-24).
"""
import argparse
import re
import struct
import subprocess
import sys
from pathlib import Path


def symbols(decomp):
    out = {}
    pat = re.compile(r"^(\w+)\s*=\s*0x([0-9A-Fa-f]+);.*size:0x([0-9A-Fa-f]+)")
    for line in (Path(decomp) / "config/main.symbols.txt").read_text().splitlines():
        m = pat.match(line)
        if m:
            out[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
    return out


def read_words(elf, addr, n):
    data = Path(elf).read_bytes()
    # program headers: find the PT_LOAD covering addr
    phoff, = struct.unpack_from("<I", data, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", data, 0x2A)
    for i in range(phnum):
        p_type, p_off, p_vaddr, _, p_filesz = struct.unpack_from("<5I", data, phoff + i * phentsize)
        if p_type == 1 and p_vaddr <= addr < p_vaddr + p_filesz:
            off = p_off + addr - p_vaddr
            return list(struct.unpack_from("<%dI" % n, data, off))
    raise SystemExit("address 0x%x not in a loaded segment" % addr)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("names", nargs="*")
    ap.add_argument("--words", nargs=2, metavar=("ADDR", "N"))
    ap.add_argument("--decomp", default="../RGDecomp")
    ap.add_argument("--elf", default="../work/SCUS_974.90")
    a = ap.parse_args()
    if a.words:
        addr, n = int(a.words[0], 0), int(a.words[1], 0)
        for i, w in enumerate(read_words(a.elf, addr, n)):
            f, = struct.unpack("<f", struct.pack("<I", w))
            print("%08x: %08x  %.9g" % (addr + 4 * i, w, f))
        return
    syms = symbols(a.decomp)
    od = str(Path(a.decomp) / "tools/binutils/mips-ps2-decompals-objdump.exe")
    for name in a.names:
        if name not in syms:
            sys.exit("unknown symbol " + name)
        addr, size = syms[name]
        r = subprocess.run([od, "-d", "-z", "--start-address=0x%x" % addr, "--stop-address=0x%x" % (addr + size), a.elf],
                           capture_output=True, text=True, check=True)
        lines = r.stdout.splitlines()
        start = next(i for i, l in enumerate(lines) if re.match(r"^\s*[0-9a-f]+:\t", l))
        print("== %s 0x%x size 0x%x" % (name, addr, size))
        print("\n".join(lines[start:]))


if __name__ == "__main__":
    main()
