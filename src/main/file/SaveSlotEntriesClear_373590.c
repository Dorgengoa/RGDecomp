#include "types.h"

extern void SaveSlotEntryClear_3761a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SaveSlotEntriesClear_373590(s32 p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        SaveSlotEntryClear_3761a0(((p0 + (l1 << 1)) + 0x78));
        l0 = ((l1 + 1) < 0x32);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
