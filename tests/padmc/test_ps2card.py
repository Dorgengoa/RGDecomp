# SPDX-License-Identifier: CC0-1.0
"""tools/saves/ps2card.py on synthetic cards (no game data): format, ECC, image / folder /
port-card round trips, slot reuse and fragmentation, the save header check, restore.
Run: python -I tests/padmc/test_ps2card.py [TMPDIR]"""
import hashlib
import os
import random
import shutil
import struct
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "..", "tools", "saves"))
import ps2card as P  # noqa: E402

TMP = None


def rg_save(seed, n=P.RG_DATA_SIZE):
    """a synthetic save file with the game's header and valid digests"""
    r = random.Random(seed)
    b = bytearray(r.getrandbits(8) for _ in range(n))
    b[0:0x50] = b"\0" * 0x50
    struct.pack_into("<hh", b, 4, 0x25, 0)
    plen = n - 0x50
    struct.pack_into("<q", b, 0x10, plen)
    struct.pack_into("<q", b, 0x30, 0x300)
    b[0x20:0x30] = hashlib.md5(bytes(b[0x50:0x50 + plen])).digest()
    b[0x40:0x50] = hashlib.md5(bytes(b[0x50:0x350])).digest()
    return bytes(b)


def iconsys(title="Rogue Galaxy", line2="Rosa"):
    b = bytearray(P.ICON_SYS_SIZE)
    b[0:4] = b"PS2D"
    t1 = title.encode("shift_jis")
    t2 = "".join(chr(ord(c) + 0xFEE0) if c != " " else "　" for c in line2).encode("shift_jis")
    struct.pack_into("<H", b, 6, len(t1))
    b[0xC0:0xC0 + len(t1) + len(t2)] = t1 + t2
    for o in (0x104, 0x144, 0x184):
        b[o:o + 6] = b"RG.ICO"
    return bytes(b)


def rg_dir(slot, seed, ico_size=23000):
    r = random.Random(seed + 1000)
    return P.SaveDir("BASCUS-97490LV5RG_%02d" % slot, [
        P.Entry("icon.sys", iconsys(line2="Slot %d" % slot)),
        P.Entry("RG.ICO", bytes(r.getrandbits(8) for _ in range(ico_size))),
        P.Entry("BASCUS-97490LV5RG_%02d" % slot, rg_save(seed)),
    ], created=struct.pack("<BBBBBBH", 0, 1, 2, 3, 4, 5, 2006), modified=struct.pack("<BBBBBBH", 0, 6, 7, 8, 9, 10, 2006))


def same_dirs(a, b):
    if [d.name for d in a] != [d.name for d in b]:
        return False
    for x, y in zip(a, b):
        if [(f.name, f.data) for f in x.files] != [(f.name, f.data) for f in y.files]:
            return False
    return True


