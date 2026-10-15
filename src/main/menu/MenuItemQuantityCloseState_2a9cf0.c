#include "types.h"

extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern const volatile f32 D_0047D6F8 __attribute__((section(".sdata")));
extern const volatile f32 D_0047D6FC __attribute__((section(".sdata")));
extern s32 D_0048235C;
extern s32 D_00482360;
extern void *D_00482374;

s32 MenuItemQuantityCloseState_2a9cf0(void)
{
    s8 temp_3;

    UiFadeWidgetAlpha_290690(D_00482360, 0x8A, 0.0f, D_0047D6F8, -1.0f);
    temp_3 = *(s8 *)((u8 *)D_00482374 + 0x40);
    if(temp_3==1){
        StateMachineSetState_28ede0(D_0048235C, 0x34, 0);
    }else if(temp_3==2){
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D6FC, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x37, 0);

    }
    return 1;
}
