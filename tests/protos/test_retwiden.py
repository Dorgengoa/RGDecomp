#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Unit tests of the `retwiden` ingest stage (tools/stages/retwiden.py, docs/PROTOS.md
"retwiden").  `control` runs the same checks with the stage disabled
(RG_PROTOS_NO_RETWIDEN=1): must FAIL."""
import os
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "stages"))
CONTROL = len(sys.argv) > 1 and sys.argv.pop() == "control"
if CONTROL:
    os.environ["RG_PROTOS_NO_RETWIDEN"] = "1"
import retwiden  # noqa: E402

UNIT = b"""#include "types.h"
static u8 Helper_100010(int a);
u8 UnitHasParent_3a3600(struct Obj0 *p0)
{
    return (p0->m3E0 != 0); /* return; in a comment */
}
static u8 Helper_100010(int a)
{
    if (a) return;
    return a > 3 ? 1 : 0;
}
s16 DirectOnly_100020(void)
{
    return -1;
}
extern "C" bool IsDead_100030(void *self, int rgp_a1)
{
    return rgp_a1 == 0;
}
"""
DATA = (b"u32 D_00474F80[3] = { (u32)&UnitHasParent_3a3600, (u32)&IsDead_100030, 0 };\n"
        b"void Reg_100040(void) { SetCb_100050(Helper_100010); DirectOnly_100020(); }\n")


class T(unittest.TestCase):
    def run_stage(self):
        st = retwiden.RetWidenStage()
        files = {"src/main/a/Unit.cpp": UNIT, "src/main_data/d.c": DATA}
        st.prepare(files)
        out, n = st.apply("src/main/a/Unit.cpp", UNIT)
        return st, out.decode(), n

    def test_widen(self):
        st, out, n = self.run_stage()
        self.assertEqual(n, 3)
        self.assertIn("u32 UnitHasParent_3a3600(struct Obj0 *p0)", out)
        self.assertIn("return (u8)((p0->m3E0 != 0));", out)
        self.assertIn("static u32 Helper_100010(int a);", out)       # own declaration
        self.assertIn("if (a) return;", out)                          # bare return kept
        self.assertIn("return (u8)(a > 3 ? 1 : 0);", out)
        self.assertIn("s16 DirectOnly_100020(void)", out)             # called only: kept
        self.assertIn("return -1;", out)
        self.assertIn('extern "C" u32 IsDead_100030(', out)
        self.assertIn("return (bool)(rgp_a1 == 0);", out)
        self.assertIn("/* return; in a comment */", out)

    def test_idempotent(self):
        st, out, n = self.run_stage()
        again, k = st.apply("src/main/a/Unit.cpp", out.encode())
        self.assertEqual(again.decode(), out)
        self.assertEqual(k, 0)

    def test_data_untouched(self):
        st = retwiden.RetWidenStage()
        st.prepare({"src/main/a/Unit.cpp": UNIT, "src/main_data/d.c": DATA})
        self.assertEqual(st.apply("src/main_data/d.c", DATA)[0], DATA)


if __name__ == "__main__":
    unittest.main()
