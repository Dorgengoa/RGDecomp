#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    s32 m08;
    s32 m0C;
};

struct Obj0 *ActInfoCallCtor_2311d0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    return p0;
}
