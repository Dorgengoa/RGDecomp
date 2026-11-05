#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""texpatch_gen.py - generate src/settings/rg_texpatch_tab.c, the target table of the upload-time
texture patches (src/settings/rg_texpatch.h; lane p6a11y 2026-11-01, docs/PROMPTS.md "Prompts
baked into other textures", docs/ACCESSIBILITY.md).

    python tools/p6/texpatch_gen.py            # write the table
    python tools/p6/texpatch_gen.py --check    # exit 1 if the checked-in table differs
    python tools/p6/texpatch_gen.py --verify --exe build/X/tests/settings/rg-texpatch-tests.exe
        [--out out/p6a11y/texpatch_verify]   # --check + every target x style / colour mode through
                                             # the C builder; PNGs (game art: stays under out/)

The table holds what identifies a texture at upload time (the sizes and FNV-1a 64 hashes of its
pixel and CLUT transfers, i.e. of the TIM2's pixel and CLUT bytes), the rectangles to patch and
the replacement hues: no game bytes.  The rectangles below were measured on the decoded
textures (tools/p6/texcensus.py scan); every site is checked here against the picture (opaque
pixels present) and every CLUT hash for sharing with another texture (a shared CLUT would carry
a marker recolour into that texture too).
"""
from __future__ import annotations

import argparse
import os
import struct
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import ps2tex  # noqa: E402

PORT = ps2tex.PORT
OUT_C = os.path.join(PORT, 'src', 'settings', 'rg_texpatch_tab.c')

# slots (rg_prompts.h): L2 L1 R1 R2 Circle Triangle Square Cross L3 R3 START SELECT
SLOT = {n: i for i, n in enumerate(['L2', 'L1', 'R1', 'R2', 'CIRCLE', 'TRIANGLE', 'SQUARE', 'CROSS',
                                     'L3', 'R3', 'START', 'SELECT'])}
SLOT_C = ['RG_GAIJI_L2', 'RG_GAIJI_L1', 'RG_GAIJI_R1', 'RG_GAIJI_R2', 'RG_GAIJI_CIRCLE', 'RG_GAIJI_TRIANGLE',
          'RG_GAIJI_SQUARE', 'RG_GAIJI_CROSS', 'RG_PROMPT_L3', 'RG_PROMPT_R3', 'RG_PROMPT_START',
          'RG_PROMPT_SELECT']
SHAPE_C = {'cell': 'RG_PROMPT_SHAPE_CELL', 'disc': 'RG_PROMPT_SHAPE_DISC', 'text': 'RG_PROMPT_SHAPE_TEXT'}
KEEP = 0xFF000000

# Okabe & Ito (2008) colour-blind-safe hues
OI = {'orange': 0xE69F00, 'sky': 0x56B4E9, 'green': 0x009E73, 'yellow': 0xF0E442, 'blue': 0x0072B2,
      'vermillion': 0xD55E00, 'purple': 0xCC79A7, 'white': 0xF0F0F0}

MENU_PAK = 'menu' + chr(92) + 'rc' + chr(92) + 'menu_static_img_en.pac'

TARGETS = [
    {
        # the battle / menu sheet: PAUSE screen Square and Triangle (PauseReasonDrawMaybe_2f5c40,
        # D_004518D0 items (108,44) / (130,44)), the "Help" bar's Triangle, L2 / L1 key caps,
        # the "L3" and "START" words; the four stat-arrow icons (orange / green / red / blue)
        'name': 'btl_st01', 'file': MENU_PAK,
        'sites': [(108, 44, 22, 22, 'SQUARE', 'cell'), (130, 44, 22, 22, 'TRIANGLE', 'cell'),
                  (4, 63, 22, 22, 'TRIANGLE', 'disc'),
                  (1, 199, 30, 18, 'L2', 'cell'), (33, 199, 30, 18, 'L1', 'cell'),
                  (1, 1, 15, 14, 'L3', 'text'), (145, 160, 36, 14, 'START', 'text')],
        # arrows: groups 0 orange, 1 green, 2 red, 3 blue (inside their blue frames)
        'marks': [(124, 179, 15, 16, 0), (148, 179, 15, 16, 1), (172, 179, 15, 16, 2), (196, 179, 15, 16, 3)],
        # protan, deutan, tritan per group (KEEP = unchanged)
        'colours': [(OI['orange'], OI['orange'], KEEP, None),
                    (OI['sky'], OI['sky'], KEEP, None),
                    (OI['vermillion'], OI['vermillion'], KEEP, None),
                    (OI['blue'], OI['blue'], KEEP, None)],
    },
    {
        # the main menu's stat-change digits (equipment / item comparisons): the same digits and
        # "AT DF" letters green (rows 0-31: up) and red (rows 32-63: down), told apart by colour
        # alone (texcensus.py colour: min dE 5.3 deutan, 5.9 protan)
        'name': 'topmenu_08a', 'file': MENU_PAK,
        'sites': [],
        'marks': [(0, 0, 128, 32, 0), (0, 32, 128, 32, 1)],
        'colours': [(OI['sky'], OI['sky'], KEEP, None),
                    (OI['vermillion'], OI['vermillion'], KEEP, None)],
    },
]


def _pak(*parts):
    return chr(92).join(parts)


def _glyphs(name, file, sites):
    # baked glyph sites found by texcensus.py prompts (score >= 0.97, the census rects); drawn as
    # 'disc' (composited: the original art outside the new glyph's shape stays)
    return {'name': name, 'file': file, 'sites': [(x, y, w, h, slot, 'disc') for x, y, w, h, slot in sites]}


# other menu sheets with baked glyphs (texcensus.py prompts, 2026-11-01; "seen" = its upload hash was
# in an RG_TEXPATCH_XLOG of the lane's routes)
TARGETS += [
    _glyphs('Itm_01', MENU_PAK, [(158, 71, 32, 20, 'L1'), (158, 99, 32, 20, 'R1')]),          # item menu tabs (seen)
    _glyphs('BR_01a', _pak('menu', 'rc', 'main_menu_img_en.pac'), [(0, 84, 22, 22, 'CROSS')]),  # main menu (seen)
    _glyphs('Loading_01', _pak('rc', 'loading2_en.img'), [(80, 41, 22, 22, 'CROSS')]),     # loading screen (seen)
    _glyphs('TP_top_01', _pak('menu', 'rc', 'insect_vs_load_rc_en.pac'), [(28, 208, 32, 20, 'L2'), (60, 208, 32, 20, 'R2')]),  # (seen)
    _glyphs('TP_save02', _pak('menu', 'rc', 'insect_vs_rc_en.pac'), [(112, 37, 32, 20, 'L1'), (144, 37, 32, 20, 'R1')]),     # (seen)
    _glyphs('TP_save02', _pak('menu', 'rc', 'insect_vs_load_rc_en.pac'), [(112, 37, 32, 20, 'L1'), (144, 37, 32, 20, 'R1')]),
    _glyphs('TP_save02', _pak('menu', 'rc', 'insect_vs_pw_rc_en.pac'), [(112, 37, 32, 20, 'L1'), (144, 37, 32, 20, 'R1')]),
    _glyphs('Fac_Plan01', _pak('menu', 'rc', 'factory_menu_rc_en.pac'), [(158, 71, 32, 20, 'L1'), (158, 99, 32, 20, 'R1')]),
    _glyphs('Fac_top01a', _pak('menu', 'rc', 'factory_menu_rc_en.pac'),
            [(100, 118, 32, 20, 'L1'), (132, 118, 32, 20, 'R1'), (100, 138, 22, 22, 'CIRCLE'),
             (122, 138, 22, 22, 'CROSS'), (144, 138, 22, 22, 'TRIANGLE'), (164, 116, 22, 22, 'SQUARE')]),
    _glyphs('Think_01', _pak('menu', 'rc', 'insect_entry_rc_en.pac'), [(158, 71, 32, 20, 'L1'), (158, 99, 32, 20, 'R1')]),
    _glyphs('Shop_02', _pak('menu', 'rc', 'shop_menu_rc_en.pac'), [(158, 71, 32, 20, 'L1'), (158, 99, 32, 20, 'R1')]),
    _glyphs('Insect_02a', _pak('menu', 'rc', 'insect_box_rc_en.pac'), [(198, 52, 22, 22, 'TRIANGLE'), (220, 52, 22, 22, 'SQUARE')]),
    _glyphs('Insect_02a', _pak('menu', 'rc', 'insectron_rc_en.pac'), [(198, 52, 22, 22, 'TRIANGLE'), (220, 52, 22, 22, 'SQUARE')]),
]


def find_texture(name, file):
    a = ps2tex.gaiji.Hd6(os.path.join(PORT, 'data', 'DATA0_0.HD6'))
    d = a.read(file)
    for base, ents in ps2tex.find_im3(d):
        for nm, t in ents:
            if nm == name:
                tx = ps2tex.decode_tim2(d, t)
                return d, tx
    raise SystemExit('%s not found in %s' % (name, file))


def all_clut_hashes():
    """fnv64 of every UI texture's CLUT bytes -> names (sharing check)"""
    out = {}
    for where, nm, d, tx in ps2tex.iter_textures():
        if tx.idx is None:
            continue
        out.setdefault(ps2tex.fnv64(d[tx.clut_off:tx.clut_off + tx.clut_size]), set()).add(nm)
    return out


def gen(check_sharing=True):
    rows, warn = [], []
    shared = all_clut_hashes() if check_sharing else {}
    for T in TARGETS:
        d, tx = find_texture(T['name'], T['file'])
        bits = 8 if tx.img_type == 5 else 4
        pix = d[tx.px_off:tx.px_off + tx.px_size]
        clut = d[tx.clut_off:tx.clut_off + tx.clut_size]
        alpha = tx.pal[tx.idx][..., 3]
        for x, y, w, h, slot, shape in T['sites']:
            if not (alpha[y:y + h, x:x + w] > 0).any():
                raise SystemExit('%s: site %s at %d,%d is empty' % (T['name'], slot, x, y))
        if T.get('marks'):
            names = shared.get(ps2tex.fnv64(clut), {T['name']}) - {T['name']}
            if names:
                warn.append('%s: CLUT shared with %s' % (T['name'], ', '.join(sorted(names))))
        rows.append(dict(T, bits=bits, w=tx.w, h=tx.h, pix_bytes=len(pix), clut_bytes=len(clut),
                         pix_hash=ps2tex.fnv64(pix), clut_hash=ps2tex.fnv64(clut), pix=pix, clut=clut))
    return rows, warn


def emit(rows):
    o = ['/* SPDX-License-Identifier: CC0-1.0 */',
         '/* Generated by tools/p6/texpatch_gen.py: do not edit.  The upload-time texture patch',
         ' * targets (rg_texpatch.h): transfer sizes and FNV-1a 64 hashes, rectangles, hues. */',
         '#include "rg_texpatch.h"', '#include "rg_prompts.h"', '']
    for i, r in enumerate(rows):
        if r['sites']:
            o.append('static const rg_tp_site k_sites_%d[] = {' % i)
            for x, y, w, h, slot, shape in r['sites']:
                o.append('    { %d, %d, %d, %d, %s, %s },' % (x, y, w, h, SLOT_C[SLOT[slot]], SHAPE_C[shape]))
            o.append('};')
        if r.get('marks'):
            o.append('static const rg_tp_mark k_marks_%d[] = {' % i)
            for x, y, w, h, g in r['marks']:
                o.append('    { %d, %d, %d, %d, %d },' % (x, y, w, h, g))
            o.append('};')
            o.append('static const uint32_t k_colours_%d[][4] = {   /* off, protan, deutan, tritan */' % i)
            for c in r['colours']:
                o.append('    { 0xFF000000u, %s },' % ', '.join('0x%08Xu' % (KEEP if v is None else v) for v in c[:3]))
            o.append('};')
    o.append('const rg_tp_target rg_tp_targets[] = {')
    for i, r in enumerate(rows):
        o.append('    { "%s", %d, %d, %d, %du, %du, 0x%016xull, 0x%016xull, %s, %d, %s, %d, %s, %d },' % (
            r['name'], r['w'], r['h'], r['bits'], r['pix_bytes'], r['clut_bytes'], r['pix_hash'], r['clut_hash'],
            'k_sites_%d' % i if r['sites'] else 'NULL', len(r['sites']),
            'k_marks_%d' % i if r.get('marks') else 'NULL', len(r.get('marks') or []),
            'k_colours_%d' % i if r.get('marks') else 'NULL', len(r.get('colours') or [])))
    o.append('};')
    o.append('const int rg_tp_ntargets = (int)(sizeof rg_tp_targets / sizeof rg_tp_targets[0]);')
    return '\n'.join(o) + '\n'


STYLES = ['playstation', 'xbox', 'nintendo', 'keyboard']
CB = ['off', 'protan', 'deutan', 'tritan']


def decode(r, pix, clut):
    """transfer bytes -> h x w x 4 RGBA (alpha doubled), as rg_tp_rgba"""
    from ps2tex import csm1
    w, h = r['w'], r['h']
    if r['bits'] == 8:
        perm = np.array(ps2tex.gaiji._swizzle8_table(w, h)).reshape(h, w)
        idx = np.frombuffer(pix, np.uint8)[perm]
        order = [csm1(i) for i in range(256)]
    else:
        raw = np.frombuffer(pix, np.uint8)
        idx = np.stack([raw & 15, raw >> 4], 1).reshape(h, w)
        order = list(range(16))
    pal = np.frombuffer(clut, np.uint8).reshape(-1, 4)[order].astype(np.int32)
    pal[:, 3] = np.minimum(255, pal[:, 3] * 2)
    return idx, pal[idx].astype(np.uint8)


def marker_min_de(r, rgba, kind):
    import texcensus
    cols = []
    for g in range(len(r['colours'])):
        px = []
        for x, y, w, h, gg in r['marks']:
            if gg == g:
                c = rgba[y:y + h, x:x + w].reshape(-1, 4)
                px.append(c[c[:, 3] > 128][:, :3])
        px = np.concatenate(px).astype(np.float64)
        sat = px.max(1) - px.min(1)
        cols.append(px[sat >= np.median(sat)].mean(0))
    return texcensus.min_de(cols, kind)


def verify(a, rows):
    """every target x style x colour-blind mode through the C builder (rg-texpatch-tests build):
    pixels outside the sites keep their index bytes, sites change for every non-PlayStation style,
    marker sets stay apart (min dE >= 12) for each deficiency the table recolours"""
    import subprocess
    import tempfile
    from PIL import Image
    bad = 0
    os.makedirs(a.out, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        for r in rows:
            fp, fc = os.path.join(tmp, 'p'), os.path.join(tmp, 'c')
            open(fp, 'wb').write(r['pix'])
            open(fc, 'wb').write(r['clut'])
            idx0, rgba0 = decode(r, r['pix'], r['clut'])
            inside = np.zeros((r['h'], r['w']), bool)
            for x, y, w, h, _s, _sh in r['sites']:
                inside[y:y + h, x:x + w] = True
            for si, st in enumerate(STYLES):
                for ci, cb in enumerate(CB):
                    if si and ci:
                        continue   # (styles with cb off; cb modes with PlayStation)
                    op, oc = os.path.join(tmp, 'op'), os.path.join(tmp, 'oc')
                    out = subprocess.run([a.exe, 'build', r['name'], fp, fc, str(si), str(ci), op, oc],
                                         capture_output=True, text=True)
                    if out.returncode:
                        print('FAIL %s %s %s: helper exit %d %s' % (r['name'], st, cb, out.returncode, out.stderr))
                        bad += 1
                        continue
                    pix, clut = open(op, 'rb').read(), open(oc, 'rb').read()
                    idx, rgba = decode(r, pix, clut)
                    allowed = inside.copy()
                    if ci:
                        for x, y, w, h, _g in r.get('marks') or []:
                            allowed[y:y + h, x:x + w] = True
                    moved = int(((idx != idx0) & ~allowed).sum())
                    changed = int(((idx != idx0) & inside).sum())
                    msg = '%-10s %-11s %-6s sites: %5d px changed, %d outside' % (r['name'], st, cb, changed, moved)
                    ok = moved == 0 and (changed > 0) == (si > 0 and bool(r['sites']))
                    if r.get('marks'):
                        de0 = marker_min_de(r, rgba0, cb if ci else 'normal')
                        de1 = marker_min_de(r, rgba, cb if ci else 'normal')
                        msg += '; markers min dE %.1f -> %.1f' % (de0, de1)
                        if ci and any(c[ci - 1] is not None and c[ci - 1] != KEEP for c in r['colours']):
                            ok &= de1 >= 12 and clut != r['clut']
                        elif not ci:
                            ok &= clut == r['clut']
                    print(('ok   ' if ok else 'FAIL ') + msg)
                    bad += not ok
                    bg = np.zeros_like(rgba)
                    bg[...] = (40, 40, 60, 255)
                    al = rgba[..., 3:4] / 255.0
                    comp = (rgba[..., :3] * al + bg[..., :3] * (1 - al)).astype(np.uint8)
                    Image.fromarray(comp, 'RGB').resize((r['w'] * 2, r['h'] * 2), Image.NEAREST).save(
                        os.path.join(a.out, '%s_%s_%s.png' % (r['name'], st, cb)))
    return bad


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--check', action='store_true')
    ap.add_argument('--no-share-check', action='store_true')
    ap.add_argument('--verify', action='store_true', help='--check + every target through --exe (rg-texpatch-tests)')
    ap.add_argument('--exe')
    ap.add_argument('--out', default=os.path.join(PORT, 'out', 'p6a11y', 'texpatch_verify'))
    a = ap.parse_args()
    if not os.path.exists(os.path.join(PORT, 'data', 'DATA0_0.HD6')):
        print('no game data: skipped')
        return 77
    if a.verify:
        a.check = True
        a.no_share_check = True
    rows, warn = gen(not a.no_share_check)
    for w in warn:
        print('WARNING', w, file=sys.stderr)
    text = emit(rows)
    if a.check:
        cur = open(OUT_C, encoding='utf-8').read() if os.path.exists(OUT_C) else ''
        if cur != text:
            print('rg_texpatch_tab.c is stale: run tools/p6/texpatch_gen.py')
            return 1
        print('rg_texpatch_tab.c up to date (%d targets)' % len(rows))
        if a.verify:
            bad = verify(a, rows)
            print('verify: %s' % ('PASS' if not bad else '%d FAIL' % bad))
            return 1 if bad else 0
        return 0
    with open(OUT_C, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)
    for r in rows:
        print('%s %dx%d T%d pix %d 0x%016x clut %d 0x%016x' % (r['name'], r['w'], r['h'], r['bits'], r['pix_bytes'],
                                                             r['pix_hash'], r['clut_bytes'], r['clut_hash']))
    return 0


if __name__ == '__main__':
    sys.exit(main())
