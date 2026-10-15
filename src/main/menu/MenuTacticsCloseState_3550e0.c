#include "types.h"

extern void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern s32 UiWidgetIsMoving_290d30(s32, s32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiGetWidgetPos_2910a0(s32, s32, void *, s32 *);
extern void MenuTacticsCloseSlideStep_3551f0(void);
extern f32 D_0047D5E4;
extern f32 D_0047D614;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482F24;

s32 MenuTacticsCloseState_3550e0(s32 arg0_unused, s32 arg1) {
    u8 sp1C[4];
    s32 sp18;

    if (arg1 != 0) {
        UiGetWidgetPos_2910a0(D_00482360, 0xBB, sp1C, &sp18);
        UiMoveWidget_290e00(D_00482360, 0xBB, 0x264, sp18, 3, D_0047D614, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0xBB, 0.0f, 0.0625f, 1.0f);
    }
    MenuTacticsCloseSlideStep_3551f0();
    if (UiWidgetIsMoving_290d30(D_00482360, 0x18) == 0) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 2, 0x18, 0xF, D_00482360);
    }
    if (D_00482F24 == 3) {
        UiMoveWidget_290e00(D_00482360, 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        D_00482F24 = 4;
    } else if (D_00482F24 == 4) {
        if (UiWidgetIsMoving_290d30(D_00482360, 1) == 0) {
            StateMachineSetState_28ede0(D_0048235C, 2, 0);
        }
    }
    return 1;
}
