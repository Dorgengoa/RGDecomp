#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    u32 m08;
    u32 m0C;
};

s64 ActInfoCallGetMask_2310a0(struct Obj0 *p0)
{
    return ((((s64)p0->m0C) << 0x20) | p0->m08);
}
