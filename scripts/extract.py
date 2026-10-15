#!/usr/bin/env python3
"""Regenerate asm/ from your retail files.

    extract.py            write asm/ from retail/ (or $RGD_RETAIL_DIR)
    extract.py --force    overwrite listings that already exist

The repository does not carry the game's disassembly. What the build still
assembles -- the Sony SDK, the Metrowerks runtime, crt0, and the layout the
links cut the C objects into -- is rebuilt here from the retail files and the
skeletons in config/asm/. A skeleton holds only the listing's structure: the
labels, section directives and the address of every row. Each row's contents
are read back out of the retail file at that address and written as a raw
`.word` / `.short` / `.byte`, so the listings assemble to exactly the retail
bytes.

Skeleton format (config/asm/<listing>.skel):

    #asmskel 1 <retail file> <lf|crlf>
    =<line>                               copied verbatim
    @<size> <indent> <sep> <off> <vram> <count>
                                          <count> rows of <size> bytes from
                                          file offset <off>, vram <vram>
"""
from __future__ import annotations

import hashlib
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import data2c
import rgd

ROOT = rgd.ROOT
SKEL = ROOT / "config" / "asm"
ASM = ROOT / "asm"
DSKEL = ROOT / "config" / "main_data"
DATA = ROOT / "src" / "main_data"

SHA1 = {
    "SCUS_974.90": "87e9eff1d795c894fc09047270baab70d6a8d2c8",
    "BIN/TITLE.BIN": "e82573fce90bd496d75efedf6d781ac04791d81d",
    "BIN/INSMENU.BIN": "c17c97b2401a2fb864b88dfbf47eb5b7989aab8d",
    "BIN/NORMAL.BIN": "147dd08d8b1d46af494db7ef146b5f1379ce9555",
    "BIN/FACTORY.BIN": "03ce9121a240b4b57cc6343f70e1eadb473b55e7",
    "BIN/INSECT.BIN": "164e56f939e39c78b10851bec1e38de39a81996a",
}


def row(size: int, ind: int, sep: int, off: int, vram: int, b: bytes) -> str:
    """One listing row holding the retail bytes `b`."""
    pad, gap = " " * ind, " " * sep
    if size == 4:
        return (f"{pad}/* {off:06X} {vram:08X} {b.hex().upper()} */"
                f"{gap}.word 0x{int.from_bytes(b, 'little'):08X}")
    if size == 2:
        return (f"{pad}/* {off:06X} {vram:08X} */"
                f"{gap}.short 0x{int.from_bytes(b, 'little'):04X}")
    return f"{pad}/* {off:06X} {vram:08X} */{gap}.byte 0x{b[0]:02X}"


def render(skel: str, retail: bytes) -> tuple[str, str]:
    """(listing text, retail file name) for one skeleton."""
    lines = skel.split("\n")
    head = lines[0].split()
    if head[:2] != ["#asmskel", "1"]:
        raise SystemExit("extract: not a version-1 skeleton")
    name, nl = head[2], "\r\n" if head[3] == "crlf" else "\n"
    out = []
    for ln in lines[1:]:
        if ln.startswith("="):
            out.append(ln[1:])
        elif ln.startswith("@"):
            size, ind, sep, off, vram, n = ln[1:].split()
            size, ind, sep, n = int(size), int(ind), int(sep), int(n)
            off, vram = int(off, 16), int(vram, 16)
            for k in range(n):
                o = off + k * size
                out.append(row(size, ind, sep, o, vram + k * size,
                               retail[o:o + size]))
        elif ln:
            raise SystemExit(f"extract: bad skeleton line {ln[:40]!r}")
    return nl.join(out), name


ELEM = {"u32": 4, "f32": 4, "s16": 2, "u8": 1, "char": 1}
DEF_RE = re.compile(r"^(?:const )?(u32|f32|s16|u8|char) \w+\[\d+\] = ", re.M)
ITEM_RE = re.compile(r"[^,{}\s][^,{}\n]*")


