#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinClearPageLineCounts_272a70(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 << 1) + 0x5C) = 0;
        l0 = ((l1 + 1) < 0x10);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
