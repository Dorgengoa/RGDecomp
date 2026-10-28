#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Lift the MWo3 overlays' static-initializer functions (MIPS) to C.

At naming 2efa6b43 every overlay's `.ctors` targets are NOT C: they sit in the
overlay's .data section (title 0x004F1700..0x004F18A0, ...) and the snapshot
carries them as opaque `.word` data (config/<ov>.symbols.txt: "clamped out").
There are 62 of them across the five overlays (4/2/17/22/17).  They are
compiler-generated `__sinit_<tu>` bodies: construct a TU's static objects
(`ios_base::Init`, MemStacks, factory part tables, ...), register their
destructors with RegisterGlobalObject_100dc0, copy a few gp words.

This module is a *symbolic executor* for that restricted shape, not a
recompiler:

  * every register value is a constant (immediates, lui/addiu addresses,
    $gp-relative addresses), an expression already materialised in a C temp,
    or undefined;
  * every branch condition must fold to a constant (they all do: the only
    branches are mwcc's `&sym != 0 ? x : y` diamonds, whose condition is a
    link-time address) -- a data-dependent branch or a loop is an ERROR;
  * calls are marshalled with the R5900 EABI (ints in $4..$11, floats in
    $f12..$f19, the rest in 8-byte stack slots) against the CALLEE'S C
    PROTOTYPE (game_protos.h, or BUILTIN_PROTOS for asm-bodied library code);
  * loads/stores that are not to the stack frame become C statements, in
    program order (loads are materialised into temps immediately).

