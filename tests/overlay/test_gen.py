#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Unit tests for the overlay registry generator pieces, on synthetic fixtures
(no snapshot, no game data): tools/ovl_lift.py (MIPS static-initializer
lifter), gen_overlay_registry.parse_data_asm / ctor_table, and the ovlsyms
ingest stage.

    python tests/overlay/test_gen.py            all must pass
    python tests/overlay/test_gen.py control    deliberately wrong (ovlsyms table
                                                shifted by 0x10): must FAIL
"""
from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools"))
sys.path.insert(0, str(PORT / "tools" / "stages"))
import gen_overlay_registry as gen  # noqa: E402
import ovl_lift  # noqa: E402
import ovlsyms  # noqa: E402

CONTROL = len(sys.argv) > 1 and sys.argv[1] == "control"
if CONTROL:
    sys.argv.pop(1)
    lo, hi = ovlsyms.OVERLAY_DATA["normal"]
    ovlsyms.OVERLAY_DATA["normal"] = (lo + 0x10, hi)


# --------------------------------------------------------------- a tiny R5900 assembler
def R(op, rs, rt, rd, sa, fn):
    return (op << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | fn


def I(op, rs, rt, imm):
    return (op << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def addiu(rt, rs, imm): return I(9, rs, rt, imm)
def lui(rt, imm): return I(0xF, 0, rt, imm)
def daddu(rd, rs, rt): return R(0, rs, rt, rd, 0, 0x2D)
def sltu(rd, rs, rt): return R(0, rs, rt, rd, 0, 0x2B)
def lw(rt, off, base): return I(0x23, base, rt, off)
def sw(rt, off, base): return I(0x2B, base, rt, off)
def sd(rt, off, base): return I(0x3F, base, rt, off)
def ld(rt, off, base): return I(0x37, base, rt, off)
def lwc1(ft, off, base): return I(0x31, base, ft, off)
def mtc1(rt, fs): return R(0x11, 4, rt, fs, 0, 0)
def mul_s(fd, fs, ft): return R(0x11, 0x10, ft, fs, fd, 2)
def jal(t): return (3 << 26) | ((t >> 2) & 0x3FFFFFF)
def jr(rs): return R(0, rs, 0, 0, 0, 8)
def beq(rs, rt, off): return I(4, rs, rt, off)
def beql(rs, rt, off): return I(0x14, rs, rt, off)
def bnez(rs, off): return I(5, rs, 0, off)
def jalr(rs): return R(0, rs, 0, 31, 0, 9)


NOP = 0
SP, RA, GP, V0, A0, A1, A2, A3, T0, T1, T2, T3 = 29, 31, 28, 2, 4, 5, 6, 7, 8, 9, 10, 11
LOAD = 0x00510000          # where the fixture "code" sits (an overlay data address)
MAIN_FN = {0x00101000: "CtorA", 0x00101100: "Register", 0x00101200: "Many",
           0x00101300: "Fl", 0x00101400: "Nop"}
PROTOS = {
    "CtorA": ("void *", ["void *"]),
    "Register": ("int", ["int", "int", "void *"]),
    "Many": ("void *", ["void *"] + ["int"] * 9),
    "Fl": ("void", ["void *", "float", "short", "float"]),
    "Nop": ("void", []),
}


def prologue():
    return [addiu(SP, SP, -0x20), sd(RA, 0x10, SP)]


def epilogue():
    return [ld(RA, 0x10, SP), jr(RA), addiu(SP, SP, 0x20)]


def namer(v, is_addr, want):
    if not is_addr:
        return f"({want})0x{v:X}"
    if v in MAIN_FN:
        return f"({want})&{MAIN_FN[v]}"
    return f"({want})A_{v:08X}"


def lift(words, protos=PROTOS):
    img = b"".join(struct.pack("<I", w) for w in words)
    lf = ovl_lift.Lifter(img, LOAD, namer, MAIN_FN.get, protos)
    return lf.lift(LOAD, "sinit_test")


class LifterTests(unittest.TestCase):
    def test_ctor_register_and_gp_copy(self):
        # the shape of every overlay TU's __sinit: construct a gp object,
        # register its dtor, copy one gp word to another
        w = prologue() + [
            jal(0x00101000), addiu(A0, GP, -0x1000),
            lui(A1, 0x10), addiu(A0, GP, -0x1000), addiu(A1, A1, 0x1400),
            jal(0x00101100), addiu(A2, GP, -0x100C),
            lw(3, -0x4000, GP), sw(3, -0x3F00, GP),
        ] + epilogue()
        L = lift(w)
        gp = ovl_lift.GP
        self.assertEqual(L.body, [
            f"int t1 = (int)(CtorA((void *)A_{gp - 0x1000:08X}));",
            f"int t2 = (int)(Register((int)A_{gp - 0x1000:08X}, (int)&Nop, (void *)A_{gp - 0x100C:08X}));",
            f"int t3 = *(int *)((void *)A_{gp - 0x4000:08X});",
            f"*(int *)((void *)A_{gp - 0x3F00:08X}) = (int)(t3);",
        ])
        self.assertEqual(L.callees, {"CtorA", "Register"})

    def test_constant_diamond_and_stack_args(self):
        # mwcc's `&sym ? 16 : 0` diamond (branch-likely, condition = link-time
        # address) and EABI stack arguments 9 and 10 (8-byte slots)
        w = [addiu(SP, SP, -0x40), sd(RA, 0x30, SP),
             lui(V0, 0x51), addiu(V0, V0, 0x40),
             beql(V0, 0, 2), daddu(A0, 0, 0),            # not taken -> slot skipped
             addiu(A0, 0, 16),
             addiu(A1, 0, 1), addiu(A2, 0, 2), addiu(A3, 0, 3),
             addiu(T0, 0, 4), addiu(T1, 0, 5), addiu(T2, 0, 6), addiu(T3, 0, 7),
             addiu(3, 0, 9), sd(3, 0, SP), addiu(3, 0, 10), sd(3, 8, SP),
             jal(0x00101200), addiu(T3, 0, 8),
             ld(RA, 0x30, SP), jr(RA), addiu(SP, SP, 0x40)]
        # A0 = 16 is a non-address constant passed as void *
        L = lift(w)
        self.assertEqual(L.body, ["int t1 = (int)(Many((void *)0x10, (int)0x1, (int)0x2, (int)0x3, "
                                  "(int)0x4, (int)0x5, (int)0x6, (int)0x8, (int)0x9, (int)0xA));"])  # t3 = 8: the delay slot runs before the call

    def test_taken_branch_likely_executes_slot(self):
        w = prologue() + [
            daddu(V0, 0, 0),
            beql(V0, 0, 2), addiu(A0, 0, 5),             # taken: slot runs, skip next
            addiu(A0, 0, 7),
            jal(0x00101000), NOP,
        ] + epilogue()
        self.assertIn("CtorA((void *)0x5)", lift(w).body[0])

    def test_float_args(self):
        w = prologue() + [
            lwc1(12, -0x2000, GP),
            lui(3, 0x40C0), mtc1(3, 1), mul_s(13, 12, 1),
            lui(A0, 0x51), addiu(A0, A0, 0x100), addiu(A1, 0, -2),
            jal(0x00101300), NOP,
        ] + epilogue()
        L = lift(w)
        self.assertEqual(L.body[0], f"float t1 = *(float *)((void *)A_{ovl_lift.GP - 0x2000:08X});")
        self.assertEqual(L.body[1], "float t2 = t1 * 0x1.8000000000000p+2f;")
        self.assertEqual(L.body[2], "Fl((void *)A_00510100, t1, (short)0xFFFFFFFE, t2);")

    def test_errors(self):
        dep = prologue() + [lw(V0, 0, GP), beq(V0, 0, 2), NOP, NOP] + epilogue()
        with self.assertRaisesRegex(ovl_lift.LiftError, "data-dependent"):
            lift(dep)
        loop = prologue() + [daddu(V0, 0, 0), beq(V0, 0, -2), NOP] + epilogue()
        with self.assertRaisesRegex(ovl_lift.LiftError, "backward"):
            lift(loop)
        unk = prologue() + [jal(0x00109990), NOP] + epilogue()
        with self.assertRaisesRegex(ovl_lift.LiftError, "no symbol"):
            lift(unk)
        noproto = prologue() + [jal(0x00101000), addiu(A0, GP, 0)] + epilogue()
        with self.assertRaisesRegex(ovl_lift.LiftError, "no prototype"):
            lift(noproto, protos={})
        undef = prologue() + [jal(0x00101000), NOP] + epilogue()   # $a0 never set
        with self.assertRaisesRegex(ovl_lift.LiftError, "undefined"):
            lift(undef)
        ind = prologue() + [jalr(V0), NOP] + epilogue()
        with self.assertRaises(ovl_lift.LiftError):
            lift(ind)

    def test_parse_protos(self):
        p = ovl_lift.parse_protos("#ifndef X\nvoid * Foo_1(void *, short, float);\nint Bar_2(void);\n#endif\n")
        self.assertEqual(p["Foo_1"], ("void *", ["void *", "short", "float"]))
        self.assertEqual(p["Bar_2"], ("int", []))


DATA_ASM = """.include "macro.inc"
.section .data, "wa"
/* Generated by spimdisasm 1.42.4 */

