/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpCursorBob_4f15d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
    u8  pad08[0x2];
    s16 f0A;
    u8  pad0C[0xA];
    s16 f16;
} B;

typedef struct A {
    u8    pad00[0x5C];
    f32   f5C;
    u8    pad60[0x28];
    void *f88;
    void *f8C;
} A;

extern f32 D_0047D3D0;
extern f32 D_0047D3EC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpCursorBob_4f15d0(A *o, s32 flag)
{
    B  *b;
    f32 s;
    s32 x;
    s32 y;

    o->f5C = 0.15707964f + o->f5C;
    if (o->f5C > 0.0f) {
        o->f5C = -3.1415927f;
    }
    s = 6.0f * Sinf_128fd0(o->f5C);
    b = ((B *)UiEntryListFindByTag_28ea40(o->f8C, 0x8944));
    x = (s32)(b->f04 + s);
    y = b->f06 + b->f16 * b->f0A;
    if (flag != 0) {
        UiSetWidgetPos_290f60(o->f88, 0x83, x, y);
    } else {
        UiMoveWidgetUniform_290f50(o->f88, 0x83, x, y, 0.5f, 0);
    }
}
