#include "types.h"

extern const f32 D_0047D6D0 __attribute__((section(".sdata")));
extern void *D_00482360;
extern void *D_0048235C;

extern void UiFadeWidgetAlpha_290690(void *p, s32 id, f32 a, f32 b, f32 c);
extern void StateMachineSetState_28ede0(void *p, s32 id, s32 z);

s32 MenuItemUseTargetCloseState_2ae440(void)
{
    f32 g = D_0047D6D0;

    UiFadeWidgetAlpha_290690(D_00482360, 0x8D, 0.0f, g, -1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    return 1;
}
