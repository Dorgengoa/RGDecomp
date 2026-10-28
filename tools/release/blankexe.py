#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""blankexe.py: make a publishable rg-game.exe that carries no bytes of the retail game's
data, plus the table setup needs to put them back from the player's own disc files.

    python tools/release/blankexe.py EXE MAP DATA OUTDIR [--min-run 12]

EXE/MAP: a linked rg-game.exe and its link map.  DATA: an rg-extract data/ folder (the
retail files are read from it, never copied).  Writes OUTDIR/rg-game.blank (the exe with
the retail bytes zeroed) and OUTDIR/rg-game.fill (where each zeroed run comes from: file,
offset, length, and SHA-256 of the blank and of the finished exe; no content).

Two passes pick the bytes:
  1. symbol-mapped: every data symbol whose name carries its retail address
     (`D_XXXXXXXX`, `data2c_fragment_XXXXXXXX`, overlay `<ov>_D_XXXXXXXX`) is compared
     byte for byte, up to the next symbol, with SCUS_974.90 (MAIN) or BIN/<OV>.BIN
     (overlays load at 0x004E9E80, header included); equal non-zero bytes are zeroed.
  2. scan: any run of >= --min-run bytes anywhere in the exe that equals a run of the ELF,
     an overlay BIN or an IOP module (not a single repeated byte) is zeroed too.
