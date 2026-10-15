#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x19C];
    u8 m19C;
};

u64 CharaGetFlag19CBit1Related_232580(struct Obj0 *p0)
{
    return (((u64)(((s64)p0->m19C) << 0x3E)) >> 0x3F);
}
