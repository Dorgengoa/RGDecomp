#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x198];
    s32 m198;
};

s32 UnitGetDeathTime_3b0580(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m198;
    return t0;
}
