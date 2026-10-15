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
    s16 m24;
    s16 m26;
    s16 m28;
    s16 m2A;
    s16 m2C;
    s16 m2E;
    s16 m30;
    s16 m32;
};

void CharaTableDataClear_227090(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m24 = 0;
    p0->m08 = 0;
    p0->m26 = 0;
    p0->m0C = 0;
    p0->m28 = 0;
    p0->m10 = 0;
    p0->m2A = 0;
    p0->m14 = 0;
    p0->m2C = 0;
    p0->m18 = 0;
    p0->m2E = 0;
    p0->m1C = 0;
    p0->m30 = 0;
    p0->m20 = 0;
    p0->m32 = 0;
}
