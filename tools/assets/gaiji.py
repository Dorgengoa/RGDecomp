#!/usr/bin/env python3
"""gaiji.py - dump and replace Rogue Galaxy's button-prompt texture (`gaiji2`).

Standard library only. Reads the extracted disc in data/ (rg-extract output) and
never writes there. Everything it makes goes to out/gaiji/ (gitignored: the dump
and the composited atlases contain game art and must never be committed).

  gaiji.py dump     [--data DIR] [--out DIR]
      gaiji2_ps.png        the original atlas, RGBA (PS2 alpha 0..0x80 -> 0..255)
      gaiji2_ps.img        the original IM3 file, byte-identical (for diffing)
      gaiji2_glyphs.json   every gaiji code: tags, rect, advance, offsets, button role
      gaiji2_rects.png     the atlas x3 with the button rects outlined (review aid)

  gaiji.py build    [--data DIR] [--out DIR] [--styles xbox,nintendo,keyboard]
                    [--bindings settings.ini] [--wide]
      prompts_<style>.png  button glyphs only, procedural, transparent elsewhere
      gaiji2_<style>.png   the original atlas with the 8 button rects redrawn
      gaiji2_<style>.img   the same, re-encoded to the game's format (IM3 + TIM2,
                           PSMT8 256x256, CSM1 CLUT, swizzled), <= 0x10800 bytes
      gaiji2_<style>.json  the metric records that atlas needs (same as the
                           original unless --wide moved keyboard glyphs)
      Each .img is decoded again and compared with the PNG (round trip).

  gaiji.py encode   IN.png OUT.img [--data DIR]   any 256x256 RGBA PNG -> game format
  gaiji.py decode   IN.img OUT.png                game format -> RGBA PNG

Formats (see docs/PROMPTS.md for the full write-up):

  HD6 index record = LE u64: bits 0-17 name-stream offset, 18-37 data offset in
  2048-byte sectors, 38-63 size/4. Names are varint token strings.
  Pack (.pak): chained entries {name[0x40] (NUL, then junk), u32 hdr=0x50,
  u32 size, u32 next (relative, 16-aligned), u32 '@ABC'}; body at +hdr; the
  chain ends at next == 0 or at a size 0xFFFFFFFF terminator.
  IM3 (.img): 'IM3\\0', u32 0x10, u32 count, u32 0; count x 0x40 entries
  {name[0x20], u32 0x40, u32 TIM2 offset, ..., +0x34 u32 TIM2 size}.
  TIM2 v4, one picture: PSMT8 (type 5) 256x256, 256-entry 32-bit CLUT in CSM1
  order (entries 8-15 and 16-23 of every 32 swapped), alpha 0..0x80, pixels stored
  as the GS holds them after a PSMCT32 upload (the "PSMT8 swizzle").

Game tables (SCUS_974.90, names from the decomp at rgd-git 675c07f):
  D_0044E680  12-byte metrics {u16 code, s16 u, s16 v, s16 w, s8 h, s8 dx, s8 dy, pad}
              (FontFindGaijiMetric_26f8c0; width = advance, FontGetGaijiWidth_26f890)
  D_0044EA00  8-byte tags {char *name, s16 len, u16 code} (TextGaijiTagFind_26f060)
  D_0047FC90  2 x {s16 u, v, w, h}: L1, R1 (InsectCageButtonHintDraw_388ee0)
"""
import argparse
import glob
import json
import math
import os
import struct
import sys
import zlib

SECTOR = 2048
HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(os.path.dirname(HERE))

# ------------------------------------------------------------ game facts ---

PAK_GLOB = 'meswin\\fontset_main_'          # D_0045F660 'meswin/fontset_main_?.pak'
PAK_LAUNCHER = 'meswin\\fontset_launcher_'  # D_0045F640
IMG_NAME = 'gaiji2.img'                     # D_0045F688
TEX_NAME = 'gaiji2'                         # D_0045F680 (name-table key)
IMG_MAX = 0x10800                           # GaijiLoadImage_2705a0 buffer cap
ELF_METRICS = 0x0044E680
ELF_TAGS = 0x0044EA00
ELF_INSECT_RECTS = 0x0047FC90

# PS2 button role of each button gaiji, and its SDL positional name.
BUTTONS = {
    0xFD04: ('L2', 'left_trigger', 'decline'),
    0xFD02: ('L1', 'left_shoulder', 'camera_turn_left'),
    0xFD03: ('R1', 'right_shoulder', 'camera_turn_right'),
    0xFD05: ('R2', 'right_trigger', 'camera_recentre'),
    0xFD06: ('Circle', 'east', 'cancel'),
    0xFD07: ('Triangle', 'north', 'menu'),
    0xFD09: ('Square', 'west', 'attack'),
    0xFD08: ('Cross', 'south', 'confirm'),
}
# Codes that have no tag (drawn by fixed-rect code or unused), from the atlas.
UNTAGGED = {
    0xFD3A: 'arrow (no tag)', 0xFD3B: 'arrow (no tag)',
    0xFD3C: 'down triangle, no tag (message-window page icon art, inferred)',
    0xFD3D: 'right triangle, no tag (choice arrow art, inferred)',
    0xFD3F: '(R) registered sign, font-type-2 variant of FD3E',
}

# Default keyboard binding per action (docs/INPUT.md "Actions"; first key shown).
DEFAULT_KEYS = {
    'confirm': 'key:Space', 'cancel': 'key:C', 'attack': 'key:Z', 'menu': 'key:Tab',
    'camera_turn_left': 'key:Q', 'camera_turn_right': 'key:E',
    'decline': 'key:1', 'camera_recentre': 'key:3',
}
OLD_IDS = {
    'shoulder_left': 'camera_turn_left', 'shoulder_right': 'camera_turn_right',
    'trigger_left': 'decline', 'trigger_right': 'camera_recentre',
}

# ---------------------------------------------------------------- archive ---


class Hd6:
    """One DATA*.HD6 index + its .DAT."""

    def __init__(self, hd6_path):
        self.dat = hd6_path[:-4] + '.DAT'
        d = open(hd6_path, 'rb').read()
        if d[:3] != b'HD6':
            raise ValueError('%s: not an HD6 index' % hd6_path)
        tok_off, tok_size = struct.unpack_from('<II', d, 4)
        name_off, name_size = struct.unpack_from('<II', d, 0x14)
        count, dir_off = struct.unpack_from('<II', d, 0x24)
        toks = d[tok_off:tok_off + tok_size].split(b'\0')
        names = d[name_off:name_off + name_size]
        self.files = {}
        for i in range(count):
            v = struct.unpack_from('<Q', d, dir_off + i * 8)[0]
            size = (v >> 38) << 2
            if size:
                self.files[_hd6_name(names, toks, v & 0x3FFFF)] = (
                    ((v >> 18) & 0xFFFFF) * SECTOR, size)

    def read(self, path):
        off, size = self.files[path]
        with open(self.dat, 'rb') as f:
            f.seek(off)
            return f.read(size)


