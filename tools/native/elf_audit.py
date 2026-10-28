#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Linux rg-game ELF audit (no Linux machine needed): what the executable needs at load time.

    python tools/native/elf_audit.py ELF [--sysroot DIR] [--readelf PATH] [--list]

Reads the ELF with llvm-readelf (header, program headers, dynamic section, dynamic
symbols) and the shared libraries it NEEDs from the cross sysroot, then reports:

  header     class / machine / type (EXEC = non-PIE), entry, interpreter, TEXTREL
  needed     the DT_NEEDED libraries and where the sysroot has them
  undefined  every undefined dynamic symbol by the NEEDED library that defines it
             (`weak` ones may stay unresolved); symbols NO needed library defines are
             listed: those would fail at load time (exit 1)
  glibc      the highest GLIBC_x.y symbol version required (the oldest distro it runs on)

--list prints every undefined symbol with its provider.  docs/LINUX.md "Audit".
"""
from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

DEF_SYSROOT = os.environ.get("RG_LINUX_SYSROOT", r"../tools\sysroot-i386-bookworm")
DEF_READELF = os.environ.get("RG_LLVM_READELF", r"../tools\llvm\bin\llvm-readelf.exe")
LIBDIRS = ("lib/i386-linux-gnu", "usr/lib/i386-linux-gnu", "lib", "usr/lib",
           "usr/lib/gcc/i686-linux-gnu/12")

# llvm-readelf --dyn-syms row: Num: Value Size Type Bind Vis Ndx Name[@ver]
SYM = re.compile(r"^\s*\d+:\s+[0-9a-fA-F]+\s+\d+\s+(\w+)\s+(\w+)\s+\w+\s+(\S+)\s+(\S+)")


def readelf(tool: str, *args: str) -> str:
    p = subprocess.run([tool, *args], capture_output=True, text=True, errors="replace")
    if p.returncode != 0:
        raise SystemExit(f"elf_audit: {tool} {' '.join(args)}: {p.stderr.strip()}")
    return p.stdout


def dyn_syms(tool: str, path: Path) -> list[tuple[str, str, str, str]]:
    """(name, version, bind, ndx) per dynamic symbol"""
    out = []
    for line in readelf(tool, "--dyn-syms", "-W", str(path)).splitlines():
        m = SYM.match(line)
        if not m:
            continue
        _typ, bind, ndx, name = m.groups()
        ver = ""
        if "@" in name:
            name, _, ver = name.partition("@")
            ver = ver.lstrip("@")
        out.append((name, ver, bind, ndx))
    return out


def find_lib(sysroot: Path, name: str) -> Path | None:
    for d in LIBDIRS:
        p = sysroot / d / name
        if p.is_file():
            return p
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("elf")
    ap.add_argument("--sysroot", default=DEF_SYSROOT)
    ap.add_argument("--readelf", default=DEF_READELF)
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args()
    elf, sysroot = Path(a.elf), Path(a.sysroot)
    if not elf.is_file():
        print(f"elf_audit: {elf} not found")
        return 2

    hdr = readelf(a.readelf, "-h", "-l", "-d", "-W", str(elf))
    get = lambda k: (re.search(rf"^\s*{k}:\s*(.*)$", hdr, re.M) or [None, "?"])[1].strip()
    interp = re.search(r"Requesting program interpreter: ([^\]]+)\]", hdr)
    needed = re.findall(r"\(NEEDED\)\s+Shared library: \[([^\]]+)\]", hdr)
    textrel = "TEXTREL" in hdr
    loads = re.findall(r"^\s*LOAD\s+0x[0-9a-f]+\s+(0x[0-9a-f]+)\s+0x[0-9a-f]+\s+(0x[0-9a-f]+)\s+(0x[0-9a-f]+)\s+([RWE ]+?)\s+0x",
                       hdr, re.M)
    print(f"# {elf} ({elf.stat().st_size:,} bytes)")
    print(f"header\t{get('Class')}\t{get('Machine')}\t{get('Type')}\tentry {get('Entry point address')}")
    print(f"interp\t{interp.group(1) if interp else '(none: static)'}")
    print(f"textrel\t{'YES (text relocations)' if textrel else 'no'}")
    for va, fsz, msz, flg in loads:
        print(f"load\t{va}\tfile {int(fsz, 16):,}\tmem {int(msz, 16):,}\t{flg}")

    provider: dict[str, str] = {}
    weak_ok = set()
    for lib in needed:
        p = find_lib(sysroot, lib)
        print(f"needed\t{lib}\t{p if p else 'NOT IN SYSROOT'}")
        if not p:
            continue
        for name, _ver, _bind, ndx in dyn_syms(a.readelf, p):
            if ndx != "UND":
                provider.setdefault(name, lib)

    by_lib: dict[str, list[str]] = defaultdict(list)
    missing, glibc = [], (0, 0)
    for name, ver, bind, ndx in dyn_syms(a.readelf, elf):
        if ndx != "UND" or not name:
            continue
        m = re.match(r"GLIBC_(\d+)\.(\d+)", ver)
        if m:
            glibc = max(glibc, (int(m.group(1)), int(m.group(2))))
        if name in provider:
            by_lib[provider[name]].append(name)
        elif bind == "WEAK":
            weak_ok.add(name)
        else:
            missing.append(f"{name}@{ver}" if ver else name)
    for lib in needed:
        print(f"undefined\t{lib}\t{len(by_lib.get(lib, []))}")
    print(f"undefined\t(weak, unresolved ok)\t{len(weak_ok)}")
    print(f"undefined\t(NO PROVIDER)\t{len(missing)}")
    print(f"glibc\tGLIBC_{glibc[0]}.{glibc[1]}" if glibc != (0, 0) else "glibc\t-")
    if a.list:
        for lib in needed:
            for s in sorted(by_lib.get(lib, [])):
                print(f"sym\t{lib}\t{s}")
        for s in sorted(weak_ok):
            print(f"sym\t(weak)\t{s}")
    for s in sorted(missing):
        print(f"MISSING\t{s}")
    if missing:
        print(f"elf_audit: FAIL: {len(missing)} undefined symbols no needed library defines")
        return 1
    print("elf_audit: PASS: every undefined symbol is defined by a NEEDED library (or weak)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
