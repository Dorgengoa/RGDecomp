#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

struct Obj0 *EffEmitterRecCtorMaybe_1a9ae0(struct Obj0 *p0)
{
    p0->m0C = 0;
    return p0;
}