def _hd6_name(names, toks, i):
    parts = []
    while i < len(names):
        v = shift = 0
        while True:
            b = names[i]
            i += 1
            v |= (b & 0x7F) << shift
            shift += 7
            if not b & 0x80:
                break
        if v == 0:
            break
        parts.append(toks[v].decode('cp932', 'replace') if v < len(toks) else '?')
    return ''.join(parts)


def pak_entries(data):
    """Level-5 pack -> [(name, body offset, size)]."""
    out, pos = [], 0
    while pos + 0x50 <= len(data):
        hdr, size, nxt = struct.unpack_from('<III', data, pos + 0x40)
        if size == 0xFFFFFFFF:
            break
        if hdr < 0x50 or pos + hdr + size > len(data):
            raise ValueError('bad pack entry at %#x' % pos)
        out.append((data[pos:pos + 0x40].split(b'\0')[0].decode('cp932'), pos + hdr, size))
        if not nxt:
            break
        pos += nxt
    return out


def find_paks(data_dir, prefix):
    """[(hd6 name, path, bytes)] for every pak whose path starts with prefix."""
    out = []
    for hd6 in sorted(glob.glob(os.path.join(data_dir, 'DATA*.HD6'))):
        a = Hd6(hd6)
        for path in sorted(a.files):
            if path.lower().startswith(prefix):
                out.append((os.path.basename(hd6), path, a.read(path)))
    return out


def load_gaiji_img(data_dir):
    """The original gaiji2.img bytes and where they came from (+ copy check)."""
    paks = find_paks(data_dir, PAK_GLOB)
    if not paks:
        raise SystemExit('no %s*.pak in %s (run rg-extract first)' % (PAK_GLOB, data_dir))
    found = []
    for src, path, pak in paks + find_paks(data_dir, PAK_LAUNCHER):
        for name, off, size in pak_entries(pak):
            if name == IMG_NAME:
                found.append(('%s:%s' % (src, path), pak[off:off + size]))
    if not found:
        raise SystemExit('%s not found in the font packs' % IMG_NAME)
    first = found[0][1]
    return first, [(where, img == first) for where, img in found]


# ------------------------------------------------------------------- ELF ---


class Elf:
    def __init__(self, path):
        self.d = open(path, 'rb').read()
        if self.d[:4] != b'\x7fELF':
            raise ValueError('%s: not an ELF' % path)
        phoff = struct.unpack_from('<I', self.d, 0x1C)[0]
        n = struct.unpack_from('<H', self.d, 0x2C)[0]
        self.segs = []
        for i in range(n):
            _t, off, va, _pa, fsz = struct.unpack_from('<5I', self.d, phoff + i * 32)
            if fsz:
                self.segs.append((va, off, fsz))

    def read(self, va, n):
        for v, off, fsz in self.segs:
            if v <= va and va + n <= v + fsz:
                return self.d[off + va - v:off + va - v + n]
        raise ValueError('address %#x not in a file-backed segment' % va)

    def cstr(self, va):
        return self.read(va, 64).split(b'\0')[0].decode('ascii')


def read_tables(data_dir):
    """Metric records, tag table and the insect-cage rects, straight from the ELF."""
    elf = Elf(os.path.join(data_dir, 'SCUS_974.90'))
    metrics, p = [], ELF_METRICS
    while True:
        code, u, v, w, h, dx, dy, _pad = struct.unpack('<HhhhbbbB', elf.read(p, 12))
        if code == 0:
            break
        metrics.append({'code': code, 'u': u, 'v': v, 'w': w, 'h': h, 'dx': dx, 'dy': dy})
        p += 12
    tags, p = [], ELF_TAGS
    while True:
        name, length, code = struct.unpack('<IhH', elf.read(p, 8))
        if name == 0:
            break
        tags.append({'tag': elf.cstr(name)[:length], 'code': code})
        p += 8
    raw = struct.unpack('<8h', elf.read(ELF_INSECT_RECTS, 16))
    insect = [dict(zip('uvwh', raw[0:4])), dict(zip('uvwh', raw[4:8]))]
    if not metrics or metrics[0]['code'] != 0xFD02 or tags[0]['tag'] != '[l1]':
        raise SystemExit('ELF tables do not look like SCUS-97490 v1.01')
    return metrics, tags, insect


def glyph_map(metrics, tags, insect):
    by_code = {}
    for t in tags:
        by_code.setdefault(t['code'], []).append(t['tag'])
    glyphs = []
    for m in metrics:
        g = dict(m)
        g['code'] = '%04X' % m['code']
        g['tags'] = by_code.get(m['code'], [])
        if m['code'] in BUTTONS:
            g['button'], g['position'], g['action'] = BUTTONS[m['code']]
        elif m['code'] in UNTAGGED:
            g['note'] = UNTAGGED[m['code']]
        glyphs.append(g)
    return {
        'texture': TEX_NAME,
        'record': '{u16 code, s16 u, s16 v, s16 w (advance), s8 h, s8 dx, s8 dy, pad}',
        'metrics_table': '%#010x' % ELF_METRICS, 'tag_table': '%#010x' % ELF_TAGS,
        'note': 'FD3E is drawn as FD3F when the text style font type is 2 '
                '(FontFindGaijiMetric_26f8c0). Non-gaiji tags (<close> etc.) are listed '
                'with their FFxx codes but have no metric.',
        'glyphs': glyphs,
        'other_tags': [{'tag': t['tag'], 'code': '%04X' % t['code']} for t in tags
                       if not any(m['code'] == t['code'] for m in metrics)],
        'insect_cage_rects': {'address': '%#010x' % ELF_INSECT_RECTS,
                              'L1': insect[0], 'R1': insect[1]},
    }


# -------------------------------------------------------------- PS2 / TIM2 ---


def _swizzle8_table(w, h):
    """perm[y*w + x] = byte offset of linear pixel (x, y) in the swizzled buffer.

    PSMT8 pixels as they lie in GS memory after the texture was uploaded as
    PSMCT32: 16x16 blocks of 8 interleaved column pairs, with every second
    4-row group rotated by 4 pixels.
    """
    if w % 16 or h % 4:
        raise ValueError('swizzle needs w % 16 == 0 and h % 4 == 0')
    perm = [0] * (w * h)
    for y in range(h):
        row = (y & ~0xF) * w
        swap = (((y + 2) >> 2) & 1) * 4
        col = ((((y & ~3) >> 1) + (y & 1)) & 7) * w * 2
        byte = (y >> 1) & 1
        for x in range(w):
            perm[y * w + x] = (row + (x & ~0xF) * 2 + col + ((x + swap) & 7) * 4
                               + byte + ((x >> 2) & 2))
    return perm


