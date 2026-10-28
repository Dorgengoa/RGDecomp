#!/usr/bin/env python3
"""Unit tests for tools/stages/hwaccess.py on small fixtures (ctest -L hwbus).

    python tests/hwbus/test_stage.py            # must pass
    python tests/hwbus/test_stage.py control    # deliberately wrong stage: must FAIL

The control disables the `#define NAME (*(volatile T *)A)` alias handling, so
a store through such a macro is no longer turned into HW_W* (the define then
becomes an rvalue and the store would not compile) -- the alias test catches it.
"""
from __future__ import annotations

import re
import sys
import unittest
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "stages"))
import hwaccess as H  # noqa: E402

CONTROL = len(sys.argv) > 1 and sys.argv[1] == "control"
if CONTROL:
    H.DEFINE_RX = re.compile(r"(?!)")       # deliberately wrong: aliases ignored
    sys.argv = sys.argv[:1]

GAME = "src/main/test/Fixture_1d0000.c"          # a game-band path


def run(src: str, rel: str = GAME, crlf: bool = False):
    st = H.HwAccessStage(None)
    data = src.replace("\n", "\r\n").encode() if crlf else src.encode()
    out, n = st(rel, data)
    again, n2 = H.HwAccessStage(None)(rel, out)
    return st, out.decode(), n, (again == out and n2 == 0)


def body(text: str) -> str:
    """the file without the stage's include line"""
    return text.split("#line 1\n", 1)[1] if text.startswith(H.MARK) else text


class Derefs(unittest.TestCase):
    def test_load_store_rmw(self):
        st, out, n, idem = run(
            "void f(int x) {\n"
            "    int a = *(volatile s32 *)0x10002010;\n"
            "    *(volatile u32 *)0x1000B410 = x + 1;\n"
            "    *(volatile s32 *)0x1000E000 |= 3;\n"
            "    while (*(volatile s32 *)0x10002010 < 0) { }\n"
            "}\n")
        b = body(out)
        self.assertIn("int a = ((s32)HW_R32(0x10002010u));", b)
        self.assertIn("HW_W32(0x1000B410u, x + 1);", b)
        self.assertIn("HW_W32(0x1000E000u, (s32)HW_R32(0x1000E000u) | (3));", b)
        self.assertIn("while (((s32)HW_R32(0x10002010u)) < 0)", b)
        self.assertEqual(n, 4)
        self.assertTrue(idem)
        self.assertTrue(out.startswith(H.MARK + ' #include "port/hwaccess.h"\n#line 1\n'))
        self.assertEqual(st.errors, [])

    def test_nested_and_widths(self):
        _, out, n, idem = run(
            "void f(void) {\n"
            "    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 | 0x10000;\n"
            "    *(volatile u64 *)0x12000000 = *(volatile u64 *)0x12000000 & ~3LL;\n"
            "    *(volatile u16 *)(0x10000010) = 1;\n"
            "    *(volatile unsigned char *)0x10000000 = 2;\n"
            "}\n")
        b = body(out)
        self.assertIn("HW_W32(0x1000F590u, ((u32)HW_R32(0x1000F520u)) | 0x10000);", b)
        # GS privileged register: a native call by register id (NATIVE_REGS, D9)
        self.assertIn("rg_gs_reg_w64(RG_GS_PMODE, ((u64)rg_gs_reg_r64(RG_GS_PMODE)) & ~3LL);", b)
        self.assertIn("HW_W16(0x10000010u, 1);", b)     # not a 32-bit T0_MODE write: stays
        self.assertIn("HW_W8(0x10000000u, 2);", b)
        self.assertEqual(n, 8)
        self.assertTrue(idem)

    def test_alias_define(self):
        _, out, n, idem = run(
            "#define GS_PMODE (*(volatile u64 *)0x12000000)\n"
            "#define T0_COUNT (*(volatile u32 *)0x10000000)\n"
            "void f(int i) {\n"
            "    GS_PMODE = 0x7F23;\n"
            "    if (i) { GS_PMODE |= 1; }\n"
            "    i = T0_COUNT / 2;\n"
            "    T0_COUNT = 0;\n"
            "}\n", crlf=True)
        b = body(out).replace("\r\n", "\n")
        self.assertIn("#define GS_PMODE (((u64)rg_gs_reg_r64(RG_GS_PMODE)))", b)
        self.assertIn("#define T0_COUNT (((u32)rg_logic_t0_count()))", b)
        self.assertIn("rg_gs_reg_w64(RG_GS_PMODE, 0x7F23);", b)
        self.assertIn("rg_gs_reg_w64(RG_GS_PMODE, GS_PMODE | (1));", b)
        self.assertIn("i = T0_COUNT / 2;", b)
        self.assertIn("rg_logic_t0_set_count(0);", b)
        self.assertNotIn("HW_", b)
        self.assertNotRegex(b, r"\bGS_PMODE\s*=|\bT0_COUNT\s*=")
        self.assertTrue(idem)

    def test_untouched(self):
        src = ("/* *(volatile u32 *)0x10000000 = 1; */\n"
               "const char *s = \"*(volatile u32 *)0x10000000\";\n"
               "void f(u8 *p) {\n"
               "    *(s32 *)(p + 0x0) = 0x10000000;\n"          # DMAtag CNT value
               "    p[1] = 0x20000000 | 3;\n"                    # tag id
               "    if (*(volatile u32 *)p & 0x10000000) {}\n"  # flag on a host field
               "}\n"
               "asm void g(void) {\n    lui $2, (0x10000000 >> 16)\n}\n")
        st, out, n, _ = run(src)
        self.assertEqual(n, 0)
        self.assertEqual(out, src)

    def test_sdk_path_untouched(self):
        src = "void f(void) { *(volatile u32 *)0x10000000 = 1; }\n"
        st, out, n, _ = run(src, rel="src/main/sdk/libgraph/sceGsFoo_108000.c")
        self.assertEqual((n, out), (0, src))
        st, out, n, _ = run(src, rel="src/main/gfx/Foo_10a000.c")   # SDK address band
        self.assertEqual((n, out), (0, src))

    def test_line_numbers_kept(self):
        _, out, _, _ = run("int x;\nvoid f(void) { *(volatile u32 *)0x10000000 = 1; }\n")
        lines = out.splitlines()
        self.assertEqual(lines[1], "#line 1")
        self.assertEqual(H.presumed_line(out, out.index("void f")), 2)


