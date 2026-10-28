#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""List the GS inputs of a recording (src/ps2/gs/gs_rec.c, RG_GS_REC) as text:
privileged writes, VSyncs, FIFO reads, and the GIF packets with their register
writes (PACKED / REGLIST / IMAGE sizes).  docs/GPU.md "Real game validation".

    python tools/gsrec_dump.py FILE.rggs [--fields A-B] [--regs] [--max N]
"""
import argparse
import struct
import sys

REG = {0x00: "PRIM", 0x01: "RGBAQ", 0x02: "ST", 0x03: "UV", 0x04: "XYZF2", 0x05: "XYZ2",
       0x06: "TEX0_1", 0x07: "TEX0_2", 0x08: "CLAMP_1", 0x09: "CLAMP_2", 0x0A: "FOG",
       0x0C: "XYZF3", 0x0D: "XYZ3", 0x14: "TEX1_1", 0x15: "TEX1_2", 0x16: "TEX2_1",
       0x17: "TEX2_2", 0x18: "XYOFFSET_1", 0x19: "XYOFFSET_2", 0x1A: "PRMODECONT",
       0x1B: "PRMODE", 0x1C: "TEXCLUT", 0x22: "SCANMSK", 0x34: "MIPTBP1_1", 0x35: "MIPTBP1_2",
       0x36: "MIPTBP2_1", 0x37: "MIPTBP2_2", 0x3B: "TEXA", 0x3D: "FOGCOL", 0x3F: "TEXFLUSH",
       0x40: "SCISSOR_1", 0x41: "SCISSOR_2", 0x42: "ALPHA_1", 0x43: "ALPHA_2", 0x44: "DIMX",
       0x45: "DTHE", 0x46: "COLCLAMP", 0x47: "TEST_1", 0x48: "TEST_2", 0x49: "PABE",
       0x4A: "FBA_1", 0x4B: "FBA_2", 0x4C: "FRAME_1", 0x4D: "FRAME_2", 0x4E: "ZBUF_1",
       0x4F: "ZBUF_2", 0x50: "BITBLTBUF", 0x51: "TRXPOS", 0x52: "TRXREG", 0x53: "TRXDIR",
       0x54: "HWREG", 0x60: "SIGNAL", 0x61: "FINISH", 0x62: "LABEL"}


def snapshot_len(b):
    o = 8
    vsz = struct.unpack_from("<I", b, o)[0]
    o += 4 + 8 * 128 + 8 * 32 + 4 + 4 + 4 + 3 * vsz + 4 + 4 + 2 * 512 + 4 + 4 + 4 + 4 + 4 + 8 + 4
    n = struct.unpack_from("<I", b, o)[0]
    o += 4 + n
    for _ in range(3):
        o += 4 * 6 + 8 + 4
        n = struct.unpack_from("<I", b, o)[0]
        o += 4 + n
    o += 4 + 7 * 4 + 4 + 4 * 1024 * 1024
    return o


def fmt_reg(a, v):
    name = REG.get(a, "%02X" % a)
    if a in (0x04, 0x05, 0x0C, 0x0D):
        x, y, z = v & 0xFFFF, (v >> 16) & 0xFFFF, v >> 32
        return "%s x=%.4f y=%.4f z=%X" % (name, x / 16.0, y / 16.0, z)
    if a == 0x03:
        return "UV u=%.4f v=%.4f" % ((v & 0x3FFF) / 16.0, ((v >> 16) & 0x3FFF) / 16.0)
    if a == 0x02:
        s, t = struct.unpack("<ff", struct.pack("<Q", v))
        return "ST s=%g t=%g" % (s, t)
    if a == 0x01:
        q = struct.unpack("<f", struct.pack("<I", v >> 32))[0]
        return "RGBAQ %08X q=%g" % (v & 0xFFFFFFFF, q)
    return "%s %016X" % (name, v)


def gif(data, out, regs):
    nq = len(data) // 16
    i = 0
    while i < nq:
        lo, hi = struct.unpack_from("<QQ", data, i * 16)
        nloop, eop, pre = lo & 0x7FFF, (lo >> 15) & 1, (lo >> 46) & 1
        prim, flg, nreg = (lo >> 47) & 0x7FF, (lo >> 58) & 3, (lo >> 60) & 15 or 16
        out.append("    GIFtag nloop=%d eop=%d flg=%d nreg=%d%s regs=%016X" % (
            nloop, eop, flg, nreg, (" PRIM=%03X" % prim) if pre else "", hi))
        i += 1
        if flg == 0:
            for k in range(nloop * nreg):
                if i + k >= nq:
                    break
                a, b = struct.unpack_from("<QQ", data, (i + k) * 16)
                d = (hi >> (4 * (k % nreg))) & 15
                if not regs:
                    continue
                if d == 0xE:
                    out.append("      " + fmt_reg(b & 0xFF, a))
                elif d == 0x5:
                    out.append("      XYZ2(p) x=%.4f y=%.4f z=%X" % ((a & 0xFFFF) / 16, ((a >> 32) & 0xFFFF) / 16, b & 0xFFFFFFFF))
                elif d == 0x1:
                    out.append("      RGBA(p) %02X %02X %02X %02X" % (a & 255, (a >> 32) & 255, b & 255, (b >> 32) & 255))
                elif d == 0x2:
                    s, t, q = struct.unpack("<fff", struct.pack("<QI", a, b & 0xFFFFFFFF))
                    out.append("      STQ(p) %g %g %g" % (s, t, q))
                elif d == 0x3:
                    out.append("      UV(p) %.4f %.4f" % ((a & 0x3FFF) / 16, ((a >> 32) & 0x3FFF) / 16))
                elif d == 0x4:
                    out.append("      XYZF2(p) x=%.4f y=%.4f" % ((a & 0xFFFF) / 16, ((a >> 32) & 0xFFFF) / 16))
                else:
                    out.append("      desc %X: %016X %016X" % (d, a, b))
            i += nloop * nreg
        elif flg == 1:
            i += (nloop * nreg + 1) // 2
        else:
            out.append("      IMAGE %d qwords" % nloop)
            i += nloop


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("file")
    ap.add_argument("--fields", default="")
    ap.add_argument("--regs", action="store_true")
    a = ap.parse_args()
    b = open(a.file, "rb").read()
    if b[:8] != b"RGGSREC1":
        sys.exit("not a GS recording")
    o = snapshot_len(b)
    f0, f1 = 0, 1 << 30
    if a.fields:
        p = a.fields.split("-")
        f0, f1 = int(p[0]), int(p[-1])
    field = 1
    out = []
    while o < len(b):
        kind, aa, v, n = struct.unpack_from("<IIQI", b, o)
        o += 20
        data = b[o:o + n]
        o += n
        if f0 <= field <= f1:
            if kind == 1:
                out.append("GIF path %d, %d qwords" % (aa, n // 16))
                gif(data, out, a.regs)
            elif kind == 2:
                out.append("PRIV %08X = %016X" % (aa, v))
            elif kind == 3:
                out.append("VSYNC (end of field %d)" % field)
            elif kind == 4:
                out.append("GIF_RESET")
            elif kind == 5:
                out.append("FIFO_READ %d bytes" % aa)
        if kind == 3:
            field += 1
    print("\n".join(out))


if __name__ == "__main__":
    main()
