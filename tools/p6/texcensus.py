#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""texcensus.py - census of the UI textures for button prompts and colour-only markers
(lane p6a11y 2026-11-01; docs/PROMPTS.md "Prompts baked into other textures",
docs/ACCESSIBILITY.md "Colour census").

    python tools/p6/texcensus.py scan    [--out out/p6a11y/texcensus]   # decode every UI texture
    python tools/p6/texcensus.py prompts [--out ...] [--thresh 0.92] [--skip-dirs map]  # button-glyph sites
    python tools/p6/texcensus.py colour  [--out ...]                    # colour-only marker sets

scan     every TIM2 picture inside an IM3 archive of a .pac / .pak / .img / .ipk / .ico / .bin
         file of DATA0_0 + DATA1_0 (each distinct picture once): OUT/tex/NNNN_<name>.png and
         OUT/index.tsv (id, where, name, type, w, h, sha1 of pixels + CLUT, fnv64 of the pixels
         = the transfer key nr_texpatch.c matches).  Game art: OUT stays under out/ (gitignored).
prompts  the PlayStation button glyphs (templates: the 8 gaiji2 button rects and the face
         buttons of btl_st01, at scales 1 and 1.5) searched in every picture by
         normalised cross-correlation of the alpha-weighted colour: OUT/prompts.tsv + .md
         (texture, glyph, x, y, w, h, score).  Already covered sites (gaiji2, the btl_st01
         rects nr_texpatch.c redraws) are marked.
colour   marker sets that differ by colour alone: in each picture the opaque connected
         components of 5..64 px are grouped by shape (same size, alpha-mask IoU >= 0.85); a
         group whose members differ in colour (CIELAB dE >= 20 for normal vision) is a colour-
         coded set.  Each set is simulated for protanopia / deuteranopia / tritanopia (Machado
         2009, severity 1) and the smallest pairwise dE is reported; dE < 12 = the members
         collide for that deficiency.  OUT/colour.tsv + .md, OUT/colour/<id>.png crops.
