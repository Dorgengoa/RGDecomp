/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsCursorBob_4f06e0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    s = 6.0f * Sinf_128fd0(o->f5C);
    it = ((Item *)UiEntryListFindByTag_28ea40(o->f90, 0x88F4));
    b = &it->b;
    x = (s32)(s + (f32)(it->b.f0 + it->b.f10 * it->b.f4));
    y = (s32)(s + (f32)(it->b.f2 + it->b.f12 * it->b.f6));
    if (flag != 0) {
        UiSetWidgetPos_290f60(o->f8C, 0x4C, x, y);
    } else {
        UiMoveWidgetUniform_290f50(o->f8C, 0x4C, x, y, 0.5f, 0);
    }
    UiSelFrameSetPos_28daa0(o->f9C, 0x4B, b->f10 * b->f4 + 0x1A, b->f12 * b->f6 + 0x1A);
    UiSelFrameAnimStep_28d820(o->f9C, 0x4B);
}
