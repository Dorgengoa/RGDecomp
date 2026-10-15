#include "types.h"

extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void UiMoveWidget_290e00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiGetWidgetPos_2910a0(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3);
extern void MenuOptionsHelpCloseSlideStep_34fd00(void);
extern f32 D_0047D4B0;
extern f32 D_0047D5E4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482EAC;

s32 MenuOptionsCloseState_34fc20(void)
{
    s32 sp1C;
    s32 sp18;

    MenuOptionsHelpCloseSlideStep_34fd00();
    if (D_00482EAC == 3) {
        UiMoveWidget_290e00(D_00482360, 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x1B3, 0x200, 0x3C, 0, D_0047D4B0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1B3, 0, -0.0625f, -1.0f);
        D_00482EAC = 4;
    } else if (D_00482EAC == 4) {
        UiGetWidgetPos_2910a0(D_00482360, 1, &sp1C, &sp18);
        if ((sp1C == -0x40) && (sp18 == -0x40)) {
            StateMachineSetState_28ede0(D_0048235C, 2, 0);
        }

    }
    return 1;
}
