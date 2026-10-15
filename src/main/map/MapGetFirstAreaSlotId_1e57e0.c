#include "types.h"

extern s32 MapGetFirstAreaSlot_1e5760(void);
extern s32 MapDataGetId_1e7bd0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapGetFirstAreaSlotId_1e57e0(void)
{
    s32 r0;
    s32 r1;

    r0 = MapGetFirstAreaSlot_1e5760();
    if (r0 != 0) {
        r1 = MapDataGetId_1e7bd0(r0);
        return r1;
    }
    return -1;
}
