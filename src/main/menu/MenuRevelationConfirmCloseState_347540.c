#include "types.h"

extern void *D_00482360;
extern void *D_0048235C;
extern s16 D_00482E38;
extern f32 D_0047D664;
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(void *, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);

s32 MenuRevelationConfirmCloseState_347540(void *a, s32 b)
{
    f32 r;
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x5D, 0.0f, D_0047D664, -1.0f);
    }
    r = UiGetWidgetAlpha_290770(D_00482360, 0x5D);
    if (r <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x5D, 0, 1);
        if (D_00482E38 != 0) {
            StateMachineSetState_28ede0(D_0048235C, 0x8C, 0);
        } else {
            StateMachineSetState_28ede0(D_0048235C, 0x8A, 0);
        }
    }
    return 1;
}
