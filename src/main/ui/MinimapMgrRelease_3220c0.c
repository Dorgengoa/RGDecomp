#include "types.h"

extern s32 MinimapSlotIsActive_322510(s32);
extern s32 MinimapSlotRelease_322490(s32);
extern s32 MinimapMgrFindSlotByName_322340(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MinimapMgrRelease_3220c0(s32 p0, s32 p1)
{
    s32 l0;
    s32 r1;
    s32 r3;
    s32 rv7;
    s32 r4;
    s32 rv6;
    s32 r5;

    if (p1 == 0) {
        l0 = 0;
        do {
            r1 = MinimapSlotIsActive_322510((p0 + l0 * 432));
            if (r1 != 0) {
                MinimapSlotRelease_322490((p0 + l0 * 432));
            }
            l0 = (l0 + 1);
        } while (l0 < 3);
        return;
    }
    r3 = MinimapMgrFindSlotByName_322340(p0, p1);
    rv7 = r3;
    if (r3 != 0) {
        r4 = MinimapSlotIsActive_322510(r3);
        rv6 = 0;
        if (r4 != 0) {
            r5 = MinimapSlotRelease_322490(r3);
            rv6 = r5;
        }
        rv7 = rv6;
    }
}
