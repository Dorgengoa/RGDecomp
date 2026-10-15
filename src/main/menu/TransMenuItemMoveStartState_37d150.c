#include "types.h"

extern void *D_00484710;
extern void *D_0048470C;
extern f32 D_0047D974;
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void StateMachineSetState_28ede0(void *, s32, s32);

s32 TransMenuItemMoveStartState_37d150(void *p, s32 flag)
{
    if (flag != 0) {
        UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 1.0f, D_0047D974, -1.0f);
        StateMachineSetState_28ede0(D_0048470C, 0x36, 0);
    }
    return 1;
}
