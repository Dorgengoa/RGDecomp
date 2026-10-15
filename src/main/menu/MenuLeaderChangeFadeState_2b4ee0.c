#include "types.h"

extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D680;

s32 MenuLeaderChangeFadeState_2b4ee0(s32 a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x132, 0.0f, D_0047D680, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x68, 0);
    }
    return 1;
}
