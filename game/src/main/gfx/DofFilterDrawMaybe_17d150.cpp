#pragma divbyzerocheck on
#pragma opt_lifetimes off
#include "types.h"
typedef rg_u128 u128;

struct Rect {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
};

struct Ctx {
    u8 pad0[0x3C];
    bool f0 : 1;        /* +0x3C */
    bool f1 : 1;
    bool f2 : 1;
    u8 pad3d[0x33];
};

extern "C" {
s32 GetDrawCtx_15de80(void);
void NameTableNodeCtor_15ae50(Ctx *);
void DrawEnvGetFrameRect_145040(s32, Rect *);
void DrawEnvGetFrameTexDesc_144cc0(s32, Ctx *);
void NameTableCopyNode_15ad70(Ctx *, void *);
void GsTex1SetFilter_15ac10(Ctx *, s32);
void GfxBlitTexRect_141000(s32, Ctx *, Rect *, Ctx *, Rect *);
s32 DrawListBeginPrim_141b00(s32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktSetZTest_13e450(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetFrameMask_13e420(s32, s32);
s32 ProjectDepth_15d0a0(f32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetTexture_13ec00(s32, Ctx *);
void GsPktWriteAD_13ec80(s32, s32, u64);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetUVFixed_13ed90(s32, s32, s32);
void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void DrawListEndPrim_141a20(s32);
}

extern "C" void DofFilterDrawMaybe_17d150(s32 n, f32 *arr, void *obj, f32 scale)
{
    Ctx a __attribute__((aligned(16)));
    Ctx b __attribute__((aligned(16)));
    Rect r __attribute__((aligned(16)));
    Rect d __attribute__((aligned(16)));
    Rect c __attribute__((aligned(16)));
    s32 g;
    s32 h;
    s32 w;
    s32 hh;
    s32 zero;
    s32 off;
    s32 i;
    f32 yy;
    f32 dx;
    s32 t1;
    s32 t2;
    Ctx *src;
    Ctx *dst;
    s32 gw;
    s32 x0;
    s32 y0;
    s32 y1;
    s32 x1;
    s32 sel;
    s32 ww;
    f32 dy;
    f32 xx;
    s32 iy;
    s32 ix;
    s32 *pe;
    s32 dd;
    s32 jy;
    s32 jx;

    if (obj == 0) {
        return;
    }
    g = GetDrawCtx_15de80();
    NameTableNodeCtor_15ae50(&a);
    NameTableNodeCtor_15ae50(&b);
    DrawEnvGetFrameRect_145040(g, &r);
    DrawEnvGetFrameTexDesc_144cc0(g, &a);
    NameTableCopyNode_15ad70(&b, obj);
    h = r.y1 - r.y0;
    w = r.x1 - r.x0;
    hh = h << 4;
    ww = w << 4;
    d.x0 = 0;
    d.y0 = 0;
    c.y1 = h << 3;
    c.x0 = 0;
    c.x1 = w << 3;
    c.y0 = 0;
    d.y1 = hh;
    d.x1 = ww;
    dst = &b;
    src = &a;
    zero = c.x0;
    off = c.y0;
    GsTex1SetFilter_15ac10(dst, 1);
    b.f2 = false;
    for (i = 0; i < n; i++) {
        c.y0 -= 8;
        c.y1 -= 8;
        c.x0 -= 8;
        c.x1 -= 8;
        GfxBlitTexRect_141000(g, src, &d, dst, &c);
        c.y0 += 8;
        c.y1 += 8;
        c.x0 += 8;
        c.x1 += 8;
        gw = DrawListBeginPrim_141b00(g);
        GsPktSetOriginMode_13e2f0(gw, 0);
        GsPktEnableZTest_13e460(gw, 0);
        GsPktSetZWriteMask_13e430(gw, 1);
        GsPktSetZTest_13e450(gw, 0);
        GsPktSetAlphaBlend_13e500(gw, 0);
        GsPktEnableAlphaTest_13e4d0(gw, 0);
        GsPktSetTextured_13e400(gw, 0);
        GsPktEnableZTest_13e460(gw, 1);
        GsPktSetZTest_13e450(gw, 2);
        GsPktEnableAlphaTest_13e4d0(gw, 0);
        GsPktSetZWriteMask_13e430(gw, 1);
        GsPktSetTextured_13e400(gw, 1);
        GsPktSetAlphaBlend_13e500(gw, 1);
        GsPktSetFrameMask_13e420(gw, 1);
        x0 = c.x0;
        y0 = c.y0;
        x1 = c.x1;
        y1 = c.y1;
        dy = arr[i] / 10.0f;
        sel = i % 2;
        s32 e[2] = {0};
        e[0] = ProjectDepth_15d0a0(arr[i]);
        e[1] = ProjectDepth_15d0a0(dy + arr[i]);
        s32 f[2] = {0};
        f[0] = (s32)(128.0f * scale);
        f[1] = (s32)(32.0f * scale);
        GsPktOpenPrim_13f730(gw, 4);
        GsPktSetTexture_13ec00(gw, dst);
        dx = (f32)(hh - off) / 16.0f;
        dy = (f32)(y1 - y0) / 16.0f;
        yy = (f32)y0;
        xx = (f32)off;
        GsPktWriteAD_13ec80(gw, 0x3B, 0x8000000080ULL);
        GsPktSetRGBAQ_13ee40(gw, 0x80, 0x80, 0x80, f[0]);
        iy = (s32)yy;
        GsPktSetUVFixed_13ed90(gw, iy, x0 + 0x10);
        ix = (s32)xx;
        GsPktSetXYZ_13ef10(gw, ix, zero, e[0]);
        GsPktSetUVFixed_13ed90(gw, iy, x1 - 0x10);
        GsPktSetXYZ_13ef10(gw, ix, ww, e[0]);
        while (xx < (f32)hh) {
            sel = (u8)!sel;
            GsPktSetRGBAQ_13ee40(gw, 0x80, 0x80, 0x80, f[0]);
            jy = (s32)(yy + dy);
            GsPktSetUVFixed_13ed90(gw, jy, x0 + 0x10);
            pe = &e[sel];
            jx = (s32)(xx + dx);
            GsPktSetXYZ_13ef10(gw, jx, zero, *pe);
            GsPktSetUVFixed_13ed90(gw, jy, x1 - 0x10);
            GsPktSetXYZ_13ef10(gw, jx, ww, *pe);
            xx += dx;
            yy += dy;
        }
        GsPktClose_13f5b0(gw);
        DrawListEndPrim_141a20(g);
        d = c;
        dd = d.y1 - d.y0;
        c.y0 += dd;
        c.y1 = c.y0 + dd * 2 / 3;
        { s32 t = *(volatile s32 *)&d.x0; dd = d.x1 - t; }
        c.x0 += dd;
        c.x1 = c.x0 + dd * 2 / 3;
        src = dst;
    }
}
