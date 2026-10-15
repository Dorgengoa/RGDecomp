#include "types.h"

extern s32 TextStyleHasClipRect_26f5f0(s32);
extern s32 GsPktSetScissorFull_26fe60(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FontResetScissor_26e340(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = TextStyleHasClipRect_26f5f0(p0);
    rv2 = r0;
    if (r0 != 0) {
        r1 = GsPktSetScissorFull_26fe60(p1);
        rv2 = r1;
    }
    return rv2;
}
