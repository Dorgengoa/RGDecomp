#include "types.h"

/* title.bin overlay, 0x004F0CB0 -- boot the title screen.
 *
 * Copies the caller's 0x70-byte boot descriptor into the frame, brings up the
 * renderer, streams the title's three archives (0x800 script, 0x124F8 and
 * 0x61A80 data), builds the nine background layers, and hands the two big
 * buffers to title_TitleObjectsCreate_4ecbc0.
 *
 * CLOSED 2026-08-25 by the pragma below, after every source axis was a
 * measured null (154 statement orders, 24 declaration orders, all flat or
 * floored at 2: the copy loop's cursor bump landed between retail's two
 * stores).  With const-nonchanging analysis on, mwcc stops treating the
 * cursor as freshly derived per store and the bump drops below both, which is
 * retail's schedule.  Found by t_knob.py's recognised-pragma sweep (116
 * variants: 108 inert, this one 0 bad).  Per-TU; inert on 004ECE80/004F0600.
 */
#pragma opt_constnonchanging on

typedef struct Cfg {
    u8 pad0[4];
    s16 f4;
    u8 pad6[0x6A];
} Cfg;

typedef struct Scene {
    u8 pad0[0x3D2C];
    s32 f3D2C;
} Scene;

extern f32 D_0047D4A0;
extern u8 D_00480434;
extern u8 D_00480440;
extern s16 D_00481B90;
extern s32 D_00484288;
extern s32 D_0048428C;
extern u8 D_00484298;
extern s32 D_00484294;
extern u8 D_004842A4;
extern u8 D_004842B0;
extern const u8 D_004B2570;
extern const u8 D_004F1420;
extern const u8 D_004F1460;
extern const u8 D_004F1638;
extern const u8 D_004F1648;
extern const u8 D_004F1660;
extern const u8 D_004F1678;
extern const u8 D_004F1688;
extern const u8 D_004F1698;
extern const u8 D_004F1A30;
extern const u8 D_004F1A90;
extern const u8 D_004F1AF0;

