#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

void SplineSegmentInit_2578f0(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m00 = 0;
    p0->m04 = 0;
    l1 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x8) = 0;
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x14) = 0;
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x20) = 0;
        *(s32 *)((u8 *)p0 + (l1 << 2) + 0x2C) = 0;
        l0 = ((l1 + 1) < 3);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
