#!/usr/bin/env python3
"""vram_gaiji.py - find and decode the gaiji2 texture in a GS local-memory dump.

The runtime's RG_GS_DUMP_DIR / RG_GS_DUMP_FIELDS writes fNNNNN.vram (the 4 MB of
GS local memory at the end of a field; docs/GPU.md). This tool locates the
button-prompt texture in it and writes it as a PNG, so a run can show which
prompt atlas the GS actually holds (docs/PROMPTS.md "Implementation"):

  python tools/prompts/vram_gaiji.py f24500.vram out.png [--data data]

gaiji2.img's pixels are stored the way the GS holds a PSMT8 texture uploaded as
PSMCT32, so the texture is a 128x128 PSMCT32 rectangle (buffer width 2) in local
memory, and its CSM1 CLUT a 16x16 PSMCT32 rectangle (buffer width 1). Both are
found by matching the original file (read from data/) on pixels outside the 8
button rects and on the CLUT entries the original uses outside them, then
decoded with tools/assets/gaiji.py. Prints the base pointers, how many of the
sampled words match, and which style the 8 rects hold (by comparing them with
gaiji.py's procedural glyphs). Exit 1 if the texture is not found.
"""
import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(PORT, 'tools', 'assets'))
import gaiji  # noqa: E402

BLOCK32 = [[0, 1, 4, 5, 16, 17, 20, 21], [2, 3, 6, 7, 18, 19, 22, 23],
           [8, 9, 12, 13, 24, 25, 28, 29], [10, 11, 14, 15, 26, 27, 30, 31]]
COLUMN32 = [[0, 1, 4, 5, 8, 9, 12, 13], [2, 3, 6, 7, 10, 11, 14, 15],
            [16, 17, 20, 21, 24, 25, 28, 29], [18, 19, 22, 23, 26, 27, 30, 31],
            [32, 33, 36, 37, 40, 41, 44, 45], [34, 35, 38, 39, 42, 43, 46, 47],
            [48, 49, 52, 53, 56, 57, 60, 61], [50, 51, 54, 55, 58, 59, 62, 63]]


def addr32(bp, bw, x, y):
    """PSMCT32 word address of (x, y) in a buffer at block bp, width bw x 64 px."""
    page = (y >> 5) * bw + (x >> 6)
    block = BLOCK32[(y >> 3) & 3][(x >> 3) & 7]
    return (bp * 64 + page * 2048 + block * 64 + COLUMN32[y & 7][x & 7]) & 0xFFFFF


def read_rect(vram, bp, bw, w, h):
    out = bytearray(w * h * 4)
    for y in range(h):
        for x in range(w):
            a = addr32(bp, bw, x, y) * 4
            o = (y * w + x) * 4
            out[o:o + 4] = vram[a:a + 4]
    return bytes(out)


def find(vram, samples, bw, nblocks=16384, step=1):
    """Best base block for a list of ((x, y), word bytes) samples."""
    best = (-1, 0)
    for bp in range(0, nblocks, step):
        n = 0
        for (x, y), word in samples:
            a = addr32(bp, bw, x, y) * 4
            if vram[a:a + 4] == word:
                n += 1
        if n > best[1]:
            best = (bp, n)
            if n == len(samples):
                break
    return best


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('vram')
    ap.add_argument('png')
    ap.add_argument('--data', default=os.path.join(PORT, 'data'))
    args = ap.parse_args(argv)
    vram = open(args.vram, 'rb').read()
    img, _ = gaiji.load_gaiji_img(args.data)
    metrics, _t, _i = gaiji.read_tables(args.data)
    L = gaiji.tim2_layout(img)
    pix = img[L['pixels']:L['pixels'] + 0x10000]
    clut = img[L['clut']:L['clut'] + 0x400]
    orig = gaiji.decode(img)
    rects = [m for m in metrics if m['code'] in gaiji.BUTTONS]

    def in_rects_word(x, y):
        # a PSMCT32 word at (x, y) of the 128x128 rectangle holds 4 PSMT8 pixels;
        # skip words whose bytes land in the button rects (rows 0..41 hold them all)
        return y < 32
    samples = []
    for y in range(40, 128, 7):
        for x in range(3, 128, 11):
            o = (y * 128 + x) * 4
            samples.append(((x, y), pix[o:o + 4]))
    samples = [s for s in samples if not in_rects_word(*s[0]) and s[1] != b'\0\0\0\0'][:64]
    tbp, nt = find(vram, samples, 2)
    used = sorted(set(orig.idx[i] for i in range(65536)
                      if not any(m['u'] <= i % 256 < m['u'] + m['w'] and
                                 m['v'] <= i // 256 < m['v'] + m['h'] for m in rects)))
    csamples = []
    for i in used[::4]:
        j = gaiji.csm1(i)          # storage position of palette index i
        x, y = j % 16, j // 16
        csamples.append(((x, y), clut[4 * j:4 * j + 4]))
    cbp, nc = find(vram, csamples, 1)
    print('texture: TBP block %d (0x%x), %d/%d sampled words match; CLUT: CBP block %d (0x%x), '
          '%d/%d match' % (tbp, tbp, nt, len(samples), cbp, cbp, nc, len(csamples)))
    if nt < len(samples) * 0.9 or nc < len(csamples) * 0.9:
        print('gaiji2 not found in this dump')
        return 1
    got_pix = read_rect(vram, tbp, 2, 128, 128)
    got_clut = read_rect(vram, cbp, 1, 16, 16)
    out = bytearray(img)
    out[L['pixels']:L['pixels'] + 0x10000] = got_pix
    out[L['clut']:L['clut'] + 0x400] = got_clut
    ind = gaiji.decode(bytes(out))
    rgba = ind.rgba()
    gaiji.write_png(args.png, 256, 256, rgba)
    outside = sum(1 for i in range(65536) if ind.idx[i] != orig.idx[i] and not any(
        m['u'] <= i % 256 < m['u'] + m['w'] and m['v'] <= i // 256 < m['v'] + m['h']
        for m in rects))
    # which style do the 8 rects hold?
    scores = {}
    base = orig.rgba()
    for style in ('ps', 'xbox', 'nintendo', 'keyboard'):
        ref = base if style == 'ps' else gaiji.build_style(style, orig, metrics, None, False)[1].rgba()
        diff = 0
        for m in rects:
            for y in range(m['v'], m['v'] + m['h']):
                for x in range(m['u'], m['u'] + m['w']):
                    i = (y * 256 + x) * 4
                    diff += ref[i:i + 4] != rgba[i:i + 4]
        scores[style] = diff
    best = min(scores, key=scores.get)
    print('index bytes changed outside the button rects: %d; rect pixels differing from each '
          'style: %s -> %s' % (outside, scores, best if scores[best] == 0 else best + ' (closest)'))
    print('wrote', args.png)
    return 0


if __name__ == '__main__':
    sys.exit(main())
