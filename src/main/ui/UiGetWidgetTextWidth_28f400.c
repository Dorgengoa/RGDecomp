#include "types.h"

extern s32 UiGetWidgetTextSize_28f430(s32, s32, void *, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiGetWidgetTextWidth_28f400(s32 p0, s32 p1, s32 p2)
{
    s32 v1C;
    s32 v18;
    s32 r0;
    s32 t0;

    r0 = UiGetWidgetTextSize_28f430(p0, p1, &v1C, &v18, p2);
    t0 = v1C;
    return t0;
}
