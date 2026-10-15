#include "types.h"

extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);

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
    u8 pad018[0x8];
    s32 m20;
    s32 m24;
};

void UiSelFrameSetPos_28daa0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    s32 t1;
    s32 t2;

    t0 = p0->m00;
    UiSetWidgetPos_290f60(t0, p1, (p2 + -0x10), (p3 + -0x10));
    t1 = p0->m20;
    p0->m10 = (p2 + t1);
    t2 = p0->m24;
    p0->m14 = (p3 + t2);
}