class Other(unittest.TestCase):
    def test_scratchpad(self):
        _, out, n, idem = run("void f(void) { u32 *p = (u32 *)0x70000100; *(volatile u64 *)0x70003FF0 = 0; }\n")
        b = body(out)
        self.assertIn("(u32 *)PS2_SPR(0x100)", b)
        self.assertIn("*(volatile u64 *)PS2_SPR(0x3FF0) = 0", b)
        self.assertEqual(n, 2)
        self.assertTrue(idem)

    def test_overlay(self):
        st, out, n, idem = run(
            "s32 f(void) { if (*(s16 *)0x5273C2 == 4) return 1; *(s8 *)0x5273CE = 1; return 0; }\n")
        b = body(out)
        self.assertIn("(*(s16 *)((unsigned char *)D_00527020 + 0x3A2)) == 4", b)
        self.assertIn("(*(s8 *)((unsigned char *)D_00527020 + 0x3AE)) = 1;", b)
        self.assertIn("extern unsigned char D_00527020[];", out)
        self.assertEqual(n, 2)
        self.assertTrue(idem)
        self.assertEqual(st.errors, [])

    def test_overlay_unmapped_is_error(self):
        st, out, n, _ = run("s32 f(void) { return *(s32 *)0x00500000; }\n")
        self.assertEqual(n, 0)
        self.assertTrue(any("not in OVERLAY_SITES" in w for _, w in st.errors))
        # an overlay file's own literal is not a MAIN->overlay access
        st, out, n, _ = run("s32 f(void) { return *(s32 *)0x00500000; }\n",
                            rel="src/overlays/normal/x/normal_Foo_4f0000.c")
        self.assertEqual((n, st.errors), (0, []))

    def test_overlay_ranges_cover_sites(self):
        for a, (ovl, sym, sa) in H.OVERLAY_SITES.items():
            lo, hi = H.OVERLAY_DATA[ovl]
            self.assertTrue(lo <= sa <= a < hi, hex(a))
            others = [o for o, (l, h) in H.OVERLAY_DATA.items() if l <= a < h]
            self.assertEqual(others, [ovl], "address must belong to exactly one overlay")


