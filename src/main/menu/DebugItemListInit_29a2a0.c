#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s16 m18;
    u8 m1A;
    u8 m1B;
};

void DebugItemListInit_29a2a0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 8;
    p0->m0C = 0;
    p0->m10 = 2;
    p0->m1A = 0;
    p0->m1B = 0;
    p0->m18 = 0;
    p0->m14 = 0;
}
