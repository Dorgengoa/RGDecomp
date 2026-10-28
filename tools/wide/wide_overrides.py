# SPDX-License-Identifier: CC0-1.0
"""Create the widescreen stage 1 overrides from the generated game/ files.
Each: copy game/<rel>, add the rg-override header (sha256 from MANIFEST.tsv),
add the port prototypes after the first #include "types.h", apply exact
replacements (each must match exactly once).

  python tools/wide/wide_overrides.py --check   dry run (all replacements still apply)
  python tools/wide/wide_overrides.py --force   rewrite them (re-port after a snapshot bump
                                                 marks them STALE in tools/ingest.py --check)
"""
import sys, os
ROOT = '.'
man = {}
for line in open(f'{ROOT}/game/MANIFEST.tsv', encoding='utf-8'):
    f = line.rstrip('\n').split('\t')
    if len(f) >= 2: man[f[0]] = f[1]

WHY = 'widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): '
WIDE = '((unsigned char)IsWidescreen_1c6ab0())'
J = [
 ('src/main/camera/SceneCameraApplyAspect_1c6a10.c', 'the WIDE projection aspect follows the canvas: rg_aspect_d() instead of 0.5625 (the same value at 16:9)',
  [('ViewSetAspect_142f50(t16, 0.5625f);', 'ViewSetAspect_142f50(t16, rg_aspect_d());')]),
 ('src/main/gfx/GsDrawSpriteCentered_3834d0.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('k = 0.75f;', 'k = rg_hud_xscale();')]),
 ('src/main/gfx/GsDrawSpriteAnchorBR_3836a0.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('s = 0.75f;', 's = rg_hud_xscale();')]),
 ('src/main/gfx/GsDrawSpriteAnchorBL_383860.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('s = 0.75f;', 's = rg_hud_xscale();')]),
 ('src/main/gfx/DrawRotatedQuad_383c70.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('IsWidescreen_1c6ab0()) ? 0.75f : 1.0f;', 'IsWidescreen_1c6ab0()) ? rg_hud_xscale() : 1.0f;')]),
 ('src/main/ui/HpGaugeDraw_31d090.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('s = s * 0.75f;', 's = s * rg_hud_xscale();')]),
 ('src/main/ui/HpGaugeDrawThin_31d2d0.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('s = s * 0.75f;', 's = s * rg_hud_xscale();')]),
 ('src/main/ui/MinimapDrawEntries_329460.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('s = s * 0.75f;', 's = s * rg_hud_xscale();')]),
 ('src/main/battle/TargetSlotDraw_320b00.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('sc = 0.75f;', 'sc = rg_hud_xscale();')]),
 ('src/main/battle/AttackChainDraw_380660.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('        sc = 0.75f;\n', '        sc = rg_hud_xscale();\n')]),
 ('src/main/battle/AttackChainStartMaybe_382910.c', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('sc = 0.75f;', 'sc = rg_hud_xscale();')]),
 ('src/main/effect/LensFlareDraw_2ed830.cpp', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('kx = kx * 0.75f;', 'kx = kx * rg_hud_xscale();')]),
 ('src/main/effect/DoorCursorDraw_304aa0.cpp', 'WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9)',
  [('f20 = f20 * 0.75f;', 'f20 = f20 * rg_hud_xscale();')]),
 ('src/main/gfx/CompassHudRender_370fb0.cpp', 'the compass model is not WIDE-aware (projection 0.75 always): with the WIDE flag it takes rg_aspect_d() and its marker sprites rg_hud_xscale(); flag off = generated code',
  [('ViewSetPerspective_1564a0(cp, D_0047D838, 0.75f, tmp.fC, tmp.f10, tmp.fC, tmp.f10);',
    'ViewSetPerspective_1564a0(cp, D_0047D838, ' + WIDE + ' ? rg_aspect_d() : 0.75f, tmp.fC, tmp.f10, tmp.fC, tmp.f10);'),
   ('        i = 0;\n        do {\n', '        hw = ' + WIDE + ' ? (s32)(208.0f * rg_hud_xscale()) : 0xD0;\n        i = 0;\n        do {\n'),
   ('GsPktSetXYZ_13ef10(o, scr.x - 0xD0, scr.y - 0xD0, 0);', 'GsPktSetXYZ_13ef10(o, scr.x - hw, scr.y - 0xD0, 0);'),
   ('GsPktSetXYZ_13ef10(o, scr.x + 0xD0, scr.y + 0xD0, 0);', 'GsPktSetXYZ_13ef10(o, scr.x + hw, scr.y + 0xD0, 0);'),
   ('    s8 *u1;\n', '    s8 *u1;\n    s32 hw; /* rg-override: marker half width (0xD0 = 13 px) */\n')]),
 ('src/main/menu/DrawModelWithCamera_28bf80.cpp', 'menu model previews are not WIDE-aware (projection 0.75 always): with the WIDE flag they take rg_aspect_d(); flag off = generated code',
  [('c->cv02() / 180.0f, 0.75f, e, f, e, f);', 'c->cv02() / 180.0f, ' + WIDE + ' ? rg_aspect_d() : 0.75f, e, f, e, f);')]),
 ('src/main/sys/GameSessionInit_1f5d80.cpp', 'the session-start projection hard-codes 0.75: with the WIDE flag it takes rg_aspect_d(); flag off = generated code',
  [('ViewSetProjectionBasic_143180(GetDrawCtx_15de80(), D_0047D4A0, 5.0f, 10000, 0.75f);',
    'ViewSetProjectionBasic_143180(GetDrawCtx_15de80(), D_0047D4A0, 5.0f, 10000, ' + WIDE + ' ? rg_aspect_d() : 0.75f);')]),
]
PROTO_C = '''/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern float rg_aspect_d(void);
extern float rg_hud_xscale(void);
'''
PROTO_CPP = '''/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern "C" float rg_aspect_d(void);
extern "C" float rg_hud_xscale(void);
'''
check = '--check' in sys.argv
for rel, why, reps in J:
    src = open(f'{ROOT}/game/{rel}', encoding='utf-8').read()
    cpp = rel.endswith('.cpp')
    proto = PROTO_CPP if cpp else PROTO_C
    if cpp and 'IsWidescreen_1c6ab0' not in src and any(WIDE in n for _, n in reps):
        proto += 'extern "C" unsigned char IsWidescreen_1c6ab0(void);\n'
    inc = '#include "types.h"\n'
    assert src.count(inc) >= 1, rel
    i = src.index(inc) + len(inc)
    out = src[:i] + proto + src[i:]
    for o, n in reps:
        c = out.count(o)
        assert c == 1, (rel, o, c)
        out = out.replace(o, n)
    hdr = f'/* rg-override: replaces game/{rel} sha256 {man[rel]}\n * why: {WHY}{why} */\n'
    dst = f'{ROOT}/overrides/{rel}'
    if check:
        print(rel, 'ok'); continue
    if os.path.exists(dst) and '--force' not in sys.argv:
        print('exists, skipped:', dst); continue
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    open(dst, 'w', encoding='utf-8', newline='').write(hdr + out)
    print('wrote', dst)
