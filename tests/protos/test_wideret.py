#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Unit tests of the `wideret` ingest stage (tools/stages/wideret.py, docs/PROTOS.md
"wideret").  `control` runs the same checks with the stage disabled
(RG_PROTOS_NO_WIDERET=1): must FAIL."""
import os
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "stages"))
CONTROL = len(sys.argv) > 1 and sys.argv.pop() == "control"
if CONTROL:
    os.environ["RG_PROTOS_NO_WIDERET"] = "1"
import wideret  # noqa: E402

LST = {
    # r |= G();  return r;   (64-bit or, 64-bit return)
    "Acc_100000": """glabel Acc_100000
    /* 0 00100000 00000000 */  jal        Wide_100100
    /* 0 00100004 00000000 */   nop
    /* 0 00100008 00000000 */  or         $16, $16, $2
    /* 0 0010000C 00000000 */  jr         $31
    /* 0 00100010 00000000 */   daddu     $2, $16, $0
""",
    # a chain: returns Acc's value
    "Chain_100200": """glabel Chain_100200
    /* 0 00100200 00000000 */  jal        Acc_100000
    /* 0 00100204 00000000 */   nop
    /* 0 00100208 00000000 */  jr         $31
    /* 0 0010020C 00000000 */   daddu     $2, $2, $0
""",
    # narrow: the result is cut with sll/sra before the return
    "Narrow_100300": """glabel Narrow_100300
    /* 0 00100300 00000000 */  jal        Wide_100100
    /* 0 00100304 00000000 */   nop
    /* 0 00100308 00000000 */  jr         $31
    /* 0 0010030C 00000000 */   sll       $2, $2, 0
""",
}
FILES = {
    "src/main/a/Wide_100100.c": b"long long Wide_100100(void)\n{\n    return 1;\n}\n",
    "src/main/a/Acc_100000.c": (b"static s32 helper(void)\n{\n    s32 h;\n    h = 0;\n    h |= Wide_100100();\n"
                                b"    return h;\n}\ns32 Acc_100000(void)\n{\n    s32 r;\n    s32 k;\n    r = 0;\n"
                                b"    k = 3;\n    r |= Wide_100100();\n    r |= helper();\n    return r;\n}\n"),
    "src/main/a/Chain_100200.c": b"s32 Chain_100200(void)\n{\n    return Acc_100000();\n}\n",
    "src/main/a/Narrow_100300.c": b"s32 Narrow_100300(void)\n{\n    return (s32)Wide_100100();\n}\n",
}


class T(unittest.TestCase):
    def setUp(self):
        self.st = wideret.WideRetStage()
        self.st.addr_table = {"asm_text": LST}
        self.st.prepare(dict(FILES))

    def out(self, rel):
        return self.st.apply(rel, FILES[rel])[0].decode()

    def test_accumulator(self):
        o = self.out("src/main/a/Acc_100000.c")
        self.assertIn("long long Acc_100000(void)", o)
        self.assertIn("long long r;", o)
        self.assertIn("s32 k;", o)                       # not fed by a wide value
        self.assertIn("static long long helper(void)", o)
        self.assertIn("long long h;", o)

    def test_chain(self):
        self.assertIn("long long Chain_100200(void)", self.out("src/main/a/Chain_100200.c"))

    def test_narrow_kept(self):
        self.assertIn("s32 Narrow_100300(void)", self.out("src/main/a/Narrow_100300.c"))

    def test_idempotent(self):
        o = self.out("src/main/a/Acc_100000.c").encode()
        st = wideret.WideRetStage()
        st.addr_table = {"asm_text": LST}
        files = dict(FILES)
        files["src/main/a/Acc_100000.c"] = o
        st.prepare(files)
        self.assertEqual(st.apply("src/main/a/Acc_100000.c", o)[0], o)


if __name__ == "__main__":
    unittest.main()
