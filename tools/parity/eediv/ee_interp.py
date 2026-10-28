# SPDX-License-Identifier: CC0-1.0
"""Tiny R5900 interpreter for leaf math routines of the retail ELF, with the EE FPU float
model that reproduced 113,903 / 113,903 retail libm calls probed on PCSX2 (docs/BRINGUP.md
"Retail parity"; tools/parity/eediv/rg_ee_ops.cpp):

  MUL, CVT.S.W: exact result rounded toward zero;  ADD / SUB: the operand with the smaller
  exponent keeps one guard bit below the other's ulp (mask 0xFFFFFFFF << (diff - 1), a
  difference of 25 or more leaves only its sign), then toward zero;  DIV: round to nearest
  even, a zero divisor gives sign | 0x7F7FFFFF (PCSX2);  inputs with exponent 0 are zero
  (DAZ), results below 2^-126 are zero (FTZ), overflow gives +-0x7F7FFFFF.

    from ee_interp import EE
    ee = EE()                                   # ../work/SCUS_974.90
    bits = ee.call_f(0x1290B8, [x_bits])        # Tanf_1290b8(x) -> result bits ($f0)

Only the instructions the libm routines use are decoded (an unknown one raises).  Used by
tools/parity/eelibm_check.py (2026-10-24).  Nothing here comes from PCSX2's source.
"""
import math
import struct
from fractions import Fraction

ELF = r"../work/SCUS_974.90"
M32 = 0xFFFFFFFF
M64 = 0xFFFFFFFFFFFFFFFF
RET = 0x00000F00          # sentinel return address
FMAX = 0x7F7FFFFF


def s32(v):
    v &= M32
    return v - (1 << 32) if v & 0x80000000 else v


def sx64(v):              # sign-extend a 32-bit value into a 64-bit register
    return s32(v) & M64


# ---------------------------------------------------------------- EE float model
def fval(b):
    """bits -> exact value as a Python float (DAZ; exponent 255 is a normal number)."""
    e = (b >> 23) & 0xFF
    if e == 0:
        return 0.0
    m = (b & 0x7FFFFF) | 0x800000
    v = math.ldexp(m, e - 150)
    return -v if b & 0x80000000 else v


def fsign(b):
    return b & 0x80000000


def chop(v, neg_zero=False):
    """exact value (Python float or Fraction) -> float bits, toward zero, FTZ, clamp."""
    if v == 0:
        return 0x80000000 if neg_zero else 0
    sign = 0x80000000 if v < 0 else 0
    a = -v if v < 0 else v
    if isinstance(a, Fraction):
        e = a.numerator.bit_length() - a.denominator.bit_length()
        if Fraction(2) ** e > a:
            e -= 1
    else:
        m, e = math.frexp(a)
        e -= 1                       # a in [2^e, 2^(e+1))
    if e < -126:
        return sign
    if e > 128:
        return sign | FMAX
    if isinstance(a, Fraction):
        mant = math.floor(a / Fraction(2) ** (e - 23))
    else:
        mant = int(math.ldexp(a, 23 - e))      # exact scaling, truncation
    if e == 128:                    # EE: exponent 255 exists; keep PCSX2's clamp
        return sign | FMAX
    return sign | ((e + 127) << 23) | (mant - 0x800000)


def rn(q):
    """exact Fraction -> float bits rounded to nearest even (FTZ, clamp)."""
    if q == 0:
        return 0
    sign = 0x80000000 if q < 0 else 0
    a = -q if q < 0 else q
    e = a.numerator.bit_length() - a.denominator.bit_length()
    if Fraction(2) ** e > a:
        e -= 1
    scaled = a / Fraction(2) ** (e - 23)
    mant = math.floor(scaled)
    rem = scaled - mant
    if rem > Fraction(1, 2) or (rem == Fraction(1, 2) and mant & 1):
        mant += 1
    if mant == 0x1000000:
        mant >>= 1
        e += 1
    if e < -126:
        return sign
    if e > 127:
        return sign | FMAX
    return sign | ((e + 127) << 23) | (mant - 0x800000)


def f_align(a, b):
    ea, eb = (a >> 23) & 0xFF, (b >> 23) & 0xFF
    d = ea - eb
    if d < 0:
        d = -d
        if d >= 25:
            a &= 0x80000000
        elif d > 0:
            a &= (M32 << (d - 1)) & M32
    else:
        if d >= 25:
            b &= 0x80000000
        elif d > 0:
            b &= (M32 << (d - 1)) & M32
    return a, b


def f_add(a, b):
    a, b = f_align(a, b)
    va, vb = fval(a), fval(b)
    r = va + vb                     # exact: the aligned operands span <= 26 bits
    if r == 0:
        return 0x80000000 if (va == 0 and vb == 0 and fsign(a) and fsign(b)) else 0
    return chop(r)


