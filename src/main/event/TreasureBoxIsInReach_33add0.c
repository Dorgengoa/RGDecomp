#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x68];
    s32 m68;
    u8 pad06C[0x4];
    u8 m70;
};

u64 TreasureBoxIsInReach_33add0(struct Obj0 *p0)
{
    s32 t0;
    u8 t1;

    t0 = p0->m68;
    if (t0 == 0) {
        return (u64)0;
    }
    t1 = p0->m70;
    if ((t1 & 1) == 0) {
        return (u64)0;
    }
    return (((u64)(((s64)t1) << 0x3B)) >> 0x3F);
}
