#include "types.h"

extern s32 UiSetWidgetVisible_290010(void *, s32, s32, s32);
extern f32 *UiGetWidgetColor_2904b0(void *, s32);
extern s32 UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(void *, s32);
extern f32 D_0047D7C8;
extern s8 D_00483480;
extern s8 D_00483498;
extern s8 D_004E9550[0x100];

s32 SeventhMysteryCloseState_394a90(void)
{
    if (*UiGetWidgetColor_2904b0(D_004E9550, 5) <= 1.0f) {
        UiFadeWidgetAlpha_290690(D_004E9550, 1, 0.0f, D_0047D7C8, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_004E9550, 1) <= 0.0f) {
        UiSetWidgetVisible_290010(D_004E9550, 1, 0, -1);
        D_00483480 = 0;
        D_00483498 = 0;
    }
    return 1;
}
