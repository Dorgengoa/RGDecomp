#include "types.h"
typedef unsigned __int128 u128;
#pragma divbyzerocheck on

typedef struct {
    f32 x, y, z, w;
} Vec4 __attribute__((aligned(16)));

typedef struct {
    Vec4 mn;
    Vec4 mx;
} Box;

typedef struct {
    s32 a, b, c, d;
} I4;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    u8 pad14[0xC];
    Box box;            /* 0x20 */
    s32 f40;
} Ent;

typedef struct {
    u8 pad0[0x40];
    f32 f40;
} Cam;

typedef struct {
    u8 pad0[0xF20];
    Cam *cam;
} Mgr;

typedef struct {
    s16 f0;
    s16 w;
    s16 h;
    u8 pad6[0x34];
    u16 b0 : 4;
    u16 lod : 6;
    u16 b10 : 6;
    u8 pad3C[0x34];
} Tex;

typedef struct {
    u8 f0 : 2;
    u8 f2 : 2;
    u8 f4 : 2;
    u8 f6 : 2;
    u8 pad1[3];
    u8 alpha;
} Blend;

typedef struct {
    u8 pad0[0x20];
    Tex *tex;           /* 0x20 */
    f32 f24;
    s32 f28;
    u8 pad2C[4];
    u8 f30[0xC];
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    u8 pad4C[4];
    s32 f50;
    s32 f54;
    u8 pad58[4];
    s32 f5C;
    s32 f60;
    s32 f64;
} Obj;

