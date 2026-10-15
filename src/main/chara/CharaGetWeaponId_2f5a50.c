#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s16 CharaGetWeaponId_2f5a50(s32 p0, s32 p1)
{
    return *(s16 *)((u8 *)(p1 << 1) + p0 + 0x23E);
}
