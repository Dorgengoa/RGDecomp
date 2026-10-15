#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void PartyMenuCursorSet_3c0710(s32 p0, s32 p1, s32 p2)
{
    if (p1 >= 0) {
        if (p1 < 0x20) {
            *(s16 *)((u8 *)(p1 << 1) + p0 + 0x28A) = p2;
            return;
        }
    }
    if (p1 >= 0x20) {
        if (p1 < 0x30) {
            *(s16 *)((u8 *)(p1 << 1) + p0 + 0x4C28) = p2;
            return;
        }
        return;
    }
}
