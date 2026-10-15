#include "types.h"

extern void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuPartyCloseSlideStep_2ba6e0(void);
extern f32 D_0047D5E4;
extern f32 D_0047D614;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482564;

s32 MenuPartyCloseState_2ba580(s32 arg0, s32 arg1)
{
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    if (arg1 != 0) {
        UiGetWidgetPos_2910a0(D_00482360, 0xB6, &sp2C, &sp28);
        UiMoveWidget_290e00(D_00482360, 0xB6, 0x264, sp28, 3, D_0047D614, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB6, 0.0f, 0.0625f, 1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 2, 1, 1);
    }
    MenuPartyCloseSlideStep_2ba6e0();
    UiGetWidgetPos_2910a0(D_00482360, 0x17, &sp24, &sp20);
    if (sp24 == -0x12 && sp20 == 0xC) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 1, 0x17, 0xE, D_00482360);
    }
    if (D_00482564 == 3) {
        UiMoveWidget_290e00(D_00482360, 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        D_00482564 = 4;
    } else if (D_00482564 == 4) {
        UiGetWidgetPos_2910a0(D_00482360, 1, &sp1C, &sp18);
        if (sp1C == -0x40 && sp18 == -0x40) {
            StateMachineSetState_28ede0(D_0048235C, 2, 0);
        }
    }
    return 1;
}