glabel D_00511000
    /* 027180 00511000 08105100 */ .word D_00511008
    /* 027184 00511004 0000803F */ .float 1
glabel D_00511008
    /* 027188 00511008 */ .short 0x0010
    /* 02718A 0051100A */ .short 0xFFFF
    /* 02718C 0051100C */ .byte 0x01
    /* 02718D 0051100D */ .byte 0x02
    /* 02718E 0051100E */ .byte 0x03
    /* 02718F 0051100F */ .byte 0x04
glabel D_00511010
    /* 027190 00511010 00105100 */ .word title_Ctor_511000
    /* 027194 00511014 00000000 */ .word 0x00000000
"""


class DataAsmTests(unittest.TestCase):
    def test_parse(self):
        words, labels = gen.parse_data_asm(DATA_ASM, 0x00511000)
        self.assertEqual(labels, {"D_00511000": 0x00511000, "D_00511008": 0x00511008,
                                  "D_00511010": 0x00511010})
        self.assertEqual([w.raw for w in words],
                         [0x00511008, 0x3F800000, 0xFFFF0010, 0x04030201, 0x00511000, 0])
        self.assertEqual([w.sym for w in words], ["D_00511008", None, None, None,
                                                  "title_Ctor_511000", None])

    def test_gap_is_error(self):
        bad = DATA_ASM.replace("00511004 0000803F", "00511008 0000803F")
        with self.assertRaises(gen.GenError):
            gen.parse_data_asm(bad, 0x00511000)

    def test_ctor_table_rule(self):
        # .data = [junk, a ctor-looking run of 3 in-overlay pointers, 0 (dtors), 0 pad]
        base = 0x00511000
        ws = [0x12345678, base + 0x100, base + 0x140, base + 0x180, 0, 0]
        img = b"".join(struct.pack("<I", w) for w in ws)
        s, e, t = ovl_lift.ctor_table(img, base, base, base + 0x400)
        self.assertEqual((s, e, t), (base + 4, base + 16, ws[1:4]))
        none = b"".join(struct.pack("<I", w) for w in [1, 2, 0])
        self.assertEqual(ovl_lift.ctor_table(none, base, base, base + 0x400)[:2], (base + 0x400, base + 0x400))


class OvlSymsTests(unittest.TestCase):
    def run1(self, rel, text):
        st = ovlsyms.OvlSymsStage()
        out, n = st.apply(rel, text.encode())
        return st, out.decode(), n

    def test_rename_collision(self):
        n_src = "extern s32 D_00524D08[]; extern s32 D_0047D248; x = D_00527020[3];"
        st, out, n = self.run1("src/overlays/normal/menu/normal_X_4f0000.c", n_src)
        self.assertEqual(out, "extern s32 normal_D_00524D08[]; extern s32 D_0047D248; "
                              "x = normal_D_00527020[3];")
        self.assertEqual(n, 2)
        st, out2, n = self.run1("src/overlays/insect/insect/insect_Y_4f0000.c", "D_00524D08;")
        self.assertEqual(out2, "insect_D_00524D08;")
        # idempotent
        st, again, n = self.run1("src/overlays/normal/menu/normal_X_4f0000.c", out)
        self.assertEqual((again, n), (out, 0))

    def test_main_and_jtbl(self):
        st, out, n = self.run1("src/main/ui/FieldHudInitOnce_204120.c", "D_00527020[0x3AE] = 1;")
        self.assertEqual((out, n), ("D_00527020[0x3AE] = 1;", 0))
        st, out, n = self.run1("src/overlays/title/menu/title_Z_4ef940.c", "jtbl_004F1600 D_004F1B80")
        self.assertEqual(out, "title_jtbl_004F1600 D_004F1B80")      # bss end is exclusive
        self.assertEqual(len(st.errors), 1)                           # ... and reported

    def test_text_range_error(self):
        st, out, n = self.run1("src/overlays/title/a.c", "D_004EA000")
        self.assertEqual((out, n), ("D_004EA000", 0))
        self.assertEqual(len(st.errors), 1)


if __name__ == "__main__":
    unittest.main(verbosity=1)
