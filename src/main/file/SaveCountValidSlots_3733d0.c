#include "types.h"

extern s32 SaveSlotEntryIsValidAt_373440(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SaveCountValidSlots_3733d0(s32 p0)
{
    s32 l1;
    s32 l0;
    s32 r2;
    s32 rv3;

    l0 = 0;
    l1 = 0;
    do {
        r2 = SaveSlotEntryIsValidAt_373440(p0, l0);
        rv3 = l1;
        if (r2 != 0) {
            rv3 = (l1 + 1);
        }
        l0 = (l0 + 1);
        l1 = rv3;
    } while (l0 < 0x32);
    return l1;
}