Anything outside the subset raises LiftError with the address -- nothing is
guessed.  The caller (tools/gen_overlay_registry.py) turns addresses into C
spellings through a `namer` callback.
"""
from __future__ import annotations

import re
import struct
from dataclasses import dataclass, field

GP = 0x00485170

# Prototypes for asm-bodied MAIN library functions the ctors call (they have
# no C definition in game/, so game_protos.h has no line for them).
# Evidence: the asm listings at naming 2efa6b43 (argument registers read).
BUILTIN_PROTOS = {
    # MSL ios_base::Init::Init(this) -- reads only $4
    "IosBaseInitCtor_102bd0": ("void *", ["void *"]),
    "WIosBaseInitCtor_103110": ("void *", ["void *"]),
    # MSL __construct_array(block $4, ctor $5, dtor $6, size $7, n $8)
    "ConstructArray_100620": ("void *", ["void *", "void *", "void *",
                                         "unsigned int", "unsigned int"]),
}

FLOAT_TYPES = {"float", "f32"}
BAD_TYPES = {"double", "f64", "long long", "unsigned long long", "s64", "u64"}


class LiftError(Exception):
    pass


@dataclass
class Val:
    kind: str                 # 'c' const, 'e' C expression (temp), 'u' undefined
    v: object = None          # int for 'c', str for 'e'
    addr: bool = False        # const that came from lui/$gp (an address)
    ftype: str = "i"          # 'i' int, 'f' float (for 'e'); for FPR 'c' = raw bits

    @staticmethod
    def c(n: int, addr: bool = False) -> "Val":
        return Val("c", n & 0xFFFFFFFF, addr)


U = Val("u")


def s16(x: int) -> int:
    return x - 0x10000 if x & 0x8000 else x


def f32_literal(bits: int) -> str:
    f = struct.unpack("<f", struct.pack("<I", bits))[0]
    if f != f or f in (float("inf"), float("-inf")):
        raise LiftError(f"non-finite float constant 0x{bits:08X}")
    if bits & 0x7F800000 == 0 and bits & 0x7FFFFF:
        raise LiftError(f"denormal float constant 0x{bits:08X}")
    return f"{f.hex()}f" if f != 0.0 else ("-0.0f" if bits >> 31 else "0.0f")


@dataclass
class Lifted:
    name: str                 # C function name
    addr: int
    body: list = field(default_factory=list)   # C lines
    callees: set = field(default_factory=set)
    ninsn: int = 0


def parse_protos(text: str) -> dict:
    """game_protos.h lines `ret name(params);` -> {name: (ret, [types])}."""
    out = {}
    for m in re.finditer(r"^([A-Za-z_][\w \*]*?)\s*\b(\w+)\s*\(([^;()]*)\)\s*;", text, re.M):
        ret, name, params = m.group(1).strip(), m.group(2), m.group(3).strip()
        if ret.startswith(("typedef", "#", "extern \"C\"")):
            continue
        if params in ("", "void"):
            plist = []
        else:
            plist = [p.strip() for p in params.split(",")]
        out[name] = (ret, plist)
    return out


def _ptype_class(t: str) -> str:
    t = " ".join(t.replace("const", " ").split())
    if t in FLOAT_TYPES:
        return "f"
    if t in BAD_TYPES or t == "...":
        return "x"
    return "i"


class Lifter:
    """namer(addr, is_addr, want) -> C text for a constant used as a value.

    want is the C parameter/store type the value lands in ('void *', 'int', ...).
    callee_name(addr) -> MAIN/overlay function name for a jal target (or None).
    """

    def __init__(self, image: bytes, load: int, namer, callee_name, protos: dict):
        self.image = image
        self.load = load
        self.namer = namer
        self.callee_name = callee_name
        self.protos = dict(BUILTIN_PROTOS)
        self.protos.update(protos)

    def word(self, a: int) -> int:
        o = a - self.load
        if o < 0 or o + 4 > len(self.image):
            raise LiftError(f"pc 0x{a:08X} outside the image")
        return struct.unpack_from("<I", self.image, o)[0]

    # ------------------------------------------------------------ helpers
    def lift(self, addr: int, cname: str, max_insn: int = 4000) -> Lifted:
        L = Lifted(cname, addr)
        self.L = L
        self.ntemp = 0
        gpr = [U] * 32
        gpr[0] = Val.c(0)
        gpr[28] = Val.c(GP, True)
        gpr[29] = Val("sp", 0)
        gpr[31] = Val("ra")
        fpr = [U] * 32
        self.stack = {}                 # entry-sp-relative offset -> (Val, width)
        self.gpr, self.fpr = gpr, fpr
        pc = addr
        steps = 0
        while True:
            steps += 1
            if steps > max_insn:
                raise LiftError(f"0x{addr:08X}: more than {max_insn} instructions")
            w = self.word(pc)
            kind, info = self.decode(pc, w)
            if kind == "jr":
                if info != 31:
                    raise LiftError(f"0x{pc:08X}: jr ${info}")
                self.exec_plain(pc + 4, self.word(pc + 4))
                break
            if kind == "branch":
                cond, target, likely = info
                taken = cond()
                if taken or not likely:
                    self.exec_plain(pc + 4, self.word(pc + 4))
                if taken:
                    if target <= pc:
                        raise LiftError(f"0x{pc:08X}: backward branch (loop) to 0x{target:08X}")
                    pc = target
                else:
                    pc += 8
                continue
            if kind == "jal":
                self.exec_plain(pc + 4, self.word(pc + 4))
                self.call(pc, info)
                pc += 8
                continue
            self.exec_plain(pc, w)
            pc += 4
        L.ninsn = steps
        return L

    def temp(self, ctype: str, expr: str) -> str:
        self.ntemp += 1
        n = f"t{self.ntemp}"
        self.L.body.append(f"{ctype} {n} = {expr};")
        return n

    def need(self, v: Val, pc: int, what: str) -> Val:
        if v.kind == "u":
            raise LiftError(f"0x{pc:08X}: {what} reads an undefined register")
        return v

    def as_c(self, v: Val, want: str, pc: int) -> str:
        """C text for value v landing in a slot of C type `want`."""
        self.need(v, pc, "value")
        if v.kind in ("sp", "ra"):
            raise LiftError(f"0x{pc:08X}: stack/return address escapes")
        cls = _ptype_class(want)
        if v.kind == "e":
            if cls == "f" and v.ftype != "f":
                raise LiftError(f"0x{pc:08X}: int value passed as float")
            if cls == "i" and v.ftype == "f":
                raise LiftError(f"0x{pc:08X}: float value passed as int")
            return v.v if cls == "f" else f"({want})({v.v})"
        # constant
        if cls == "f":
            return f32_literal(v.v)
        return self.namer(v.v, v.addr, want)

    def addr_of(self, base: Val, off: int, pc: int):
        """(kind, value): ('stack', entry-sp offset) or ('mem', C pointer text)."""
        self.need(base, pc, "address base")
        if base.kind == "sp":
            return "stack", base.v + off
        if base.kind == "c":
            return "mem", self.namer((base.v + off) & 0xFFFFFFFF, True, "void *")
        if base.kind == "e" and base.ftype == "i":
            return "mem", f"((unsigned char *)({base.v}) + {off})"
        raise LiftError(f"0x{pc:08X}: unsupported address base")

    # ------------------------------------------------------------ decode
    def decode(self, pc: int, w: int):
        op = w >> 26
        rs, rt = (w >> 21) & 31, (w >> 16) & 31
        imm = s16(w & 0xFFFF)
        g = self.gpr

        def val(r):
            return g[r]

        if op == 0 and (w & 0x3F) == 0x08:
            return "jr", rs
        if op == 3:
            return "jal", ((pc + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
        if op in (4, 5, 0x14, 0x15, 6, 7, 0x16, 0x17):
            target = (pc + 4 + (imm << 2)) & 0xFFFFFFFF
            likely = op >= 0x14

            def k(r):
                v = self.need(val(r), pc, "branch")
                if v.kind != "c":
                    raise LiftError(f"0x{pc:08X}: data-dependent branch")
                return v.v

            base = op & ~0x10

            def cond():
                a = k(rs)
                if base == 4:
                    return a == k(rt)
                if base == 5:
                    return a != k(rt)
                sa = a - (1 << 32) if a & 0x80000000 else a
                if base == 6:
                    return sa <= 0
                return sa > 0
            return "branch", (cond, target, likely)
        return "plain", None

    def exec_plain(self, pc: int, w: int):
        op = w >> 26
        rs, rt, rd = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        imm = s16(w & 0xFFFF)
        uimm = w & 0xFFFF
        g, f = self.gpr, self.fpr
        kind, _ = self.decode(pc, w)
        if kind != "plain":
            raise LiftError(f"0x{pc:08X}: control transfer in a delay slot")

        def setg(r, v):
            if r != 0:
                g[r] = v

        def cval(r, what):
            v = self.need(g[r], pc, what)
            return v

        if op == 0:
            fn = w & 0x3F
            if w == 0:
                return
            if fn in (0x2D, 0x21, 0x25):            # daddu/addu/or (move or add)
                a, b = g[rs], g[rt]
                if rt == 0:
                    setg(rd, a)
                    return
                if rs == 0:
                    setg(rd, b)
                    return
                a, b = cval(rs, "add"), cval(rt, "add")
                if a.kind == "c" and b.kind == "c":
                    if fn == 0x25:
                        setg(rd, Val.c(a.v | b.v, a.addr or b.addr))
                    else:
                        setg(rd, Val.c(a.v + b.v, a.addr or b.addr))
                    return
                raise LiftError(f"0x{pc:08X}: non-constant add/or")
            if fn in (0x2B, 0x2A):                  # sltu / slt
                a, b = cval(rs, "slt"), cval(rt, "slt")
                if a.kind == "c" and b.kind == "c":
                    if fn == 0x2B:
                        setg(rd, Val.c(1 if a.v < b.v else 0))
                    else:
                        sa = a.v - (1 << 32) if a.v >> 31 else a.v
                        sb = b.v - (1 << 32) if b.v >> 31 else b.v
                        setg(rd, Val.c(1 if sa < sb else 0))
                    return
                raise LiftError(f"0x{pc:08X}: non-constant compare")
            if fn == 0x00:                          # sll
                a = cval(rt, "sll")
                if a.kind != "c":
                    raise LiftError(f"0x{pc:08X}: non-constant sll")
                setg(rd, Val.c(a.v << ((w >> 6) & 31)))
                return
            raise LiftError(f"0x{pc:08X}: unsupported SPECIAL funct 0x{fn:02X} ({w:08X})")
        if op == 9:                                  # addiu
            if rs == 29 and rt == 29:
                if g[29].kind != "sp":
                    raise LiftError(f"0x{pc:08X}: sp lost")
                g[29] = Val("sp", g[29].v + imm)
                return
            a = cval(rs, "addiu")
            if a.kind == "sp":
                setg(rt, Val("sp", a.v + imm))
                return
            if a.kind != "c":
                raise LiftError(f"0x{pc:08X}: addiu on a non-constant")
            setg(rt, Val.c(a.v + imm, a.addr or rs == 28))
            return
        if op == 0x0D:                               # ori
            a = cval(rs, "ori")
            if a.kind != "c":
                raise LiftError(f"0x{pc:08X}: ori on a non-constant")
            setg(rt, Val.c(a.v | uimm, a.addr))
            return
        if op == 0x0F:                               # lui
            setg(rt, Val.c(uimm << 16, True))
            return
        if op in (0x0B, 0x0A):                       # sltiu / slti
            a = cval(rs, "slti")
            if a.kind != "c":
                raise LiftError(f"0x{pc:08X}: slti on a non-constant")
            b = imm & 0xFFFFFFFF
            if op == 0x0B:
                setg(rt, Val.c(1 if a.v < b else 0))
            else:
                sa = a.v - (1 << 32) if a.v >> 31 else a.v
                setg(rt, Val.c(1 if sa < imm else 0))
            return
        # ---- memory
        if op in (0x3F, 0x2B, 0x1F, 0x28, 0x29):     # sd sw sq sb sh
            width = {0x3F: 8, 0x2B: 4, 0x1F: 16, 0x28: 1, 0x29: 2}[op]
            where, a = self.addr_of(g[rs], imm, pc)
            v = g[rt]
            if where == "stack":
                self.stack[a] = (v, width)
                return
            if width in (8, 16):
                raise LiftError(f"0x{pc:08X}: {width*8}-bit store to memory")
            ctype = {4: "int", 2: "short", 1: "signed char"}[width]
            self.L.body.append(f"*({ctype} *)({a}) = {self.as_c(v, ctype, pc)};")
            return
        if op in (0x37, 0x23, 0x1E, 0x20, 0x24, 0x21, 0x25):  # ld lw lq lb lbu lh lhu
            where, a = self.addr_of(g[rs], imm, pc)
            if where == "stack":
                ent = self.stack.get(a)
                setg(rt, ent[0] if ent else U)      # epilogue restores ($31 etc.)
                return
            if op in (0x37, 0x1E):
                raise LiftError(f"0x{pc:08X}: 64/128-bit load from memory")
            ctype = {0x23: "int", 0x20: "signed char", 0x24: "unsigned char",
                     0x21: "short", 0x25: "unsigned short"}[op]
            setg(rt, Val("e", self.temp("int", f"*({ctype} *)({a})")))
            return
        if op == 0x31:                               # lwc1
            where, a = self.addr_of(g[rs], imm, pc)
            if where == "stack":
                ent = self.stack.get(a)
                f[rt] = ent[0] if ent else U
                return
            f[rt] = Val("e", self.temp("float", f"*(float *)({a})"), ftype="f")
            return
        if op == 0x39:                               # swc1
            where, a = self.addr_of(g[rs], imm, pc)
            if where == "stack":
                self.stack[a] = (f[rt], 4)
                return
            self.L.body.append(f"*(float *)({a}) = {self.as_c(f[rt], 'float', pc)};")
            return
        if op == 0x11:                               # COP1
            fmt = rs
            ft, fs, fd = rt, rd, (w >> 6) & 31
            if fmt == 4:                             # mtc1 rt -> fs
                v = cval(rt, "mtc1")
                if v.kind == "c":
                    f[fs] = Val.c(v.v)
                    return
                f[fs] = Val("e", self.temp("float", f"rg_ovl_bits_f32({v.v})"), ftype="f")
                return
            if fmt == 0x10:
                fn = w & 0x3F
                if fn == 6:                          # mov.s
                    f[fd] = f[fs]
                    return
                ops = {0: "+", 1: "-", 2: "*", 3: "/"}
                if fn in ops:
                    a = self.as_c(self.need(f[fs], pc, "fpu"), "float", pc)
                    b = self.as_c(self.need(f[ft], pc, "fpu"), "float", pc)
                    f[fd] = Val("e", self.temp("float", f"{a} {ops[fn]} {b}"), ftype="f")
                    return
                if fn == 7:
                    a = self.as_c(self.need(f[fs], pc, "fpu"), "float", pc)
                    f[fd] = Val("e", self.temp("float", f"-{a}"), ftype="f")
                    return
            raise LiftError(f"0x{pc:08X}: unsupported COP1 {w:08X}")
        raise LiftError(f"0x{pc:08X}: unsupported opcode {op:#x} ({w:08X})")

    # ------------------------------------------------------------ calls
    def call(self, pc: int, target: int):
        name = self.callee_name(target)
        if not name:
            raise LiftError(f"0x{pc:08X}: jal 0x{target:08X} has no symbol")
        proto = self.protos.get(name)
        if proto is None:
            raise LiftError(f"0x{pc:08X}: no prototype for {name}")
        ret, params = proto
        if params and params[-1] == "...":
            raise LiftError(f"0x{pc:08X}: varargs callee {name}")
        sp = self.gpr[29]
        if sp.kind != "sp":
            raise LiftError(f"0x{pc:08X}: sp lost at call")
        ni = nf = ns = 0
        args = []
        for t in params:
            cls = _ptype_class(t)
            if cls == "x":
                raise LiftError(f"0x{pc:08X}: {name} parameter type {t!r} unsupported")
            if cls == "f" and nf < 8:
                v = self.fpr[12 + nf]
                nf += 1
            elif cls == "i" and ni < 8:
                v = self.gpr[4 + ni]
                ni += 1
            else:
                ent = self.stack.get(sp.v + 8 * ns)
                ns += 1
                if ent is None:
                    raise LiftError(f"0x{pc:08X}: {name} stack argument {ns} not stored")
                v = ent[0]
            if v.kind == "u":
                raise LiftError(f"0x{pc:08X}: {name} argument {len(args)+1} ({t}) undefined")
            args.append(self.as_c(v, t, pc))
        self.L.callees.add(name)
        call = f"{name}({', '.join(args)})"
        # clobber caller-saved state
        for r in list(range(1, 16)) + [24, 25]:
            self.gpr[r] = U
        for r in range(0, 20):
            self.fpr[r] = U
        rc = " ".join(ret.replace("const", " ").split())
        if rc == "void":
            self.L.body.append(call + ";")
        elif _ptype_class(rc) == "f":
            self.fpr[0] = Val("e", self.temp("float", call), ftype="f")
        else:
            self.gpr[2] = Val("e", self.temp("int", f"(int)({call})"))


def ctor_table(image: bytes, load: int, data_vram: int, end: int):
    """link_overlay.py's rule: the .ctors table is the maximal run of words at
    the END of .data that point inside the loaded overlay (trailing zeros
    ignored); .dtors starts right after it and is empty (its null)."""
    d0 = data_vram - load
    data = image[d0:]
    words = [struct.unpack_from("<I", data, i)[0] for i in range(0, len(data) - 3, 4)]
    i = len(words) - 1
    while i >= 0 and words[i] == 0:
        i -= 1
    stop = i + 1
    while i >= 0 and load <= words[i] < end:
        i -= 1
    start = i + 1
    if start >= stop:
        return end, end, []
    return data_vram + 4 * start, data_vram + 4 * stop, words[start:stop]
