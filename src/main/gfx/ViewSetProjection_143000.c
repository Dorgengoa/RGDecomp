#include "types.h"

typedef struct {
    f32 a;
    f32 v;
    f32 ten;
    f32 b;
    f32 c;
    f32 t4;
    f32 t8;
    f32 m0;
    f32 m1;
    f32 tC;
    f32 t10;
    f32 r;
    f32 d;
    f32 e;
    f32 f;
} P;

typedef struct {
    u8 pad0[4];
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    u8 pad14[4];
    s32 x18;
    u8 pad1C[4];
    s32 x20;
    u8 pad24[0x14];
    s32 x38;
} T;

extern void ViewSetScreenMatrix_1562b0(s32, P *, T *);
extern void ViewSetPerspective_1564a0(s32, f32, f32, f32, f32, f32, f32);
extern f32 D_0047D4A4;

void ViewSetProjection_143000(u8 *arg0, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f)
{
    P p;
    s32 o;
    T *t;
    s32 k;
    f32 v;

    o = *(s32 *)(arg0 + 0xF20);
    if (o == 0) {
        return;
    }
    t = *(T **)(arg0 + 0x270);
    p.a = a;
    switch (t->x38) {
    case 0x30:
        v = D_0047D4A4;
        break;
    case 0x31:
        k = 0xFED260;
        v = (f32)k;
        break;
    case 0x32:
    case 0x3A:
        k = 0xFDE8;
        v = (f32)k;
        break;
    default:
        v = 0.0f;
        break;
    }
    p.ten = 10.0f;
    p.v = v;
    p.b = b;
    p.c = c;
    p.e = e;
    p.f = f;
    k = 0x7FF;
    p.t4 = (f32)t->x4;
    p.t8 = (f32)t->x8;
    { f32 m = (f32)k; p.m0 = m; p.m1 = m; }
    p.tC = (f32)t->xC;
    p.t10 = (f32)t->x10;
    p.d = d;
    p.r = (d * (f32)t->x18) / (f32)t->x20;
    ViewSetScreenMatrix_1562b0(o, &p, t);
    ViewSetPerspective_1564a0(o, a, p.r, b, c, e, f);
}
