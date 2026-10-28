#!/usr/bin/env python3
"""compare.py - the port's C prompt atlas builder against tools/assets/gaiji.py.

src/settings/rg_prompts.c re-implements `gaiji.py build` (procedural glyphs,
palette quantisation, PSMT8 swizzle, CSM1 CLUT) so the game can build the
per-style gaiji2 images at run time from the user's own data. This script
checks that both produce the same picture for every style:

  python tools/prompts/compare.py --exe build/prompts-i686/tests/settings/rg-prompts-tests.exe
        [--data data] [--out out/prompts/atlas] [--bindings rg.ini]

For each style it builds gaiji2_<style>.img with gaiji.py (in memory) and with
the C helper (`rg-prompts-tests build_img`), decodes both and compares the RGBA
of all 256x256 pixels; it also checks that every pixel outside the 8 button
rects keeps its exact index byte. PNGs of the C build go to --out (game art:
out/ is gitignored, never commit them). Exit 0 = identical pictures, 1 =
differences (printed), 77 = no game data (ctest SKIP_RETURN_CODE).
"""
import argparse
import os
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(PORT, 'tools', 'assets'))
import gaiji  # noqa: E402

BUTTON_ORDER = [0xFD04, 0xFD02, 0xFD03, 0xFD05, 0xFD06, 0xFD07, 0xFD09, 0xFD08]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--exe', required=True, help='rg-prompts-tests executable')
    ap.add_argument('--data', default=os.path.join(PORT, 'data'))
    ap.add_argument('--out', default=os.path.join(PORT, 'out', 'prompts', 'atlas'))
    ap.add_argument('--bindings', help='settings .ini for the keyboard labels')
    ap.add_argument('--styles', default='xbox,nintendo,keyboard')
    args = ap.parse_args(argv)
    if not os.path.exists(os.path.join(args.data, 'SCUS_974.90')):
        print('no game data in %s: skipped' % args.data)
        return 77
    img, _ = gaiji.load_gaiji_img(args.data)
    metrics, _tags, _insect = gaiji.read_tables(args.data)
    rects = {m['code']: m for m in metrics if m['code'] in gaiji.BUTTONS}
    for code, want in zip(BUTTON_ORDER, [(0, 0, 32, 20), (32, 0, 32, 20), (64, 0, 32, 20),
                                         (96, 0, 32, 20), (0, 20, 22, 22), (22, 20, 22, 22),
                                         (44, 20, 22, 22), (66, 20, 22, 22)]):
        m = rects[code]
        if (m['u'], m['v'], m['w'], m['h']) != want:
            print('FAIL: ELF rect %04X = %r, rg_prompts.c has %r' % (code, m, want))
            return 1
    orig = gaiji.decode(img)
    binding = gaiji.read_bindings(args.bindings)
    keys = [binding.get(gaiji.BUTTONS[c][2]) or '-' for c in BUTTON_ORDER]
    os.makedirs(args.out, exist_ok=True)
    inside = [False] * (256 * 256)
    for m in rects.values():
        for y in range(m['v'], m['v'] + m['h']):
            for x in range(m['u'], m['u'] + m['w']):
                inside[y * 256 + x] = True
    bad = 0
    with tempfile.TemporaryDirectory() as tmp:
        src = os.path.join(tmp, 'gaiji2.img')
        with open(src, 'wb') as f:
            f.write(img)
        for style in [s for s in args.styles.split(',') if s]:
            _layer, ind, _used = gaiji.build_style(style, orig, metrics, binding, False)
            ref = ind.rgba()
            dst = os.path.join(tmp, style + '.img')
            cmd = [args.exe, 'build_img', src, style, dst]
            if style == 'keyboard':
                cmd += keys
            subprocess.run(cmd, check=True)
            c_img = open(dst, 'rb').read()
            got_ind = gaiji.decode(c_img)
            got = got_ind.rgba()
            gaiji.write_png(os.path.join(args.out, 'gaiji2_%s.png' % style), 256, 256, got)
            diff = [i for i in range(256 * 256) if ref[4 * i:4 * i + 4] != got[4 * i:4 * i + 4]]
            moved = sum(1 for i in range(256 * 256)
                        if not inside[i] and got_ind.idx[i] != orig.idx[i])
            hdr_same = c_img[:0x90] == img[:0x90] and len(c_img) == len(img)
            worst = 0
            for i in diff:
                worst = max(worst, max(abs(ref[4 * i + k] - got[4 * i + k]) for k in range(4)))
            print('%-9s %5d / 65536 pixels differ from gaiji.py (worst channel %d); '
                  '%d index bytes moved outside the rects; headers %s'
                  % (style, len(diff), worst, moved, 'same' if hdr_same else 'DIFFERENT'))
            if diff or moved or not hdr_same:
                bad += 1
                for i in diff[:8]:
                    print('   (%d,%d) gaiji.py %s  C %s' % (i % 256, i // 256,
                                                         tuple(ref[4 * i:4 * i + 4]),
                                                         tuple(got[4 * i:4 * i + 4])))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
