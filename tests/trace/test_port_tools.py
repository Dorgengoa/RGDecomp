# SPDX-License-Identifier: CC0-1.0
"""Unit tests for the Python side of the port trace (trace.tools_unit):
port_trace.py's config/ignore handling, gen_port_symtab.py, and the
consistency of tools/trace/port_regions.cfg with the region files."""
import os
import re
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
TT = os.path.join(PORT, "tools", "trace")
sys.path.insert(0, TT)

import gen_port_symtab as gps  # noqa: E402
import port_trace  # noqa: E402
import trace  # noqa: E402

PORTCFG = os.path.join(TT, "port_regions.cfg")
SYMS = os.path.join(TT, "regions_symbols.cfg")
GOLDEN = os.path.join(TT, "goldens", "newgame_battle.tsv")
GAME_SRC = os.path.join(PORT, "game", "src")


class PortCfg(unittest.TestCase):
    def test_names_exist(self):
        names = {r[1] for r in trace.load_regions(os.path.join(TT, "regions_golden.cfg"))}
        with open(PORTCFG, encoding="utf-8") as f:
            for line in f:
                t = line.split("#", 1)[0].split()
                if t and t[0] in ("ptrs", "ps2ptr"):
                    self.assertIn(t[1], names, line)

    def test_ignore_default_and_strict(self):
        rx = re.compile(port_trace.ignore_regex(PORTCFG))
        for n in ("sym:GameScene", "sym:Camera3", "sym:VblankWaitFlag", "iop", "ram4m@00400000", "sym:Pad0"):
            self.assertTrue(rx.search(n), n)
        for n in ("sym:RandState", "sym:VblankCount", "sym:GameModeStack", "sym:GameDataPtr", "sym:SkillTimers"):
            self.assertFalse(rx.search(n), n)
        strict = re.compile(port_trace.ignore_regex(PORTCFG, strict=True))
        self.assertTrue(strict.search("sym:VblankWaitFlag"))
        self.assertFalse(strict.search("sym:GameScene"))

    def test_every_symbol_classified_once(self):
        exc, pend = port_trace.read_portcfg(PORTCFG)
        for name in (r[1] for r in trace.load_regions(SYMS)):
            hits = [p for p, _ in exc + pend if re.search(p, name)]
            self.assertLessEqual(len(hits), 1, (name, hits))

    def test_golden_vbls(self):
        if not os.path.exists(GOLDEN):
            self.skipTest("no golden")
        v = port_trace.golden_vbls(GOLDEN)
        self.assertGreater(len(v), 200)
        self.assertEqual(v, sorted(set(v)))
        self.assertEqual(v[-1], 25040)


class SymtabGen(unittest.TestCase):
    def test_fixture(self):
        syms = gps.read_symbols(os.path.join(HERE, "data", "symtab_fixture.txt"))
        rows, gaps = gps.build(trace.load_regions(os.path.join(HERE, "data", "symtab_regions.cfg")), syms, "^sym:")
        got = {name: (a, size) for a, size, name, users in rows}
        self.assertEqual(got, {"D_00481000": (0x00481000, 16), "D_00481010": (0x00481010, 0x10),
                               "D_00481020": (0x00481020, 4), "D_004E9E00": (0x004E9E00, 0x80)})
        self.assertEqual(gaps, [])

    def test_gap_reported(self):
        syms = {0x1000: ("D_00001000", 4)}
        regs = [("ee", "sym:X", 0x1000, 0x1010, None)]
        rows, gaps = gps.build(regs, syms, "^sym:")
        self.assertEqual(len(rows), 1)
        self.assertEqual(gaps, [("sym:X", 0x1004, 0x1010)])

    def test_real_game(self):
        if not os.path.isdir(GAME_SRC):
            self.skipTest("no game/src")
        syms = gps.scan_src(GAME_SRC)
        rows, gaps = gps.build(trace.load_regions(SYMS), syms, "^sym:")
        self.assertEqual(gaps, [])
        names = {r[2] for r in rows}
        self.assertIn("D_004810C4", names)
        self.assertIn("D_00449858", names)          # RandState's pointer
        for a, size, name, users in rows:
            self.assertTrue(a + size <= gps.ARENA[0] or a >= gps.ARENA[1], name)
            self.assertTrue(re.fullmatch(r"D_[0-9A-F]{8}", name), name)
        with tempfile.TemporaryDirectory() as d:
            out = os.path.join(d, "t.c")
            gps.write_c(out, rows, "f", "test")
            text = open(out, encoding="utf-8").read()
            self.assertEqual(text.count("extern char D_"), len(rows))


if __name__ == "__main__":
    unittest.main()