extern void func_108F98(s32 a);
extern void func_1290B8(f32 v);
extern void func_134A98(void *a, void *b);
extern u32 func_134BB0(void *a);
extern void func_13E2F0(void *a, s32 b);
extern void func_13E3D0(void *a, s32 b);
extern void func_13E3E0(void *a, s32 b);
extern void func_13E400(void *a, s32 b);
extern void func_13E430(void *a, s32 b);
extern void func_13E460(void *a, s32 b);
extern void func_13E4D0(void *a, s32 b);
extern void func_13E4F0(void *a, s32 b);
extern void func_13E500(void *a, s32 b);
extern void func_13EC00(void *a, void *b);
extern void func_13ED90(void *a, s32 b, s32 c);
extern void func_13EE40(void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_13F110(void *a, s32 b, s32 c, s32 d);
extern void func_13F5B0(void *a);
extern void func_13F730(void *a, s32 b);
extern void func_13FCB0(void *a);
extern void func_1418C0(void *a, s32 b, f32 v);
extern void func_1425D0(void *a, s32 b);
extern void func_141A20(void *a);
extern void *func_141B00(void *a);
extern void func_141C20(void *a, s32 b);
extern void func_143180(void *a, f32 x, f32 y, f32 z, f32 w);
extern void func_144140(void *a, s32 b, s32 c);
extern void func_145980(void *a, s32 b, s32 c, void *d);
extern void func_14D810(void *a, void *b, s32 c);
extern void func_14D830(void *a);
extern void func_14D8E0(void *a);
extern void *func_14D950(void *a, s32 b);
extern void *func_14DA10(void *a, s32 b);
extern void func_14DEE0(void *a, void *b, s32 c);
extern void func_14DFF0(void *a);
extern void func_1594D0(void *a, void *b, s32 c, void *d, s32 e);
extern void *func_159FB0(void *a, void *b, s32 c);
extern void func_15CA70(void *a);
extern void func_15CB30(void *a);
extern void func_15CC00(void *a, void *b);
extern void func_15DC50(void *a, s32 b, void *c, s32 d, s32 e);
extern void *func_15DE40(void);
extern Scene *func_15DE80(void);
extern void func_1849E0(void *a);
extern s32 func_1C2860(void *a, void *b, s32 *c);
extern s32 func_1C3540(void);
extern void func_1C6A90(s32 a);
extern void *func_1C6C70(void);
extern void *func_1C6DC0(void);
extern void func_1CD880(void *a, s32 b, s32 c);
extern s32 func_1CD620(void *a);
extern void func_1CDE60(void *a, s32 b, s32 c, s32 d, s32 e, void *f);
extern void func_1CE040(void *a);
extern void func_1F5BD0(void *a);
extern s32 *func_1F59D0(void);
extern void func_1FE5A0(s32 a, s32 b);
extern void func_1FEAC0(s32 a);
extern void func_202290(void *a);
extern void func_202390(void *a);
extern s32 func_2025E0(void);
extern void func_206940(void *a);
extern void func_207A90(s32 a);
extern void func_207AC0(s32 a);
extern void func_207BE0(void *a, void *b);
extern void func_207E20(s32 a, s32 b);
extern void func_207ED0(void);
extern void func_207F10(s32 a);
extern void func_208A10(void *a, s32 b, void *c);
extern void func_2F65A0(void);
extern void func_2F74C0(void);
extern void func_2F7720(void);
extern void title_TitleObjectsCreate_4ecbc0(void *a, void *b);
extern s32 title_TitleUvToFixed_4f13a0(s32 a);

void title_TitleSessionInit_4f0cb0(const s32 *arg)
{
    Cfg c;
    s32 n;
    void *buf;
    void *disc;
    Scene *sc;
    void *fs;
    s32 *env;
    s32 i;
    void *prim;
    s32 *d;
    s32 k;
    s32 a;
    s32 b;

    d = (s32 *)&c;
    k = 14;
    do {
        a = arg[0];
        b = arg[1];
        arg += 2;
        d[0] = a;
        d[1] = b;
        d += 2;
        k--;
    } while (k > 0);
    D_00480434 = 1;
    D_00484294 = 0;
    D_004842A4 = 0;
    func_208A10((void *)&D_004F1638, 0x3C, d);
    func_1849E0((void *)&D_004B2570);
    func_207ED0();
    if (c.f4 == 1) {
        func_207F10(1);
    }
    if (func_1C3540() != 0) {
        func_1C6A90(1);
    }
    func_2F65A0();
    func_1F5BD0(func_1C6C70());
    disc = func_1C6DC0();
    func_14D830(disc);
    func_14D8E0(disc);
    func_15DC50(disc, 0x2710, disc, 0, 0xEA60);
    func_14D8E0(disc);
    sc = func_15DE80();
    func_14DEE0((void *)((char *)sc + 0xD0), func_14D950(disc, 0x3A98), 0x3A98);
    func_144140(sc, 2, 0);
    func_13FCB0(sc);
    fs = func_15DE40();
    func_145980(sc, 0x180, 0x33A, disc);
    func_14D8E0(disc);
    func_2F7720();
    func_1FEAC0(1);
    func_202290(disc);
    env = func_1F59D0();
    func_1CE040(env);
    *env = func_2025E0();
    func_1CDE60(env, 0x80, 0xC0, 0x10, 0x80, disc);
    func_206940(disc);
    func_1849E0((void *)&D_004B2570);
    if (D_00481B90 != 0) {
        func_14DFF0((void *)&D_004F1AF0);
        func_14D810((void *)&D_004F1AF0, func_14DA10(disc, 0x800), 0x800);
        if (func_134BB0((void *)&D_004F1648) < 0x10) {
            func_134A98((void *)&D_004F1AF0, (void *)&D_004F1648);
        }
        func_14D830((void *)&D_004F1AF0);
        func_14D8E0((void *)&D_004F1AF0);
        buf = func_14D950((void *)&D_004F1AF0, 0x400);
        if (func_1C2860((void *)&D_004F1660, buf, &n) != 0) {
            func_1594D0(fs, buf, 0x32C, (void *)&D_004F1AF0, 0);
            func_14D8E0((void *)&D_004F1AF0);
            sc->f3D2C = 0;
            i = 0;
            do {
                func_108F98(0);
                func_1425D0(sc, 1);
                func_1418C0(sc, 0x32C, 1.0f);
                prim = func_141B00(sc);
                func_13E400(prim, 0);
                func_13E2F0(prim, 0);
                func_13E500(prim, 1);
                func_13E4F0(prim, 1);
                func_13E4D0(prim, 1);
                func_13E430(prim, 0);
                func_13E460(prim, 0);
                func_13E3D0(prim, 0);
                func_13F730(prim, 6);
                func_13EE40(prim, 0, 0, 0, 0x80);
                func_13F110(prim, 0, 0, 0);
                func_13F110(prim, 0x1FF, 0x1BF, 0);
                func_13F5B0(prim);
                func_13E2F0(prim, 0);
                func_13E500(prim, 1);
                func_13E4F0(prim, 2);
                func_13E4D0(prim, 1);
                func_13E430(prim, 0);
                func_13E460(prim, 0);
                func_13E3D0(prim, 1);
                func_13E400(prim, 1);
                func_13E3E0(prim, 1);
                func_13F730(prim, 6);
                func_13EC00(prim, func_159FB0(fs, (void *)&D_004F1678, 0x32C));
                func_13EE40(prim, 0x80, 0x80, 0x80, i << 5);
                func_13ED90(prim, title_TitleUvToFixed_4f13a0(0), title_TitleUvToFixed_4f13a0(0));
                func_13F110(prim, 0x160, 0x160, 0);
                func_13ED90(prim, title_TitleUvToFixed_4f13a0(0x7F),
                            title_TitleUvToFixed_4f13a0(0x3F));
                func_13F110(prim, 0x1DF, 0x19F, 0);
                func_13F5B0(prim);
                func_141A20(sc);
                func_141C20(sc, 1);
                i = i + 1;
            } while (i <= 8);
        }
    }
    func_1FE5A0(0, 1);
    func_1849E0((void *)&D_004B2570);
    func_15CC00((void *)&D_004F1420, (void *)&D_004F1460);
    func_15CB30((void *)&D_00480440);
    func_15CA70((void *)&D_004842B0);
    func_1290B8(D_0047D4A0);
    func_143180(sc, D_0047D4A0, 5.0f, (f32)0x2710, 0.75f);
    func_1849E0((void *)&D_004B2570);
    func_202390(disc);
    func_207BE0(disc, disc);
    func_207AC0(1);
    func_207E20(0x1F4, 1);
    func_1CD880(env, 1, 1);
    while (func_1CD620(env) > 0) {
        func_2F74C0();
        func_207A90(1);
    }
    func_1CD880(env, 0, 0);
    func_14DFF0((void *)&D_004F1A90);
    func_14D810((void *)&D_004F1A90, func_14DA10(disc, 0x124F8), 0x124F8);
    if (func_134BB0((void *)&D_004F1688) < 0x10) {
        func_134A98((void *)&D_004F1A90, (void *)&D_004F1688);
    }
    func_14D830((void *)&D_004F1A90);
    func_14DFF0((void *)&D_004F1A30);
    func_14D810((void *)&D_004F1A30, func_14DA10(disc, 0x61A80), 0x61A80);
    if (func_134BB0((void *)&D_004F1698) < 0x10) {
        func_134A98((void *)&D_004F1A30, (void *)&D_004F1698);
    }
    func_14D830((void *)&D_004F1A30);
    D_00484288 = 0;
    D_0048428C = 0;
    title_TitleObjectsCreate_4ecbc0((void *)&D_004F1A90, (void *)&D_004F1A30);
    D_00484298 = 0;
}
