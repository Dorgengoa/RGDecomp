#include "types.h"

extern s32 MinimapSlotGetName_322520(s32);
extern void MinimapPresetExplored_32b100(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MinimapMgrPresetExploredAll_321700(s32 p0)
{
    s32 l0;
    s32 r1;

    l0 = 0;
    while (l0 < 3) {
        if ((p0 + (((l0 * 0x24) - (l0 * 0x9)) << 4)) == 0) {
            return;
        }
        r1 = MinimapSlotGetName_322520((p0 + (((l0 * 0x24) - (l0 * 0x9)) << 4)));
        MinimapPresetExplored_32b100(r1);
        l0 = (l0 + 1);
    }
}
