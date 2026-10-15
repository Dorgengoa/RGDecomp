#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471060[];

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    u8 m10;
    u8 pad011[0x3];
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    void *m24;
};

struct Obj0 *MotionEventBaseCtor_1b1d70(struct Obj0 *p0)
{
    p0->m24 = D_00471060;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m0C = 0;
    p0->m08 = 0;
    p0->m14 = 0;
    p0->m1C = 0xBF800000;
    p0->m20 = 0xBF800000;
    p0->m18 = 0;
    p0->m10 = 0;
    return p0;
}
