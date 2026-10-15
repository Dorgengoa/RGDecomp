#include "types.h"

extern s32 UiPageGetLayout_289b60(s32);
extern s32 UiFindWidget_290460(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiPageFindWidget_289b00(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = UiPageGetLayout_289b60(p0);
    rv2 = r1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = UiFindWidget_290460(r0, p1);
        rv2 = r1;
    }
    return rv2;
}
