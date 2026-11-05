#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""ps2tex.py - find and decode the game's IM3 / TIM2 textures (library for texcensus.py and
texpatch_gen.py; lane p6a11y 2026-11-01, docs/PROMPTS.md "Prompts baked into other textures",
docs/ACCESSIBILITY.md).

Reads the extracted disc in data/ (never writes there).  Game art decoded with it stays under
out/ (gitignored) and is never committed.

  IM3   'IM3\\0', u32 0x10, u32 count, u32 0; count x 0x40 entries {name[0x20], u32 0x40,
        u32 TIM2 offset, ...}
  TIM2  one picture: header {u32 total, clut_size, img_size, u16 hdr_size, clut_colors,
        u8 fmt, mips, clut_type, img_type, u16 w, h, u64 tex0 ...}; img_type 5 = PSMT8,
        4 = PSMT4 (32-bit CLUT; T8 CLUTs in CSM1 order).  T8 pixels are stored as the GS holds
        them after an upload as PSMCT32 (gaiji.py's swizzle); T4 pixels are linear, low nibble
        first.  The GS address helpers below (nr_gsmem.c) are for reading GS memory dumps.
"""
from __future__ import annotations

import glob
import hashlib
import os
import struct
import sys

import numpy as np

PORT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(PORT, 'tools', 'assets'))
import gaiji  # noqa: E402  (Hd6, pak_entries, the T8 swizzle)

# ------------------------------------------------------------ GS addresses (nr_gsmem.c) ---


def _blk32(bx, by):
    return (bx & 1) | ((by & 1) << 1) | ((bx & 2) << 1) | ((by & 2) << 2) | ((bx & 4) << 2)


def _blk16(bx, by):
    return (by & 1) | ((bx & 1) << 1) | ((by & 2) << 1) | ((bx & 2) << 2) | ((by & 4) << 2)


def _col32(x, y):
    return (x & 1) | ((y & 1) << 1) | ((x & 6) << 1)


def addr32(bw, x, y):
    """byte address (bp 0) of CT32 pixel (x, y)"""
    page = (x >> 6) + (y >> 5) * bw
    blk = _blk32((x >> 3) & 7, (y >> 3) & 3)
    return ((page * 32 + blk) << 8) | (((y >> 1) & 3) << 6) | (_col32(x & 7, y & 1) << 2)


def addr8(bw, x, y):
    page = (x >> 7) + (y >> 6) * (bw >> 1)
    blk = _blk32((x >> 4) & 7, (y >> 4) & 3)
    col, cy = (y >> 2) & 3, y & 3
    hi, xx = cy >> 1, x & 7
    xx = np.where((hi ^ (col & 1)) != 0, xx ^ 4, xx)
    return ((page * 32 + blk) << 8) | (col << 6) | (_col32(xx, cy & 1) << 2) | ((((x >> 3) & 1) << 1) | hi)


def addr4n(bw, x, y):
    """nibble address"""
    page = (x >> 7) + (y >> 7) * (bw >> 1)
    blk = _blk16((x >> 5) & 3, (y >> 4) & 7)
    col, cy = (y >> 2) & 3, y & 3
    hi, xx = cy >> 1, x & 7
    xx = np.where((hi ^ (col & 1)) != 0, xx ^ 4, xx)
    return ((((page * 32 + blk) << 8) | (col << 6) | (_col32(xx, cy & 1) << 2)) << 1) + ((((x >> 3) & 3) << 1) | hi)


def csm1(i):
    return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1)


# ------------------------------------------------------------------- TIM2 ---------------

class Tex:
    """One decoded TIM2 picture.  idx: h x w uint8 indices (None for direct colour);
    pal: N x 4 uint8 PS2 RGBA (alpha 0..0x80); rgba(): h x w x 4 (alpha doubled)."""

    def __init__(self, **kw):
        self.__dict__.update(kw)

    def rgba(self):
        if self.idx is None:
            return self.direct
        lut = self.pal.astype(np.int32).copy()
        lut[:, 3] = np.minimum(255, lut[:, 3] * 2)
        return lut[self.idx].astype(np.uint8)


def _perm(img_type, w, h):
    """index in the stored pixel bytes (byte, or nibble for T4) of each linear pixel."""
    ys, xs = np.mgrid[0:h, 0:w]
    if img_type == 5:
        if w % 16 == 0 and h % 4 == 0:
            return np.array(gaiji._swizzle8_table(w, h), dtype=np.int64).reshape(h, w)
        return None
    if img_type == 4:
        # PSMT4 pictures are stored linear (low nibble first), measured on menu_font01
        return (ys * w + xs).astype(np.int64)
    return None


_perm_cache = {}


def decode_tim2(b: bytes, t: int):
    """TIM2 at offset t of b -> Tex, or None if unsupported."""
    if b[t:t + 4] != b'TIM2':
        return None
    p = t + 0x10
    if p + 0x30 > len(b):
        return None
    (total, clut_size, img_size, hdr_size, clut_colors, _fmt, mips, clut_type, img_type,
     w, h) = struct.unpack_from('<IIIHHBBBBHH', b, p)
    px = p + hdr_size
    cl = px + img_size
    info = dict(w=w, h=h, img_type=img_type, clut_type=clut_type, clut_colors=clut_colors,
                px_off=px, px_size=img_size, clut_off=cl, clut_size=clut_size, tim2=t,
                tex0=struct.unpack_from('<Q', b, p + 0x18)[0], idx=None, pal=None, direct=None)
    if not w or not h or cl + clut_size > len(b):
        return None
    if img_type in (4, 5) and clut_colors in (16, 256) and clut_size >= clut_colors * 4:
        key = (img_type, w, h)
        if key not in _perm_cache:
            _perm_cache[key] = _perm(img_type, w, h)
        perm = _perm_cache[key]
        if perm is None:
            return None
        raw = np.frombuffer(b, dtype=np.uint8, count=img_size, offset=px)
        if img_type == 5:
            idx = raw[perm]
        else:
            nib = perm
            byte = raw[np.minimum(nib >> 1, raw.size - 1)]
            idx = np.where(nib & 1, byte >> 4, byte & 15).astype(np.uint8)
        craw = np.frombuffer(b, dtype=np.uint8, count=clut_colors * 4, offset=cl).reshape(-1, 4)
        order = np.array([csm1(i) for i in range(clut_colors)]) if clut_colors == 256 else np.arange(16)
        info.update(idx=idx.astype(np.uint8), pal=craw[order].copy())
        return Tex(**info)
    if img_type == 3 and img_size == w * h * 4:      # CT32
        raw = np.frombuffer(b, dtype=np.uint8, count=img_size, offset=px).reshape(h, w, 4).copy()
        raw[..., 3] = np.minimum(255, raw[..., 3].astype(np.int32) * 2)
        info.update(direct=raw)
        return Tex(**info)
    return None


def im3_entries(b: bytes, base: int = 0):
    """[(name, tim2 offset)] of the IM3 archive at b[base:]"""
    if b[base:base + 4] != b'IM3\0' or struct.unpack_from('<I', b, base + 4)[0] != 0x10:
        return []
    n = struct.unpack_from('<I', b, base + 8)[0]
    if not 0 < n < 512:
        return []
    out = []
    for i in range(n):
        e = base + 0x10 + i * 0x40
        if e + 0x40 > len(b):
            break
        nm = b[e:e + 0x20].split(b'\0')[0].decode('cp932', 'replace')
        t = base + struct.unpack_from('<I', b, e + 0x24)[0]
        if b[t:t + 4] == b'TIM2':
            out.append((nm, t))
    return out


def find_im3(b: bytes):
    """every IM3 archive in a file (16-aligned magic)"""
    out, i = [], b.find(b'IM3\0')
    while i >= 0:
        if i % 16 == 0:
            ents = im3_entries(b, i)
            if ents:
                out.append((i, ents))
        i = b.find(b'IM3\0', i + 4)
    return out


UI_EXT = ('.pac', '.pak', '.img', '.ipk', '.ico', '.bin')


def iter_ui_files(data_dir=None, exts=UI_EXT, hd6s=('DATA0_0.HD6', 'DATA1_0.HD6')):
    """(hd6, path, bytes) of every file with a UI-ish extension, each distinct content once"""
    data_dir = data_dir or os.path.join(PORT, 'data')
    seen = set()
    for name in hd6s:
        a = gaiji.Hd6(os.path.join(data_dir, name))
        for path in sorted(a.files):
            if not path.lower().endswith(exts):
                continue
            d = a.read(path)
            h = hashlib.sha1(d).digest()
            if h in seen:
                continue
            seen.add(h)
            yield name, path, d


def iter_textures(data_dir=None, exts=UI_EXT):
    """(where, name, file bytes, Tex) for every decodable TIM2 in an IM3 of the UI files,
    each distinct picture (pixels + CLUT) once"""
    seen = set()
    for hd6, path, d in iter_ui_files(data_dir, exts):
        for base, ents in find_im3(d):
            for nm, t in ents:
                tx = decode_tim2(d, t)
                if tx is None:
                    continue
                h = hashlib.sha1(d[tx.px_off:tx.clut_off + tx.clut_size]).hexdigest()
                if h in seen:
                    continue
                seen.add(h)
                tx.sha1 = h
                yield '%s:%s@%#x' % (hd6, path, base), nm, d, tx


def fnv64(data: bytes) -> int:
    """FNV-1a 64 (the transfer content hash of nr_texpatch.c)"""
    h = 0xCBF29CE484222325
    for c in data:
        h = ((h ^ c) * 0x100000001B3) & 0xFFFFFFFFFFFFFFFF
    return h


def write_png(path, rgba):
    from PIL import Image
    Image.fromarray(np.ascontiguousarray(rgba), 'RGBA').save(path)
