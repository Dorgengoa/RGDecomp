/* rgp:protos */
#define RGP_SELF_UiSelFrameSetRect_28db40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
};

void UiSelFrameSetRect_28db40(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7)
{
    s32 t0;

    p0->m10 = (p2 + p6);
    p0->m14 = (p3 + p7);
    p0->m18 = p4;
    p0->m1C = p5;
    p0->m20 = p6;
    p0->m24 = p7;
    t0 = p0->m00;
    UiSetWidgetPos_290f60(t0, p1, (p2 + -0x10), (p3 + -0x10));
}