Then the table is applied to the blank and the result must hash to the original exe.
`rg-setup` (src/release) does the same fill on the player's machine.
"""
import argparse
import hashlib
import re
import struct
import sys
from pathlib import Path

OVL_BASE = 0x004E9E80
OVL_FILES = {"title": "BIN/TITLE.BIN", "normal": "BIN/NORMAL.BIN", "factory": "BIN/FACTORY.BIN",
             "insect": "BIN/INSECT.BIN", "insmenu": "BIN/INSMENU.BIN"}


def pe_sections(exe):
    pe, = struct.unpack_from("<I", exe, 0x3C)
    nsec, = struct.unpack_from("<H", exe, pe + 6)
    opt, = struct.unpack_from("<H", exe, pe + 20)
    base, = struct.unpack_from("<I", exe, pe + 24 + 28)
    secs = []
    for i in range(nsec):
        o = pe + 24 + opt + 40 * i
        name = exe[o:o + 8].rstrip(b"\0").decode()
        vsize, va, rsize, raw = struct.unpack_from("<4I", exe, o + 8)
        secs.append((name, base + va, min(vsize, rsize), raw))
    return secs


def va_to_off(secs, va):
    for _, sva, size, raw in secs:
        if sva <= va < sva + size:
            return raw + va - sva
    return None


def elf_map(elf):
    """MAIN ELF: list of (va, file offset, file size) for loadable segments with bytes."""
    phoff, = struct.unpack_from("<I", elf, 0x1C)
    phsz, n = struct.unpack_from("<HH", elf, 0x2A)
    segs = []
    for i in range(n):
        t, off, va, _, fs, _, _, _ = struct.unpack_from("<8I", elf, phoff + i * phsz)
        if t == 1 and fs:
            segs.append((va, off, fs))
    return segs


def map_symbols(path):
    rx = re.compile(r"^\s*000\d:[0-9a-f]{8}\s+_(\S+)\s+([0-9a-f]{16})\s")
    out = []
    for line in open(path, encoding="latin-1"):
        m = rx.match(line)
        if m:
            out.append((int(m.group(2), 16), m.group(1)))
    out.sort()
    return out


def runs_of(mask):
    """Yield (start, length) of the set positions of a bytearray mask."""
    i, n = 0, len(mask)
    while i < n:
        if mask[i]:
            j = i
            while j < n and mask[j]:
                j += 1
            yield i, j - i
            i = j
        else:
            i += 1


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("exe")
    ap.add_argument("map")
    ap.add_argument("data")
    ap.add_argument("outdir")
    ap.add_argument("--min-run", type=int, default=12)
    a = ap.parse_args()
    exe = Path(a.exe).read_bytes()
    data = Path(a.data)
    secs = pe_sections(exe)
    files = {"SCUS_974.90": (data / "SCUS_974.90").read_bytes()}
    for rel in OVL_FILES.values():
        files[rel] = (data / rel).read_bytes()
    for p in sorted((data / "MODULES").glob("*")):
        files["MODULES/" + p.name] = p.read_bytes()
    segs = elf_map(files["SCUS_974.90"])

    # owner[i] = (file key, file offset) for each exe byte to blank
    src_file = [None] * len(exe)
    src_off = [0] * len(exe)

    def mark(exe_off, key, foff, n):
        fb = files[key]
        for k in range(n):
            e, f = exe_off + k, foff + k
            if f >= len(fb) or e >= len(exe):
                break
            if exe[e] == fb[f] and exe[e] != 0 and src_file[e] is None:
                src_file[e] = key
                src_off[e] = f

    # pass 1: symbol-mapped
    syms = map_symbols(a.map)
    srx = re.compile(r"^(?:(title|normal|factory|insect|insmenu)_)?(?:D_|data2c_fragment_)([0-9A-F]{8})$")
    n1 = 0
    for i, (va, name) in enumerate(syms):
        m = srx.match(name)
        if not m:
            continue
        nxt = syms[i + 1][0] if i + 1 < len(syms) else va
        size = nxt - va
        off = va_to_off(secs, va)
        if off is None or size <= 0 or size > 0x100000:
            continue
        retail = int(m.group(2), 16)
        if m.group(1):
            key, foff = OVL_FILES[m.group(1)], retail - OVL_BASE
        else:
            key, foff = "SCUS_974.90", None
            for sva, soff, fs in segs:
                if sva <= retail < sva + fs:
                    foff = soff + retail - sva
            if foff is None:
                continue  # .bss: no retail bytes
        if foff < 0:
            continue
        mark(off, key, foff, size)
        n1 += 1

    # pass 2: scan for runs shared with any retail file
    W = a.min_run
    index = {}
    for key, fb in files.items():
        for f in range(0, len(fb) - W + 1, 4):
            w = fb[f:f + W]
            if w.count(w[0]) == W:
                continue
            index.setdefault(w, (key, f))
    n2 = 0
    e = 0
    while e <= len(exe) - W:
        hit = index.get(exe[e:e + W])
        if hit:
            key, f = hit
            fb = files[key]
            n = W
            while e + n < len(exe) and f + n < len(fb) and exe[e + n] == fb[f + n]:
                n += 1
            mark(e, key, f, n)
            n2 += 1
            e += n
        else:
            e += 1

    # emit runs: contiguous exe bytes from one file at contiguous offsets
    blank = bytearray(exe)
    rows = []
    i = 0
    while i < len(exe):
        if src_file[i] is None:
            i += 1
            continue
        key, f0, j = src_file[i], src_off[i], i
        while j < len(exe) and src_file[j] == key and src_off[j] == f0 + (j - i):
            blank[j] = 0
            j += 1
        rows.append((i, key, f0, j - i))
        i = j

    # verify the round trip
    test = bytearray(blank)
    for eo, key, fo, n in rows:
        test[eo:eo + n] = files[key][fo:fo + n]
    if bytes(test) != exe:
        sys.exit("blankexe: round trip FAILED")
    out = Path(a.outdir)
    out.mkdir(parents=True, exist_ok=True)
    (out / "rg-game.blank").write_bytes(bytes(blank))
    with open(out / "rg-game.fill", "w", encoding="ascii", newline="\n") as fh:
        fh.write("# rg-game.fill v1: exe_offset file file_offset length (hex); see README\n")
        fh.write(f"blank_sha256 {hashlib.sha256(blank).hexdigest()}\n")
        fh.write(f"exe_sha256 {hashlib.sha256(exe).hexdigest()}\n")
        fh.write(f"exe_size {len(exe):x}\n")
        for eo, key, fo, n in rows:
            fh.write(f"{eo:x} {key} {fo:x} {n:x}\n")
    total = sum(r[3] for r in rows)
    print(f"blankexe: {len(rows)} runs, {total} bytes blanked "
          f"({n1} mapped symbols, {n2} scan hits); round trip OK")


if __name__ == "__main__":
    main()
