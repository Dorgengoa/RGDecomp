#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x16B0];
    s32 m16B0;
    u8 pad16B4[0x4];
    s16 m16B8;
};

s32 MapAreaDataGetLightSet_1e8ea0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;

    t0 = p0->m16B0;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m16B8;
    if ((u32)t1 <= (u32)p1) {
        return 0;
    }
    return (t0 + (((p1 * 0x1C) + p1) << 4));
}
