#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 EffectFindFreeSlot_2dfdd0(s32 p0, struct Obj0 *p1)
{
    s32 l0;
    s16 t0;

    l0 = 0;
    while (l0 < 0x30) {
        t0 = *(s16 *)((u8 *)p0 + (((l0 << 3) - l0) << 5) + 0xE);
        if (t0 < 0) {
            p1->m00 = l0;
            return (p0 + (((l0 << 3) - l0) << 5));
        }
        l0 = (l0 + 1);
    }
    return 0;
}
