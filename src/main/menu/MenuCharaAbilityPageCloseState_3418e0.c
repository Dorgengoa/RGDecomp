#include "types.h"

extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 fa, f32 fb, f32 fc);
extern void UiMoveWidgetUniform_290f50(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, f32 fa0);
extern s32 StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);

extern s32 D_0048235C;
extern s32 D_00482360;
extern f32 D_0047D650;
extern f32 D_0047D654;
extern f32 D_0047D658;

s32 MenuCharaAbilityPageCloseState_3418e0(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 0.0f, D_0047D650, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x18D, 0.0f, D_0047D654, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, -0x28, 0, D_0047D658);
        UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, -0x25, 0, D_0047D658);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x6E, 0);
    return 1;
}
