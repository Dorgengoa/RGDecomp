#pragma opt_lifetimes off
#include "types.h"

typedef struct Pt {
    f32 x;
    f32 y;
    s32 z;
    s32 w;
} Pt;

typedef struct UV {
    s16 u;
    s16 v;
} UV;

typedef struct Rect {
    u8 pad0[4];
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 du;
    s16 dv;
} Rect;

f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetAntialias_13e390(s32, s32);
void GsPktSetGouraud_13e3b0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetUseUV_13e3e0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetXYZf_13f060(s32, f32, f32, f32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void DrawListEndPrim_141a20(s32);
s32 DrawListBeginPrim_141b00(s32);
s32 NameTableFindByName_159fb0(s32, void *, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
extern u8 D_004614B0[];
extern const f32 D_0047D1DC __attribute__((section(".sdata")));
extern f32 D_0047D490;
extern f32 D_0047D494;
extern const f32 D_004824E8 __attribute__((section(".sdata")));

s32 ItemSpriteSpinDrawCb_2b3bb0(s32 arg0, Rect *rc, s32 x, s32 y) {
    Pt pts[4];
    s32 j;
    UV uv[4];
    f32 t;
    s32 res;
    s32 ctx;
    s32 gs;
    s32 tex;
    f32 hx;
    f32 hy;
    s32 u;
    s32 v;
    s32 du;
    s32 dv;
    f32 sn;
    f32 cs;
    f32 k;
    s32 i;
    Pt *p;
    f32 px;
    f32 py;
    u8 *q;
    u32 n;

    t = D_004824E8 - D_0047D1DC;
    *(f32 *)&D_004824E8 = t;
    if (t <= 0.0f) {
        *(f32 *)&D_004824E8 = D_0047D490;
    }
    res = GetDrawCtxNameTable_15de40();
    ctx = GetDrawCtx_15de80();
    gs = DrawListBeginPrim_141b00(ctx);
    GsPktSetBlendMode_13e4f0(gs, 1);
    GsPktSetAlphaBlend_13e500(gs, 1);
    GsPktSetAntialias_13e390(gs, 0);
    GsPktEnableAlphaTest_13e4d0(gs, 1);
    GsPktEnableZTest_13e460(gs, 0);
    GsPktSetTextured_13e400(gs, 1);
    GsPktSetUseUV_13e3e0(gs, 1);
    GsPktSetOriginMode_13e2f0(gs, 0);
    GsPktSetTexFilter_13e3d0(gs, 0);
    GsPktSetZWriteMask_13e430(gs, 1);
    GsPktSetGouraud_13e3b0(gs, 0);
    tex = NameTableFindByName_159fb0(res, D_004614B0, 0x32D);
    GsPktOpenPrim_13f730(gs, 4);
    GsPktSetTexture_13ec00(gs, tex);
    hx = (f32)rc->w / 2.0f;
    u = rc->u;
    v = rc->v;
    du = rc->du;
    dv = rc->dv;
    hy = (f32)rc->h / 2.0f;
    sn = Sinf_128fd0(*(f32 *)&D_004824E8);
    cs = Cosf_128d30(*(f32 *)&D_004824E8);
    pts[0].x = -hx;
    pts[0].y = -hy;
    pts[0].z = 0;
    pts[0].w = 0;
    pts[1].x = hx;
    pts[1].y = -hy;
    pts[1].z = 0;
    pts[1].w = 0;
    pts[2].x = -hx;
    pts[2].y = hy;
    pts[2].z = 0;
    pts[2].w = 0;
    pts[3].x = hx;
    pts[3].y = hy;
    pts[3].z = 0;
    pts[3].w = 0;
    for (j = 0; j < 4; j++) {
        p = &pts[j];
        px = p->x;
        py = p->y;
        p->x = px * cs + py * sn;
        p->y = D_0047D494 * (px * -sn + py * cs);
    }
    GsPktSetRGBAQ_13ee40(gs, 0x80, 0x80, 0x80, 0x80);
    q = (u8 *)uv;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            q++;
        } while (--n != 0);
    }
    uv[0].u = u;
    uv[0].v = v;
    uv[1].u = u + du;
    uv[1].v = v;
    uv[2].u = u;
    uv[2].v = v + dv;
    uv[3].u = u + du;
    uv[3].v = v + dv;
    for (i = 0; i < 4; i++) {
        GsPktSetUV_13ed60(gs, uv[i].u, uv[i].v);
        GsPktSetXYZf_13f060(gs, (f32)x + pts[i].x, (f32)y + pts[i].y, 0.0f);
    }
    GsPktClose_13f5b0(gs);
    DrawListEndPrim_141a20(ctx);
    return 1;
}