def unswizzle8(buf, w, h):
    perm = _swizzle8_table(w, h)
    return bytes(buf[p] for p in perm)


def swizzle8(lin, w, h):
    perm = _swizzle8_table(w, h)
    out = bytearray(w * h)
    for i, p in enumerate(perm):
        out[p] = lin[i]
    return bytes(out)


def csm1(i):
    """CSM1 CLUT order: swap entries 8-15 with 16-23 in every 32 (self-inverse)."""
    return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1)


class Indexed:
    """A decoded gaiji texture: w x h linear indices + 256 PS2 RGBA (alpha 0..0x80)."""

    def __init__(self, w, h, idx, pal, template=None):
        self.w, self.h, self.idx, self.pal, self.template = w, h, bytes(idx), list(pal), template

    def rgba(self):
        """8-bit RGBA bytes, alpha = min(255, 2 * ps2_alpha)."""
        lut = [bytes((r, g, b, min(255, a * 2))) for r, g, b, a in self.pal]
        return b''.join(lut[i] for i in self.idx)


def _tim2_at(img):
    if img[:4] != b'IM3\0' or struct.unpack_from('<I', img, 4)[0] != 0x10:
        raise ValueError('not an IM3 file')
    if struct.unpack_from('<I', img, 8)[0] != 1:
        raise ValueError('IM3 with more than one texture')
    t = struct.unpack_from('<I', img, 0x10 + 0x24)[0]
    if img[t:t + 4] != b'TIM2':
        raise ValueError('IM3 entry does not point at a TIM2')
    return t


def tim2_layout(img):
    """Offsets of the picture header, pixels and CLUT inside an IM3 gaiji file."""
    t = _tim2_at(img)
    if img[t + 5] != 0 or struct.unpack_from('<H', img, t + 6)[0] != 1:
        raise ValueError('expected a 16-byte-aligned TIM2 with one picture')
    p = t + 0x10
    (total, clut_size, img_size, hdr_size, clut_colors, _fmt, mips, clut_type, img_type,
     w, h) = struct.unpack_from('<IIIHHBBBBHH', img, p)
    if (img_type, clut_type, clut_colors, mips) != (5, 3, 256, 1):
        raise ValueError('expected PSMT8 + 256-colour 32-bit CSM1 CLUT, got type %d/%#x/%d'
                         % (img_type, clut_type, clut_colors))
    if img_size != w * h or clut_size != 1024:
        raise ValueError('unexpected TIM2 sizes')
    tex0 = struct.unpack_from('<Q', img, p + 0x18)[0]
    return {'pic': p, 'pixels': p + hdr_size, 'clut': p + hdr_size + img_size,
            'w': w, 'h': h, 'end': p + total, 'tex0': tex0}


def decode(img):
    """IM3/TIM2 gaiji bytes -> Indexed."""
    L = tim2_layout(img)
    w, h = L['w'], L['h']
    idx = unswizzle8(img[L['pixels']:L['pixels'] + w * h], w, h)
    c = L['clut']
    pal = [tuple(img[c + 4 * csm1(i):c + 4 * csm1(i) + 4]) for i in range(256)]
    return Indexed(w, h, idx, pal, template=img)


def encode(ind, template, name=None):
    """Indexed -> IM3/TIM2 bytes, headers copied from template (the original)."""
    L = tim2_layout(template)
    if (ind.w, ind.h) != (L['w'], L['h']):
        raise ValueError('size must be %dx%d' % (L['w'], L['h']))
    if len(ind.pal) != 256 or any(not 0 <= a <= 0x80 for *_c, a in ind.pal):
        raise ValueError('palette must be 256 entries with alpha 0..0x80')
    out = bytearray(template[:L['end']])
    out[L['pixels']:L['pixels'] + ind.w * ind.h] = swizzle8(ind.idx, ind.w, ind.h)
    c = L['clut']
    for i, col in enumerate(ind.pal):
        out[c + 4 * csm1(i):c + 4 * csm1(i) + 4] = bytes(col)
    if name is not None:
        nb = name.encode('ascii')
        if len(nb) >= 0x20:
            raise ValueError('IM3 name too long')
        out[0x10:0x10 + len(nb) + 1] = nb + b'\0'
    if len(out) > IMG_MAX:
        raise ValueError('encoded image is %#x bytes, over the %#x cap' % (len(out), IMG_MAX))
    return bytes(out)


def ps2_alpha(a8):
    """8-bit PNG alpha -> PS2 alpha (inverse of min(255, 2a) on its image)."""
    return (a8 + 1) // 2


def index_rgba(rgba, w, h, fixed=None, editable=None, template=None):
    """RGBA bytes -> Indexed.

    fixed: optional palette (list of 256 PS2 RGBA) whose entries stay; editable:
    the indices of it that may be reassigned. Exact colours map to themselves; the
    free slots go greedily to the new colours that would otherwise cost the most,
    and the rest map to the nearest entry. Without `fixed`, an image of <= 256
    colours is exact and a larger one keeps its 256 most frequent colours.
    """
    px = [(rgba[i], rgba[i + 1], rgba[i + 2], ps2_alpha(rgba[i + 3]))
          for i in range(0, len(rgba), 4)]
    counts = {}
    for c in px:
        counts[c] = counts.get(c, 0) + 1
    if fixed is None:
        cols = sorted(counts, key=lambda c: -counts[c])[:256]
        pal = cols + [(0, 0, 0, 0)] * (256 - len(cols))
        free = []
    else:
        pal = list(fixed)
        free = sorted(editable or [])
    lookup = {}
    for i, c in enumerate(pal):
        if i not in free:
            lookup.setdefault(c, i)
    if fixed is not None and (0, 0, 0, 0) not in lookup:
        for i, c in enumerate(pal):
            if c[3] == 0 and i not in free:
                lookup[(0, 0, 0, 0)] = i
                break
    missing = {c: n for c, n in counts.items() if c not in lookup}
    if missing and free:
        fixed_cols = [c for c in lookup]
        best = {c: min(_dist(c, f) for f in fixed_cols) if fixed_cols else 1e18
                for c in missing}
        for slot in free:
            if not best:
                break
            pick = max(best, key=lambda c: best[c] * missing[c])
            if best[pick] == 0:
                break
            pal[slot] = pick
            lookup[pick] = slot
            del best[pick]
            for c in best:
                best[c] = min(best[c], _dist(c, pick))
    cache = {}

    def index_of(c):
        i = lookup.get(c)
        if i is None:
            i = cache.get(c)
            if i is None:
                i = min(lookup.items(), key=lambda kv: _dist(c, kv[0]))[1]
                cache[c] = i
        return i

    return Indexed(w, h, bytes(index_of(c) for c in px), pal, template)


