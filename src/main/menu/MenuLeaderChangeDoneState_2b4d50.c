#include "types.h"

extern void UiSetWidgetColor_2905b0(void *, s32, f32, f32, f32, f32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void *D_00482360;
extern void *D_0048235C;

s32 MenuLeaderChangeDoneState_2b4d50(void)
{
    UiSetWidgetColor_2905b0(D_00482360, 0x132, 1.0f, 1.0f, 1.0f, 1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x4B, 0);
    return 1;
}
