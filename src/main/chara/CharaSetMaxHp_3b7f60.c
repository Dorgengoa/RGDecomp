#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaSetMaxHp_3b7f60(s32 p0, s32 p1, s32 p2)
{
    if (p2 >= 0) {
        if (p2 < 2) {
            *(s32 *)((u8 *)(p2 << 2) + p0 + 0x1C) = p1;
        }
    }
}