"""
from __future__ import annotations

import argparse
import csv
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import ps2tex  # noqa: E402

PORT = ps2tex.PORT
DEF_OUT = os.path.join(PORT, 'out', 'p6a11y', 'texcensus')

# the rects nr_texpatch.c redraws (keep in step with src/settings/rg_texprompts.c)
COVERED = {
    'btl_st01': [(108, 44, 22, 22), (130, 44, 22, 22), (4, 63, 22, 22), (1, 199, 30, 18),
                 (33, 199, 30, 18), (1, 1, 15, 14), (145, 160, 36, 14)],
}


def cmd_scan(a):
    os.makedirs(os.path.join(a.out, 'tex'), exist_ok=True)
    rows = []
    for i, (where, nm, d, tx) in enumerate(ps2tex.iter_textures(a.data)):
        safe = ''.join(c if c.isalnum() or c in '_-' else '_' for c in nm)[:40]
        fn = '%04d_%s.png' % (i, safe)
        ps2tex.write_png(os.path.join(a.out, 'tex', fn), tx.rgba())
        key = ps2tex.fnv64(d[tx.px_off:tx.px_off + tx.px_size]) if tx.px_size <= 1 << 20 else 0
        rows.append([i, where, nm, tx.img_type, tx.w, tx.h, tx.sha1, '%016x' % key, fn])
        if i % 200 == 0:
            print(i, where, nm, file=sys.stderr)
    with open(os.path.join(a.out, 'index.tsv'), 'w', newline='', encoding='utf-8') as f:
        w = csv.writer(f, delimiter='\t')
        w.writerow(['id', 'where', 'name', 'type', 'w', 'h', 'sha1', 'fnv64_pixels', 'png'])
        w.writerows(rows)
    print('%d textures -> %s' % (len(rows), a.out))


def load_index(out):
    with open(os.path.join(out, 'index.tsv'), encoding='utf-8') as f:
        return list(csv.DictReader(f, delimiter='\t'))


def load_rgba(out, row):
    from PIL import Image
    return np.asarray(Image.open(os.path.join(out, 'tex', row['png'])).convert('RGBA'))


# ------------------------------------------------------------------ prompts --------------

def templates(out, rows):
    """[(label, rgba)] of the PlayStation glyphs"""
    t = []
    gaiji = ps2tex.gaiji
    try:
        img, _ = gaiji.load_gaiji_img(os.path.join(PORT, 'data'))
        ind = gaiji.decode(img)
        rgba = np.frombuffer(ind.rgba(), np.uint8).reshape(256, 256, 4)
        metrics, _tags, _ins = gaiji.read_tables(os.path.join(PORT, 'data'))
        names = {0xFD02: 'L1', 0xFD03: 'R1', 0xFD04: 'L2', 0xFD05: 'R2', 0xFD06: 'Circle',
                 0xFD07: 'Triangle', 0xFD08: 'Cross', 0xFD09: 'Square'}   # (tags (O) (A) (X) (#))
        for m in metrics:
            if m['code'] in names:
                u, v, w, h = m['u'], m['v'], m['w'], m['h']
                t.append(('gaiji2:' + names[m['code']], rgba[v:v + h, u:u + w]))
    except Exception as e:   # noqa: BLE001
        print('gaiji2 templates skipped:', e, file=sys.stderr)
    for r in rows:
        # (the US sheet; menu_static_img2_en.pac holds a JP-text copy with another layout)
        if r['name'] == 'btl_st01' and 'menu_static_img_en' in r['where']:
            im = load_rgba(out, r)
            t.append(('btl_st01:Square', im[44:66, 108:130]))
            t.append(('btl_st01:Triangle', im[44:66, 130:152]))
            break
    return t


def _feat(rgba):
    a = rgba[..., 3:4].astype(np.float32) / 255.0
    return rgba[..., :3].astype(np.float32) / 255.0 * a, a[..., 0]


def _resize(rgba, s):
    from PIL import Image
    h, w = rgba.shape[:2]
    nw, nh = max(4, int(round(w * s))), max(4, int(round(h * s)))
    return np.asarray(Image.fromarray(rgba, 'RGBA').resize((nw, nh), Image.BILINEAR))


def ncc_map(img_f, tpl_f):
    """normalised cross-correlation (valid positions), summed over the channels"""
    from scipy.signal import fftconvolve
    th, tw = tpl_f.shape[:2]
    ih, iw = img_f.shape[:2]
    if th > ih or tw > iw:
        return None
    num = np.zeros((ih - th + 1, iw - tw + 1), np.float64)
    den_i = np.zeros_like(num)
    den_t = 0.0
    ones = np.ones((th, tw))
    for c in range(img_f.shape[2]):
        t = tpl_f[..., c] - tpl_f[..., c].mean()
        im = img_f[..., c].astype(np.float64)
        num += fftconvolve(im, t[::-1, ::-1], mode='valid')
        s1 = fftconvolve(im, ones, mode='valid')
        s2 = fftconvolve(im * im, ones, mode='valid')
        den_i += np.maximum(s2 - s1 * s1 / (th * tw), 0)
        den_t += (t * t).sum()
    # flat windows (no variance) cannot match: they would divide by ~0
    out = num / np.sqrt(np.maximum(den_i * den_t, 1e-12))
    out[den_i < 1e-3 * th * tw * img_f.shape[2]] = 0.0
    return out


def cmd_prompts(a):
    rows = load_index(a.out)
    tpls = templates(a.out, rows)
    print('%d templates' % len(tpls), file=sys.stderr)
    tset = []
    for lab, t in tpls:
        for s in (1.0, 1.5):
            r = _resize(np.ascontiguousarray(t), s) if s != 1.0 else t
            c, al = _feat(r)
            tset.append((lab, s, np.concatenate([c, al[..., None]], 2)))
    hits = []
    skip = tuple(d + chr(92) for d in a.skip_dirs.split(',') if d)
    for k, row in enumerate(rows):
        if row['where'].split(':', 1)[-1].startswith(skip):
            continue   # (map textures: scenery, no prompts)
        im = load_rgba(a.out, row)
        if im.shape[0] < 12 or im.shape[1] < 12:
            continue
        c, al = _feat(im)
        f = np.concatenate([c, al[..., None]], 2)
        for lab, s, t in tset:
            m = ncc_map(f, t)
            if m is None:
                continue
            th, tw = t.shape[:2]
            while True:
                y, x = np.unravel_index(np.argmax(m), m.shape)
                sc = m[y, x]
                if sc < a.thresh:
                    break
                hits.append((row, lab, s, int(x), int(y), tw, th, float(sc)))
                m[max(0, y - th // 2):y + th // 2 + 1, max(0, x - tw // 2):x + tw // 2 + 1] = -1
        if k % 200 == 0:
            print(k, len(hits), file=sys.stderr)
    # one hit per site (best template)
    best = {}
    for row, lab, s, x, y, w, h, sc in hits:
        key = (row['id'], x // 8, y // 8)
        if key not in best or sc > best[key][-1]:
            best[key] = (row, lab, s, x, y, w, h, sc)
    sites = sorted(best.values(), key=lambda v: (int(v[0]['id']), v[4], v[3]))
    with open(os.path.join(a.out, 'prompts.tsv'), 'w', newline='', encoding='utf-8') as f:
        w = csv.writer(f, delimiter='\t')
        w.writerow(['id', 'texture', 'where', 'glyph', 'scale', 'x', 'y', 'w', 'h', 'score', 'covered'])
        for row, lab, s, x, y, ww, hh, sc in sites:
            cov = any(abs(x - cx) <= 3 and abs(y - cy) <= 3 for cx, cy, _w, _h in COVERED.get(row['name'], []))
            if row['name'] == 'gaiji2':
                cov = True
            w.writerow([row['id'], row['name'], row['where'], lab, s, x, y, ww, hh, '%.3f' % sc,
                        'yes' if cov else 'no'])
    tex = sorted({(v[0]['id'], v[0]['name']) for v in sites}, key=lambda t: int(t[0]))
    with open(os.path.join(a.out, 'prompts.md'), 'w', encoding='utf-8') as f:
        f.write('# Button-glyph sites in UI textures (texcensus.py prompts)\n\n')
        f.write('%d sites in %d textures (threshold %.2f)\n\n' % (len(sites), len(tex), a.thresh))
        f.write('| id | texture | glyph | x,y | w x h | score | covered |\n|---|---|---|---|---|---|---|\n')
        for row, lab, s, x, y, ww, hh, sc in sites:
            cov = any(abs(x - cx) <= 3 and abs(y - cy) <= 3 for cx, cy, _w, _h in COVERED.get(row['name'], []))
            f.write('| %s | %s | %s x%.2f | %d,%d | %dx%d | %.3f | %s |\n'
                    % (row['id'], row['name'], lab, s, x, y, ww, hh, sc,
                       'yes' if cov or row['name'] == 'gaiji2' else 'no'))
    print('%d sites in %d textures -> %s' % (len(sites), len(tex), os.path.join(a.out, 'prompts.md')))


# ------------------------------------------------------------------- colour --------------

MACHADO = {
    'protan': np.array([[0.152286, 1.052583, -0.204868], [0.114503, 0.786281, 0.099216],
                        [-0.003882, -0.048116, 1.051998]]),
    'deutan': np.array([[0.367322, 0.860646, -0.227968], [0.280085, 0.672501, 0.047413],
                        [-0.011820, 0.042940, 0.968881]]),
    'tritan': np.array([[1.255528, -0.076749, -0.178779], [-0.078411, 0.930809, 0.147602],
                        [0.004733, 0.691367, 0.303900]]),
}


def srgb_lin(c):
    c = np.asarray(c, np.float64) / 255.0
    return np.where(c <= 0.04045, c / 12.92, ((c + 0.055) / 1.055) ** 2.4)


def lin_srgb(c):
    c = np.clip(c, 0, 1)
    return 255.0 * np.where(c <= 0.0031308, c * 12.92, 1.055 * c ** (1 / 2.4) - 0.055)


def simulate(rgb, kind):
    """sRGB 0..255 (..., 3) -> what a viewer with that deficiency sees (sRGB 0..255)"""
    if kind == 'normal':
        return np.asarray(rgb, np.float64)
    return lin_srgb(srgb_lin(rgb) @ MACHADO[kind].T)


def lab(rgb):
    lin = srgb_lin(rgb)
    m = np.array([[0.4124, 0.3576, 0.1805], [0.2126, 0.7152, 0.0722], [0.0193, 0.1192, 0.9505]])
    xyz = lin @ m.T / np.array([0.95047, 1.0, 1.08883])
    f = np.where(xyz > 0.008856, np.cbrt(xyz), 7.787 * xyz + 16 / 116)
    return np.stack([116 * f[..., 1] - 16, 500 * (f[..., 0] - f[..., 1]), 200 * (f[..., 1] - f[..., 2])], -1)


def min_de(cols, kind):
    L = lab(simulate(np.array(cols), kind))
    best = 1e9
    for i in range(len(L)):
        for j in range(i + 1, len(L)):
            best = min(best, float(np.linalg.norm(L[i] - L[j])))
    return best


def components(alpha, thr=96):
    from scipy import ndimage
    lab_, n = ndimage.label(alpha >= thr)
    out = []
    for i, sl in enumerate(ndimage.find_objects(lab_), 1):
        if sl is None:
            continue
        h, w = sl[0].stop - sl[0].start, sl[1].stop - sl[1].start
        if 5 <= w <= 64 and 5 <= h <= 64:
            out.append((sl, lab_[sl] == i))
    return out


def cmd_colour(a):
    rows = load_index(a.out)
    os.makedirs(os.path.join(a.out, 'colour'), exist_ok=True)
    sets = []
    for k, row in enumerate(rows):
        im = load_rgba(a.out, row)
        comps = components(im[..., 3])
        if len(comps) < 2 or len(comps) > 400:
            continue
        used = [False] * len(comps)
        for i, (sl, m) in enumerate(comps):
            if used[i]:
                continue
            grp = [i]
            for j in range(i + 1, len(comps)):
                sl2, m2 = comps[j]
                if used[j] or m2.shape != m.shape:
                    continue
                iou = (m & m2).sum() / max(1, (m | m2).sum())
                if iou >= 0.85:
                    grp.append(j)
            if len(grp) < 2:
                continue
            cols = []
            for g in grp:
                sl2, m2 = comps[g]
                px = im[sl2][m2][:, :3].astype(np.float64)
                # the member's dominant colour: mean of its most saturated half
                sat = px.max(1) - px.min(1)
                cols.append(px[sat >= np.median(sat)].mean(0))
            if min_de(cols, 'normal') < 20:
                continue
            for g in grp:
                used[g] = True
            res = {kd: min_de(cols, kd) for kd in ('protan', 'deutan', 'tritan')}
            sets.append((row, [comps[g][0] for g in grp], cols, res))
        if k % 200 == 0:
            print(k, len(sets), file=sys.stderr)
    from PIL import Image
    with open(os.path.join(a.out, 'colour.tsv'), 'w', newline='', encoding='utf-8') as f, \
            open(os.path.join(a.out, 'colour.md'), 'w', encoding='utf-8') as md:
        w = csv.writer(f, delimiter='\t')
        w.writerow(['set', 'id', 'texture', 'where', 'n', 'rects', 'colours', 'dE_protan', 'dE_deutan',
                    'dE_tritan', 'collides'])
        md.write('# Colour-only marker sets in UI textures (texcensus.py colour)\n\n')
        md.write('Same shape, different colour; min pairwise CIELAB dE after a Machado 2009 simulation '
                 '(< 12 = collide).\n\n| set | texture | n | rects | colours | protan | deutan | tritan |'
                 '\n|---|---|---|---|---|---|---|---|\n')
        for si, (row, sls, cols, res) in enumerate(sets):
            rects = ' '.join('%d,%d,%d,%d' % (s[1].start, s[0].start, s[1].stop - s[1].start,
                                               s[0].stop - s[0].start) for s in sls)
            colstr = ' '.join('#%02x%02x%02x' % tuple(int(v) for v in c) for c in cols)
            coll = ','.join(k for k, v in res.items() if v < 12)
            w.writerow([si, row['id'], row['name'], row['where'], len(sls), rects, colstr,
                        '%.1f' % res['protan'], '%.1f' % res['deutan'], '%.1f' % res['tritan'], coll])
            md.write('| %d | %s (%s) | %d | %s | %s | %.1f | %.1f | %.1f |\n'
                     % (si, row['name'], row['id'], len(sls), rects, colstr, res['protan'],
                        res['deutan'], res['tritan']))
            im = load_rgba(a.out, row)
            crops = [im[s] for s in sls]
            hh = max(c.shape[0] for c in crops)
            strip = np.zeros((hh * 4, sum(c.shape[1] + 2 for c in crops), 4), np.uint8)
            x = 0
            for c in crops:
                for r, kd in enumerate(('normal', 'protan', 'deutan', 'tritan')):
                    sim = simulate(c[..., :3], kd).astype(np.uint8)
                    strip[r * hh:r * hh + c.shape[0], x:x + c.shape[1], :3] = sim
                    strip[r * hh:r * hh + c.shape[0], x:x + c.shape[1], 3] = c[..., 3]
                x += c.shape[1] + 2
            Image.fromarray(strip, 'RGBA').resize((strip.shape[1] * 3, strip.shape[0] * 3),
                                                  Image.NEAREST).save(os.path.join(a.out, 'colour', '%03d_%s.png' % (si, row['name'])))
    print('%d colour-coded sets -> %s' % (len(sets), os.path.join(a.out, 'colour.md')))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('cmd', choices=['scan', 'prompts', 'colour'])
    ap.add_argument('--out', default=DEF_OUT)
    ap.add_argument('--data', default=None)
    ap.add_argument('--thresh', type=float, default=0.92)
    ap.add_argument('--skip-dirs', default='map', help='prompts: top-level data dirs not searched')
    a = ap.parse_args(argv)
    {'scan': cmd_scan, 'prompts': cmd_prompts, 'colour': cmd_colour}[a.cmd](a)


if __name__ == '__main__':
    main()
