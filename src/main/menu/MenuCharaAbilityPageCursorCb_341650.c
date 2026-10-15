#pragma opt_propagation off
#include "types.h"
#pragma opt_common_subs off

extern s32 PadIsTriggered_1839f0(void *arg0, s32 arg1);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
extern void UiSetWidgetPos_290f60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void MenuCharaAbilityPageFill_3406a0(void *arg0, s8 arg1, s16 arg2);
extern void MenuCycleCharaSel_341220(void *arg0, s32 arg1);
extern f32 D_0047D34C;
extern s32 D_00482360;
extern void *D_00482378;
extern u8 D_004B2570[0xA000];

s32 MenuCharaAbilityPageCursorCb_341650(void *arg0)
{
    u8 *p;
    s16 k;
    f32 sc;
    f32 fx;
    s32 ka,kb;
    f32 a,b;

    if (PadIsTriggered_1839f0(D_004B2570, 0xA000) != 0) {
        MenuCycleCharaSel_341220(arg0, 0);
    } else {
    p = D_00482378;
    ka=*(s16 *)(p+0x76);kb=*(s16*)((u8*)arg0+0x12);
    if(kb==ka) {
        a=*(f32 *)(p+0x70);b=(f32)*(s16*)((u8*)arg0+0x16);
        UiMoveWidgetUniform_290f50(D_00482360, 0x19A, 0x180, (s32)(48.0f + b*a), D_0047D34C, 0);
        p = D_00482378;
        MenuCharaAbilityPageFill_3406a0(p, *(s8 *)(p + 0x6C), *(s16 *)((u8 *)arg0 + 0x16));
    }
    UiSetWidgetPos_290f60(D_00482360, 0x18D, 0, *(s16 *)((u8 *)arg0 + 0x12) * *(s16 *)((u8 *)arg0 + 0x6));
    *(s16 *)((u8 *)D_00482378 + 0x76) = *(s16 *)((u8 *)arg0 + 0x12);
    }
    return 1;
}
