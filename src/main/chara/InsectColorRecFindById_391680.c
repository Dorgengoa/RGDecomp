#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s8 D_00483438;
extern s32 D_0048343C;

s32 InsectColorRecFindById_391680(s32 p0)
{
    s32 t0;
    s8 t1;
    s32 l0;
    s16 t2;

    t0 = D_0048343C;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_00483438;
    l0 = 0;
    while (l0 < t1) {
        t2 = *(s16 *)((u8 *)t0 + (((l0 * 0x24) + l0) << 2));
        if (p0 == t2) {
            return (t0 + (((l0 * 0x24) + l0) << 2));
        }
        l0 = (l0 + 1);
    }
    return 0;
}
