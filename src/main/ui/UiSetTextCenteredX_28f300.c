#include "types.h"

extern s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern void UiSetTextX_28f590(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UiSetTextCenteredX_28f300(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 rv1;

    r0 = UiGetWidgetTextWidth_28f400(p0, p1, p3);
    rv1 = (p2 - (r0 >> 1));
    if ((p2 - (r0 >> 1)) == -1) {
        rv1 = 0;
    }
    UiSetTextX_28f590(p0, p1, rv1, p3);
}
