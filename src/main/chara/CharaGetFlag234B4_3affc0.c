#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x234];
    u8 m234;
};

u64 CharaGetFlag234B4_3affc0(struct Obj0 *p0)
{
    return (((u64)(((s64)p0->m234) << 0x3B)) >> 0x3F);
}
