#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x104];
    s32 m104;
    u8 pad108[0x39C];
    s32 m4A4;
};

void SplinePathStart_256aa0(struct Obj0 *p0)
{
    if (p0->m104 > 0) {
        p0->m4A4 = 1;
    }
}
