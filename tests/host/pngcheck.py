# SPDX-License-Identifier: CC0-1.0
"""Independent PNG check for rg_png_encode: decode with Python's zlib and
compare every pixel with the test image of host_tests.c (cmd png_write)."""
import struct
import sys
import zlib


def main(path):
    data = open(path, "rb").read()
    assert data[:8] == b"\x89PNG\r\n\x1a\n", "signature"
    off, idat, ihdr = 8, b"", None
    while off < len(data):
        (n,) = struct.unpack(">I", data[off:off + 4])
        typ = data[off + 4:off + 8]
        body = data[off + 8:off + 8 + n]
        (crc,) = struct.unpack(">I", data[off + 8 + n:off + 12 + n])
        assert zlib.crc32(typ + body) & 0xFFFFFFFF == crc, "crc %r" % typ
        if typ == b"IHDR":
            ihdr = struct.unpack(">IIBBBBB", body)
        elif typ == b"IDAT":
            idat += body
        off += 12 + n
    w, h, depth, ctype, comp, filt, inter = ihdr
    assert (depth, ctype, comp, filt, inter) == (8, 6, 0, 0, 0), ihdr
    raw = zlib.decompress(idat)
    assert len(raw) == h * (1 + 4 * w)
    for y in range(h):
        row = raw[y * (1 + 4 * w):(y + 1) * (1 + 4 * w)]
        assert row[0] == 0, "filter"
        for x in range(w):
            want = ((x * 7 + y) & 255, (x ^ y) & 255, (x * y) & 255, (255 - x) & 255)
            got = tuple(row[1 + 4 * x:5 + 4 * x])
            assert got == want, (x, y, got, want)
    print("%s: %dx%d decoded by zlib, all pixels match" % (path, w, h))


if __name__ == "__main__":
    main(sys.argv[1])
