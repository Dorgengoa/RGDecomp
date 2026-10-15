#include "types.h"
#pragma opt_dead_assignments off

typedef struct { f32 x, y, z; } V3;

typedef struct {
    u8 pad0[0x230];
    V3 pos;
    u8 pad23C[8];
    f32 alpha;
} Self;

typedef struct {
    u8 pad0[0x10];
    f32 h;
} Hit;

extern void HpGaugeSetBarWidth_31e300(Self *, s32);
extern s32 HpGaugeGetBarWidth_31e2f0(Self *);
extern s32 FindS16Index16_31e870(Self *, s32);
extern s32 HpGaugeGetHop_31e5a0(Self *, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void *ObjRecGetLiveObject_1c4a90(s32, s32);
extern Hit *ObjGetNthAttachPointPos_1ade20(void *, s32, s32, V3 *);
extern s32 ProjectToScreenOffset_15d160(s32 *, V3 *);
extern s32 ModelGetRootFrame_1511a0(void *);
extern void FrameGetWorldPos_148f30(s32, V3 *);
extern f32 ModelObjGetScaledHeight_23b110(void *);
extern s32 GetDrawCtx_15de80(void);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 ScreenPointInBounds_15d4a0(f32 *);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetAntialias_13e390(s32, s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktWriteAD_13ec80(s32, s32, s64);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void DrawListEndPrim_141a20(s32);
extern f32 D_0047D5D0;
extern f32 D_00452630[];
typedef struct { u8 pad0[0x18E]; s16 f18E; } Sub;
typedef struct { u8 pad0[0x18]; Sub *f18; } Mgr;
extern Mgr *GetGameData_1fede0(void);
extern f32 D_0047D82C;
extern f32 D_0045B080[];
typedef struct { f32 a, b, c; } C3;
typedef union { C3 f; s32 i[3]; } U3;
extern C3 D_0047F280 __attribute__((section(".sdata")));
extern C3 D_0047F290 __attribute__((section(".sdata")));
extern C3 D_0047F2A0 __attribute__((section(".sdata")));

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

s32 HpGaugeDrawBar_31c310(Self *self, s32 id, s32 mode, f32 a, f32 unused, f32 b, f32 c) {
    s32 scr[4];
    f32 v0[4];
    f32 v1[4];
    s16 sz;
    f32 d;
    f32 e;
    void *obj;
    Hit *hit;
    s32 ctx;
    s32 dl;
    s32 hh;
    s32 s;
    s32 w;
    s32 h;
    s32 sel;
    s32 n;
    f32 k;

    HpGaugeSetBarWidth_31e300(self, 0x2C);
    sz = (s32)(b * (f32)HpGaugeGetBarWidth_31e2f0(self));
    if (a <= 0.0f && mode == -1) {
        return 0;
    }
    d = (f32)HpGaugeGetHop_31e5a0(self, FindS16Index16_31e870(self, id));
    if (!(d <= 0.0f)) {
        d = D_0047D5D0 * (d * d);
    }
    obj = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id);
    if (obj == 0) {
        return 0;
    }
    e = 0.0f;
    if (id >= 0 && id < 9) {
        e = D_00452630[id];
    }
    if ((hit = ObjGetNthAttachPointPos_1ade20(obj, 0x96, 0, &self->pos)) != 0) {
        self->pos.y += hit->h * (D_0047D82C * *(volatile f32 *)D_0045B080);
        self->pos.y += d;
        self->pos.y += 2.0f;
        self->pos.y += e;
        if (ProjectToScreenOffset_15d160(scr, &self->pos) == 0) {
            return 0;
        }
        scr[0] = (f32)scr[0] / 16.0f;
        scr[1] = (f32)scr[1] / 16.0f;
    } else if (ObjGetNthAttachPointPos_1ade20(obj, 0, 0, &self->pos) != 0) {
        self->pos.y += d;
        self->pos.y += e;
        if (ProjectToScreenOffset_15d160(scr, &self->pos) == 0) {
            return 0;
        }
        scr[0] = (f32)scr[0] / 16.0f;
        scr[1] = (f32)scr[1] / 16.0f;
    } else {
        FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(obj), &self->pos);
        {
            f32 h_ = ModelObjGetScaledHeight_23b110(obj);
            self->pos.y += -1.5f + h_;
        }
        self->pos.y += d;
        self->pos.y += e;
        if (ProjectToScreenOffset_15d160(scr, &self->pos) == 0) {
            return 0;
        }
        scr[0] = (f32)scr[0] / 16.0f;
        scr[1] = (f32)scr[1] / 16.0f;
    }
    ctx = GetDrawCtx_15de80();
    if (ctx == 0) {
        return 0;
    }
    dl = DrawListBeginPrim_141b00(ctx);
    if (dl == 0) {
        return 0;
    }
    e = b / 32.0f;
    hh = 10.0f * e + 10.0f;
    {
    s32 p0[2] = {0};
    s = sz;
    p0[0] = scr[0] - s / 2;
    p0[1] = scr[1] - hh / 2;
    {
    s32 p1[2] = {0};
    p1[0] = p0[0] + s;
    p1[1] = p0[1] + hh;
    w = DrawEnvGetWidth_1451e0(ctx);
    h = DrawEnvGetHeight_1451d0(ctx);
    ZERO(v0, 0x10);
    v0[0] = p0[0];
    v0[1] = p0[1];
    v0[2] = scr[2];
    ZERO(v1, 0x10);
    v1[0] = p1[0];
    v1[1] = p1[1];
    v1[2] = scr[2];
    if (ScreenPointInBounds_15d4a0(v0) == 0 || ScreenPointInBounds_15d4a0(v1) == 0) {
        return 0;
    }
    if (p1[0] < 0 || w + s < p1[0]) {
        return 0;
    }
    if (p1[1] < 0 || h + hh < p1[1]) {
        return 0;
    }
    if (p0[0] > w || p0[0] < -s) {
        return 0;
    }
    if (p0[1] > h || p0[1] < -hh) {
        return 0;
    }
    sel = id == GetGameData_1fede0()->f18->f18E;
    GsPktSetOriginMode_13e2f0(dl, 0);
    GsPktSetTextured_13e400(dl, 0);
    GsPktSetZWriteMask_13e430(dl, 0);
    GsPktSetAlphaBlend_13e500(dl, 1);
    GsPktSetBlendMode_13e4f0(dl, 1);
    GsPktEnableZTest_13e460(dl, 1);
    GsPktSetZTest_13e450(dl, 0);
    GsPktSetGouraud_13e3b0(dl, 1);
    GsPktSetTexFilter_13e3d0(dl, 0);
    GsPktSetAntialias_13e390(dl, 0);
    if (sel) {
        GsPktOpenPrim_13f730(dl, 3);
        GsPktWriteAD_13ec80(dl, 0x40, ((s64)(w - 1) << 16) | ((s64)(h - 1) << 48));
        GsPktSetRGBAQ_13ee40(dl, 0x80, 0x80, 0x80, (s32)(96.0f * c * self->alpha));
        GsPktSetXYZPixel_13f110(dl, p0[0], p0[1], scr[2]);
        GsPktSetXYZPixel_13f110(dl, p1[0], p0[1], scr[2]);
        GsPktSetXYZPixel_13f110(dl, p0[0], p1[1], scr[2]);
        GsPktSetXYZPixel_13f110(dl, p0[0], p1[1], scr[2]);
        GsPktSetXYZPixel_13f110(dl, p1[0], p0[1], scr[2]);
        GsPktSetXYZPixel_13f110(dl, p1[0], p1[1], scr[2]);
        GsPktClose_13f5b0(dl);
    }
    if (sel) {
        GsPktOpenPrim_13f730(dl, 3);
        GsPktWriteAD_13ec80(dl, 0x40, ((s64)(w - 1) << 16) | ((s64)(h - 1) << 48));
        GsPktSetRGBAQ_13ee40(dl, 0, 0, 0, (s32)(96.0f * c * self->alpha));
        GsPktSetXYZPixel_13f110(dl, p0[0] + 2, p0[1] + 2, scr[2]);
        GsPktSetXYZPixel_13f110(dl, p1[0] - 2, p0[1] + 2, scr[2]);
        GsPktSetXYZPixel_13f110(dl, p0[0] + 2, p1[1] - 2, scr[2]);
        GsPktSetXYZPixel_13f110(dl, p0[0] + 2, p1[1] - 2, scr[2]);
        GsPktSetXYZPixel_13f110(dl, p1[0] - 2, p0[1] + 2, scr[2]);
        GsPktSetXYZPixel_13f110(dl, p1[0] - 2, p1[1] - 2, scr[2]);
        GsPktClose_13f5b0(dl);
    }
    p1[0] -= 3;
    p0[0] += 3;
    n = (f32)p0[0] + a * (f32)(p1[0] - p0[0]);
    if (n < p0[0]) {
        n = p0[0];
    }
    {
    U3 r;
    U3 g;
    U3 bl;
    r = *(U3 *)&D_0047F280;
    g = *(U3 *)&D_0047F290;
    bl = *(U3 *)&D_0047F2A0;
    GsPktOpenPrim_13f730(dl, 3);
    GsPktWriteAD_13ec80(dl, 0x40, ((s64)(w - 1) << 16) | ((s64)(h - 1) << 48));
    k = 128.0f * c;
    GsPktSetRGBAQ_13ee40(dl, r.i[0], g.i[0], bl.i[0], (s32)(k * self->alpha));
    GsPktSetXYZPixel_13f110(dl, p0[0], p0[1] + 3, scr[2]);
    GsPktSetRGBAQ_13ee40(dl, r.i[1], g.i[1], bl.i[1], (s32)(k * self->alpha));
    GsPktSetXYZPixel_13f110(dl, n, p0[1] + 3, scr[2]);
    GsPktSetRGBAQ_13ee40(dl, r.i[0], g.i[0], bl.i[0], (s32)(k * self->alpha));
    GsPktSetXYZPixel_13f110(dl, p0[0], p1[1] - 3, scr[2]);
    GsPktSetRGBAQ_13ee40(dl, r.i[0], g.i[0], bl.i[0], (s32)(k * self->alpha));
    GsPktSetXYZPixel_13f110(dl, p0[0], p1[1] - 3, scr[2]);
    GsPktSetRGBAQ_13ee40(dl, r.i[1], g.i[1], bl.i[1], (s32)(k * self->alpha));
    GsPktSetXYZPixel_13f110(dl, n, p1[1] - 3, scr[2]);
    GsPktSetRGBAQ_13ee40(dl, r.i[1], g.i[1], bl.i[1], (s32)(k * self->alpha));
    GsPktSetXYZPixel_13f110(dl, n, p0[1] + 3, scr[2]);
    GsPktClose_13f5b0(dl);
    }
        }
    }
    DrawListEndPrim_141a20(ctx);
    return 1;
}
