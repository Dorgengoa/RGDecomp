#include "types.h"

extern const f32 D_0047D708 __attribute__((section(".sdata")));
extern void *D_00482360 __attribute__((section(".sdata")));
extern void *D_0048235C __attribute__((section(".sdata")));
extern const u8 D_004DB430[];

extern void UiFadeWidgetAlpha_290690(void *a, s32 b, f32 c, f32 d, f32 e);
extern void StateMachineSetState_28ede0(void *a, s32 b, s32 c);
extern void UiSelFrameAnimStep_28d820(const u8 *a, s32 b);

s32 MenuPartyListCloseState_2a69c0(void)
{
    UiFadeWidgetAlpha_290690(D_00482360, 0x99, 0.0f, D_0047D708, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482360, 0x9C, 0.0f, *(volatile const f32 *)&D_0047D708, -1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
