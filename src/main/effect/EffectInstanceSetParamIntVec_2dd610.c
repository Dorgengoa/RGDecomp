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
};

void EffectInstanceSetParamIntVec_2dd610(s32 p0, s32 p1, struct Obj0 *p2)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;

    t0 = p2->m00;
    *(s32 *)((u8 *)(p1 << 4) + p0 + 0xB0) = t0;
    t1 = p2->m04;
    *(s32 *)((u8 *)(p1 << 4) + p0 + 0xB4) = t1;
    t2 = p2->m08;
    *(s32 *)((u8 *)(p1 << 4) + p0 + 0xB8) = t2;
    t3 = p2->m0C;
    *(s32 *)((u8 *)(p1 << 4) + p0 + 0xBC) = t3;
}
