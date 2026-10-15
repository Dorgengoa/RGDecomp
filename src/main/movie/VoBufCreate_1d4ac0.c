#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
};

s32 VoBufCreate_1d4ac0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 l0;
    s32 t0;

    p0->m00 = p1;
    p0->m04 = p2;
    p0->m08 = p2;
    p0->m14 = p3;
    p0->m10 = 0;
    p0->m0C = 0;
    l0 = 0;
    while (l0 < p3) {
        t0 = p0->m04;
        *(s32 *)((u8 *)t0 + (l0 * 0x48)) = 0;
        l0 = (l0 + 1);
    }
    return 0;
}
