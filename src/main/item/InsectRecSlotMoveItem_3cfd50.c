#include "types.h"

extern s32 InsectRecSlotAddItem_3d0190(s32, s32);
extern void InsectRecSlotRemoveItem_3cfde0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004838E8;

s32 InsectRecSlotMoveItem_3cfd50(s32 p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 rv4;
    s32 rv3;
    s32 r0;
    s32 rv2;

    t0 = D_004838E8;
    if (t0 == 0) {
        return 0;
    }
    if (p1 == 0) {
        rv4 = 0;
    } else {
        if (p2 == 0) {
            rv3 = 0;
        } else {
            r0 = InsectRecSlotAddItem_3d0190(p0, p2);
            rv2 = 1;
            if ((r0 & 0xFF) == 0) {
                rv2 = 0;
            } else {
                InsectRecSlotRemoveItem_3cfde0(p1, p2, 0);
                rv2 = 1;
            }
            rv3 = rv2;
        }
        rv4 = rv3;
    }
    return rv4;
}
