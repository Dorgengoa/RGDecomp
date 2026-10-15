#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MesWinGetItemSlot_2746e0(s32 p0, s32 p1)
{
    s32 t0;

    if (p1 <= 0) {
        return -1;
    }
    if (p1 > 0x10) {
        return -1;
    }
    t0 = *(s32 *)((u8 *)(p1 << 2) + p0 + 0x1B5C);
    return t0;
}
