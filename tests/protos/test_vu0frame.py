#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Unit tests of the `vu0frame` ingest stage (tools/stages/vu0frame.py,
docs/UB-AUDIT.md).  `control` runs the same checks with frame helpers
disabled (every function gets its own frame): must FAIL."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "stages"))
import vu0frame  # noqa: E402

CONTROL = len(sys.argv) > 1 and sys.argv.pop() == "control"

SRC = b"""#define vfa RG_VU0_BIND_VF(1, int)
static inline void Mul(void)
{
    vfa = 1;
}
static void Fill(int *p, int n);
void F(int *x)
{
    if (x) {
        void Mul(void);
        XS
        Mul();
        *x = vfa * 2;
        Fill(x, 2);
    }
}
static void Fill(int *p, int n)
{
    rg_vu0_sqc2(1, p);
}
int Plain(int a)
{
    return a + 1;
}
int Cb(void) { return 0; }
static int Taken(void) { rg_vu0_sqc2(1, 0); return 1; }
int (*g_cb)(void) = Taken;
void U(void) { Taken(); }
"""


def run(src: bytes):
    st = vu0frame.Vu0FrameStage()
    if CONTROL:
        st.apply = _no_helpers(st)
    out, n = st.apply("t.c", src)
    return st, out.decode("latin-1"), n


def _no_helpers(st):
    orig = vu0frame.Vu0FrameStage.apply

    def apply(rel, data):
        save = vu0frame.H_PARAM
        try:
            # a helper-less stage: pretend no function is static
            return orig(st, rel, data.replace(b"static ", b"       "))
        finally:
            vu0frame.H_PARAM = save
    return apply


class Vu0Frame(unittest.TestCase):
    def test_frames(self):
        st, out, n = run(SRC)
        self.assertIn("void F(int *x)\n{ RG_VU0_FRAME;", out)
        self.assertIn("void U(void) { Taken(); }", out)   # Taken keeps its own frame
        self.assertNotIn("Plain(int a)\n{ RG_VU0_FRAME;", out)

    def test_helper(self):
        st, out, n = run(SRC)
        self.assertIn("static inline void Mul(rg_vu0_state *rg_vu0_p_)", out)
        self.assertIn('#pragma push_macro("rg_vu0")\n#define rg_vu0 (*rg_vu0_p_)', out)
        self.assertIn("Mul(&rg_vu0);", out)
        # block-scope declaration and forward declaration get the parameter
        self.assertIn("void Mul(rg_vu0_state *rg_vu0_p_);", out)
        self.assertIn("static void Fill(rg_vu0_state *rg_vu0_p_, int *p, int n);", out)
        self.assertIn("Fill(&rg_vu0, x, 2);", out)
        # a macro name before a call is not a declaration
        self.assertIn("XS\n        Mul(&rg_vu0);", out)

    def test_address_taken(self):
        st, out, n = run(SRC)
        self.assertIn("static int Taken(void) { RG_VU0_FRAME;", out)
        self.assertTrue(any(r[2] == "info-helper-addr" and r[1] == "Taken" for r in st.rows))

    def test_idempotent(self):
        st, out, n = run(SRC)
        st2, out2, n2 = run(out.encode("latin-1"))
        self.assertEqual(out, out2)
        self.assertEqual(n2, 0)


if __name__ == "__main__":
    unittest.main()
