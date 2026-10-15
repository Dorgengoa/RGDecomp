#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    struct Obj0 *m24;
};

void BlockHeapInit_1c26c0(struct Obj0 *p0, s32 p1, s32 p2)
{
    p0->m1C = p1;
    p0->m20 = p2;
    p0->m18 = 0;
    p0->m14 = 0;
    p0->m08 = 0;
    p0->m10 = 0;
    p0->m0C = 0;
    p0->m08 = 0;
    p0->m0C = p1;
    p0->m10 = (p1 + p2);
    p0->m24 = (struct Obj0 *)((u8 *)p0 + 8);
}
