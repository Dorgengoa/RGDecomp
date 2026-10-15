#include "types.h"

extern s32 CageRecIsPlaced_3d0d20(s32);
extern s32 CageRecUnplace_3d0a70(s32);
extern s32 CageRecClearCatch_3d0960(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CageRecRecall_3d0a20(s32 p0)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = CageRecIsPlaced_3d0d20(p0);
    rv3 = 1;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        r1 = CageRecUnplace_3d0a70(p0);
        r2 = CageRecClearCatch_3d0960(p0);
        rv3 = 1;
    }
    return rv3;
}
