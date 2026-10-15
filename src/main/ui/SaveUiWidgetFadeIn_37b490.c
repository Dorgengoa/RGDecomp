#include "types.h"

extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D34C;
extern s32 D_004831D4;

void SaveUiWidgetFadeIn_37b490(s32 p0)
{
    s32 t0;
    s32 t1;
    s32 t2;
    f32 t3;

    t0 = D_004831D4;
    if (t0 != 0) {
        UiSetWidgetsVisibleById_291110(t0, (p0 & 0xFFFF), 1, 1);
        t1 = D_004831D4;
        UiSetWidgetAlpha_2907a0(t1, (p0 & 0xFFFF), 0.0f);
        t2 = D_004831D4;
        t3 = D_0047D34C;
        UiFadeWidgetAlpha_290690(t2, (p0 & 0xFFFF), 1.0f, t3, -1.0f);
        return;
    }
}