class Native(unittest.TestCase):
    def test_native_registers(self):
        _, out, n, idem = run(
            "void f(int i) {\n"
            "    i = *(volatile u32 *)0x10000000;\n"
            "    *(volatile u32 *)0x10000010 = 0x83;\n"
            "    *(volatile u32 *)0x10003C10 = 8;\n"
            "    i = (*(volatile u64 *)0x12001000 >> 13) & 1;\n"
            "    *(volatile u64 *)0x12000080 = 5;\n"
            "    *(volatile u32 *)0x1000E010 = 4;\n"     # DMAC: no native owner here, stays
            "}\n")
        b = body(out)
        self.assertIn("i = ((u32)rg_logic_t0_count());", b)
        self.assertIn("rg_logic_t0_set_mode(0x83);", b)
        self.assertIn("rg_vif1_fbrst_w32(8);", b)
        self.assertIn("i = (((u64)rg_gs_reg_r64(RG_GS_CSR)) >> 13) & 1;", b)
        self.assertIn("rg_gs_reg_w64(RG_GS_DISPLAY1, 5);", b)
        self.assertIn("HW_W32(0x1000E010u, 4);", b)
        self.assertEqual(n, 11)
        self.assertTrue(idem)

    def test_gs_reg_ids_match_header(self):
        hdr = (H.PORT / "include" / "port" / "hwaccess.h").read_text(encoding="utf-8")
        for a, name in H.GS_REGS.items():
            m = re.search(r"#define RG_GS_" + name + r"\s+(\d+)u", hdr)
            self.assertTrue(m, name)
            idx = (16 + ((a - 0x12001000) >> 4)) if a >= 0x12001000 else (a - 0x12000000) >> 4
            self.assertEqual(int(m.group(1)), idx, name)


class Masks(unittest.TestCase):
    def test_table_rules(self):
        rel = "src/main/gs/GsUploadImage16Blocks_1d27a0.c"
        src = ("void GsUploadImage16Blocks_1d27a0(void *dst, void *src) {\n"
               "    sceGifPkInit_10a400(&pk, (int)(((u64)(u32)dst & 0x0FFFFFFF) | 0x20000000));\n"
               "    sceGifPkRef(&pk, (u64)(u32)src & 0x0FFFFFFF, 0x40, 0, 0, 0);\n}\n")
        st, out, n, idem = run(src, rel=rel)
        b = body(out)
        # identity on host pointers: stripped to the operand (D9, no marker left)
        self.assertIn("sceGifPkInit_10a400(&pk, (int)(((u64)(u32)dst)));", b)
        self.assertIn("sceGifPkRef(&pk, ((u64)(u32)src), 0x40", b)
        self.assertNotIn("PS2_", b)
        self.assertEqual((n, st.errors), (2, []))
        self.assertTrue(idem)

    def test_regex_rules(self):
        rel = "src/main/movie/ViBufRestartDma_1d3e70.cpp"
        src = ("#define LOW28(x) ((x) & 0x0FFFFFFF)\n"
               "void f(C *c, int a, int mode) {\n"
               "    madr = LOW28(c->phys);\n"
               "    tag = LOW28(c->unk28) | (mode << 28) | 0x100;\n"
               "    madr = LOW28(c->phys + a * 16);\n}\n")
        st, out, n, idem = run(src, rel=rel)
        b = body(out)
        self.assertIn("madr = (c->phys);", b)
        self.assertIn("madr = (c->phys + a * 16);", b)
        self.assertIn("tag = LOW28(c->unk28) | (mode << 28) | 0x100;", b)   # CHCR stays
        self.assertIn("#define LOW28(x) ((x) & 0x0FFFFFFF)", b)
        self.assertEqual((n, st.errors), (2, []))
        self.assertTrue(idem)

    def test_ucab_and_leave(self):
        st, out, n, _ = run("void f(s32 k1, s32 k2) { g(k1 | 0x30000000); g(k2 | 0x30000000); }\n",
                            rel="src/main/gfx/DrawListInitDoubleBufMaybe_1427e0.c")
        self.assertIn("g((k1)); g((k2));", body(out))
        # ViBufAddDma's CHCR TAG field is NOT an address: no rule, untouched
        src = "void f(u32 ch) { ch = (ch & 0x0FFFFFFF) | 0x30000000; }\n"
        st, out, n, _ = run(src, rel="src/main/movie/ViBufAddDma_1d4240.c")
        self.assertEqual((n, out), (0, src))

    def test_rule_count_mismatch_is_error(self):
        st, out, n, _ = run("void f(s32 k1) { g(k1 | 0x30000000); }\n",
                            rel="src/main/gfx/DrawListInitDoubleBufMaybe_1427e0.c")
        self.assertTrue(any("not found" in w for _, w in st.errors))   # k2 missing


if __name__ == "__main__":
    r = unittest.main(exit=False, verbosity=1).result
    sys.exit(0 if r.wasSuccessful() else 1)
