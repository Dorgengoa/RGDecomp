#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 RecStackFindFreeSlot_1c4420(s32 p0)
{
    s32 l0;
    s32 t0;

    l0 = 1;
    while (l0 < 0x40) {
        t0 = *(s32 *)((u8 *)p0 + (l0 << 2));
        if (t0 == 0) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
