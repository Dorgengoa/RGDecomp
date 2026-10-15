#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004832B0;

s32 MenuObjParamsFindById_3867c0(s32 p0)
{
    s32 t0;
    s32 l0;
    u8 t1;

    t0 = D_004832B0;
    l0 = 0;
    while (l0 < 0x10) {
        t1 = *(u8 *)((u8 *)t0 + (((l0 * 0xC) + l0) << 2));
        if (p0 == t1) {
            return (t0 + (((l0 * 0xC) + l0) << 2));
        }
        l0 = (l0 + 1);
    }
    return 0;
}