void BBoxUnion_13dea0(Box *, Box *);
void VecMin_13df90(Vec4 *, Vec4 *, Vec4 *);
void VecMax_13dfe0(Vec4 *, Vec4 *, Vec4 *);
void VecFtoi4_13e2e0(s32 *, Vec4 *);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetFrameMask_13e420(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetAlphaReg_13e4e0(s32, Blend *);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetTexture_13ec00(s32, Tex *);
void GsPktSetTexa_13eca0(s32, u64);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void GsPktCommit_13f190(s32);
void GsPktRawWriteEndStubMaybe_13f1e0(s32);
void GsPktAddDmaCallTag_13f1f0(s32, u8 *);
void GsPktRawWriteBeginStubMaybe_13f250(s32);
void GsPktOpen_13f4a0(s32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktDisableTests_13f9e0(s32);
void DrawCtxCallTagCacheClear_13fd40(Mgr *);
void DrawListEndPrim_141a20(Mgr *);
s32 DrawListBeginPrim_141b00(Mgr *);
void DrawListAddEnv_1421d0(Mgr *);
void DrawEnvPop_144800(Mgr *);
void DrawEnvPush_144830(Mgr *);
void DrawEnvGetFrameTexDesc_144cc0(Mgr *, Tex *);
void DrawEnvSetFrameFromDesc_144fe0(Mgr *, Tex *, s32);
void DrawEnvGetCenteredRect_145060(Mgr *, s32 *);
void DrawCtxClearClipRangeSetMaybe_148030(Mgr *);
void DrawListResetClipRangeMaybe_148040(Mgr *);
s32 ModelEmitDrawPacketsMaybe_14ec20(s32, Mgr *, Ent *);
s32 ModelPrepareDrawMaybe_14f760(s32, Mgr *, Ent *);
void NameTableNodeCtor_15ae50(Tex *);
s32 ProjectToScreen_15d340(s32 *, u8 *);
Mgr *GetDrawCtx_15de80(void);
void ScreenTexOverlayDrawMultiMaybe_16a510(s32, I4 *, Tex *, s32 *, s32, s32 *, s32);
void ScreenTexOverlayDrawSingleMaybe_16a780(s32, I4 *, Tex *, I4 *, s32, s32, s32, s32);
f32 ModelObjGetCBlurAlphaMaybe_1ad5a0(s32);
Tex *ModelObjGetCBlurTexMaybe_1ad5b0(s32);
Ent *ObjGetPart_1adf30(s32, s32);

extern u8 D_00445C60[];
extern f32 D_0047D244;
extern f32 D_0047D248;
extern f32 D_0047D24C;
extern f32 D_0047DF50;
extern f32 D_0047DF54;
extern f32 D_0047DF60[4];
extern s32 D_0047DF70;
typedef struct { s32 v[4]; } S4 __attribute__((aligned(16)));
extern s32 D_0047DF80[4];



static inline void Sh(s32 c, s32 lx, s32 ly, s32 hx, s32 hy, Tex *tex, s32 *col, s32 mode, s32 *ofs) {
    I4 r;
    r.a = ly;
    r.b = lx;
    r.c = hy;
    r.d = hx;
    ScreenTexOverlayDrawMultiMaybe_16a510(c, &r, tex, col, mode, ofs, 0);
}

static inline void Qd(s32 c, s32 lx, s32 ly, s32 hx, s32 hy, Tex *tex, s32 *rgba, s32 a) {
    I4 r;
    r.a = ly;
    r.b = lx;
    r.c = hy;
    r.d = hx;
    ScreenTexOverlayDrawSingleMaybe_16a780(c, &r, tex, (I4 *)rgba, 0, 0, a, 0);
}

static inline s32 All2(s32 id, Mgr *mgr, Ent **list, s32 *flag, s32 n, s32 w54) {
    s32 *pf;
    s32 save40;
    s32 total;
    s32 i;
    Ent *e;

    total = 0;
    for (i = 0; i < n; i++) {
        e = list[i];
        save40 = e->f40;
        pf = &flag[i];
        e->f40 = w54;
        *pf = ModelPrepareDrawMaybe_14f760(id, mgr, e);
        if (*pf != 0) {
            total += ModelEmitDrawPacketsMaybe_14ec20(id, mgr, e);
        }
        e->f40 = save40;
    }
    return total;
}

#define ZERO(v, n) { u8 *p_ = (u8 *)&(v); u32 n_ = (n); if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }

s32 ModelDrawOffscreenCompositeMaybe_16aac0(Obj *o, s32 id, f32 scale, f32 alpha) {
    s32 ofs[2];
    Blend bl;
    s32 flag[16];
    Ent *list[16];
    Box box;
    s32 vp[4];
    Vec4 vmin;
    Vec4 vmax;
    s32 hi[4];
    s32 lo[4];
    Tex tex;
    s32 col[4];
    s32 buf[4];
    Mgr *mgr;
    Cam *cam;
    Ent *e;
    Ent **pl;
    Tex *sh;
    s32 *pf;
    s32 *pf2;
    s32 *p1;
    s32 s40b;
    s32 w54;
    s32 total;
    s32 i;
    s32 any;
    s32 y0;
    s32 save40;
    s32 save10;
    s32 x0;
    s32 x1;
    s32 y1;
    s32 n;
    s32 t;
    s32 lx;
    s32 ly;
    s32 hx;
    s32 hy;
    s32 c;
    s32 mode;
    s32 ox;
    s32 oy;
    s32 old;
    s32 a;
    s32 hw;
    s32 hh;
    s32 tw;
    s32 th;
    s32 w;
    s32 h;
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    s32 k;
    f32 f4;
    f32 f2;
    f32 f0;
    f32 fade;

    if (o->f5C == 0) return 0;
    w54 = o->f54;
    if (o->f50 == 0) return 0;
    mgr = GetDrawCtx_15de80();
    cam = mgr->cam;
    for (n = 0; n < 16; n++) {
        pl = &list[n];
        *pl = ObjGetPart_1adf30(id, n - 1);
        if (*pl == 0) break;
    }
    if (!(scale <= 1.0f)) scale = 1.0f;
    scale = scale * scale;
    if (o->f24 < 0.0f || o->tex == 0) {
        return All2(id, mgr, list, flag, n, w54);
    }
    if (alpha < 1.0f) w54 = 0;
    any = 0;
    for (i = 0; i < n; i++) {
        e = list[i];
        s40b = e->f40;
        e->f40 = w54;
        save10 = e->f10;
        e->f10 = 1;
        pf2 = &flag[i];
        *pf2 = ModelPrepareDrawMaybe_14f760(id, mgr, e);
        if (*pf2 != 0) {
            if (any == 0) {
                any = 1;
                *(u128 *)&box.mn = *(u128 *)&e->box.mn;
                *(u128 *)&box.mx = *(u128 *)&e->box.mx;
            } else {
                BBoxUnion_13dea0(&box, (Box *)((s32)e + 0x20));
            }
        }
        e->f10 = save10;
        e->f40 = s40b;
    }
    if (any == 0) return 0;
    f0 = cam->f40;
    f4 = D_0047DF50 * (o->f24 * scale);
    f2 = f4 * f0;
    total = 0;
    f0 = 0.5f * (f2 + f4);
    fade = 1.0f;
    if (f0 < fade) fade = f0;
    oy = (s32)(16.0f * f4);
    ox = (s32)(16.0f * f2);
    DrawEnvGetCenteredRect_145060(mgr, vp);
    ZERO(vmin, 16);
    vmin.x = (f32)vp[3];
    vmin.y = (f32)vp[2];
    ZERO(vmax, 16);
    vmax.x = (f32)vp[1];
    vmax.y = (f32)vp[0];
    VecMax_13dfe0(&box.mx, &box.mx, &vmax);
    VecMin_13df90(&box.mn, &box.mn, &vmin);
    VecFtoi4_13e2e0(hi, &box.mn);
    VecFtoi4_13e2e0(lo, &box.mx);
    x0 = lo[0] - 0x80;
    x1 = hi[0] + 0x80;
    y0 = lo[1] - 0x80;
    y1 = hi[1] + 0x80;
    if (x0 < vp[1] * 16) x0 = vp[1] * 16;
    if (y0 < vp[0] * 16) y0 = vp[0] * 16;
    if (vp[3] * 16 < x1) x1 = vp[3] * 16;
    if (vp[2] * 16 < y1) y1 = vp[2] * 16;
    DrawEnvPush_144830(mgr);
    DrawEnvSetFrameFromDesc_144fe0(mgr, o->tex, 0);
    DrawListAddEnv_1421d0(mgr);
    c = DrawListBeginPrim_141b00(mgr);
    GsPktSetOriginMode_13e2f0(c, 2);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktEnableAlphaTest_13e4d0(c, 0);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexa_13eca0(c, 0x8080 | ((u64)0x80 << 32));
    GsPktSetRGBAQ_13ee40(c, 0, 0, 0, 0);
    for (x0 -= 16; x0 < x1 + 16; x0 += 0x200) {
        GsPktSetXYZ_13ef10(c, x0, y0 - 16, 0);
        t = x0 + 0x200;
        if (x1 + 16 < t) t = x1 + 16;
        GsPktSetXYZ_13ef10(c, t, y1 + 16, 0);
    }
    GsPktClose_13f5b0(c);
    GsPktOpenPrim_13f730(c, 6);
    GsPktSetTexa_13eca0(c, 0x8080 | ((u64)0x80 << 32));
    GsPktClose_13f5b0(c);
    DrawListEndPrim_141a20(mgr);
    DrawListResetClipRangeMaybe_148040(mgr);
    for (i = 0; i < n; i++) {
        e = list[i];
        if (flag[i] != 0) {
            save40 = e->f40;
            e->f40 = w54;
            total += ModelEmitDrawPacketsMaybe_14ec20(id, mgr, e);
            e->f40 = save40;
        }
    }
    DrawCtxClearClipRangeSetMaybe_148030(mgr);
    lx = lo[0];
    hx = hi[0];
    ly = lo[1];
    hy = hi[1];
    NameTableNodeCtor_15ae50(&tex);
    DrawEnvGetFrameTexDesc_144cc0(mgr, &tex);
    old = tex.lod;
    tex.lod = 1;
    DrawEnvPop_144800(mgr);
    DrawListAddEnv_1421d0(mgr);
    ZERO(col, 16);
    col[0] = (s32)o->f40;
    col[1] = (s32)o->f44;
    col[2] = (s32)o->f48;
    col[3] = (s32)(128.0f * fade * alpha);
    for (k = 0; k < 3; k++) {
        col[k] = (s32)((1.0f - D_0047DF54) * (f32)col[k] + D_0047DF54 * D_0047DF60[k]);
    }
    c = DrawListBeginPrim_141b00(mgr);
    GsPktOpen_13f4a0(c);
    GsPktRawWriteBeginStubMaybe_13f250(c);
    GsPktAddDmaCallTag_13f1f0(c, D_00445C60);
    GsPktRawWriteEndStubMaybe_13f1e0(c);
    GsPktCommit_13f190(c);
    GsPktSetOriginMode_13e2f0(c, 2);
    GsPktEnableZTest_13e460(c, 0);
    GsPktSetZWriteMask_13e430(c, 1);
    GsPktSetTextured_13e400(c, 1);
    GsPktSetTexFilter_13e3d0(c, 1);
    GsPktSetAlphaBlend_13e500(c, 1);
    GsPktSetBlendMode_13e4f0(c, 1);
    GsPktEnableAlphaTest_13e4d0(c, 1);
    GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
    mode = o->f64;
    if (D_0047DF70 >= 0) mode = D_0047DF70;
    if (!(o->f24 <= 0.0f) && !(alpha < 1.0f) && ox > 0 && !(fade < D_0047D244) && mode > 0) {
        ZERO(ofs, 8);
        ofs[1] = oy;
        ofs[0] = ox;
        if (mode == 2) {
            ofs[0] = ox * 3 / 4;
            ofs[1] = ofs[1] * 3 / 4;
        }
        if (mode < 2) {
            col[0] = (s32)((f32)col[0] * D_0047D248);
            col[1] = (s32)((f32)col[1] * D_0047D248);
            col[2] = (s32)((f32)col[2] * D_0047D248);
        }
        Sh(c, lx, ly, hx, hy, &tex, col, mode, ofs);
    }
    a = 0;
    if (o->f28 != 0) {
        o->f3C = 1.0f;
        if (ProjectToScreen_15d340(buf, o->f30) != 0) {
            GsPktSetZWriteMask_13e430(c, 0);
            a = buf[2];
        }
    }
    GsPktSetAlphaBlend_13e500(c, 1);
    {
        S4 rgba_ = *(S4 *)D_0047DF80;
        bl.f0 = 0;
        bl.f2 = 1;
        bl.f4 = 2;
        bl.f6 = 1;
        t = (s32)(128.0f * alpha);
        bl.alpha = t;
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 5, 1);
        if (o->f60 == 0) {
            rgba_.v[3] = t;
            GsPktSetBlendMode_13e4f0(c, 1);
            Qd(c, lx, ly, hx, hy, &tex, rgba_.v, a);
        } else if (!(o->f24 <= 0.0f)) {
            tex.lod = old;
            GsPktSetAlphaReg_13e4e0(c, &bl);
            Qd(c, lx, ly, hx, hy, &tex, rgba_.v, a);
        } else {
            rgba_.v[3] = t;
            GsPktSetBlendMode_13e4f0(c, 1);
            Qd(c, lx, ly, hx, hy, &tex, rgba_.v, a);
            rgba_.v[3] = 0x80;
            tex.lod = old;
            GsPktSetAlphaTestFunc_13e4c0(c, 5, 0x81);
            GsPktSetAlphaReg_13e4e0(c, &bl);
            Qd(c, lx, ly, hx, hy, &tex, rgba_.v, a);
        }
    }
    DrawListEndPrim_141a20(mgr);
    DrawCtxCallTagCacheClear_13fd40(mgr);
    sh = ModelObjGetCBlurTexMaybe_1ad5b0(id);
    f0 = ModelObjGetCBlurAlphaMaybe_1ad5a0(id);
    if (sh != 0 && !(f0 <= D_0047D24C)) {
        DrawEnvPush_144830(mgr);
        DrawEnvSetFrameFromDesc_144fe0(mgr, sh, 0);
        DrawListAddEnv_1421d0(mgr);
        c = DrawListBeginPrim_141b00(mgr);
        GsPktSetFrameMask_13e420(c, 2);
        GsPktDisableTests_13f9e0(c);
        GsPktSetTexFilter_13e3d0(c, 1);
        GsPktSetTextured_13e400(c, 1);
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, 1);
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 5, 1);
        GsPktOpenPrim_13f730(c, 6);
        GsPktSetTexture_13ec00(c, &tex);
        GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, (s32)(128.0f * f0));
        w = tex.w;
        tw = sh->w;
        h = tex.h;
        th = sh->h;
        hw = w / 2;
        u0 = lx / 16 + hw + 1;
        hh = h / 2;
        v0 = ly / 16 + hh + 1;
        u1 = hx / 16 + hw - 1;
        v1 = hy / 16 + hh - 1;
        GsPktSetUV_13ed60(c, u0, v0);
        GsPktSetXYZPixel_13f110(c, u0 * tw / w, v0 * th / h, 0);
        GsPktSetUV_13ed60(c, u1, v1);
        GsPktSetXYZPixel_13f110(c, u1 * tw / w, v1 * th / h, 0);
        GsPktClose_13f5b0(c);
        DrawListEndPrim_141a20(mgr);
        DrawEnvPop_144800(mgr);
        DrawListAddEnv_1421d0(mgr);
    }
    return total;
}