def _dist(a, b):
    """Premultiplied RGBA distance (PS2 alpha 0..128)."""
    aa, ab = a[3] / 128.0, b[3] / 128.0
    d = 0.0
    for k in range(3):
        d += (a[k] * aa - b[k] * ab) ** 2
    return d + (2.0 * (a[3] - b[3])) ** 2


# -------------------------------------------------------------------- PNG ---


def write_png(path, w, h, rgba):
    def chunk(t, d):
        c = struct.pack('>I', len(d)) + t + d
        return c + struct.pack('>I', zlib.crc32(t + d) & 0xFFFFFFFF)
    raw = b''.join(b'\0' + rgba[y * w * 4:(y + 1) * w * 4] for y in range(h))
    data = (b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 6, 0, 0, 0))
            + chunk(b'IDAT', zlib.compress(raw, 9)) + chunk(b'IEND', b''))
    with open(path, 'wb') as f:
        f.write(data)


def read_png(path):
    """8-bit non-interlaced PNG (gray, RGB, RGBA, gray+alpha, palette) -> (w, h, RGBA)."""
    d = open(path, 'rb').read()
    if d[:8] != b'\x89PNG\r\n\x1a\n':
        raise ValueError('%s: not a PNG' % path)
    pos, idat, plte, trns = 8, b'', None, b''
    while pos < len(d):
        n = struct.unpack_from('>I', d, pos)[0]
        t, body = d[pos + 4:pos + 8], d[pos + 8:pos + 8 + n]
        if t == b'IHDR':
            w, h, depth, ctype, _c, _f, inter = struct.unpack('>IIBBBBB', body)
        elif t == b'IDAT':
            idat += body
        elif t == b'PLTE':
            plte = body
        elif t == b'tRNS':
            trns = body
        pos += 12 + n
    if depth != 8 or inter:
        raise ValueError('only 8-bit non-interlaced PNG is supported')
    bpp = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}[ctype]
    raw = zlib.decompress(idat)
    stride = w * bpp
    prev = bytearray(stride)
    rows = []
    for y in range(h):
        f = raw[y * (stride + 1)]
        line = bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        for i in range(stride):
            a = line[i - bpp] if i >= bpp else 0
            b = prev[i]
            c = prev[i - bpp] if i >= bpp else 0
            if f == 1:
                line[i] = (line[i] + a) & 255
            elif f == 2:
                line[i] = (line[i] + b) & 255
            elif f == 3:
                line[i] = (line[i] + ((a + b) >> 1)) & 255
            elif f == 4:
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                pr = a if pa <= pb and pa <= pc else (b if pb <= pc else c)
                line[i] = (line[i] + pr) & 255
        rows.append(bytes(line))
        prev = line
    out = bytearray()
    for line in rows:
        for x in range(w):
            p = line[x * bpp:(x + 1) * bpp]
            if ctype == 6:
                out += p
            elif ctype == 2:
                out += p + b'\xff'
            elif ctype == 0:
                out += bytes((p[0], p[0], p[0], 255))
            elif ctype == 4:
                out += bytes((p[0], p[0], p[0], p[1]))
            else:
                i = p[0]
                out += plte[i * 3:i * 3 + 3] + bytes((trns[i] if i < len(trns) else 255,))
    return w, h, bytes(out)


# ----------------------------------------------------------------- drawing ---
# A tiny procedural vector renderer: shapes are inside-tests sampled 4x4 per pixel,
# composited "over" in premultiplied float RGBA. Letters come from a stroke font
# drawn here (capsule polylines on a 4x6 grid); no third-party art or fonts.

STROKES = {
    'A': [[(0, 6), (0, 2), (2, 0), (4, 2), (4, 6)], [(0, 3.6), (4, 3.6)]],
    'B': [[(0, 0), (0, 6), (3, 6), (4, 5), (4, 4), (3, 3), (0, 3)],
          [(0, 0), (3, 0), (4, 1), (4, 2), (3, 3)]],
    'C': [[(4, 1), (3, 0), (1, 0), (0, 1), (0, 5), (1, 6), (3, 6), (4, 5)]],
    'D': [[(0, 0), (0, 6), (2.5, 6), (4, 4.5), (4, 1.5), (2.5, 0), (0, 0)]],
    'E': [[(4, 0), (0, 0), (0, 6), (4, 6)], [(0, 3), (3, 3)]],
    'F': [[(4, 0), (0, 0), (0, 6)], [(0, 3), (3, 3)]],
    'G': [[(4, 1), (3, 0), (1, 0), (0, 1), (0, 5), (1, 6), (3, 6), (4, 5), (4, 3), (2, 3)]],
    'H': [[(0, 0), (0, 6)], [(4, 0), (4, 6)], [(0, 3), (4, 3)]],
    'I': [[(1, 0), (3, 0)], [(2, 0), (2, 6)], [(1, 6), (3, 6)]],
    'J': [[(4, 0), (4, 5), (3, 6), (1, 6), (0, 5)]],
    'K': [[(0, 0), (0, 6)], [(4, 0), (0, 4)], [(1.5, 2.6), (4, 6)]],
    'L': [[(0, 0), (0, 6), (4, 6)]],
    'M': [[(0, 6), (0, 0), (2, 3), (4, 0), (4, 6)]],
    'N': [[(0, 6), (0, 0), (4, 6), (4, 0)]],
    'O': [[(1, 0), (3, 0), (4, 1), (4, 5), (3, 6), (1, 6), (0, 5), (0, 1), (1, 0)]],
    'P': [[(0, 6), (0, 0), (3, 0), (4, 1), (4, 2), (3, 3), (0, 3)]],
    'Q': [[(1, 0), (3, 0), (4, 1), (4, 5), (3, 6), (1, 6), (0, 5), (0, 1), (1, 0)],
          [(2.5, 4.5), (4, 6)]],
    'R': [[(0, 6), (0, 0), (3, 0), (4, 1), (4, 2), (3, 3), (0, 3)], [(2, 3), (4, 6)]],
    'S': [[(4, 1), (3, 0), (1, 0), (0, 1), (0, 2), (1, 3), (3, 3), (4, 4), (4, 5), (3, 6),
           (1, 6), (0, 5)]],
    'T': [[(0, 0), (4, 0)], [(2, 0), (2, 6)]],
    'U': [[(0, 0), (0, 5), (1, 6), (3, 6), (4, 5), (4, 0)]],
    'V': [[(0, 0), (2, 6), (4, 0)]],
    'W': [[(0, 0), (1, 6), (2, 3), (3, 6), (4, 0)]],
    'X': [[(0, 0), (4, 6)], [(4, 0), (0, 6)]],
    'Y': [[(0, 0), (2, 3), (4, 0)], [(2, 3), (2, 6)]],
    'Z': [[(0, 0), (4, 0), (0, 6), (4, 6)]],
    '0': [[(1, 0), (3, 0), (4, 1), (4, 5), (3, 6), (1, 6), (0, 5), (0, 1), (1, 0)],
          [(3.5, 1), (0.5, 5)]],
    '1': [[(1, 1), (2, 0), (2, 6)], [(1, 6), (3, 6)]],
    '2': [[(0, 1), (1, 0), (3, 0), (4, 1), (4, 2), (0, 6), (4, 6)]],
    '3': [[(0, 1), (1, 0), (3, 0), (4, 1), (4, 2), (3, 3), (4, 4), (4, 5), (3, 6), (1, 6),
           (0, 5)], [(1.5, 3), (3, 3)]],
    '4': [[(3, 6), (3, 0), (0, 4), (4, 4)]],
    '5': [[(4, 0), (0, 0), (0, 3), (3, 3), (4, 4), (4, 5), (3, 6), (0, 6)]],
    '6': [[(4, 0), (1, 0), (0, 1), (0, 5), (1, 6), (3, 6), (4, 5), (4, 4), (3, 3), (0, 3)]],
    '7': [[(0, 0), (4, 0), (1.5, 6)]],
    '8': [[(1, 0), (3, 0), (4, 1), (4, 2), (3, 3), (1, 3), (0, 2), (0, 1), (1, 0)],
          [(1, 3), (0, 4), (0, 5), (1, 6), (3, 6), (4, 5), (4, 4), (3, 3)]],
    '9': [[(0, 6), (3, 6), (4, 5), (4, 1), (3, 0), (1, 0), (0, 1), (0, 2), (1, 3), (4, 3)]],
    '-': [[(0.5, 3), (3.5, 3)]],
    '+': [[(0, 3), (4, 3)], [(2, 1), (2, 5)]],
    '=': [[(0.5, 2), (3.5, 2)], [(0.5, 4), (3.5, 4)]],
    '.': [[(2, 6), (2, 6)]],
    ',': [[(2, 5.5), (1.4, 7)]],
    ';': [[(2, 2), (2, 2)], [(2, 5.5), (1.4, 7)]],
    "'": [[(2, 0), (2, 1.6)]],
    '`': [[(1.5, 0), (2.5, 1.2)]],
    '/': [[(4, 0), (0, 6)]],
    '\\': [[(0, 0), (4, 6)]],
    '[': [[(3, 0), (1, 0), (1, 6), (3, 6)]],
    ']': [[(1, 0), (3, 0), (3, 6), (1, 6)]],
    '?': [[(0, 1), (1, 0), (3, 0), (4, 1), (4, 2), (2, 3.5), (2, 4.2)], [(2, 6), (2, 6)]],
    '\u2191': [[(2, 6), (2, 0)], [(0, 2), (2, 0), (4, 2)]],   # up arrow
    '\u2193': [[(2, 0), (2, 6)], [(0, 4), (2, 6), (4, 4)]],   # down arrow
    '\u2190': [[(4, 3), (0, 3)], [(2, 1), (0, 3), (2, 5)]],   # left arrow
    '\u2192': [[(0, 3), (4, 3)], [(2, 1), (4, 3), (2, 5)]],   # right arrow
}
GLYPH_GAP = 1.4   # grid units between letters


