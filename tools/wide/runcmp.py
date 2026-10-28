# SPDX-License-Identifier: CC0-1.0
"""runcmp.py RUN_A RUN_B : compare two tools/wide/run.sh runs (docs/WIDESCREEN.md "Stage 1"):
the STATUS lines, every RG_GS_DUMP file byte-wise (display PNGs: count of differing
pixels) and every --shot native PNG.  RUN_x is a run directory, or a name under
$RG_WIDE_RUNS (default out/wide/stage1/runs)."""
import sys, os, hashlib, zlib, struct

R = os.environ.get('RG_WIDE_RUNS', 'out/wide/stage1/runs')


def png_pixels(p):
    d = open(p, 'rb').read()
    i = 8; idat = b''; w = h = 0; ct = 0
    while i < len(d):
        n, t = struct.unpack('>I4s', d[i:i + 8])
        c = d[i + 8:i + 8 + n]
        if t == b'IHDR': w, h, bd, ct = struct.unpack('>IIBB', c[:10])
        if t == b'IDAT': idat += c
        i += 12 + n
    raw = zlib.decompress(idat)
    bpp = {2: 3, 6: 4}[ct]
    stride = w * bpp
    out = bytearray(); prev = bytearray(stride); k = 0
    for y in range(h):
        f = raw[k]; row = bytearray(raw[k + 1:k + 1 + stride]); k += 1 + stride
        for x in range(stride):
            a = row[x - bpp] if x >= bpp else 0
            b = prev[x]; c = prev[x - bpp] if x >= bpp else 0
            if f == 1: row[x] = (row[x] + a) & 255
            elif f == 2: row[x] = (row[x] + b) & 255
            elif f == 3: row[x] = (row[x] + (a + b) // 2) & 255
            elif f == 4:
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                pr = a if pa <= pb and pa <= pc else (b if pb <= pc else c)
                row[x] = (row[x] + pr) & 255
        out += row; prev = row
    return w, h, bpp, bytes(out)


def ndiff(pa, pb):
    wa, ha, ba, a = png_pixels(pa)
    wb, hb, bb, b = png_pixels(pb)
    if (wa, ha, ba) != (wb, hb, bb): return 'size %dx%d vs %dx%d' % (wa, ha, wb, hb)
    n = sum(1 for i in range(0, len(a), ba) if a[i:i + ba] != b[i:i + ba])
    return '%d px differ (%.2f%%)' % (n, 100.0 * n / (wa * ha))


def status(run):
    return [l.strip() for l in open(f'{run}/log.txt', errors='replace') if l.startswith('STATUS')]


a, b = [x if os.path.isdir(x) else f'{R}/{x}' for x in sys.argv[1:3]]
R = ''
sa, sb = status(a), status(b)
print('STATUS lines: %d / %d, %s' % (len(sa), len(sb), 'identical' if sa == sb else 'DIFFER'))
if sa != sb:
    for x, y in zip(sa, sb):
        if x != y: print('  first diff:', x, '|', y); break
da, db = f'{a}/dump', f'{b}/dump'
same = diff = 0
for f in sorted(os.listdir(da)):
    if not os.path.exists(f'{db}/{f}'): print('  missing in B', f); continue
    if open(f'{da}/{f}', 'rb').read() == open(f'{db}/{f}', 'rb').read(): same += 1
    else:
        diff += 1
        print('  dump differs:', f, ndiff(f'{da}/{f}', f'{db}/{f}') if f.endswith('_display.png') else '')
print('dump files: %d identical, %d differ' % (same, diff))
sh = f'{a}/shot'
for f in sorted(os.listdir(sh)):
    if f.endswith('-view.png'): continue
    p, q = f'{sh}/{f}', f'{b}/shot/{f}'
    if not os.path.exists(q): print('  shot missing in B', f); continue
    if open(p, 'rb').read() == open(q, 'rb').read(): print('  shot', f, 'identical')
    else: print('  shot', f, ndiff(p, q))
