#include "types.h"

extern s32 UiFindWidget_290460(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiGetWidgetColor_2904b0(s32 p0, s32 p1)
{
    s32 r0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        return (r0 + 0x30);
    }
    return 0;
}