def _rgb(hexs, a=1.0):
    v = int(hexs.lstrip('#'), 16)
    return ((v >> 16) / 255.0, ((v >> 8) & 255) / 255.0, (v & 255) / 255.0, a)


class Canvas:
    SS = 4

    def __init__(self, w, h):
        self.w, self.h = w, h
        self.px = [[0.0, 0.0, 0.0, 0.0] for _ in range(w * h)]

    def fill(self, inside, bbox, color):
        """Composite colour over every pixel, weighted by the sampled coverage."""
        x0, y0, x1, y1 = bbox
        x0, y0 = max(0, int(math.floor(x0))), max(0, int(math.floor(y0)))
        x1, y1 = min(self.w, int(math.ceil(x1))), min(self.h, int(math.ceil(y1)))
        n = self.SS
        offs = [(i + 0.5) / n for i in range(n)]
        r, g, b, a = color
        for y in range(y0, y1):
            for x in range(x0, x1):
                cov = sum(1 for sy in offs for sx in offs if inside(x + sx, y + sy))
                if cov:
                    k = a * cov / (n * n)
                    p = self.px[y * self.w + x]
                    inv = 1.0 - k
                    p[0] = r * k + p[0] * inv
                    p[1] = g * k + p[1] * inv
                    p[2] = b * k + p[2] * inv
                    p[3] = k + p[3] * inv

    def rrect(self, x, y, w, h, r, color, rt=None):
        """Rounded rectangle; rt = separate radius for the top corners."""
        rt = r if rt is None else rt

        def inside(px, py):
            if not (x <= px <= x + w and y <= py <= y + h):
                return False
            rad = rt if py < y + h / 2 else r
            cx = min(max(px, x + rad), x + w - rad)
            cy = min(max(py, y + rad), y + h - rad)
            return (px - cx) ** 2 + (py - cy) ** 2 <= rad * rad
        self.fill(inside, (x, y, x + w, y + h), color)

    def ellipse(self, cx, cy, rx, ry, color):
        self.fill(lambda px, py: ((px - cx) / rx) ** 2 + ((py - cy) / ry) ** 2 <= 1.0,
                  (cx - rx, cy - ry, cx + rx, cy + ry), color)

    def strokes(self, lines, radius, color):
        segs = []
        for line in lines:
            pts = line if len(line) > 1 else line * 2
            segs += list(zip(pts, pts[1:]))
        xs = [p[0] for s in segs for p in s]
        ys = [p[1] for s in segs for p in s]
        rr = radius * radius

        def inside(px, py):
            for (ax, ay), (bx, by) in segs:
                dx, dy = bx - ax, by - ay
                ll = dx * dx + dy * dy
                t = 0.0 if ll == 0 else max(0.0, min(1.0, ((px - ax) * dx + (py - ay) * dy) / ll))
                ex, ey = ax + t * dx - px, ay + t * dy - py
                if ex * ex + ey * ey <= rr:
                    return True
            return False
        self.fill(inside, (min(xs) - radius, min(ys) - radius, max(xs) + radius,
                           max(ys) + radius), color)

    def rgba(self):
        """8-bit RGBA, alpha snapped to what the PS2 can hold (0..0x80 -> 0..255)."""
        out = bytearray()
        for r, g, b, a in self.px:
            pa = int(round(a * 128))
            if pa == 0:
                out += b'\0\0\0\0'
                continue
            f = 1.0 / a
            out += bytes((min(255, int(round(r * f * 255))), min(255, int(round(g * f * 255))),
                          min(255, int(round(b * f * 255))), min(255, pa * 2)))
        return bytes(out)


