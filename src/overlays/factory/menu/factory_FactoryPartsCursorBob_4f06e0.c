#include "types.h"

typedef struct Box {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u8  pad8[8];
    s16 f10;
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Box;

typedef struct Item {
    u8  pad0[4];
    Box b;
} Item;

typedef struct Scr {
    u8    pad00[0x5C];
    f32   f5C;
    u8    pad60[0x28];
    u8    f88;
    u8    pad89[3];
    void *f8C;
    void *f90;
    u8    pad94[8];
    u8    f9C[0x40];
} Scr;

extern f32   D_0047D3D0;
extern f32   D_0047D3EC;

extern f32   func_128FD0(f32 t);
extern void  func_28D820(void *w, s32 id);
extern void  func_28DAA0(void *w, s32 id, s32 x, s32 y);
extern Item *func_28EA40(void *ctx, s32 id);
extern void  func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);

void factory_FactoryPartsCursorBob_4f06e0(Scr *o, s32 flag)
{
    Item *it;
    Box  *b;
    f32   s;
    s32   x;
    s32   y;

    if (o->f88 != 0) {
        return;
    }
    o->f5C = o->f5C + D_0047D3D0;
    if (o->f5C > 0.0f) {
        o->f5C = D_0047D3EC;
    }
    s = 6.0f * func_128FD0(o->f5C);
    it = func_28EA40(o->f90, 0x88F4);
    b = &it->b;
    x = (s32)(s + (f32)(it->b.f0 + it->b.f10 * it->b.f4));
    y = (s32)(s + (f32)(it->b.f2 + it->b.f12 * it->b.f6));
    if (flag != 0) {
        func_290F60(o->f8C, 0x4C, x, y);
    } else {
        func_290F50(o->f8C, 0x4C, x, y, 0, 0.5f);
    }
    func_28DAA0(o->f9C, 0x4B, b->f10 * b->f4 + 0x1A, b->f12 * b->f6 + 0x1A);
    func_28D820(o->f9C, 0x4B);
}
