#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Read files out of the game's DATA*.HD6/.DAT archives and the .pac containers in them
(docs/SAVE-FORMAT.md "Game data the save editor uses").  For deriving fixture cards
from the game's own tables (story flags, map jump points, transporters) instead of
guessing.  Game-derived output goes under out/ (never committed).

    python tools/fixtures/gamedata.py list [PATTERN]          # archive names (regex, case-insensitive)
    python tools/fixtures/gamedata.py get NAME [-o FILE]       # one archive file
    python tools/fixtures/gamedata.py pac NAME [--extract DIR] # list / unpack a .pac
    python tools/fixtures/gamedata.py cfg NAME [MEMBER]        # cfg text (from the archive or a .pac member)

Archive index: one u64 per file: name-stream offset bits 0-17, data offset bits
18-37 (x 2048), size / 4 bits 38-63 (recomp/tools/asset_viewer.py; hd6_map.py's
u16/u24/u24 reading is off for many files).  Text files end at the first NUL.
DATA0_0 is the English disc's main archive.  A .pac / .chr is a chain of entries
{char name[0x40]; u32 header size (0x50); u32 size; u32 next (relative); ..} with
the body at +header size; the .cfg.bin bodies are CfgVm byte code (cfgdump.py).
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
DATA = PORT / "data"

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")


class Archive:
    def __init__(self, stem="DATA0_0"):
        d = (DATA / f"{stem}.HD6").read_bytes()
        assert d[:3] == b"HD6"
        tok_off, tok_size = struct.unpack_from("<II", d, 4)
        name_off, name_size = struct.unpack_from("<II", d, 0x14)
        count, dir_off = struct.unpack_from("<II", d, 0x24)
        toks = d[tok_off:tok_off + tok_size].split(b"\0")
        names = d[name_off:name_off + name_size]
        self.dat = DATA / f"{stem}.DAT"
        self.files = {}
        for i in range(count):
            (r,) = struct.unpack_from("<Q", d, dir_off + 8 * i)
            nm = r & 0x3FFFF
            off = ((r >> 18) & 0xFFFFF) * 2048
            size = (r >> 38) * 4
            self.files[self._name(names, toks, nm).lower()] = (off, size)

    @staticmethod
    def _name(names, toks, i):
        out = []
        while i < len(names):
            v = shift = 0
            while True:
                b = names[i]
                i += 1
                v |= (b & 0x7F) << shift
                shift += 7
                if not b & 0x80:
                    break
            if v == 0:
                break
            out.append(toks[v].decode("latin-1") if v < len(toks) else f"<tok{v}>")
        return "".join(out)

    def get(self, name: str) -> bytes:
        if Path(name).is_file():   # a file already extracted
            return Path(name).read_bytes()
        key = name.replace("/", "\\").lower()
        if key not in self.files:
            raise KeyError(name)
        off, size = self.files[key]
        with open(self.dat, "rb") as f:
            f.seek(off)
            return f.read(size)


def pac_members(b: bytes):
    """Members of a .pac / .chr chain: (name, body offset, body size)."""
    out = []
    pos = 0
    while pos + 0x50 <= len(b):
        hs, size, nxt = struct.unpack_from("<III", b, pos + 0x40)
        nm = b[pos:pos + 0x40].split(bytes(1), 1)[0].decode("cp932", "replace")
        if not nm or hs < 0x40 or pos + hs + size > len(b):
            break
        out.append((nm, pos + hs, size))
        if nxt <= 0:
            break
        pos += nxt
    return out


def text(b: bytes) -> str:
    return b.split(b"\0", 1)[0].decode("cp932", "replace")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--archive", default="DATA0_0")
    sp = ap.add_subparsers(dest="cmd", required=True)
    p = sp.add_parser("list"); p.add_argument("pattern", nargs="?", default=".")
    p = sp.add_parser("get"); p.add_argument("name"); p.add_argument("-o")
    p = sp.add_parser("pac"); p.add_argument("name"); p.add_argument("--extract")
    p = sp.add_parser("cfg"); p.add_argument("name"); p.add_argument("member", nargs="?")
    a = ap.parse_args(argv)
    ar = Archive(a.archive)
    if a.cmd == "list":
        rx = re.compile(a.pattern, re.I)
        for n, (off, size) in ar.files.items():
            if rx.search(n):
                print(f"{size:9d}  {n}")
    elif a.cmd == "get":
        b = ar.get(a.name)
        if a.o:
            Path(a.o).write_bytes(b)
        else:
            sys.stdout.buffer.write(b)
    elif a.cmd == "pac":
        b = ar.get(a.name)
        ms = pac_members(b)
        if not ms:
            print(f"gamedata: {a.name}: unknown pac layout; first bytes {b[:64].hex()}")
            return 1
        for nm, off, size in ms:
            print(f"{off:#09x} {size:8d}  {nm}")
            if a.extract:
                o = Path(a.extract) / nm.replace("\\", "/")
                o.parent.mkdir(parents=True, exist_ok=True)
                o.write_bytes(b[off:off + size])
    elif a.cmd == "cfg":
        b = ar.get(a.name)
        if a.member:
            for nm, off, size in pac_members(b):
                if nm.lower().replace("\\", "/").endswith(a.member.lower()):
                    b = b[off:off + size]
                    break
            else:
                print(f"gamedata: no member {a.member}")
                return 1
        print(text(b))
    return 0


if __name__ == "__main__":
    sys.exit(main())
