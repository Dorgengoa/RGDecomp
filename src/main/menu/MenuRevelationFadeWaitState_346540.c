#include "types.h"

extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern s32 D_00482360;

s32 MenuRevelationFadeWaitState_346540(void)
{
    s32 t0;
    f32 r0;
    s32 t1;

    t0 = D_00482360;
    r0 = UiGetWidgetAlpha_290770(t0, 0x65);
    if (r0 <= 0.0f) {
        t1 = D_0048235C;
        StateMachineSetState_28ede0(t1, 0x7A, 0);
    }
    return 1;
}
