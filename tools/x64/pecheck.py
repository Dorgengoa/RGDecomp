#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""x64 low-address link gate (P7 strategy A, docs/X64-PLAN.md step 1).

    python tools/x64/pecheck.py EXE [EXE ...] [--delete-on-fail] [--quiet]

An x64 rg-port executable must keep EVERY address of its process below 2 GB:
game memory stores pointers as 4-byte words (`__ptr32`, ADDR32 data
relocations).  That holds only for an image linked

    /LARGEADDRESSAWARE:NO  /DYNAMICBASE:NO  /HIGHENTROPYVA:NO  /BASE:<below 2 GB>

lld-link does NOT diagnose an ADDR32 relocation that overflows (the default
x64 base is 0x140000000): without these flags it writes an exe that crashes
(docs/X64-PLAN.md section 4, probe t4b).  This script reads the PE headers and
fails (exit 1) unless, for a PE32+ (x64) image:

  * IMAGE_FILE_LARGE_ADDRESS_AWARE (COFF Characteristics 0x0020) is clear
  * IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE (0x0040) is clear
  * IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA (0x0020) is clear
  * ImageBase + SizeOfImage <= 0x80000000

A PE32 (i686) image only needs LARGE_ADDRESS_AWARE clear (the i686 exe's own
rule: docs/DMAC.md reads bit 31 of a host pointer).  CMake runs it as part of
every x64 executable's link rule (CMakeLists.txt, RG_ARCH=x64), so a link
without the flags fails the build; --delete-on-fail removes the bad exe so a
later build cannot pick it up.  ctest `x64.lowmem_link_control` links a probe
without the flags and expects this script to fail.
"""
from __future__ import annotations

import struct
import sys
from pathlib import Path

LAA = 0x0020
DYN = 0x0040
HEVA = 0x0020
LIMIT = 0x80000000


def check(path: Path) -> list[str]:
    b = path.read_bytes()
    if b[:2] != b"MZ":
        return ["not an MZ/PE file"]
    pe = struct.unpack_from("<I", b, 0x3C)[0]
    if b[pe:pe + 4] != b"PE\0\0":
        return ["no PE signature"]
    machine, = struct.unpack_from("<H", b, pe + 4)
    chars, = struct.unpack_from("<H", b, pe + 22)
    opt = pe + 24
    magic, = struct.unpack_from("<H", b, opt)
    errs = []
    if chars & LAA:
        errs.append("LARGE_ADDRESS_AWARE is set (link with /LARGEADDRESSAWARE:NO)")
    if magic == 0x10B:                       # PE32 (i686)
        return errs
    if magic != 0x20B:
        return errs + [f"unknown optional-header magic {magic:#x}"]
    base, = struct.unpack_from("<Q", b, opt + 24)
    size, = struct.unpack_from("<I", b, opt + 56)
    dllc, = struct.unpack_from("<H", b, opt + 70)
    if dllc & DYN:
        errs.append("DYNAMIC_BASE is set (link with /DYNAMICBASE:NO)")
    if dllc & HEVA:
        errs.append("HIGH_ENTROPY_VA is set (link with /HIGHENTROPYVA:NO)")
    if base + size > LIMIT:
        errs.append(f"image [{base:#x}, {base + size:#x}) is not below 2 GB "
                    f"(link with a low /BASE, e.g. /BASE:0x00400000)")
    if machine != 0x8664:
        errs.append(f"PE32+ but machine {machine:#x} is not AMD64")
    return errs


def main(argv: list[str]) -> int:
    files = [a for a in argv if not a.startswith("--")]
    delete = "--delete-on-fail" in argv
    quiet = "--quiet" in argv
    if not files:
        print(__doc__)
        return 2
    bad = 0
    for f in files:
        p = Path(f)
        errs = check(p)
        if errs:
            bad += 1
            for e in errs:
                print(f"pecheck: {p}: FAIL: {e}", file=sys.stderr)
            if delete:
                try:
                    p.unlink()
                    print(f"pecheck: {p}: deleted", file=sys.stderr)
                except OSError as ex:
                    print(f"pecheck: {p}: could not delete: {ex}", file=sys.stderr)
        elif not quiet:
            print(f"pecheck: {p}: ok")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
