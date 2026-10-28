# SPDX-License-Identifier: CC0-1.0
"""Create the widescreen stage 3 menu overrides from the generated game/ files
(docs/WIDESCREEN.md "Stage 3").  Same scheme as wide_overrides.py / label_overrides.py:
copy game/<rel>, add the rg-override header (sha256 from MANIFEST.tsv), the prototypes
after the first #include "types.h", exact replacements (each must match exactly once).

  python tools/wide/menu_overrides.py --check   dry run
  python tools/wide/menu_overrides.py --force   rewrite them (after a snapshot bump)
"""
import os
import sys

ROOT = '.'
man = {}
for line in open(f'{ROOT}/game/MANIFEST.tsv', encoding='utf-8'):
    f = line.rstrip('\n').split('\t')
    if len(f) >= 2:
        man[f[0]] = f[1]

WHY = 'widescreen stage 3 (docs/WIDESCREEN.md "Stage 3", no aspect switch for menus): '
J = [
    ('src/main/menu/MenuCaptureScreenTex_298810.c',
     'the main menu\'s portrait circle shows a 256x256 copy of the field frame (x 191..446, '
     'y 106..361) taken when the menu opens; on a wide canvas the frame is anamorphic, so the '
     'copy is resampled from the frame region that shows what the 4:3 copy shows '
     '(rg_layout_capture_wide; returns 0 = generated code at 4:3)',
     [('    y = 0;\n    r = 0;\n',
       '    if (rg_layout_capture_wide(src, dst)) /* rg-override */\n        return;\n    y = 0;\n    r = 0;\n')]),
]
PROTO_C = '''/* rg-override: widescreen stage 3 (src/settings/rg_layout.h) */
extern int rg_layout_capture_wide(const u8 *src, u8 *dst);
'''
check = '--check' in sys.argv
for rel, why, reps in J:
    src = open(f'{ROOT}/game/{rel}', encoding='utf-8').read()
    inc = '#include "types.h"\n'
    i = src.index(inc) + len(inc)
    out = src[:i] + PROTO_C + src[i:]
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
