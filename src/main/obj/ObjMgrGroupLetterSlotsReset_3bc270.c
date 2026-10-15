#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ObjMgrGroupLetterSlotsReset_3bc270(s32 p0)
{
    s32 l0;

    l0 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l0 << 2) + 0x14) = -1;
        *(u8 *)((u8 *)p0 + (l0 << 2) + 0x16) = 0;
        l0 = (l0 + 1);
    } while (l0 < 0x10);
}
