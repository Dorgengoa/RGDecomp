#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    u128 m00;
};

void EffectInstanceGetParamFloatVec_2dd5f0(s32 p0, s32 p1, struct Obj0 *p2)
{
    u128 t0;

    t0 = *(u128 *)((u8 *)p0 + (p1 << 4) + 0x70);
    p2->m00 = t0;
}
