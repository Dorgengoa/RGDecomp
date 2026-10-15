#include "types.h"

extern void StateMachineSetState_28ede0(s32 a, s32 b, s32 c);
extern void UiSetWidgetVisible_290010(s32 a, s32 b, s32 c, s32 d);
extern void UiFadeWidgetAlpha_290690(s32 a, s32 b, f32 c, f32 d, f32 e);
extern void UiMoveWidgetUniform_290f50(s32 a, s32 b, s32 c, s32 d, s32 e, f32 f);
extern void UiSetWidgetPos_290f60(s32 a, s32 b, s32 c, s32 d);
extern void UiSetWidgetsVisibleById_291110(s32 a, s32 b, s32 c, s32 d);

extern f32 D_0047D638;
extern s32 D_0048235C;
extern s32 D_00482360;

s32 MenuHelpPanelSlideInState_34e0e0(s32 arg0, s32 arg1)
{
    (void) arg0;
    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21C, 0, 1);
        UiSetWidgetVisible_290010(D_00482360, 0x20F, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x20F, 0x200, 0x4B);
        UiMoveWidgetUniform_290f50(D_00482360, 0x20F, 0x5A, 0x4B, 0, D_0047D638);
        UiFadeWidgetAlpha_290690(D_00482360, 0x20F, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 0, 1);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x83, 0);
    return 1;
}
