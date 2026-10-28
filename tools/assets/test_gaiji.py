#!/usr/bin/env python3
"""Tests for tools/assets/gaiji.py (stdlib unittest).

    python tools/assets/test_gaiji.py [-v]

The format tests use a synthetic IM3/TIM2 and need no game data. The data tests
read data/ (rg-extract output) when it exists and are skipped otherwise; they
write nothing outside a temporary directory.
"""
import os
import random
import struct
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gaiji  # noqa: E402

DATA = os.environ.get('RG_DATA', os.path.join(gaiji.PORT, 'data'))
HAVE_DATA = os.path.exists(os.path.join(DATA, 'SCUS_974.90')) and os.path.exists(
    os.path.join(DATA, 'DATA0_0.HD6'))


def make_template(w=256, h=256, name=b'gaiji2'):
    """A minimal IM3 + TIM2 (PSMT8, CSM1 CLUT) shaped like the game's file."""
    pic = struct.pack('<IIIHHBBBBHH', 0x30 + w * h + 1024, 1024, w * h, 0x30, 256, 0, 1,
                      3, 5, w, h) + b'\0' * 0x18
    tim = b'TIM2' + bytes((4, 0)) + struct.pack('<H', 1) + b'\0' * 8 + pic
    tim += b'\0' * (w * h + 1024)
    entry = name.ljust(0x20, b'\0') + struct.pack('<II', 0x40, 0x50) + b'\0' * 12 + \
        struct.pack('<I', len(tim)) + b'\0' * 8
    return b'IM3\0' + struct.pack('<III', 0x10, 1, 0) + entry + tim


def random_indexed(w, h, seed, ncolours=256):
    rnd = random.Random(seed)
    pal = [(rnd.randrange(256), rnd.randrange(256), rnd.randrange(256), rnd.randrange(129))
           for _ in range(ncolours)]
    pal += [(0, 0, 0, 0)] * (256 - len(pal))
    idx = bytes(rnd.randrange(ncolours) for _ in range(w * h))
    return gaiji.Indexed(w, h, idx, pal)


class Format(unittest.TestCase):
    def test_swizzle_is_a_permutation_and_inverts(self):
        for w, h in ((256, 256), (64, 32), (128, 64), (16, 4)):
            perm = gaiji._swizzle8_table(w, h)
            self.assertEqual(sorted(perm), list(range(w * h)))
            data = bytes(random.Random(w).randrange(256) for _ in range(w * h))
            self.assertEqual(gaiji.unswizzle8(gaiji.swizzle8(data, w, h), w, h), data)
            self.assertEqual(gaiji.swizzle8(gaiji.unswizzle8(data, w, h), w, h), data)

    def test_csm1_is_an_involution(self):
        for i in range(256):
            self.assertEqual(gaiji.csm1(gaiji.csm1(i)), i)
        self.assertEqual(gaiji.csm1(8), 16)
        self.assertEqual(gaiji.csm1(23), 15)

    def test_encode_decode_indexed(self):
        tpl = make_template()
        ind = random_indexed(256, 256, 1)
        enc = gaiji.encode(ind, tpl)
        self.assertEqual(len(enc), len(tpl))
        back = gaiji.decode(enc)
        self.assertEqual(back.idx, ind.idx)
        self.assertEqual(back.pal, ind.pal)
        self.assertEqual(gaiji.encode(back, tpl), enc)

    def test_rgba_round_trip(self):
        """decode(encode(x)) == x for an RGBA image of <= 256 PS2-representable colours."""
        tpl = make_template()
        x = random_indexed(256, 256, 2, ncolours=200).rgba()
        ind = gaiji.index_rgba(x, 256, 256, template=tpl)
        self.assertEqual(gaiji.decode(gaiji.encode(ind, tpl)).rgba(), x)

    def test_alpha_mapping(self):
        for a in range(129):
            self.assertEqual(gaiji.ps2_alpha(min(255, a * 2)), a)

    def test_rename_and_cap(self):
        tpl = make_template()
        enc = gaiji.encode(random_indexed(256, 256, 3), tpl, name='gaiji2x')
        self.assertEqual(enc[0x10:0x18], b'gaiji2x\0')
        self.assertLessEqual(len(enc), gaiji.IMG_MAX)
        bad = random_indexed(256, 256, 4)
        bad.pal[0] = (0, 0, 0, 0x81)
        with self.assertRaises(ValueError):
            gaiji.encode(bad, tpl)

    def test_png_round_trip(self):
        x = random_indexed(37, 11, 5).rgba()
        with tempfile.TemporaryDirectory() as d:
            p = os.path.join(d, 't.png')
            gaiji.write_png(p, 37, 11, x)
            self.assertEqual(gaiji.read_png(p), (37, 11, x))

    def test_bindings(self):
        ini = ('[input]\nbind.confirm = key:Return, pad:a\nbind.cancel = mouse:x+, '
               'mouse:right   # comment\nbind.shoulder_left = key:Left Shift\n'
               'bind.menu =\n[display]\nbind.attack = key:K\n'
               'input.bind.decline = key:Keypad 8\n')
        with tempfile.TemporaryDirectory() as d:
            p = os.path.join(d, 's.ini')
            with open(p, 'w') as f:
                f.write(ini)
            b = gaiji.read_bindings(p)
        self.assertEqual(b['confirm'], 'key:Return')
        self.assertEqual(b['cancel'], 'mouse:right')          # motion skipped
        self.assertEqual(b['camera_turn_left'], 'key:Left Shift')  # old id
        self.assertIsNone(b['menu'])                          # unbound
        self.assertEqual(b['attack'], 'key:Z')                # other section ignored
        self.assertEqual(b['decline'], 'key:1')               # 'display.input.bind...'
        self.assertEqual(gaiji.key_label('key:Keypad 8'), 'K8')
        self.assertEqual(gaiji.key_label('key:Space'), 'SPC')
        self.assertEqual(gaiji.key_label('key:Space', wide=True), 'SPACE')
        self.assertEqual(gaiji.key_label('mouse:left'), ('mouse', 'left'))

    def test_stroke_font_covers_labels(self):
        for lab in list(gaiji.KEY_LABELS.values()) + list(gaiji.KEY_LABELS_WIDE.values()):
            for ch in lab:
                self.assertIn(ch, gaiji.STROKES, lab)
        for ch in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789':
            self.assertIn(ch, gaiji.STROKES)


