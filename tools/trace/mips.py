# SPDX-License-Identifier: CC0-1.0
"""Tiny MIPS (R5900 subset) assembler for the probe trampolines and the
in-guest experiment programs (probe.py). Written from the MIPS ISA encoding
tables; nothing here comes from PCSX2.

Usage:
    a = Asm(0x98000)
    a.label("top"); a.lw(T5, 0, T4); a.bne(T5, ZERO, "top"); ...
    words = a.assemble()      # resolves labels; returns list of u32

Branch helpers emit their delay slot as a nop unless delay=False is given
(then the caller emits the next instruction as the slot).
"""
import struct

ZERO, AT, V0, V1, A0, A1, A2, A3 = range(8)
T0, T1, T2, T3, T4, T5, T6, T7 = range(8, 16)
S0, S1, S2, S3, S4, S5, S6, S7 = range(16, 24)
T8, T9, K0, K1, GP, SP, FP, RA = range(24, 32)


def hi(a):
    return ((a + 0x8000) >> 16) & 0xFFFF


def lo(a):
    return a & 0xFFFF


def R(op, rs, rt, rd, sa, fn):
    return (op << 26) | (rs << 21) | (rt << 16) | (rd << 11) | ((sa & 31) << 6) | fn


def I(op, rs, rt, imm):
    return (op << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def J(op, target):
    return (op << 26) | ((target >> 2) & 0x03FFFFFF)


def is_control(w):
    """True for jumps, branches, eret/syscall-like control transfers: words
    that must not be relocated into a trampoline."""
    op = w >> 26
    if op in (0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17, 0x01):
        return True
    if op == 0 and (w & 0x3F) in (0x08, 0x09, 0x0C, 0x0D):   # jr jalr syscall break
        return True
    if op in (0x10, 0x11, 0x12) and ((w >> 21) & 0x1F) == 0x08:  # COPz branches
        return True
    if op == 0x10 and (w & 0x3F) == 0x18:                       # eret
        return True
    return False


class Asm:
    def __init__(self, base):
        self.base = base
        self.code = []
        self.labels = {}
        self.fix = []          # (index, kind, label)

    @property
    def pc(self):
        return self.base + 4 * len(self.code)

    def label(self, name):
        assert name not in self.labels, name
        self.labels[name] = self.pc

    def w(self, word):
        self.code.append(word & 0xFFFFFFFF)

    # ---- plain instructions
    def nop(self): self.w(0)
    def sync(self): self.w(0x0000000F)
    def syscall(self): self.w(0x0000000C)
    def ei(self): self.w(0x42000038)
    def di(self): self.w(0x42000039)
    def mfc0(self, rt, rd): self.w(0x40000000 | (rt << 16) | (rd << 11))
    def addu(self, rd, rs, rt): self.w(R(0, rs, rt, rd, 0, 0x21))
    def daddu(self, rd, rs, rt): self.w(R(0, rs, rt, rd, 0, 0x2D))
    def subu(self, rd, rs, rt): self.w(R(0, rs, rt, rd, 0, 0x23))
    def or_(self, rd, rs, rt): self.w(R(0, rs, rt, rd, 0, 0x25))
    def sltu(self, rd, rs, rt): self.w(R(0, rs, rt, rd, 0, 0x2B))
    def slt(self, rd, rs, rt): self.w(R(0, rs, rt, rd, 0, 0x2A))
    def sll(self, rd, rt, sa): self.w(R(0, 0, rt, rd, sa, 0x00))
    def srl(self, rd, rt, sa): self.w(R(0, 0, rt, rd, sa, 0x02))
    def move(self, rd, rs): self.daddu(rd, rs, ZERO)
    def jr(self, rs): self.w(R(0, rs, 0, 0, 0, 0x08))
    def jalr(self, rs): self.w(R(0, rs, 0, RA, 0, 0x09))
    def addiu(self, rt, rs, imm): self.w(I(0x09, rs, rt, imm))
    def slti(self, rt, rs, imm): self.w(I(0x0A, rs, rt, imm))
    def sltiu(self, rt, rs, imm): self.w(I(0x0B, rs, rt, imm))
    def andi(self, rt, rs, imm): self.w(I(0x0C, rs, rt, imm))
    def ori(self, rt, rs, imm): self.w(I(0x0D, rs, rt, imm))
    def lui(self, rt, imm): self.w(I(0x0F, 0, rt, imm))
    def lw(self, rt, off, base): self.w(I(0x23, base, rt, off))
    def lbu(self, rt, off, base): self.w(I(0x24, base, rt, off))
    def sw(self, rt, off, base): self.w(I(0x2B, base, rt, off))
    def sb(self, rt, off, base): self.w(I(0x28, base, rt, off))
    def lq(self, rt, off, base): self.w(I(0x1E, base, rt, off))
    def sq(self, rt, off, base): self.w(I(0x1F, base, rt, off))

    # ---- pseudo
    def li(self, rt, v):
        v &= 0xFFFFFFFF
        if v < 0x8000 or v >= 0xFFFF8000:
            self.addiu(rt, ZERO, v)
        elif v & 0xFFFF == 0:
            self.lui(rt, v >> 16)
        else:
            self.lui(rt, hi(v))
            self.addiu(rt, rt, lo(v))

    def lwa(self, rt, addr, tmp=AT):
        self.lui(tmp, hi(addr))
        self.lw(rt, lo(addr), tmp)

    def swa(self, rt, addr, tmp=AT):
        self.lui(tmp, hi(addr))
        self.sw(rt, lo(addr), tmp)

    def sys(self, num):
        """Inline syscall (as the libkernl stubs do): v1 = num; syscall."""
        self.addiu(V1, ZERO, num)
        self.syscall()

    # ---- control flow with labels / absolute targets
    def _branch(self, op, rs, rt, target, delay):
        self.fix.append((len(self.code), "b", target))
        self.w(I(op, rs, rt, 0))
        if delay:
            self.nop()

    def beq(self, rs, rt, target, delay=True): self._branch(0x04, rs, rt, target, delay)
    def bne(self, rs, rt, target, delay=True): self._branch(0x05, rs, rt, target, delay)
    def blez(self, rs, target, delay=True): self._branch(0x06, rs, 0, target, delay)
    def bgtz(self, rs, target, delay=True): self._branch(0x07, rs, 0, target, delay)
    def b(self, target, delay=True): self._branch(0x04, 0, 0, target, delay)

    def bltz(self, rs, target, delay=True):
        self.fix.append((len(self.code), "b", target))
        self.w(I(0x01, rs, 0, 0))
        if delay:
            self.nop()

    def j(self, target, delay=True):
        self.fix.append((len(self.code), "j", target))
        self.w(J(2, 0))
        if delay:
            self.nop()

    def jal(self, target, delay=True):
        self.fix.append((len(self.code), "jal", target))
        self.w(J(3, 0))
        if delay:
            self.nop()

    def assemble(self):
        for idx, kind, target in self.fix:
            t = self.labels[target] if isinstance(target, str) else target
            here = self.base + 4 * idx
            if kind == "hi":
                self.code[idx] |= hi(t)
                continue
            if kind == "lo":
                self.code[idx] |= lo(t)
                continue
            if kind == "b":
                off = (t - (here + 4)) >> 2
                assert -0x8000 <= off < 0x8000, (target, off)
                self.code[idx] = (self.code[idx] & 0xFFFF0000) | (off & 0xFFFF)
            else:
                assert (t & 0xF0000000) == (here & 0xF0000000)
                self.code[idx] |= (t >> 2) & 0x03FFFFFF
        return list(self.code)

    def blob(self):
        words = self.assemble()
        return struct.pack("<%dI" % len(words), *words)