def f_sub(a, b):
    return f_add(a, b ^ 0x80000000)


def f_mul(a, b):
    r = fval(a) * fval(b)           # exact: 24 x 24 bits
    return chop(r, neg_zero=bool((a ^ b) & 0x80000000))


def f_div(a, b):
    if ((b >> 23) & 0xFF) == 0:
        return ((a ^ b) & 0x80000000) | FMAX
    va = fval(a)
    if va == 0:
        return (a ^ b) & 0x80000000
    return rn(Fraction(va) / Fraction(fval(b)))


# ---------------------------------------------------------------- the machine
class EE:
    def __init__(self, elf=ELF):
        d = open(elf, "rb").read()
        phoff, = struct.unpack_from("<I", d, 0x1C)
        phentsize, phnum = struct.unpack_from("<HH", d, 0x2A)
        self.segs = []
        for i in range(phnum):
            t, off, va, _, fsz = struct.unpack_from("<5I", d, phoff + i * phentsize)
            if t == 1 and fsz:
                self.segs.append((va, d[off:off + fsz]))
        self.ram = {}
        self.icache = {}

    # memory (word granularity is enough here)
    def rd32(self, a):
        a &= M32
        if a in self.ram:
            return self.ram[a]
        for va, blob in self.segs:
            if va <= a < va + len(blob):
                return struct.unpack_from("<I", blob, a - va)[0]
        return 0

    def wr32(self, a, v):
        self.ram[a & M32] = v & M32

    def call_f(self, addr, fargs=(), iargs=(), max_steps=200000):
        """call addr with float args in $f12, $f13 and int args in a0.. ; returns $f0 bits."""
        self.call(addr, fargs, iargs, max_steps)
        return self.f[0]

    def call(self, addr, fargs=(), iargs=(), max_steps=200000):
        self.ram = {}
        r = [0] * 32
        f = [0] * 32
        for i, v in enumerate(fargs):
            f[12 + i] = v & M32
        for i, v in enumerate(iargs):
            r[4 + i] = v & M64
        r[29] = 0x01F00000
        r[31] = RET
        self.r, self.f = r, f
        self.cc = False
        pc, npc = addr, addr + 4
        steps = 0
        while pc != RET:
            steps += 1
            if steps > max_steps:
                raise RuntimeError("step limit at %08x" % pc)
            w = self.rd32(pc)
            tgt, likely_skip = self.step(pc, w)
            if likely_skip:
                pc, npc = npc + 4, npc + 8
            elif tgt is not None:
                # execute the delay slot
                ds = self.rd32(npc)
                t2, _ = self.step(npc, ds)
                if t2 is not None:
                    raise RuntimeError("branch in delay slot at %08x" % npc)
                pc, npc = tgt, tgt + 4
            else:
                pc, npc = npc, npc + 4
            self.r[0] = 0
        return self.r[2]

    def step(self, pc, w):
        """execute one instruction; returns (branch target or None, skip delay slot)."""
        r, f = self.r, self.f
        op = w >> 26
        rs, rt, rd, sa, fn = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63
        imm = w & 0xFFFF
        simm = imm - 0x10000 if imm & 0x8000 else imm
        btgt = (pc + 4 + (simm << 2)) & M32

        def br(cond, likely=False):
            if cond:
                return btgt, False
            return None, likely

        if op == 0:                                   # SPECIAL
            a, b = r[rs], r[rt]
            if fn == 0x00: r[rd] = sx64((b & M32) << sa)
            elif fn == 0x02: r[rd] = sx64((b & M32) >> sa)
            elif fn == 0x03: r[rd] = sx64(s32(b) >> sa)
            elif fn == 0x04: r[rd] = sx64((b & M32) << (a & 31))
            elif fn == 0x06: r[rd] = sx64((b & M32) >> (a & 31))
            elif fn == 0x07: r[rd] = sx64(s32(b) >> (a & 31))
            elif fn == 0x08: return r[rs] & M32, False   # jr
            elif fn == 0x0A:                              # movz
                if b == 0: r[rd] = a
            elif fn == 0x0B:                              # movn
                if b != 0: r[rd] = a
            elif fn in (0x20, 0x21): r[rd] = sx64(a + b)
            elif fn in (0x22, 0x23): r[rd] = sx64(a - b)
            elif fn == 0x24: r[rd] = a & b
            elif fn == 0x25: r[rd] = a | b
            elif fn == 0x26: r[rd] = a ^ b
            elif fn == 0x27: r[rd] = ~(a | b) & M64
            elif fn == 0x2A: r[rd] = 1 if s32(a) < s32(b) else 0
            elif fn == 0x2B: r[rd] = 1 if (a & M32) < (b & M32) else 0
            elif fn == 0x2D: r[rd] = (a + b) & M64        # daddu (move)
            elif fn == 0x2F: r[rd] = (a - b) & M64        # dsubu
            else:
                raise NotImplementedError("special %02x at %08x" % (fn, pc))
            return None, False
        if op == 1:                                   # REGIMM
            v = s32(r[rs])
            if rt == 0x00: return br(v < 0)
            if rt == 0x01: return br(v >= 0)
            if rt == 0x02: return br(v < 0, True)
            if rt == 0x03: return br(v >= 0, True)
            raise NotImplementedError("regimm %02x at %08x" % (rt, pc))
        if op == 2: return ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2), False
        if op == 3:
            r[31] = pc + 8
            return ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2), False
        if op == 4: return br(r[rs] == r[rt])
        if op == 5: return br(r[rs] != r[rt])
        if op == 6: return br(s32(r[rs]) <= 0)
        if op == 7: return br(s32(r[rs]) > 0)
        if op == 0x14: return br(r[rs] == r[rt], True)
        if op == 0x15: return br(r[rs] != r[rt], True)
        if op == 0x16: return br(s32(r[rs]) <= 0, True)
        if op == 0x17: return br(s32(r[rs]) > 0, True)
        if op in (8, 9): r[rt] = sx64(r[rs] + simm); return None, False
        if op == 0x0A: r[rt] = 1 if s32(r[rs]) < simm else 0; return None, False
        if op == 0x0B: r[rt] = 1 if (r[rs] & M32) < (simm & M32) else 0; return None, False
        if op == 0x0C: r[rt] = r[rs] & imm; return None, False
        if op == 0x0D: r[rt] = r[rs] | imm; return None, False
        if op == 0x0E: r[rt] = r[rs] ^ imm; return None, False
        if op == 0x0F: r[rt] = sx64(imm << 16); return None, False
        ea = (r[rs] + simm) & M32
        if op == 0x23: r[rt] = sx64(self.rd32(ea)); return None, False          # lw
        if op == 0x2B: self.wr32(ea, r[rt]); return None, False                # sw
        if op == 0x37:                                                         # ld
            r[rt] = self.rd32(ea) | (self.rd32(ea + 4) << 32); return None, False
        if op == 0x3F:                                                         # sd
            self.wr32(ea, r[rt]); self.wr32(ea + 4, r[rt] >> 32); return None, False
        if op == 0x31: f[rt] = self.rd32(ea); return None, False               # lwc1
        if op == 0x39: self.wr32(ea, f[rt]); return None, False                # swc1
        if op == 0x11:                                                         # COP1
            fmt = rs
            ft, fs, fd = rt, rd, sa
            if fmt == 0x00: r[rt] = sx64(f[fs]); return None, False            # mfc1
            if fmt == 0x04: f[fs] = r[rt] & M32; return None, False            # mtc1
            if fmt == 0x08:                                                    # bc1
                t = (rt & 1) == 1
                likely = (rt & 2) != 0
                return br(self.cc == t, likely)
            if fmt == 0x10:
                a, b = f[fs], f[ft]
                if fn == 0x00: f[fd] = f_add(a, b)
                elif fn == 0x01: f[fd] = f_sub(a, b)
                elif fn == 0x02: f[fd] = f_mul(a, b)
                elif fn == 0x03: f[fd] = f_div(a, b)
                elif fn == 0x05: f[fd] = a & 0x7FFFFFFF
                elif fn == 0x06: f[fd] = a
                elif fn == 0x07: f[fd] = a ^ 0x80000000
                elif fn == 0x24:                                               # cvt.w.s (trunc)
                    v = fval(a)
                    i = int(v)
                    if i > 0x7FFFFFFF: i = 0x7FFFFFFF
                    if i < -0x80000000: i = -0x80000000
                    f[fd] = i & M32
                elif fn == 0x32: self.cc = fval(a) == fval(b)
                elif fn == 0x34: self.cc = fval(a) < fval(b)
                elif fn == 0x36: self.cc = fval(a) <= fval(b)
                else:
                    raise NotImplementedError("cop1.s %02x at %08x" % (fn, pc))
                return None, False
            if fmt == 0x14 and fn == 0x20:                                     # cvt.s.w
                f[fd] = chop(s32(f[fs]))
                return None, False
            raise NotImplementedError("cop1 fmt %02x fn %02x at %08x" % (fmt, fn, pc))
        raise NotImplementedError("op %02x at %08x (%08x)" % (op, pc, w))
