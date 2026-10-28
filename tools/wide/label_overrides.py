# SPDX-License-Identifier: CC0-1.0
"""Create the widescreen world-text overrides (NPC name labels, damage numbers) from the
generated game/ files (docs/WIDESCREEN.md "Stage 2", world-anchored text).
Each: copy game/<rel>, add the rg-override header (sha256 from MANIFEST.tsv), the
rg_layout_about_* prototypes after the first #include "types.h", and exact replacements
(each must match exactly once).  Same scheme as wide_overrides.py.

  python tools/wide/label_overrides.py --check   dry run
  python tools/wide/label_overrides.py --force   rewrite them (after a snapshot bump)
"""
import os
import sys

ROOT = '.'
man = {}
for line in open(f'{ROOT}/game/MANIFEST.tsv', encoding='utf-8'):
    f = line.rstrip('\n').split('\t')
    if len(f) >= 2:
        man[f[0]] = f[1]

WHY = 'widescreen stage 2 (docs/WIDESCREEN.md "Stage 2", world-anchored text): '
BEGIN = 'rg_layout_about_begin'
END = 'rg_layout_about_end();'
J = [
    ('src/main/battle/DamagePopupDraw_2d3240.cpp',
     'each damage number / damage sprite is squeezed about its projected point (rg_layout_about_*; no-op at 4:3)',
     [('    s32 vv;\n', '    s32 vv;\n    s32 rg_ax; /* rg-override: projected X (12.4) = the number\'s anchor */\n'),
      ('        if (ProjectToScreen_15d340(pos, p) == 0) {\n            continue;\n        }\n',
       '        if (ProjectToScreen_15d340(pos, p) == 0) {\n            continue;\n        }\n        rg_ax = pos[0];\n'),
      ('        GsPktOpenPrim_13f730(pk, 6);\n        GsPktSetTexture_13ec00(pk, tex);\n        GsPktSetRGBAQVec_13edd0(pk, p->col);\n        GsPktSetUV_13ed60(pk, uu, vv);\n',
       f'        {BEGIN}((float)rg_ax, 0);\n        GsPktOpenPrim_13f730(pk, 6);\n        GsPktSetTexture_13ec00(pk, tex);\n        GsPktSetRGBAQVec_13edd0(pk, p->col);\n        GsPktSetUV_13ed60(pk, uu, vv);\n'),
      ('        GsPktClose_13f5b0(pk);\n    }\n}\n', f'        GsPktClose_13f5b0(pk);\n        {END}\n    }}\n}}\n'),
      ('            GsPktOpenPrim_13f730(pk, 6);\n', f'            {BEGIN}((float)pos[0], 0);\n            GsPktOpenPrim_13f730(pk, 6);\n'),
      ('            GsPktClose_13f5b0(pk);\n            return;\n', f'            GsPktClose_13f5b0(pk);\n            {END}\n            return;\n')]),
    ('src/main/ui/ScreenMarkerDrawAll_31af50.cpp',
     'NPC / party name labels and their icons are squeezed about the label\'s projected point (rg_layout_about_*; no-op at 4:3)',
     [('    f32 g;\n\n    if (self->f140 == 0) return;\n',
       '    f32 g;\n    s32 rgax[32]; /* rg-override: label centre X (screen pixels), -99999 none */\n\n    if (self->f140 == 0) return;\n'),
      ('        hgt[i] = 0;\n', '        hgt[i] = 0;\n        rgax[i] = -99999;\n'),
      ('        FontDrawText_26cdc0(font, str, half, y);\n',
       f'        rgax[m] = sx;\n        {BEGIN}((float)sx, 1);\n        FontDrawText_26cdc0(font, str, half, y);\n        {END}\n'),
      ('                GsPktOpenPrim_13f730(c, 6);\n',
       f'                if (rgax[q] != -99999) {BEGIN}((float)rgax[q], 1);\n                GsPktOpenPrim_13f730(c, 6);\n'),
      ('                GsPktClose_13f5b0(c);\n', f'                GsPktClose_13f5b0(c);\n                {END}\n')]),
]
PROTO_CPP = '''/* rg-override: widescreen stage 2 world-anchored text (src/settings/rg_layout.h) */
extern "C" void rg_layout_about_begin(float ax, int screen_px);
extern "C" void rg_layout_about_end(void);
'''
check = '--check' in sys.argv
for rel, why, reps in J:
    src = open(f'{ROOT}/game/{rel}', encoding='utf-8').read()
    inc = '#include "types.h"\n'
    i = src.index(inc) + len(inc)
    out = src[:i] + PROTO_CPP + src[i:]
    for o, n in reps:
        c = out.count(o)
        assert c == 1, (rel, o, c)
        out = out.replace(o, n)
    hdr = f'/* rg-override: replaces game/{rel} sha256 {man[rel]}\n * why: {WHY}{why} */\n'
    dst = f'{ROOT}/overrides/{rel}'
    if check:
        print(rel, 'ok')
        continue
    if os.path.exists(dst) and '--force' not in sys.argv:
        print('exists, skipped:', dst)
        continue
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    open(dst, 'w', encoding='utf-8', newline='').write(hdr + out)
    print('wrote', dst)
