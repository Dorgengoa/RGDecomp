#include "types.h"

extern s32 MinimapSlotIsActive_322510(s32);
extern void MinimapSetCenterPos_324870(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MinimapMgrSetCenterPos_321910(s32 p0, s32 p1)
{
    s32 l0;
    s32 r1;

    l0 = 0;
    do {
        r1 = MinimapSlotIsActive_322510((p0 + (((l0 * 0x24) - (l0 * 0x9)) << 4)));
        if (r1 != 0) {
            MinimapSetCenterPos_324870((p0 + (((l0 * 0x24) - (l0 * 0x9)) << 4)), p1);
        }
        l0 = (l0 + 1);
    } while (l0 < 3);
    return 1;
}
