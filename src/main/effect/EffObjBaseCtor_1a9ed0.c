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
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
};

struct Obj0 *EffObjBaseCtor_1a9ed0(struct Obj0 *p0)
{
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m08 = 0;
    p0->m28 = 0;
    p0->m24 = 0;
    p0->m2C = 0;
    p0->m34 = 0;
    p0->m30 = 0;
    p0->m38 = 0;
    p0->m14 = -1;
    p0->m3C = 0;
    p0->m20 = 0;
    return p0;
}
