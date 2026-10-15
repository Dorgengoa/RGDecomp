/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- `const` +
   __attribute__((section(".sdata"))) on the gp float extern(s) this unit
   READS.  The barrier it removes is the surrounding stores, not a write to
   the symbol; const-ing only the floats is right, const-ing every extern
   goes length-wrong. */
#include "types.h"

extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern const f32 D_0047D440 __attribute__((section(".sdata")));
extern const f32 D_0047D470 __attribute__((section(".sdata")));
extern const f32 D_0047D564 __attribute__((section(".sdata")));
extern const f32 D_0047D57C __attribute__((section(".sdata")));
extern const f32 D_0047D580 __attribute__((section(".sdata")));
extern s32 D_0048235C;
extern s32 D_00482360;
extern void *D_0048238C;

s32 RevelationBoardFadeInStateMaybe_345df0(s32 arg0, s32 arg1)
{
    if (arg1 != 0) {
        *(u8 *)((u8 *)D_0048238C + 0x7A2) = 0;
        UiFadeWidgetAlpha_290690(D_00482360, 0x47, 1.0f, D_0047D57C, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4F, 1.0f, D_0047D564, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x4B, 1.0f, D_0047D580, -1.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x4B, 0xC, 0x153, 0, D_0047D440);
    }
    if (!(UiGetWidgetAlpha_290770(D_00482360, 0x47) <= D_0047D470)) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x24F, 0, 1);
        StateMachineSetState_28ede0(D_0048235C, 0x8A, 0);
    }
    return 1;
}
