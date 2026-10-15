#include "types.h"

extern s32 Bit64Test_33de60(s32, s32);
extern s32 UiPanelStep_33d590(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiPanelStepIfOpen_33de10(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = Bit64Test_33de60(p0, 0);
    rv2 = 1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = UiPanelStep_33d590(p0);
        rv2 = 1;
    }
    return rv2;
}
