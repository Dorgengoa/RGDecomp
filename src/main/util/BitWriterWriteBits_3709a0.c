#include "types.h"

extern void BitWriterSetBit_370cc0(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 BitWriterWriteBits_3709a0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 l1;
    s32 l0;
    s16 t0;

    l1 = 1;
    l0 = 0;
    while (l0 < p2) {
        t0 = p0->m00;
        p0->m00 = (t0 + 1);
        BitWriterSetBit_370cc0(p0, t0, ((p1 & l1) != 0));
        l1 = (l1 << 1);
        l0 = (l0 + 1);
    }
    return p2;
}