def text_units(text):
    return len(text) * (4 + GLYPH_GAP) - GLYPH_GAP if text else 0


def draw_text(cv, text, cx, cy, max_w, max_h, color, max_scale=2.0):
    """Centre text in a max_w x max_h box around (cx, cy); scale to fit."""
    text = ''.join(ch if ch in STROKES else '?' for ch in text.upper())
    tw = text_units(text)
    s = min(max_scale, max_w / (tw + 1.2), max_h / 7.2)
    radius = max(0.55, 0.5 * s)
    x = cx - tw * s / 2
    y = cy - 3 * s
    lines = []
    for ch in text:
        for line in STROKES[ch]:
            lines.append([(x + px * s, y + py * s) for px, py in line])
        x += (4 + GLYPH_GAP) * s
    cv.strokes(lines, radius, color)


def text_width_px(text, scale=1.6):
    return text_units(text) * scale + 2 * max(0.55, 0.5 * scale)


# ---------------------------------------------------------------- styles ---

XBOX_FACE = {'south': ('A', '#5DC21E'), 'east': ('B', '#E3352B'),
             'west': ('X', '#2D8FE6'), 'north': ('Y', '#F5C400')}
NINTENDO_FACE = {'south': 'B', 'east': 'A', 'west': 'Y', 'north': 'X'}   # positional
SHOULDER_TEXT = {
    'xbox': {'left_shoulder': 'LB', 'right_shoulder': 'RB',
             'left_trigger': 'LT', 'right_trigger': 'RT'},
    'nintendo': {'left_shoulder': 'L', 'right_shoulder': 'R',
                 'left_trigger': 'ZL', 'right_trigger': 'ZR'},
}
DARK, EDGE, LIGHT, WHITE = '#3A3A3E', '#141416', '#5C5C62', '#F4F4F4'


def draw_pad_face(cv, x, y, w, h, letter, color):
    cx, cy = x + w / 2, y + h / 2
    r = min(w, h) / 2 - 0.5
    cv.ellipse(cx, cy, r, r, _rgb(EDGE))
    cv.ellipse(cx, cy, r - 1.2, r - 1.2, _rgb(LIGHT))
    cv.ellipse(cx, cy + 0.6, r - 2.0, r - 2.4, _rgb(DARK))
    draw_text(cv, letter, cx, cy + 0.3, (r - 2) * 1.5, (r - 2) * 1.45, _rgb(color))


def draw_pad_shoulder(cv, x, y, w, h, text, trigger):
    rt = 7.0 if trigger else 4.0
    cv.rrect(x + 0.5, y + 0.5, w - 1, h - 1, 4.0, _rgb(EDGE), rt)
    cv.rrect(x + 1.5, y + 1.5, w - 3, h - 3, 3.0, _rgb(LIGHT), rt - 1)
    cv.rrect(x + 2.0, y + 2.6, w - 4, h - 4.6, 2.6, _rgb(DARK), rt - 1.5)
    draw_text(cv, text, x + w / 2, y + h / 2 + 0.4, w - 9, h - 8, _rgb(WHITE))


def draw_keycap(cv, x, y, w, h, label):
    cv.rrect(x + 0.5, y + 0.5, w - 1, h - 1, 3.5, _rgb('#1E1E22'))
    cv.rrect(x + 1.5, y + 1.5, w - 3, h - 3, 2.6, _rgb('#8C8C94'))
    cv.rrect(x + 1.5, y + 1.5, w - 3, h - 5, 2.6, _rgb('#E8E8EC'))
    draw_text(cv, label, x + w / 2, y + (h - 2) / 2, w - 7, h - 9, _rgb('#18181C'))


def draw_mouse(cv, x, y, w, h, which):
    bw, bh = min(w - 6, (h - 3) * 0.66), h - 3
    bx, by = x + (w - bw) / 2, y + 1.5
    cv.rrect(bx, by, bw, bh, bw / 2 - 0.5, _rgb('#1E1E22'))
    cv.rrect(bx + 1, by + 1, bw - 2, bh - 2, bw / 2 - 1.5, _rgb('#E8E8EC'))
    split = by + bh * 0.42
    mid = bx + bw / 2
    hi = _rgb('#E3352B')
    if which == 'left':
        cv.fill(lambda px, py: px < mid - 0.5 and py < split - 0.5 and _in_rrect(
            px, py, bx + 1, by + 1, bw - 2, bh - 2, bw / 2 - 1.5), (bx, by, mid, split), hi)
    elif which == 'right':
        cv.fill(lambda px, py: px > mid + 0.5 and py < split - 0.5 and _in_rrect(
            px, py, bx + 1, by + 1, bw - 2, bh - 2, bw / 2 - 1.5), (mid, by, bx + bw, split), hi)
    elif which == 'middle':
        cv.rrect(mid - 1.2, by + 2.5, 2.4, bh * 0.28, 1.2, hi)
    cv.strokes([[(bx + 1, split), (bx + bw - 1, split)], [(mid, by + 1), (mid, split)]],
               0.5, _rgb('#1E1E22'))
    if which in ('x1', 'x2'):
        draw_text(cv, '4' if which == 'x1' else '5', mid, split + (by + bh - split) / 2,
                  bw - 3, (by + bh - split) - 3, _rgb('#18181C'))


def _in_rrect(px, py, x, y, w, h, r):
    if not (x <= px <= x + w and y <= py <= y + h):
        return False
    cx = min(max(px, x + r), x + w - r)
    cy = min(max(py, y + r), y + h - r)
    return (px - cx) ** 2 + (py - cy) ** 2 <= r * r


KEY_LABELS = {
    'space': 'SPC', 'return': 'ENT', 'tab': 'TAB', 'backspace': 'BS', 'escape': 'ESC',
    'left shift': 'SHF', 'right shift': 'SHF', 'left ctrl': 'CTL', 'right ctrl': 'CTL',
    'left alt': 'ALT', 'right alt': 'ALT', 'capslock': 'CAP', 'delete': 'DEL',
    'insert': 'INS', 'home': 'HOM', 'end': 'END', 'page up': 'PGU', 'page down': 'PGD',
    'up': '\u2191', 'down': '\u2193', 'left': '\u2190', 'right': '\u2192',
    'comma': ',', 'period': '.', 'slash': '/', 'backslash': '\\', 'semicolon': ';',
    'apostrophe': "'", 'grave': '`', 'minus': '-', 'equals': '=',
    'leftbracket': '[', 'rightbracket': ']', 'keypad enter': 'KEN',
}
KEY_LABELS_WIDE = {'space': 'SPACE', 'return': 'ENTER', 'backspace': 'BKSP',
                   'left shift': 'SHIFT', 'right shift': 'SHIFT', 'left ctrl': 'CTRL',
                   'right ctrl': 'CTRL', 'capslock': 'CAPS', 'page up': 'PGUP',
                   'page down': 'PGDN', 'escape': 'ESC'}