class Ecc(unittest.TestCase):
    def test_hamming_single_bit(self):
        # every single-bit error in a 128-byte chunk gives a distinct, nonzero syndrome:
        # the code corrects one bit, as the card's ECC must
        r = random.Random(7)
        for _ in range(3):
            chunk = bytes(r.getrandbits(8) for _ in range(128))
            e0 = P.ecc128(chunk)
            seen = set()
            for bit in range(128 * 8):
                c = bytearray(chunk)
                c[bit // 8] ^= 1 << (bit % 8)
                e1 = P.ecc128(bytes(c))
                syn = bytes(x ^ y for x, y in zip(e0, e1))
                self.assertNotEqual(syn, b"\0\0\0")
                seen.add(syn)
            self.assertEqual(len(seen), 128 * 8)

    def test_erased_chunk(self):
        self.assertEqual(P.ecc128(b"\xff" * 128), b"\x77\x7f\x7f")
        self.assertEqual(P.ecc128(b"\0" * 128), b"\x77\x7f\x7f")

    def test_column_parity_order(self):
        # mcman's column-parity bit order (the one retail reads: docs/BRINGUP.md 2026-10-18
        # (f)): bits 0..2 = parity under 0x55, 0x33, 0x0F; bits 4..6 = 0xAA, 0xCC, 0xF0.
        c = bytearray(128)
        c[0] = 0x01                     # in 0x55, 0x33, 0x0F -> bits 0..2
        self.assertEqual(P.ecc128(bytes(c)), b"\x70\x00\x7f")
        c = bytearray(128)
        c[5] = 0x80                     # in 0xAA, 0xCC, 0xF0 -> bits 4..6
        self.assertEqual(P.ecc128(bytes(c)), b"\x07\x05\x7a")
        c = bytearray(128)
        c[0] = 0x02                     # 0xAA, 0x33, 0x0F -> bits 4, 1, 2
        self.assertEqual(P.ecc128(bytes(c))[0], 0x77 ^ 0x16)

    def test_matches_cardboot(self):
        # tools/trace/cardboot.py rewrites exported images with the ECC retail accepted for all
        # 25 library cards; ps2card must write the same, so that rewrite changes nothing
        sys.path.insert(0, os.path.join(HERE, "..", "..", "tools", "trace"))
        try:
            import cardboot as CB
        except Exception as e:          # the PCSX2 harness modules are optional here
            self.skipTest("cardboot not importable: %s" % e)
        r = random.Random(11)
        for _ in range(200):
            chunk = bytes(r.getrandbits(8) for _ in range(128))
            self.assertEqual(P.ecc128(chunk), CB.ecc128(chunk))
        # every page ps2card wrote (formatted card: superblock, FAT, root directory) carries
        # the spare area cardboot would write; erased pages stay 0xFF (as on a PCSX2 card)
        c = P.format_image()
        b, n = bytes(c.img), 0
        for p in range(P.PAGES):
            o = p * (P.PAGE + P.SPARE)
            page = b[o:o + P.PAGE]
            if page == bytes([0xFF]) * P.PAGE:
                continue
            n += 1
            want = b"".join(CB.ecc128(page[i:i + 128]) for i in range(0, P.PAGE, 128)) + bytes(4)
            self.assertEqual(b[o + P.PAGE:o + P.PAGE + P.SPARE], want, "page %d" % p)
        self.assertGreater(n, 10)


class Image(unittest.TestCase):
    def test_format(self):
        c = P.format_image()
        self.assertEqual(len(c.img), P.SIZE_ECC)
        self.assertEqual((c.alloc_offset, c.alloc_end, c.backup1, c.backup2), (41, 8135, 1023, 1022))
        self.assertEqual(c.list(), [])
        self.assertEqual(len(c.free_clusters()), 8134)
        self.assertEqual(c.verify(), [])
        raw = P.format_image(ecc=False)
        self.assertEqual(len(raw.img), P.SIZE_RAW)
        self.assertEqual(raw.list(), [])

    def test_ecc_damage_reported(self):
        c = P.format_image()
        c.add_dir(rg_dir(0, 1))
        self.assertEqual(c.verify(), [])
        o = (c.alloc_offset + 5) * P.PPC * c.raw_page + 17
        c.img[o] ^= 0x10
        self.assertTrue(any("ECC" in p for p in c.verify()))

    def test_add_list_remove(self):
        for ecc in (True, False):
            c = P.format_image(ecc)
            dirs = [rg_dir(s, s) for s in range(4)]  # root grows to 3 clusters
            free0 = len(c.free_clusters())
            for d in dirs:
                c.add_dir(d)
            self.assertTrue(same_dirs(c.list(), dirs))
            got = c.list()[0]
            self.assertEqual((got.created, got.modified), (dirs[0].created, dirs[0].modified))
            self.assertEqual(c.verify(), [])
            used = free0 - len(c.free_clusters())
            self.assertEqual(used, 4 * (3 + 1 + 23 + 111) + 2)  # + two root clusters
            # remove one, its entry slot and clusters are reused
            self.assertTrue(c.remove_dir("BASCUS-97490LV5RG_01"))
            self.assertEqual([d.name for d in c.list()], ["BASCUS-97490LV5RG_00", "BASCUS-97490LV5RG_02",
                                                          "BASCUS-97490LV5RG_03"])
            big = rg_dir(9, 9, ico_size=60000)  # bigger than the hole: a fragmented chain
            c.add_dir(big)
            self.assertEqual(c.list()[1].name, "BASCUS-97490LV5RG_09")
            self.assertTrue(same_dirs([c.list()[1]], [big]))
            self.assertEqual(c.verify(), [])
            with self.assertRaises(P.CardError):
                c.add_dir(rg_dir(0, 5))

    def test_full_card(self):
        c = P.format_image()
        n = 0
        with self.assertRaises(P.CardError):
            while True:
                c.add_dir(rg_dir(n, n % 3))
                n += 1
        self.assertGreater(n, 50)

    def test_save_and_reload(self):
        p = os.path.join(TMP, "rt.ps2")
        c = P.format_image()
        c.add_dir(rg_dir(0, 1))
        c.save(p)
        c2 = P.ImageCard(p)
        self.assertTrue(same_dirs(c2.list(), [rg_dir(0, 1)]))
        self.assertFalse(os.path.exists(p + ".tmp"))

    def test_rejects(self):
        p = os.path.join(TMP, "blank.ps2")
        with open(p, "wb") as f:
            f.write(b"\xff" * P.SIZE_ECC)  # PCSX2's new card: unformatted
        with self.assertRaises(P.CardError):
            P.ImageCard(p)
        with open(p, "wb") as f:
            f.write(b"\0" * 1000)
        with self.assertRaises(P.CardError):
            P.ImageCard(p)


class Cli(unittest.TestCase):
    def setUp(self):
        self.d = tempfile.mkdtemp(dir=TMP)
        self.saves = os.path.join(self.d, "saves")

    def port_card_with(self, *dirs):
        pc = P.PortCard(self.saves, 1)
        for d in dirs:
            pc.add_dir(d)
        pc.save()
        return pc

    def test_export_import_image(self):
        self.port_card_with(rg_dir(0, 1), rg_dir(3, 2))
        img = os.path.join(self.d, "Mcd001.ps2")
        self.assertEqual(P.main(["export", img, "--format", "--saves", self.saves]), 0)
        self.assertEqual(P.main(["verify", img]), 0)
        self.assertTrue(same_dirs(P.ImageCard(img).list(), [rg_dir(0, 1), rg_dir(3, 2)]))
        # back into a fresh port card (slot 2), times and modes kept
        saves2 = os.path.join(self.d, "saves2")
        self.assertEqual(P.main(["import", img, "--saves", saves2, "--slot", "2"]), 0)
        back = P.PortCard(saves2, 2).list()
        self.assertTrue(same_dirs(back, [rg_dir(0, 1), rg_dir(3, 2)]))
        self.assertEqual(back[0].modified, rg_dir(0, 1).modified)
        self.assertEqual(back[0].files[2].mode, P.MODE_FILE)
        # the metadata file is the one src/ps2/padmc/mccard.c reads
        with open(os.path.join(saves2, "card2.card")) as f:
            meta = f.read().splitlines()
        self.assertEqual(meta[0], "RGMC 1")
        rec = [l.split() for l in meta if l.endswith(" /BASCUS-97490LV5RG_00")]
        self.assertEqual(len(rec), 1)
        self.assertEqual(rec[0][2:6], ["d", "8427", rg_dir(0, 1).created.hex().upper(),
                                       rg_dir(0, 1).modified.hex().upper()])
        seqs = [int(l.split()[1]) for l in meta if l.startswith("E ")]
        self.assertEqual(sorted(seqs), list(range(len(seqs))))  # unique, root first
        self.assertTrue(any(l.endswith(" /BASCUS-97490LV5RG_03/icon.sys") for l in meta))
        # again: refused without --force, replaced (old copy backed up) with it
        self.assertEqual(P.main(["import", img, "--saves", saves2, "--slot", "2"]), 2)
        self.assertEqual(P.main(["import", img, "--saves", saves2, "--slot", "2", "--force"]), 0)
        bk = os.path.join(saves2, "backups", "card2", "BASCUS-97490LV5RG_00")
        self.assertEqual(len(os.listdir(bk)), 1)
        # export into the existing image: one more save
        self.port_card_with(rg_dir(7, 3))
        self.assertEqual(P.main(["export", img, "--save", "BASCUS-97490LV5RG_07", "--saves", self.saves]), 0)
        self.assertEqual([d.name for d in P.ImageCard(img).list()],
                         ["BASCUS-97490LV5RG_00", "BASCUS-97490LV5RG_03", "BASCUS-97490LV5RG_07"])
        self.assertEqual(P.main(["verify", img]), 0)

    def test_folder_card(self):
        self.port_card_with(rg_dir(0, 1))
        fc = os.path.join(self.d, "Mcd001")
        os.makedirs(fc)
        open(os.path.join(fc, "_pcsx2_superblock"), "wb").close()
        self.assertEqual(P.main(["export", fc, "--saves", self.saves]), 0)
        self.assertTrue(os.path.isfile(os.path.join(fc, "BASCUS-97490LV5RG_00", "RG.ICO")))
        open(os.path.join(fc, "BASCUS-97490LV5RG_00", "_pcsx2_index"), "wb").close()
        saves2 = os.path.join(self.d, "s2")
        self.assertEqual(P.main(["import", fc, "--saves", saves2]), 0)
        self.assertTrue(same_dirs(P.PortCard(saves2, 1).list(), [rg_dir(0, 1)]))

    def test_check(self):
        p = os.path.join(self.d, "BASCUS-97490LV5RG_00")
        with open(p, "wb") as f:
            f.write(rg_save(5))
        self.assertEqual(P.main(["check", p]), 0)
        b = bytearray(rg_save(5))
        b[0x9000] ^= 1  # payload only: the header digest still matches
        with open(p, "wb") as f:
            f.write(b)
        self.assertEqual(P.check_save(bytes(b)), ["payload digest (MD5 at +0x20) does not match"])
        self.assertEqual(P.main(["check", p]), 1)

    def test_restore(self):
        self.port_card_with(rg_dir(0, 1))
        card = os.path.join(self.saves, "card1", "BASCUS-97490LV5RG_00")
        snap = os.path.join(self.saves, "backups", "card1", "BASCUS-97490LV5RG_00", "2026-10-12_120000")
        os.makedirs(snap)
        for f in rg_dir(0, 2).files:
            with open(os.path.join(snap, f.name), "wb") as o:
                o.write(f.data)
        # the broken state an interrupted save leaves: icon.err, no icon.sys
        os.replace(os.path.join(card, "icon.sys"), os.path.join(card, "icon.err"))
        self.assertEqual(P.main(["restore", "BASCUS-97490LV5RG_00", "--saves", self.saves]), 0)
        self.assertEqual(sorted(os.listdir(card)), ["BASCUS-97490LV5RG_00", "RG.ICO", "icon.sys"])
        self.assertTrue(same_dirs(P.PortCard(self.saves, 1).list(), [rg_dir(0, 2)]))

    def test_fixture_for_c(self):
        """a card for padmc.mc_pyimport: written by this tool, read by src/ps2/padmc"""
        base = os.environ.get("RG_PADMC_TMP")
        if not base:
            self.skipTest("RG_PADMC_TMP not set")
        saves = os.path.join(base, "padmc_pyimport")
        shutil.rmtree(saves, ignore_errors=True)
        self.port_card_with(rg_dir(0, 1), rg_dir(3, 2))
        img = os.path.join(self.d, "fixture.ps2")
        self.assertEqual(P.main(["export", img, "--format", "--saves", self.saves]), 0)
        self.assertEqual(P.main(["import", img, "--saves", saves]), 0)

    def test_list_titles(self):
        self.assertEqual(P.icon_title(iconsys(line2="Rosa")), "Rogue Galaxy / Rosa")


if __name__ == "__main__":
    base = sys.argv[1] if len(sys.argv) > 1 else tempfile.gettempdir()
    TMP = os.path.join(base, "ps2card_tests")
    shutil.rmtree(TMP, ignore_errors=True)
    os.makedirs(TMP)
    unittest.main(argv=[sys.argv[0]], verbosity=1)
