#include "types.h"

extern void EventRecInitWithKey_2e5800(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
};

void EventVolumeRecInit_2e4ec0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    EventRecInitWithKey_2e5800(p0, p1);
    p0->m10 = p2;
    p0->m14 = p3;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m24 = 0;
}
