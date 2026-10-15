#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x48];
    s32 m48;
    u8 pad04C[0x8];
    s32 m54;
};

u8 AudioDecIsPreset_1d3050(struct Obj0 *p0)
{
    return (p0->m54 >= p0->m48);
}
