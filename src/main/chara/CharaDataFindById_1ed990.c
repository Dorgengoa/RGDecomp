#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaDataFindById_1ed990(s32 p0, s32 p1)
{
    s32 l0;
    s16 t0;

    l0 = 0;
    while (l0 < 0x20) {
        t0 = *(s16 *)((u8 *)p0 + (((l0 * 0x1C) + l0) << 2) + 0x62);
        if (p1 == t0) {
            return (p0 + (((l0 * 0x1C) + l0) << 2));
        }
        l0 = (l0 + 1);
    }
    return 0;
}
