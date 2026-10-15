"""hosted.py -- a `static` function that lives in ANOTHER unit's translation unit.

config/hosted.txt rows are `GUEST HOST`: GUEST is defined `static` inside HOST's
source, as in the original TU (mwcc only compiles a caller with a static callee's
real clobber set when the callee is in the same TU -- see MovieReadThread_1d4f50, whose
retail code keeps $a2 live across its jal to ReadBufEndGet_1d32c0).  mwcc emits one
`.text` per function, but the lcf line `HOST.o (.text)` would lay both down
contiguously at HOST's address.  So before linking, the GUEST's `.text` in
HOST.o is renamed `.text.GUEST`, and the lcf places that section at GUEST's slot.
mwcc rejects a section attribute on a function (`illegal type qualifier`), so
the rename has to happen on the object.
"""
import struct
from pathlib import Path


def load(path: Path) -> dict:
    """{guest: host}"""
    if not path.exists():
        return {}
    out = {}
    for ln in path.read_text().splitlines():
        f = ln.split("#")[0].split()
        if f:
            out[f[0]] = f[1]
    return out


def _secs(d):
    shoff, = struct.unpack_from("<I", d, 32)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", d, 46)
    return shoff, shentsize, shnum, shstrndx


def section_name(d, i):
    shoff, es, n, sx = _secs(d)
    so = struct.unpack_from("<I", d, shoff + sx * es + 16)[0]
    nm = struct.unpack_from("<I", d, shoff + i * es)[0]
    return d[so + nm:d.index(b"\0", so + nm)].decode()


def section_size(d, want):
    """(size, addralign) of the section named `want`, or (0, 0)."""
    shoff, es, n, sx = _secs(d)
    for i in range(n):
        if section_name(d, i) == want:
            size, = struct.unpack_from("<I", d, shoff + i * es + 20)
            align, = struct.unpack_from("<I", d, shoff + i * es + 32)
            return size, align
    return 0, 0


def guest_section(d, guest):
    """Index of the section holding the FUNC symbol `guest`, or None."""
    shoff, es, n, sx = _secs(d)
    for i in range(n):
        typ, = struct.unpack_from("<I", d, shoff + i * es + 4)
        if typ != 2:  # SHT_SYMTAB
            continue
        off, size, link = struct.unpack_from("<III", d, shoff + i * es + 16)
        stroff, = struct.unpack_from("<I", d, shoff + link * es + 16)
        for k in range(size // 16):
            st_name, _v, _s, st_info, _o, st_shndx = struct.unpack_from(
                "<IIIBBH", d, off + k * 16)
            nm = d[stroff + st_name:d.index(b"\0", stroff + st_name)].decode()
            if nm == guest and (st_info & 0xF) == 2:  # STT_FUNC
                return st_shndx
    return None


def rename_guest(data: bytes, guest: str) -> bytes:
    """HOST object bytes with GUEST's `.text` renamed `.text.GUEST`.

    The new name is appended to a copy of .shstrtab placed at the end of the
    file; every other byte and offset is left as it was.
    """
    d = bytearray(data)
    idx = guest_section(d, guest)
    if idx is None or section_name(d, idx) != ".text":
        raise ValueError(f"{guest}: no `.text` FUNC section in the host object")
    shoff, es, n, sx = _secs(d)
    so, ssz = struct.unpack_from("<II", d, shoff + sx * es + 16)
    blob = bytes(d[so:so + ssz]) + f".text.{guest}".encode() + b"\0"
    at = len(d)
    d += blob
    struct.pack_into("<II", d, shoff + sx * es + 16, at, len(blob))
    struct.pack_into("<I", d, shoff + idx * es, ssz)
    return bytes(d)