def key_label(binding, wide=False):
    """'key:Left Shift' -> 'SHF'; 'mouse:left' -> ('mouse', 'left')."""
    kind, _, name = binding.partition(':')
    if kind == 'mouse':
        return ('mouse', name.lower())
    n = name.strip().lower()
    if wide and n in KEY_LABELS_WIDE:
        return KEY_LABELS_WIDE[n]
    if n in KEY_LABELS:
        return KEY_LABELS[n]
    if n.startswith('keypad '):
        return 'K' + key_label('key:' + n[7:])
    return name.strip().upper()[:4]


def read_bindings(path):
    """First key/mouse binding per action from a settings .ini (docs/SETTINGS.md)."""
    out = dict(DEFAULT_KEYS)
    if not path:
        return out
    section = ''
    for line in open(path, encoding='utf-8-sig'):
        s = line.split('#', 1)[0].strip()
        if not s:
            continue
        if s.startswith('[') and s.endswith(']'):
            section = s[1:-1].strip().lower()
            continue
        key, eq, val = s.partition('=')
        if not eq:
            continue
        key = key.strip().lower()
        if section and not key.startswith(section + '.'):
            key = section + '.' + key
        if not key.startswith('input.bind.'):
            continue
        action = OLD_IDS.get(key[11:], key[11:])
        if action not in out:
            continue
        binds = [b.strip() for b in val.strip().strip('"').split(',') if b.strip()]
        firsts = [b for b in binds if b.lower().startswith(('key:', 'mouse:'))
                  and b.lower()[6:] not in ('x+', 'x-', 'y+', 'y-')]
        out[action] = firsts[0] if firsts else None
    return out


def draw_glyph(cv, style, m, binding=None, wide=False):
    x, y, w, h = m['u'], m['v'], m['w'], m['h']
    _btn, pos, action = BUTTONS[m['code']]
    if style == 'keyboard':
        b = binding.get(action) if binding else DEFAULT_KEYS[action]
        if b is None:
            draw_keycap(cv, x, y, w, h, '-')
            return
        lab = key_label(b, wide)
        if isinstance(lab, tuple):
            draw_mouse(cv, x, y, w, h, lab[1])
        else:
            draw_keycap(cv, x, y, w, h, lab)
        return
    if pos in XBOX_FACE:
        if style == 'xbox':
            draw_pad_face(cv, x, y, w, h, *XBOX_FACE[pos])
        else:
            draw_pad_face(cv, x, y, w, h, NINTENDO_FACE[pos], WHITE)
    else:
        draw_pad_shoulder(cv, x, y, w, h, SHOULDER_TEXT[style][pos], 'trigger' in pos)


# ------------------------------------------------------------- building ---


def free_rows(ind):
    """Rows of the atlas that are fully transparent, as [(start, end)) runs."""
    clear = [all(ind.pal[ind.idx[y * ind.w + x]][3] == 0 for x in range(ind.w))
             for y in range(ind.h)]
    runs, y = [], 0
    while y < ind.h:
        if clear[y]:
            s = y
            while y < ind.h and clear[y]:
                y += 1
            runs.append((s, y))
        else:
            y += 1
    return runs


def wide_layout(metrics, ind, binding):
    """Keyboard metrics with each button glyph widened to its label, packed into the
    biggest free band of the atlas. Returns new metric dicts (others unchanged)."""
    band = max(free_rows(ind), key=lambda r: r[1] - r[0])
    x, y, row_h = 0, band[0] + 1, 0
    out = []
    for m in metrics:
        m = dict(m)
        if m['code'] in BUTTONS:
            action = BUTTONS[m['code']][2]
            lab = key_label(binding.get(action) or 'key:-', True)
            need = m['w'] if isinstance(lab, tuple) else int(
                math.ceil(text_width_px(lab, 1.6) + 8))
            w = max(m['w'], need)
            if x + w > ind.w:
                x, y, row_h = 0, y + row_h + 1, 0
            if y + m['h'] > band[1]:
                raise SystemExit('no free atlas space for wide keyboard glyphs')
            m['u'], m['v'], m['w'] = x, y, w
            x += w + 1
            row_h = max(row_h, m['h'])
        out.append(m)
    return out


def build_style(style, orig, metrics, binding, wide):
    """-> (prompts_rgba, composite Indexed, metrics used)."""
    used = wide_layout(metrics, orig, binding) if wide else [dict(m) for m in metrics]
    # The original button rects are always redrawn (short labels): fixed-rect
    # draws such as InsectCageButtonHintDraw_388ee0 read them. --wide adds a second,
    # wider copy of each button glyph in free atlas space and points the metrics there.
    redraw = [m for m in metrics if m['code'] in BUTTONS]
    if wide:
        redraw += [m for m in used if m['code'] in BUTTONS]
    cv = Canvas(orig.w, orig.h)
    for m in redraw:
        is_wide = wide and m not in metrics
        draw_glyph(cv, style, m, binding, is_wide)
    layer = cv.rgba()
    base = orig.rgba()
    w = orig.w
    # Original pixels inside the redrawn rects are replaced by the new art.
    in_new = [False] * (w * orig.h)
    for m in redraw:
        for yy in range(m['v'], m['v'] + m['h']):
            for xx in range(m['u'], m['u'] + m['w']):
                in_new[yy * w + xx] = True
    comp = bytearray(base)
    for i, inside in enumerate(in_new):
        if inside:
            comp[i * 4:i * 4 + 4] = layer[i * 4:i * 4 + 4]
    # Palette: every index still used outside the redrawn rects is fixed; the rest
    # are free for the new art.
    keep = set(orig.idx[i] for i in range(len(orig.idx)) if not in_new[i])
    editable = [i for i in range(256) if i not in keep]
    ind = index_rgba(bytes(comp), orig.w, orig.h, fixed=orig.pal, editable=editable,
                     template=orig.template)
    return layer, ind, used


