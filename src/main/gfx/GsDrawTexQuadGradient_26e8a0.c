#include "types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect;

typedef union {
    u64 v;
    struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } c;
} Color;

extern void GsPktSetTexture_13ec00(void *, s32);
extern void GsPktSetUV_13ed60(void *, s32, s32);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(void *, s32, s32, s32);
extern void GsPktClose_13f5b0(void *);
extern void GsPktOpenPrim_13f730(void *, s32);

void GsDrawTexQuadGradient_26e8a0(void *ctx, s32 tex, Rect *pa, Rect *pb, s32 mode, u64 c1v, u64 c2v, s32 alpha, s32 z)
{
    Rect a;
    Rect b;
    Color col[2];
    s32 ay;
    s32 byv;
    s32 x2;
    s32 y2;
    s32 bx2;
    s32 by2;
    s32 al;
    s32 bl;
    s32 g;
    s32 r;

    col[0].v = c1v;
    col[1].v = c2v;
    a = *pa;
    b = *pb;
    if (ctx == NULL) {
        return;
    }
    GsPktOpenPrim_13f730(ctx, 4);
    if (tex != 0) {
        GsPktSetTexture_13ec00(ctx, tex);
    }
    x2 = a.x + a.w;
    ay = a.y;
    y2 = ay + a.h - 1;
    bx2 = b.x + b.w - 1;
    byv = b.y;
    by2 = byv + b.h - 2;
    al = alpha * col[0].c.a / 128;
    bl = col[0].c.b;
    g = col[0].c.g;
    r = col[0].c.r;
    GsPktSetRGBAQ_13ee40(ctx, r, g, bl, al);
    GsPktSetUV_13ed60(ctx, a.x, ay);
    GsPktSetXYZPixel_13f110(ctx, b.x, byv, z);
    if (mode == 1) {
        GsPktSetRGBAQ_13ee40(ctx, col[1].c.r, col[1].c.g, col[1].c.b, alpha * col[1].c.a / 128);
    }
    GsPktSetUV_13ed60(ctx, x2, ay);
    GsPktSetXYZPixel_13f110(ctx, bx2, byv, z);
    if (mode == 2) {
        GsPktSetRGBAQ_13ee40(ctx, col[1].c.r, col[1].c.g, col[1].c.b, alpha * col[1].c.a / 128);
    }
    GsPktSetUV_13ed60(ctx, a.x, y2);
    GsPktSetXYZPixel_13f110(ctx, b.x, by2, z);
    if (mode == 1) {
        GsPktSetRGBAQ_13ee40(ctx, r, g, bl, al);
    }
    GsPktSetUV_13ed60(ctx, x2, y2);
    GsPktSetXYZPixel_13f110(ctx, bx2, by2, z);
    GsPktClose_13f5b0(ctx);
}
