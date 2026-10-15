#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    u8 pad024[0x4];
    s32 m28;
    s32 m2C;
    u8 pad030[0x4];
    s32 m34;
};

s32 MemStackPeekQw_14d9d0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;

    t0 = p0->m20;
    if (t0 != 0) {
        return 0;
    }
    t1 = p0->m2C;
    t2 = p0->m34;
    if ((t1 + p1) > t2) {
        return 0;
    }
    t3 = p0->m28;
    return (t3 + (t1 << 4));
}
