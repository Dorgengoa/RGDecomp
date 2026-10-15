#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void S32ArrayInsertAt_1dde90(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 l0;
    s32 t0;

    l0 = (p1 + -1);
    while (l0 >= p3) {
        t0 = *(s32 *)((u8 *)p0 + (l0 << 2));
        *(s32 *)((u8 *)p0 + (l0 << 2) + 0x4) = t0;
        l0 = (l0 + -1);
    }
    *(s32 *)((u8 *)p0 + (p3 << 2)) = p2;
}
