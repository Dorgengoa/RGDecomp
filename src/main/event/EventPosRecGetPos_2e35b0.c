#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
    f32 m1C;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    s32 m0C;
};

void EventPosRecGetPos_2e35b0(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m00 = p0->m14;
    p1->m04 = p0->m18;
    p1->m08 = p0->m1C;
    p1->m0C = 0;
}
