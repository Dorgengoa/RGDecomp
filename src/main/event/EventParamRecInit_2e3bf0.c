#include "types.h"

extern void EventRecInitWithKey_2e5800(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    f32 m10;
    f32 m14;
    f32 m18;
};

void EventParamRecInit_2e3bf0(struct Obj0 *p0, s32 p1, f32 fa0, f32 fa1, f32 fa2)
{
    EventRecInitWithKey_2e5800(p0, p1);
    p0->m10 = fa0;
    p0->m14 = fa1;
    p0->m18 = fa2;
}
