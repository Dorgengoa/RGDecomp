#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x19E];
    s16 m19E;
};

s32 UnitSetActionCategory_3b66c0(struct Obj0 *p0, s32 p1)
{
    p0->m19E = p1;
    return 1;
}