def rect_preview(ind, metrics, scale=3):
    """Atlas magnified, on a checkerboard, with every button rect outlined."""
    w, h = ind.w * scale, ind.h * scale
    src = ind.rgba()
    out = bytearray(w * h * 4)
    for y in range(h):
        for x in range(w):
            i = ((y // scale) * ind.w + x // scale) * 4
            bg = 200 if ((x // 12) + (y // 12)) & 1 else 160
            a = src[i + 3] / 255.0
            o = (y * w + x) * 4
            for k in range(3):
                out[o + k] = int(src[i + k] * a + bg * (1 - a))
            out[o + 3] = 255
    for m in metrics:
        col = (255, 0, 255) if m['code'] in BUTTONS else (0, 160, 255)
        x0, y0 = m['u'] * scale, m['v'] * scale
        x1, y1 = (m['u'] + m['w']) * scale - 1, (m['v'] + m['h']) * scale - 1
        for x in range(x0, x1 + 1):
            for yy in (y0, y1):
                if 0 <= x < w and 0 <= yy < h:
                    out[(yy * w + x) * 4:(yy * w + x) * 4 + 3] = bytes(col)
        for yy in range(y0, y1 + 1):
            for x in (x0, x1):
                if 0 <= x < w and 0 <= yy < h:
                    out[(yy * w + x) * 4:(yy * w + x) * 4 + 3] = bytes(col)
    return w, h, bytes(out)


# -------------------------------------------------------------------- CLI ---


def _out_dir(args):
    d = os.path.join(args.out, 'gaiji')
    os.makedirs(d, exist_ok=True)
    return d


def cmd_dump(args):
    img, copies = load_gaiji_img(args.data)
    metrics, tags, insect = read_tables(args.data)
    ind = decode(img)
    if encode(ind, img) != img:
        raise SystemExit('re-encode of the original is not byte-identical')
    out = _out_dir(args)
    write_png(os.path.join(out, 'gaiji2_ps.png'), ind.w, ind.h, ind.rgba())
    with open(os.path.join(out, 'gaiji2_ps.img'), 'wb') as f:
        f.write(img)
    gm = glyph_map(metrics, tags, insect)
    L = tim2_layout(img)
    gm['format'] = {
        'container': 'IM3 (1 entry) -> TIM2 v4, 16-byte header alignment, 1 picture',
        'psm': 'PSMT8', 'width': ind.w, 'height': ind.h,
        'clut': '256 x 32-bit RGBA, CSM1 order, alpha 0..0x80',
        'pixels': 'swizzled (PSMT8 stored as uploaded through PSMCT32)',
        'gs_tex0': '%#018x' % L['tex0'], 'file_size': len(img), 'cap': IMG_MAX,
        'palette_entries_used': len(set(ind.idx)),
        'copies': [{'source': w, 'identical': same} for w, same in copies],
    }
    with open(os.path.join(out, 'gaiji2_glyphs.json'), 'w') as f:
        json.dump(gm, f, indent=1)
    write_png(os.path.join(out, 'gaiji2_rects.png'), *rect_preview(ind, metrics))
    print('gaiji2.img %d bytes from %s; %d metrics, %d tags -> %s'
          % (len(img), copies[0][0], len(metrics), len(tags), out))
    for where, same in copies[1:]:
        print('  copy %s: %s' % (where, 'identical' if same else 'DIFFERENT'))


def cmd_build(args):
    img, _ = load_gaiji_img(args.data)
    metrics, tags, insect = read_tables(args.data)
    orig = decode(img)
    binding = read_bindings(args.bindings)
    out = _out_dir(args)
    for style in [s.strip() for s in args.styles.split(',') if s.strip()]:
        if style not in ('xbox', 'nintendo', 'keyboard'):
            raise SystemExit('unknown style %r' % style)
        wide = args.wide and style == 'keyboard'
        layer, ind, used = build_style(style, orig, metrics, binding, wide)
        suffix = style + ('_wide' if wide else '')
        write_png(os.path.join(out, 'prompts_%s.png' % suffix), orig.w, orig.h, layer)
        rgba = ind.rgba()
        write_png(os.path.join(out, 'gaiji2_%s.png' % suffix), ind.w, ind.h, rgba)
        enc = encode(ind, img)
        with open(os.path.join(out, 'gaiji2_%s.img' % suffix), 'wb') as f:
            f.write(enc)
        # Round trip: decode(encode(x)) == x, on pixels and on bytes.
        back = decode(enc)
        ok = back.rgba() == rgba and encode(back, img) == enc
        ok = ok and index_rgba(rgba, ind.w, ind.h, fixed=ind.pal, editable=[],
                               template=img).rgba() == rgba
        gm = glyph_map(used, tags, insect)
        gm['style'] = style
        gm['wide'] = wide
        if style == 'keyboard':
            gm['bindings'] = {BUTTONS[c][0]: binding.get(BUTTONS[c][2]) for c in BUTTONS}
        with open(os.path.join(out, 'gaiji2_%s.json' % suffix), 'w') as f:
            json.dump(gm, f, indent=1)
        changed = sum(1 for a, b in zip(ind.pal, orig.pal) if a != b)
        print('%-14s %d bytes, %d palette slots reassigned, round trip %s'
              % (suffix, len(enc), changed, 'OK' if ok else 'FAILED'))
        if not ok:
            raise SystemExit(1)


def cmd_encode(args):
    img, _ = load_gaiji_img(args.data)
    w, h, rgba = read_png(args.png)
    # Keep the original palette order where the colours still occur (so the
    # original's own PNG re-encodes byte-identical); unused slots take new colours.
    orig = decode(img)
    present = set((rgba[i], rgba[i + 1], rgba[i + 2], ps2_alpha(rgba[i + 3]))
                  for i in range(0, len(rgba), 4))
    editable = [i for i, c in enumerate(orig.pal) if c not in present]
    ind = index_rgba(rgba, w, h, fixed=orig.pal, editable=editable, template=img)
    enc = encode(ind, img)
    with open(args.img, 'wb') as f:
        f.write(enc)
    exact = decode(enc).rgba() == bytes(
        c if i % 4 != 3 else min(255, ps2_alpha(c) * 2) for i, c in enumerate(rgba))
    print('%s: %d bytes, %s' % (args.img, len(enc), 'exact' if exact else
                                 'QUANTISED (more than 256 colours)'))


def cmd_decode(args):
    ind = decode(open(args.img, 'rb').read())
    write_png(args.png, ind.w, ind.h, ind.rgba())


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument('--data', default=os.path.join(PORT, 'data'),
                        help='extracted disc (rg-extract output), read-only')
    common.add_argument('--out', default=os.path.join(PORT, 'out'),
                        help='output root; files go to <out>/gaiji')
    sub = ap.add_subparsers(dest='cmd', required=True)
    sub.add_parser('dump', parents=[common]).set_defaults(fn=cmd_dump)
    b = sub.add_parser('build', parents=[common])
    b.add_argument('--styles', default='xbox,nintendo,keyboard')
    b.add_argument('--bindings', help='settings .ini to read input.bind.* from')
    b.add_argument('--wide', action='store_true',
                   help='keyboard: widen glyphs to full key names (changes metrics)')
    b.set_defaults(fn=cmd_build)
    e = sub.add_parser('encode', parents=[common])
    e.add_argument('png')
    e.add_argument('img')
    e.set_defaults(fn=cmd_encode)
    d = sub.add_parser('decode')
    d.add_argument('img')
    d.add_argument('png')
    d.set_defaults(fn=cmd_decode)
    args = ap.parse_args(argv)
    args.fn(args)


if __name__ == '__main__':
    main()
