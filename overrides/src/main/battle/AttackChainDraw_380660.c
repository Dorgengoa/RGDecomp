/* rg-override: replaces game/src/main/battle/AttackChainDraw_380660.c sha256 ced6af81cf0b278b56615dda749b1c8ba92561267c95ee90125a60b6ccf2ed59
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
/* rgp:protos */
#define RGP_SELF_AttackChainDraw_380660 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern float rg_aspect_d(void);
extern float rg_hud_xscale(void);
#pragma divbyzerocheck on

typedef struct { f32 x, y, z, w; } V4;
typedef struct { s32 v[4]; } Rect;
typedef struct { V4 c[2]; } Cols;

typedef struct Pt {
    f32 m0;
    u8 pad4[4];
    u16 m8;
    u16 mA;
    f32 mC;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    u8 pad20[4];
    V4 pts[32];
} Pt;

typedef struct Obj {
    Pt *m0;
    s16 m4;
    s16 pad6;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 mE;
    s32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 sqrtf(f32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004540D0[];
extern V4 D_00454090[];
extern Rect D_00463BB0[];
extern Rect D_00463C30;
extern Rect D_00463C40;
extern Rect D_00463C50;
extern Rect D_00463C60;
extern Rect D_00463C70;
extern Rect D_00463C80;
extern Rect D_00463C90;
extern Rect D_00463CA0;
extern Rect D_00463CB0;
extern Rect D_00463CC0;
extern Rect D_00463CD0;
extern Rect D_00463CE0;
extern Rect D_00463CF0;
extern Rect D_00463D00;
extern Rect D_00463D10;
extern s32 D_00463D18;
extern s32 D_00463D1C;
extern Rect D_00463D20;
extern s32 D_00463D28;
extern s32 D_00463D2C;
extern Rect D_00463DD0;
extern s32 D_00463DE0[];
extern s32 D_00463DF0[];
extern s32 D_00463E00[];
extern f32 D_0047D278;
extern f32 D_0047D288;
extern f32 D_0047D5D0;
extern f32 D_0047D7C4;
extern f32 D_0047D7CC;
extern f32 D_0047D7E0;
extern f32 D_0047D7E8;
extern f32 D_0047D7EC;
extern f32 D_0047D7F0;
extern f32 D_0047D7F4;
extern f32 D_0047D7F8;
extern f32 D_0047D7FC;
extern f32 D_0047D800;
extern f32 D_0047D804;
extern V4 D_0047FB80 __attribute__((section(".sdata")));
extern V4 D_0047FB90 __attribute__((section(".sdata")));
extern V4 D_0047FBA0 __attribute__((section(".sdata")));
extern V4 D_0047FBB0 __attribute__((section(".sdata")));

void AttackChainDraw_380660(Obj *o)
{
    Cols cols __attribute__((aligned(16)));
    f32 fa[4] __attribute__((aligned(16)));
    Pt *p2;
    s32 i2;
    s32 h;
    s32 w;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 g;
    s32 res;
    Pt *p;
    Rect *img;
    V4 *sel;
    s32 i;
    s16 kind;
    s32 j;
    s32 n;
    s32 g2;
    s32 v;
    s32 dg;
    s32 tot;
    s32 cnt;
    u8 cur;
    s32 near;
    Pt *p3;
    s32 v3;
    s32 j3;
    f32 cx;
    f32 cy;
    f32 sc;
    f32 k16;
    f32 k8;
    f32 d;
    f32 dd;
    f32 tt;
    f32 u;
    f32 s1;
    f32 s2;
    f32 m;
    f32 ox;
    f32 oy;
    f32 sz;
    f32 al;
    f32 a2;
    f32 r;
    f32 t;
    f32 e;
    f32 off;
    f32 neg;
    f32 x;
    f32 y;
    f32 dx;
    f32 fr;
    f32 q;
    f32 mx;
    f32 my;

    if (o->m0 == NULL) {
        return;
    }
    if (((short)AttackChainGetPhase_382eb0(o)) == 0) {
        return;
    }
    if (((short)AttackChainGetPhase_382eb0(o)) == 1) {
        return;
    }
    h = GetDrawCtx_15de80();
    cx = 0.5f * DrawEnvGetWidth_1451e0(h);
    cy = 0.5f * DrawEnvGetHeight_1451d0(h);
    if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
        sc = rg_hud_xscale();
    } else {
        sc = 1.0f;
    }
    w = GetDrawCtxNameTable_15de40();
    t1 = ((s32)NameTableFindByName_159fb0(w, D_00463DE0, 0x32D));
    t2 = ((s32)NameTableFindByName_159fb0(w, D_00463DF0, 0x32D));
    if (t1 != 0 && t2 != 0) {
        DrawListAddTexLoad_1418c0(h, 0x32D, 1.0f);
        g = ((s32)DrawListBeginPrim_141b00(h));
        GsPktSetTextured_13e400(g, 1);
        GsPktSetOriginMode_13e2f0(g, 0);
        GsPktSetUseUV_13e3e0(g, 1);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktSetBlendMode_13e4f0(g, 1);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktSetZWriteMask_13e430(g, 0);
        GsPktEnableZTest_13e460(g, 0);
        GsPktSetTexFilter_13e3d0(g, 1);
        GsPktOpenPrim_13f730(g, 0);
        GsPktSetRGBAQ_13ee40(g, 0, 0, 0, 0x80);
        GsPktSetXYZf_13f060(g, 0.0f, 0.0f, -1.0f);
        GsPktClose_13f5b0(g);
        k16 = 16.0f * sc;
        k8 = 8.0f * sc;
        cols = *(Cols *)D_004540D0;
        if (((short)AttackChainGetPhase_382eb0(o)) == 2) {
            for (i = 0, p = o->m0; i < o->m4; i++, p++) {
                kind = -1;
                if (p->m8 == 0x20) {
                    kind = 0;
                }
                if (p->m8 == 0x40) {
                    kind = 1;
                }
                if (p->m8 == 0x10) {
                    kind = 2;
                }
                if (p->m8 == 0x80) {
                    kind = 3;
                }
                if (i < o->mA) {
                    if (p->m18 <= 0.0f) {
                        continue;
                    }
                    d = o->m18 - p->m18;
                    if (0.0f == d) {
                        continue;
                    }
                    if (d <= 10.0f) {
                        tt = 1.0f - d / 10.0f;
                        *(V4 *)fa = D_0047FB90;
                        {
                            f32 fb[4] __attribute__((aligned(16))) = {0};
                            fb[0] = 2.0f * tt;
                            fb[1] = D_0047D288 * tt;
                            fb[2] = D_0047D7E0 * tt;
                            fb[3] = D_0047D5D0 * tt;
                            GsPktSetBlendMode_13e4f0(g, 1);
                            u = tt * tt;
                            u = 1.0f - u;
                            s1 = 32.0f + 16.0f * u;
                            s2 = 32.0f + 96.0f * u;
                            GsPktOpenPrim_13f730(g, 6);
                            GsPktSetTexture_13ec00(g, t1);
                            GsDrawSpriteCenteredAlpha_383480(g, &D_00463BB0[kind], p->mC, p->m10, s1, s1, tt);
                            GsDrawSpriteCenteredAlpha_383480(g, &D_00463CC0, p->mC, p->m10, s2, s2, tt);
                            GsPktClose_13f5b0(g);
                            j = 0;
                            m = 4.0f + (f32)(8.0f * u);
                            tt = k16 + sc * m;
                            u = D_0047D7E8 + D_0047D7EC * m;
                            for (; j < 4; j++) {
                                sz = 24.0f * fa[j];
                                cols.c[1].w = 128.0f * fb[j];
                                GsPktOpenPrim_13f730(g, 6);
                                GsPktSetTexture_13ec00(g, t1);
                                GsDrawSpriteCentered_3834d0(g, &D_00463C70, &cols.c[1], p->mC - tt, p->m10 - u, sz, sz);
                                GsDrawSpriteCentered_3834d0(g, &D_00463C80, &cols.c[1], p->mC + tt, p->m10 - u, sz, sz);
                                GsDrawSpriteCentered_3834d0(g, &D_00463C90, &cols.c[1], p->mC - tt, p->m10 + u, sz, sz);
                                GsDrawSpriteCentered_3834d0(g, &D_00463CA0, &cols.c[1], p->mC + tt, p->m10 + u, sz, sz);
                                GsPktClose_13f5b0(g);
                                GsPktSetBlendMode_13e4f0(g, 2);
                            }
                            GsPktSetBlendMode_13e4f0(g, 1);
                        }
                    }
                    if (d <= 20.0f) {
                        V4 *pt;
                        V4 c __attribute__((aligned(16)));
                        tt = 1.0f - d / 20.0f;
                        GsPktSetBlendMode_13e4f0(g, 2);
                        GsPktOpenPrim_13f730(g, 6);
                        GsPktSetTexture_13ec00(g, t1);
                        pt = p->pts;
                        u = 1.0f - tt * tt;
                        for (j = 0; j < 32; j++, pt++) {
                            VecCopy_1cbe30(&c, &D_00454090[j % 4]);
                            c.w = 128.0f * sqrtf(tt);
                            GsDrawSpriteCentered_3834d0(g, &D_00463CD0, &c, p->mC + sc * (pt->x + pt->z * u), p->m10 + D_0047D7EC * (pt->y + pt->w * u), 8.0f, 8.0f);
                        }
                        GsPktClose_13f5b0(g);
                        GsPktSetBlendMode_13e4f0(g, 1);
                    }
                    continue;
                }
                dd = p->m0 - o->m1C;
                if (45.0f <= dd) {
                    continue;
                }
                cur = 1;
                if (o->mA != i) {
                    cur = 0;
                }
                if (cur) {
                    al = 1.0f;
                } else {
                    al = 0.5f;
                }
                if (((short)AttackChainGetPhase_382eb0(o)) >= 4) {
                    cols.c[0].w = 64.0f;
                    GsPktOpenPrim_13f730(g, 6);
                    GsPktSetTexture_13ec00(g, t1);
                    GsDrawSpriteCentered_3834d0(g, &D_00463C70, &cols.c[0], p->mC - k16, p->m10 - D_0047D7E8, 24.0f, 24.0f);
                    GsDrawSpriteCentered_3834d0(g, &D_00463C80, &cols.c[0], p->mC + k16, p->m10 - D_0047D7E8, 24.0f, 24.0f);
                    GsDrawSpriteCentered_3834d0(g, &D_00463C90, &cols.c[0], p->mC - k16, p->m10 + D_0047D7E8, 24.0f, 24.0f);
                    GsDrawSpriteCentered_3834d0(g, &D_00463CA0, &cols.c[0], p->mC + k16, p->m10 + D_0047D7E8, 24.0f, 24.0f);
                    GsDrawSpriteCenteredAlpha_383480(g, &D_00463BB0[kind], p->mC, p->m10, 32.0f, 32.0f, 0.5f);
                    GsPktClose_13f5b0(g);
                    res = 1;
                } else {
                    res = 4;
                    if (dd >= 30.0f) {
                        GsPktOpenPrim_13f730(g, 6);
                        GsPktSetTexture_13ec00(g, t1);
                        j = 0;
                        m = (2.0f * (dd - 30.0f)) / 15.0f;
                        sz = 128.0f * al;
                        for (; j < 2; j++) {
                            t = m - (f32)j;
                            if (t < 0.0f) {
                                t = 0.0f;
                            }
                            if (!(t <= 1.0f)) {
                                t -= 1.0f;
                            }
                            r = 30.0f * (1.0f + 2.0f * t);
                            q = 20.0f + (f32)(128.0f * t);
                            cols.c[0].w = sz;
                            tt = sc * q;
                            u = D_0047D7EC * q;
                            GsDrawSpriteCentered_3834d0(g, &D_00463C30, &cols.c[0], p->mC - tt, p->m10 - u, r, r);
                            GsDrawSpriteCentered_3834d0(g, &D_00463C40, &cols.c[0], p->mC + tt, p->m10 - u, r, r);
                            GsDrawSpriteCentered_3834d0(g, &D_00463C50, &cols.c[0], p->mC - tt, p->m10 + u, r, r);
                            GsDrawSpriteCentered_3834d0(g, &D_00463C60, &cols.c[0], p->mC + tt, p->m10 + u, r, r);
                        }
                        GsPktClose_13f5b0(g);
                        continue;
                    }
                        a2 = 128.0f * al;
                        cols.c[1].w = a2;
                        cols.c[0].w = a2;
                        near = dd <= 8.0f;
                        sel = &cols.c[(u8)near];
                        GsPktOpenPrim_13f730(g, 6);
                        GsPktSetTexture_13ec00(g, t1);
                        GsDrawSpriteCentered_3834d0(g, &D_00463C70, sel, p->mC - k16, p->m10 - D_0047D7E8, 24.0f, 24.0f);
                        GsDrawSpriteCentered_3834d0(g, &D_00463C80, sel, p->mC + k16, p->m10 - D_0047D7E8, 24.0f, 24.0f);
                        GsDrawSpriteCentered_3834d0(g, &D_00463C90, sel, p->mC - k16, p->m10 + D_0047D7E8, 24.0f, 24.0f);
                        GsDrawSpriteCentered_3834d0(g, &D_00463CA0, sel, p->mC + k16, p->m10 + D_0047D7E8, 24.0f, 24.0f);
                        if (cur && dd <= 8.0f) {
                            e = -8.0f + (f32)(10.0f + dd);
                            t = (e - 10.0f * Floorf_128e30(e / 10.0f)) / 10.0f;
                            cols.c[1].w = 128.0f * (0.75f * (1.0f - t) * al);
                            ox = k16 + t * k8;
                            oy = D_0047D7E8 + t * D_0047D7F0;
                            GsDrawSpriteCentered_3834d0(g, &D_00463C70, &cols.c[1], p->mC - ox, p->m10 - oy, 24.0f, 24.0f);
                            GsDrawSpriteCentered_3834d0(g, &D_00463C80, &cols.c[1], p->mC + ox, p->m10 - oy, 24.0f, 24.0f);
                            GsDrawSpriteCentered_3834d0(g, &D_00463C90, &cols.c[1], p->mC - ox, p->m10 + oy, 24.0f, 24.0f);
                            GsDrawSpriteCentered_3834d0(g, &D_00463CA0, &cols.c[1], p->mC + ox, p->m10 + oy, 24.0f, 24.0f);
                        }
                        GsPktClose_13f5b0(g);
                        if (dd <= 45.0f && dd <= 8.0f) {
                            cols.c[1].w = a2;
                            DrawRotatedQuad_383c70(g, &D_00463CB0, t1, &cols.c[1], p->mC, p->m10 - D_0047D7F4, 58.0f, 20.0f, 0.0f);
                            r = (dd - -8.0f) / 16.0f;
                            {
                                f32 ta[4] __attribute__((aligned(16)));
                                *(V4 *)ta = D_0047FBA0;
                                {
                                    f32 tb[4] __attribute__((aligned(16))) = {0};
                                    tb[0] = 2.0f * r;
                                    tb[1] = D_0047D7C4 * r;
                                    tb[2] = D_0047D5D0 * r;
                                    tb[3] = D_0047D7CC * r;
                                    GsPktSetBlendMode_13e4f0(g, 1);
                                    j = 0;
                                    img = &D_00463BB0[kind];
                                    for (; j < 4; j++) {
                                        cols.c[1].w = al * (128.0f * tb[j]);
                                        DrawRotatedQuadAlpha_383c20(g, img, t1, p->mC, p->m10, 32.0f * ta[j], 32.0f * ta[j], al * tb[j], 0.0f);
                                        GsPktSetBlendMode_13e4f0(g, 2);
                                    }
                                    GsPktSetBlendMode_13e4f0(g, 1);
                                }
                            }
                        }
                }
                if (dd <= 30.0f) {
                    if (((short)AttackChainGetPhase_382eb0(o)) == 2) {
                        n = 0x20;
                    } else {
                        n = 1;
                    }
                    if (kind == 1) {
                        off = D_0047D7F8;
                    } else {
                        off = 0.0f;
                    }
                    GsPktSetBlendMode_13e4f0(g, 2);
                    img = &D_00463BB0[kind + 4];
                    for (; n >= 0; n--) {
                        e = dd + 0.125f * (f32)n;
                        if (n == 0) {
                            GsPktSetBlendMode_13e4f0(g, 1);
                        }
                        if (e <= 0.0f) {
                            continue;
                        }
                        neg = e / 30.0f;
                        if (!(neg < 0.5f)) {
                            neg = 0.25f + neg * neg;
                        }
                        neg = neg * D_0047D278;
                        q = D_0047D7FC * neg;
                        a2 = -neg;
                        x = 160.0f * (a2 * Cosf_128d30(AngleWrap_1cbf30((p->m14 - q) - D_0047D7F8)));
                        y = 160.0f * (a2 * Sinf_128fd0(AngleWrap_1cbf30((p->m14 - q) - D_0047D7F8)));
                        e = 1.0f - 0.984375f * neg;
                        sz = (48.0f * (1.0f + 3.0f * (neg * neg))) / e;
                        y = y / e;
                        x = x / e;
                        u = 0.25f * (1.0f - 0.5f * neg) * Powf_1291c0(D_0047D800, (f32)n);
                        if (u < 0.0f) {
                            u = 0.0f;
                        }
                        if (n == 0) {
                            u = 1.0f - 0.25f * neg;
                        }
                        DrawRotatedQuadAlpha_383c20(g, img, t1, p->mC + sc * x, p->m10 + D_0047D7EC * y, sz, sz, u,
                                     off + 2.0f * (D_0047D804 * a2));
                    }
                    GsPktSetBlendMode_13e4f0(g, 1);
                }
                if (res == 1) {
                    break;
                }
            }
        }
        x = 32.0f;
        GsPktOpenPrim_13f730(g, 6);
        GsPktSetTexture_13ec00(g, t1);
        for (i2 = 0, p2 = o->m0; i2 < o->m4; i2++, p2++) {
            kind = -1;
            if (p2->m8 == 0x20) {
                kind = 0;
            }
            if (p2->m8 == 0x40) {
                kind = 1;
            }
            if (p2->m8 == 0x10) {
                kind = 2;
            }
            if (p2->m8 == 0x80) {
                kind = 3;
            }
            if (i2 == o->mA) {
                q = 240.0f;
            } else if (o->mA < i2) {
                q = 128.0f;
            } else {
                q = 32.0f;
            }
            {
                V4 cc __attribute__((aligned(16)));
                *(V4 *)&cc = D_0047FBB0;
                cc.x = q;
                cc.y = q;
                cc.z = q;
                GsDrawSpriteCentered_3834d0(g, &D_00463BB0[kind], &cc, x, 416.0f, 24.0f, 24.0f);
            }
            if (i2 == o->mA) {
                GsDrawSpriteCenteredAlpha_383480(g, &D_00463CE0, x, 395, 22.0f, 12.0f, 1.0f);
            }
            x += 28.0f;
        }
        GsPktClose_13f5b0(g);
        GsPktOpenPrim_13f730(g, 6);
        GsPktSetTexture_13ec00(g, t2);
        if (((short)AttackChainGetPhase_382eb0(o)) != 1) {
            GsDrawSpriteAnchorBL_383860(g, &D_00463CF0, &D_0047FB80, 512.0f - 62.0f * sc, 380.0f, 128.0f, 26.0f);
        }
        if (((short)AttackChainGetPhase_382eb0(o)) != 1) {
            GsDrawSpriteAnchorBLAlpha_383810(g, &D_00463D00, 96.0f * sc, 380.0f, 128.0f, 26.0f, 1.0f);
        }
        GsPktClose_13f5b0(g);
        DrawListEndPrim_141a20(h);
    }
    t3 = ((s32)NameTableFindByName_159fb0(w, D_00463E00, 0x32B));
    if (t3 == 0) {
        return;
    }
    DrawListAddTexLoad_1418c0(h, 0x32B, 1.0f);
    g2 = ((s32)DrawListBeginPrim_141b00(h));
    GsPktSetTextured_13e400(g2, 1);
    GsPktSetOriginMode_13e2f0(g2, 0);
    GsPktSetUseUV_13e3e0(g2, 1);
    GsPktSetAlphaBlend_13e500(g2, 1);
    GsPktSetBlendMode_13e4f0(g2, 1);
    GsPktEnableAlphaTest_13e4d0(g2, 1);
    GsPktSetZWriteMask_13e430(g2, 0);
    GsPktEnableZTest_13e460(g2, 0);
    GsPktSetTexFilter_13e3d0(g2, 1);
    GsPktOpenPrim_13f730(g2, 0);
    GsPktSetRGBAQ_13ee40(g2, 0, 0, 0, 0x80);
    GsPktSetXYZf_13f060(g2, 0.0f, 0.0f, -1.0f);
    GsPktClose_13f5b0(g2);
    GsPktOpenPrim_13f730(g2, 6);
    GsPktSetTexture_13ec00(g2, t3);
    if (((short)AttackChainGetPhase_382eb0(o)) != 1) {
        cnt = o->mA;
        fr = 0.0f;
        if (cnt > 0) {
            fr = 1.0f - (o->m18 - ((Pt *)((u8 *)o->m0 + cnt * sizeof(Pt)))[-1].m18) / 8.0f;
            if (!(fr <= 1.0f)) {
                fr = 1.0f;
            }
            if (!(fr <= 0.0f)) {
                cnt--;
            }
        }
        dx = 15.0f * sc;
        x = 512.0f - 62.0f * sc;
        GsDrawSpriteAnchorBR_3836a0(g2, &D_00463BB0[GameFlowGetChainNo_285f20() + 0x18], &D_0047FB80, x, 376.0f, 20.0f, 26.0f);
        x -= dx;
        GsDrawSpriteAnchorBR_3836a0(g2, &D_00463DD0, &D_0047FB80, x, 376.0f, 20.0f, 26.0f);
        x -= dx;
        GsDrawSpriteAnchorBR_3836a0(g2, &D_00463BB0[cnt + 0x18], &D_0047FB80, x, 376.0f, 20.0f, 26.0f);
        if (!(fr <= 0.0f)) {
            t = 1.0f - fr;
            t = 1.0f - t * t;
            e = 1.0f + 3.0f * t;
            GsDrawSpriteAnchorBR_3836a0(g2, &D_00463BB0[o->mA + 0x18], &D_0047FB80, x, 376.0f - D_0047D7EC * (48.0f * (fr * fr)), 20.0f * e, 26.0f * e);
        }
    }
    if (((short)AttackChainGetPhase_382eb0(o)) != 1) {
        tot = o->m10;
        if (o->mC > 0) {
            for (j3 = 0, p3 = o->m0; j3 < o->mC; j3++, p3++) {
                d = o->m18 - p3->m1C;
                if (d < 0.0f) {
                    continue;
                }
                if (d <= 24.0f) {
                    mx = 96.0f + p3->mC;
                    mx = 0.5f * (f32)mx;
                    my = 0.5f * (376.0f + p3->m10) - 128.0f;
                    if (d <= 8.0f) {
                        t = d / 8.0f;
                        u = t * t;
                        x = p3->mC + u * (mx - p3->mC);
                        y = p3->m10 + u * (my - p3->m10);
                        e = 1.0f + 1.5f * t;
                    } else {
                        t = (d - 8.0f) / 16.0f;
                        x = 96.0f + (1.0f - t) * (mx - 96.0f);
                        u = t * t;
                        u = 1.0f - u;
                        y = 376.0f + u * (my - 376.0f);
                        e = 1.0f + 1.5f * u;
                    }
                    v3 = p3->mA;
                    tot -= v3;
                    s1 = 26.0f * e;
                    s2 = 20.0f * e;
                    dx = sc * (15.0f * e);
                    do {
                        dg = v3 % 10;
                        GsDrawSpriteAnchorBRAlpha_383650(g2, &D_00463BB0[dg + 0x18], x, y, s2, s1, 1.0f);
                        x -= dx;
                        v3 = (v3 - dg) / 10;
                    } while (v3 > 0);
                }
            }
        }
        x = 96.0f;
        dx = 15.0f * sc;
        do {
            dg = tot % 10;
            GsDrawSpriteAnchorBRAlpha_383650(g2, &D_00463BB0[dg + 0x18], x, 376.0f, 20.0f, 26.0f, 1.0f);
            x -= dx;
            tot = (tot - dg) / 10;
        } while (tot > 0);
    }
    if (((short)AttackChainGetPhase_382eb0(o)) >= 4) {
        if (!(o->m20 < 0.0f)) {
            t = (o->m18 - o->m20) / 15.0f;
            if (!(t <= 1.0f)) {
                t = 1.0f;
            }
            t = t - 0.5f;
            t = 2.0f * (1.0f + 0.5f * (1.0f - 4.0f * (t * t)));
            GsDrawSpriteCenteredAlpha_383480(g2, &D_00463D20, cx, 56.0f + cy, t * (f32)D_00463D20.v[2], t * (f32)D_00463D20.v[3], 1.0f);
        }
    } else if (((short)AttackChainGetPhase_382eb0(o)) == 3) {
        if (!(o->m24 < 0.0f)) {
            t = (o->m18 - o->m24) / 15.0f;
            if (!(t <= 1.0f)) {
                t = 1.0f;
            }
            t = t - 0.5f;
            t = 2.0f * (1.0f + 0.5f * (1.0f - 4.0f * (t * t)));
            GsDrawSpriteCenteredAlpha_383480(g2, &D_00463D10, cx, 56.0f + cy, t * (f32)D_00463D10.v[2], t * (f32)D_00463D10.v[3], 1.0f);
        }
    }
    GsPktClose_13f5b0(g2);
    DrawListEndPrim_141a20(h);
}
