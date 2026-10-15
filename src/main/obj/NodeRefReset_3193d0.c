#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    u8 m08;
    u8 pad009[0x1F];
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
};

void NodeRefReset_3193d0(struct Obj0 *p0)
{
    p0->m00 = -1;
    p0->m02 = -1;
    p0->m04 = -1;
    p0->m08 = 0;
    p0->m06 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m30 = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3C = 0;
    p0->m40 = 0;
    p0->m44 = 0;
    p0->m48 = 0;
    p0->m4C = 0;
}