def main_reader(elf: bytes):
    """vram -> bytes of the retail ELF's loadable segments."""
    phoff, = struct.unpack_from("<I", elf, 28)
    phentsize, phnum = struct.unpack_from("<HH", elf, 42)
    segs = []
    for i in range(phnum):
        p_type, off, vaddr, _, filesz = struct.unpack_from(
            "<IIIII", elf, phoff + i * phentsize)
        if p_type == 1 and filesz:
            segs.append((vaddr, off, filesz))

    def read(vram: int, n: int) -> bytes:
        for vaddr, off, filesz in segs:
            if vaddr <= vram and vram + n <= vaddr + filesz:
                return elf[off + vram - vaddr:off + vram - vaddr + n]
        raise SystemExit(f"extract: 0x{vram:08X} is not in the retail image")
    return read


def literal(code: str, b: bytes) -> str:
    """A data value spelled exactly as scripts/data2c.py writes it."""
    if code == "h":
        return "0x%08Xu" % int.from_bytes(b, "little")
    if code == "f":
        text = format(struct.unpack("<f", b)[0], ".9g")
        if "." not in text and "e" not in text:
            text += ".0"
        return text + "f"
    if code == "d":
        v = int.from_bytes(b, "little")
        return str(v - 0x10000 if len(b) == 2 and v >= 0x8000 else v)
    if code == "s":
        return data2c.escape(b)
    raise SystemExit(f"extract: unknown value code {code!r}")


def render_data(skel: str, read) -> str:
    """One src/main_data file: every `$<code>` refilled from retail."""
    m = DEF_RE.search(skel)
    addr = int(re.search(r"data2c_sizecheck_([0-9A-F]{8})", skel).group(1), 16)
    size = int(re.search(r"\(sizeof\(\w+\) == (\d+)\)", skel).group(1))
    elem = ELEM[m.group(1)]
    if m.group(1) == "char":
        return skel.replace('"$s"', '"' + literal("s", read(addr, size)) + '"', 1)
    start = skel.index("{", m.end()) + 1
    end = skel.index("};", start)
    out, pos = [], start
    for k, item in enumerate(ITEM_RE.finditer(skel, start, end)):
        tok = item.group(0).rstrip()
        out.append(skel[pos:item.start()])
        if tok.startswith("$"):
            out.append(literal(tok[1], read(addr + k * elem, elem)))
        else:
            out.append(tok)
        pos = item.start() + len(tok)
    return skel[:start] + "".join(out) + skel[pos:]


def load_retail(name: str, cache: dict) -> bytes:
    if name not in cache:
        p = rgd.RETAIL_DIR / name
        if not p.exists():
            raise SystemExit(f"extract: {p} is missing -- copy it from your "
                             "disc (see README.md)")
        data = p.read_bytes()
        if hashlib.sha1(data).hexdigest() != SHA1[name]:
            raise SystemExit(f"extract: {p} does not match the retail SHA-1 "
                             f"{SHA1[name]}")
        cache[name] = data
    return cache[name]


def main() -> None:
    force = "--force" in sys.argv[1:]
    cache: dict = {}
    skels = sorted(SKEL.rglob("*.skel"))
    if not skels:
        raise SystemExit(f"extract: no skeletons under {SKEL}")
    for s in skels:
        dest = ASM / s.relative_to(SKEL).with_suffix("")
        if dest.exists() and not force:
            print(f"  {dest.relative_to(ROOT)}: exists, kept (--force rewrites)")
            continue
        skel = s.read_text(encoding="utf-8")
        name = skel.split("\n", 1)[0].split()[2]
        text, _ = render(skel, load_retail(name, cache))
        dest.parent.mkdir(parents=True, exist_ok=True)
        tmp = dest.with_name(dest.name + ".tmp")
        tmp.write_bytes(text.encode("utf-8"))
        tmp.replace(dest)
        print(f"  {dest.relative_to(ROOT)}")
    read = main_reader(load_retail("SCUS_974.90", cache))
    n = 0
    for s in sorted(DSKEL.glob("*.c.skel")):
        dest = DATA / s.name[:-5]
        if dest.exists() and not force:
            continue
        text = render_data(s.read_text(encoding="utf-8"), read)
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(text.encode("utf-8"))
        n += 1
    print(f"  src/main_data: {n} files")
    print("extract: asm/ and src/main_data/ are ready")


if __name__ == "__main__":
    main()
