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
    s16 m10;
    s16 m12;
    s16 m14;
    s16 m16;
};

void ParamRecReset_1cfdb0(struct Obj0 *p0)
{
    p0->m10 = 0;
    p0->m12 = -1;
    p0->m14 = -1;
    p0->m16 = 0;
    p0->m00 = 0x3F800000;
    p0->m04 = 0x3F800000;
    p0->m08 = 0;
    p0->m0C = 0;
}
