#include "types.h"

extern const f32 D_0047D968 __attribute__((section(".sdata")));
extern void *D_00484710 __attribute__((section(".sdata")));
extern void *D_0048470C __attribute__((section(".sdata")));
extern const u8 D_004E9230[];

extern void UiFadeWidgetAlpha_290690(void *a, s32 b, f32 c, f32 d, f32 e);
extern void StateMachineSetState_28ede0(void *a, s32 b, s32 c);
extern void UiSelFrameAnimStep_28d820(const u8 *a, s32 b);

s32 TransMenuItemPartyListCloseState_37c4a0(void)
{
    UiFadeWidgetAlpha_290690(D_00484710, 0x7617, 0.0f, D_0047D968, -1.0f);
    UiFadeWidgetAlpha_290690(D_00484710, 0x761A, 0.0f, *(volatile const f32 *)&D_0047D968, -1.0f);
    StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
