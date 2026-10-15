#include "types.h"

extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuItemHideWidgets_2a5a60(s32);
extern f32 D_0047D5D0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482374;

s32 MenuRevelationItemCloseState_3469d0(s32 arg0, s32 arg1)
{
    if (arg1 != 0) {
        UiMoveWidgetUniform_290f50(D_00482360, 0x65, 0x200, 0x49, 0, D_0047D5D0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x65, 0.0f, -2.0f, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A9, 0.0f, -2.0f, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, -2.0f, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00482360, 0x65) <= 0.0f) {
        UiSetWidgetVisible_290010(D_00482360, 0x65, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x7E, 0, -1);
        UiSetWidgetVisible_290010(D_00482360, 0x8A, 0, -1);
        MenuItemHideWidgets_2a5a60(D_00482374);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x227, 0, 1);
        StateMachineSetState_28ede0(D_0048235C, 0x8A, 0);
    }
    return 1;
}
