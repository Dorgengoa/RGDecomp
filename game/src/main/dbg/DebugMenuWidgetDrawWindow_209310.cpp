/* rgp:protos */
#line 1
#include "types.h"
typedef struct { f32 w[4]; } SD4_0047E5E0;
extern "C" SD4_0047E5E0 D_0047E5E0 __attribute__((section(".sdata")));
typedef struct { f32 w[4]; } SD4_0047E5F0;
extern "C" SD4_0047E5F0 D_0047E5F0 __attribute__((section(".sdata")));

class W {
public:
    u8 pad0[0x18];
    W **x18;
    s16 x1C;
    s16 x1E;
    s16 x20;
    s16 x22;
    s16 x24;
    s16 x26;
    s16 x28;
    u16 x2A;
    VC_VPTR_MEMBER;
    s32 Print(s8 * a0) { return VCM(s32, (void *, s8 *), 0xC, a0); }
};

extern "C" {
s32 Sprintf_1343b8(s8 *, const s8 *);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetRGBAQVec_13edd0(s32, f32 *);
void GsPktSetXYZf_13f060(s32, f32, f32, f32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void DrawListEndPrim_141a20(s32);
s32 DrawListBeginPrim_141b00(s32);
s32 GetDrawCtx_15de80(void);
s32 TextGridCellRect_208650(s32 *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
void TextGridCellRectFillRgba_208820(s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);
void TextGridPrintAt_208880(s32, s32, s32, s32, s8 *, f32);
void StrMeasureLines_208950(s32 *, s32 *, s8 *);
void DebugMenuWidgetDrawTextClipped_209a30(W *, s8 *, s32, s32, s32, s32, s32, s32, f32);
s32 DebugMenuWidgetGetFlags_209de0(W *);
s32 DebugMenuWidgetHasPosFlagMaybe_209e20(int);
extern s8 D_0045C630[];
extern s8 D_0045C638[];
extern s8 D_0045C640[];
extern s8 D_0045C648[];
void DebugMenuWidgetDrawWindow_209310(W *w, s32 x, s32 y, f32 scale);
}

extern "C" void DebugMenuWidgetDrawWindow_209310(W *w, s32 x, s32 y, f32 scale)
{
    volatile s32 wv;
    s32 hv;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s8 hdr[0x40] __attribute__((aligned(16)));
    s8 buf[0x2000] __attribute__((aligned(16)));
    f32 c0[4] __attribute__((aligned(16)));
    f32 c1[4] __attribute__((aligned(16)));
    s8 *p;
    W **pp;
    s8 *q;
    s32 i;
    s32 k;
    s32 hh;
    s32 width;
    s32 len;
    s32 half;
    s32 ctx;
    s32 g;
    s32 end;
    s32 sc;
    bool scroll;
    f32 lw;
    f32 x0;
    f32 x1;
    f32 y0;
    f32 y1;

    if (((unsigned char)DebugMenuWidgetHasPosFlagMaybe_209e20((int)w)) == 0) {
        x = 0;
        y = 0;
    }
    {
        u8 *p_ = (u8 *)hdr;
        u32 n_ = 0x40;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    {
        u8 *p_ = (u8 *)buf;
        u32 n_ = 0x2000;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    wv = 0;
    hv = 0;
    pp = w->x18;
    p = buf;
    if (pp != 0) {
        for (i = 0; i < w->x1C; i++, pp++) {
            W *e = *pp;
            if (e != 0) {
                p += e->Print(p);
            }
            p += Sprintf_1343b8(p, D_0045C630);
        }
    }
    StrMeasureLines_208950((s32 *)&wv, &hv, buf);
    if (wv < w->x1E) {
        wv = w->x1E;
    }
    scroll = false;
    hh = hv;
    width = wv + 2;
    if (w->x20 > 0 && w->x20 < hh) {
        s32 d = w->x22 - w->x24;
        if (d < 0) {
            w->x24 = w->x22;
        }
        if (!(d < w->x20)) {
            w->x24 = w->x22 - w->x20 + 1;
        }
        hh = w->x20;
        scroll = true;
    }
    q = hdr;
    q += Sprintf_1343b8(q, D_0045C638);
    q += w->Print(q);
    len = q + Sprintf_1343b8(q, D_0045C640) - hdr;
    if (width < len) {
        width = len;
    }
    if (width & 1) {
        width++;
    }
    half = (width - len) >> 1;
    q = hdr;
    for (k = 0; k < half; k++) {
        q += Sprintf_1343b8(q, D_0045C648);
    }
    q += Sprintf_1343b8(q, D_0045C638);
    q += w->Print(q);
    Sprintf_1343b8(q, D_0045C640);
    x += w->x26;
    y += w->x28;
    ctx = GetDrawCtx_15de80();
    g = DrawListBeginPrim_141b00(ctx);
    GsPktSetTextured_13e400(g, 0);
    GsPktSetOriginMode_13e2f0(g, 0);
    GsPktSetAlphaBlend_13e500(g, 1);
    GsPktSetBlendMode_13e4f0(g, 1);
    GsPktEnableAlphaTest_13e4d0(g, 1);
    GsPktSetZWriteMask_13e430(g, 0);
    GsPktEnableZTest_13e460(g, 0);
    lw = 88.0f * scale;
    TextGridCellRectFillRgba_208820(g, x, y, 0, 0, width, hh + 1, 6, 160.0f, 160.0f, 160.0f, lw);
    TextGridCellRectFillRgba_208820(g, x, y, 0, 0, width, hh + 1, 4, 0.0f, 0.0f, 0.0f, lw);
    TextGridCellRectFillRgba_208820(g, x, y, 0, 0, width, 1, 1, 128.0f, 128.0f, 128.0f, lw);
    if (w->x18 != 0 && w->x1C > 0) {
        TextGridCellRectFillRgba_208820(g, x, y, scroll, w->x22 - w->x24 + 1, width - scroll, 1, 1, 64.0f, 64.0f, 192.0f, lw);
    }
    if (scroll && w->x18 != 0) {
        lw = 64.0f * scale;
        k = w->x24;
        sc = scroll;
        width -= sc;
        end = k + hh;
        for (; k < end; k++) {
            if (((unsigned short)DebugMenuWidgetGetFlags_209de0(w->x18[k])) & 8) {
                TextGridCellRectFillRgba_208820(g, x, y, sc, k - w->x24 + 1, width, 1, -2, 192.0f, 64.0f, 64.0f, lw);
            }
        }
    }
    if (scroll) {
        if (TextGridCellRect_208650(&r0, &r1, &r2, &r3, x, y, 0, 1, 1, hh, 0) != 0) {
            x0 = (f32)(r0 - 1);
            *(SD4_0047E5E0 *)c0 = D_0047E5E0;
            x1 = (f32)(r2 - 2);
            y0 = (f32)(r1 - 1);
            y1 = (f32)(r3 + 2);
            c0[3] = 64.0f * scale;
            *(SD4_0047E5F0 *)c1 = D_0047E5F0;
            c1[3] = 128.0f * scale;
            GsPktOpenPrim_13f730(g, 6);
            GsPktSetRGBAQVec_13edd0(g, c0);
            GsPktSetXYZf_13f060(g, x0, y0, 1.0f);
            GsPktSetXYZf_13f060(g, x1, y1, 1.0f);
            GsPktSetRGBAQVec_13edd0(g, c1);
            y1 = y1 - y0;
            GsPktSetXYZf_13f060(g, x0, y0 + (f32)w->x24 * y1 / (f32)hv, 1.0f);
            GsPktSetXYZf_13f060(g, x1, y0 + y1 * (f32)(w->x24 + hh) / (f32)hv, 1.0f);
            GsPktClose_13f5b0(g);
        }
    }
    DrawListEndPrim_141a20(ctx);
    TextGridPrintAt_208880(x, y, 0, 0, hdr, scale * scale);
    DebugMenuWidgetDrawTextClipped_209a30(w, buf, wv, hv, x, y, 1, 1, (f32)scale);
}
