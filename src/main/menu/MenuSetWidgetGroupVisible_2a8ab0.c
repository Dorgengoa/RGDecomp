#include "types.h"

extern void UiSetWidgetListVisible_28c120(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461430[];
extern s32 D_00482360;

void MenuSetWidgetGroupVisible_2a8ab0(s32 p0)
{
    s32 t0;

    t0 = D_00482360;
    UiSetWidgetListVisible_28c120(t0, D_00461430, (p0 != 0));
}
