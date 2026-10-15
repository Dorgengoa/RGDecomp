#include "types.h"

typedef unsigned __int128 u128;

typedef struct View {
    u8 pad0[0x28];
    s32 x28;
    s32 x2C;
    u8 pad30[4];
    s32 x34;
} View;

typedef struct Buf {
    s32 x0;
    s32 x4;
    View v;
} Buf;

typedef struct Pos {
    u8 pad0[4];
    s32 x;
    s32 y;
} Pos;

typedef struct Txt {
    u8 pad[0x140];
} Txt;

typedef struct Obj {
    s32 idx;
    u128 *cur;
    Buf *buf[0x4A];
    Txt t;
    Pos *pos;
    u8 pad274[0x3CC8 - 0x274];
    s32 on;
} Obj;

void GsPktSetOriginMode_13e2f0(Txt *, s32);
void GsPktSetTextured_13e400(Txt *, s32);
void GsPktSetZWriteMask_13e430(Txt *, s32);
void GsPktEnableZTest_13e460(Txt *, s32);
void GsPktSetAlphaBlend_13e500(Txt *, s32);
void GsPktSetRGBAQ_13ee40(Txt *, s32, s32, s32, s32);
void GsPktSetXYZf_13f060(Txt *, f32, f32, f32);
void GsPktSetXYZPixel_13f110(Txt *, s32, s32, s32);
void GsPktClose_13f5b0(Txt *);
void GsPktOpenPrim_13f730(Txt *, s32);
u32 GsPktEnd_13f790(Txt *);
void GsPktBegin_13f7e0(Txt *);
void GsPktInit_13f7f0(Txt *, View *, Pos *);
void MemStackAllocQw_14d950(View *, s32);
s32 DrawEnvWritePacket_157460(Pos *, u32);
extern const u128 D_0047DE40 __attribute__((section(".sdata")));

#define VIEW(b) ((b) ? &(b)->v : 0)

static inline View *getView(Obj *a) {
    Buf *b = a->buf[a->idx];
    return b ? &b->v : 0;
}

void GfxDrawPerfMeter_1431c0(Obj *a, f32 f0, f32 f1) {
    s32 y;
    u32 r;
    u32 k;
    Pos *pp;
    Txt *t;
    f32 r1;
    s32 x;
    Buf *b;
    View *w;
    f32 r0;
    View *v;

    if (a->on == 0) return;
    v = getView(a);
    r0 = (100.0f * (f32)(v->x34 - v->x2C)) / (f32)v->x34;
    b = ((Buf **)((u8 *)a + 8))[*(s32 *)a];
    r1 = 100.0f - ((100.0f * (f32)(((s32)a->cur - b->x0) / 4)) / 4.0f) / (f32)b->x4;
    pp = a->pos;
    GsPktInit_13f7f0(&a->t, VIEW(b), pp);
    GsPktBegin_13f7e0(&a->t);
    t = &a->t;
    GsPktEnableZTest_13e460(t, 0);
    GsPktSetTextured_13e400(t, 0);
    GsPktSetAlphaBlend_13e500(t, 1);
    GsPktSetZWriteMask_13e430(t, 1);
    GsPktSetOriginMode_13e2f0(t, 0);
    GsPktOpenPrim_13f730(t, 6);
    GsPktSetRGBAQ_13ee40(t, 0x80, 0x80, 0x80, 0x80);
    x = a->pos->x;
    y = a->pos->y - 0x28;
    if (!(f1 < 100.0f)) {
        GsPktSetRGBAQ_13ee40(t, 0xFF, 0, 0, 0x40);
    } else {
        GsPktSetRGBAQ_13ee40(t, 0x80, 0x80, 0x80, 0x40);
    }
    GsPktSetXYZPixel_13f110(t, x, y, 0);
    GsPktSetXYZPixel_13f110(t, x - 0x64, y + 8, 0);
    GsPktSetXYZPixel_13f110(t, x, y + 0xC, 0);
    GsPktSetXYZPixel_13f110(t, x - 0x64, y + 0x10, 0);
    if (!(f0 <= 100.0f)) {
        GsPktSetRGBAQ_13ee40(t, 0xFF, 0, 0, 0x40);
    } else if (!(f0 <= 50.0f)) {
        GsPktSetRGBAQ_13ee40(t, 0, 0x40, 0x40, 0x40);
    } else {
        GsPktSetRGBAQ_13ee40(t, 0, 0, 0x80, 0x40);
    }
    GsPktSetXYZPixel_13f110(t, x, y, 0);
    GsPktSetXYZf_13f060(t, (f32)x - f0, (f32)(y + 8), 0.0f);
    GsPktSetXYZPixel_13f110(t, x, y + 0xC, 0);
    GsPktSetXYZf_13f060(t, (f32)x - f1, (f32)(y + 0x10), 0.0f);
    GsPktSetRGBAQ_13ee40(t, 0, 0x80, 0, 0x40);
    GsPktSetXYZPixel_13f110(t, x, y + 0x18, 0);
    GsPktSetXYZf_13f060(t, (f32)x - r1, (f32)(y + 0x1C), 0.0f);
    GsPktSetXYZPixel_13f110(t, x, y + 0x20, 0);
    GsPktSetXYZf_13f060(t, (f32)x - r0, (f32)(y + 0x24), 0.0f);
    GsPktClose_13f5b0(t);
    r = GsPktEnd_13f790(&a->t);
    if (r != 0) {
        *a->cur = D_0047DE40;
        ((u32 *)a->cur)[1] = r & 0x0FFFFFFF;
        a->cur++;
    }
    pp = a->pos;
    w = VIEW(a->buf[a->idx]);
    if (w != 0) {
        k = w->x28 + w->x2C * 16;
        MemStackAllocQw_14d950(w, DrawEnvWritePacket_157460(pp, k));
        *a->cur = D_0047DE40;
        ((u32 *)a->cur)[1] = k & 0x0FFFFFFF;
        a->cur++;
    }
}