@unittest.skipUnless(HAVE_DATA, 'no extracted disc in %s' % DATA)
class GameData(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.img, cls.copies = gaiji.load_gaiji_img(DATA)
        cls.metrics, cls.tags, cls.insect = gaiji.read_tables(DATA)
        cls.orig = gaiji.decode(cls.img)

    def test_original_reencodes_byte_identical(self):
        self.assertEqual(gaiji.encode(self.orig, self.img), self.img)
        self.assertTrue(all(same for _w, same in self.copies))

    def test_format(self):
        L = gaiji.tim2_layout(self.img)
        self.assertEqual((L['w'], L['h']), (256, 256))
        self.assertEqual((L['tex0'] >> 20) & 0x3F, 0x13)   # PSMT8
        self.assertEqual((L['tex0'] >> 14) & 0x3F, 4)      # TBW 256/64
        self.assertLessEqual(len(self.img), gaiji.IMG_MAX)
        self.assertTrue(all(a <= 0x80 for *_c, a in self.orig.pal))

    def test_button_table(self):
        by = {m['code']: m for m in self.metrics}
        want = {0xFD04: (0, 0, 32, 20), 0xFD02: (32, 0, 32, 20), 0xFD03: (64, 0, 32, 20),
                0xFD05: (96, 0, 32, 20), 0xFD06: (0, 20, 22, 22), 0xFD07: (22, 20, 22, 22),
                0xFD09: (44, 20, 22, 22), 0xFD08: (66, 20, 22, 22)}
        for code, r in want.items():
            m = by[code]
            self.assertEqual((m['u'], m['v'], m['w'], m['h']), r)
        tags = {t['tag']: t['code'] for t in self.tags}
        self.assertEqual(tags['(X)'], 0xFD08)
        self.assertEqual(tags['[l2]'], 0xFD04)
        self.assertEqual(self.insect[0], {'u': 32, 'v': 0, 'w': 32, 'h': 20})
        self.assertEqual(self.insect[1], {'u': 64, 'v': 0, 'w': 32, 'h': 20})

    def test_styles_round_trip(self):
        binding = dict(gaiji.DEFAULT_KEYS, cancel='mouse:right')
        for style, wide in (('xbox', False), ('nintendo', False), ('keyboard', False),
                            ('keyboard', True)):
            layer, ind, used = gaiji.build_style(style, self.orig, self.metrics, binding, wide)
            x = ind.rgba()
            enc = gaiji.encode(ind, self.img)
            self.assertLessEqual(len(enc), gaiji.IMG_MAX)
            self.assertEqual(gaiji.decode(enc).rgba(), x, style)          # decode(encode(x))
            again = gaiji.index_rgba(x, 256, 256, fixed=ind.pal, editable=[])
            self.assertEqual(gaiji.encode(again, self.img), enc, style)   # stable bytes
            # Pixels outside every button rect are untouched.
            rects = [m for m in self.metrics + used if m['code'] in gaiji.BUTTONS]
            src = self.orig.rgba()
            inside = bytearray(256 * 256)
            for m in rects:
                for y in range(m['v'], m['v'] + m['h']):
                    inside[y * 256 + m['u']:y * 256 + m['u'] + m['w']] = bytes([1]) * m['w']
            for i in range(256 * 256):
                if not inside[i]:
                    self.assertEqual(x[i * 4:i * 4 + 4], src[i * 4:i * 4 + 4], (style, i))
            if not wide:
                self.assertEqual([(m['u'], m['v'], m['w']) for m in used],
                                 [(m['u'], m['v'], m['w']) for m in self.metrics])


if __name__ == '__main__':
    unittest.main()
