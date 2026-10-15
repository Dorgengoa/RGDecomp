/* main s27m: CLOSED -- UiFadeWidgetAlpha_290690 takes THREE f32s (the `0` is `mtc1 $zero,$f12`),
   D_0047D670 const+.sdata, its SECOND read volatile so it is not CSEd across the call. */
/* PARK: same length as retail, 8 bad words. Residue is the mtc1/lwc1/addiu
   argument-setup ORDER for the float+int args feeding the two
   UiFadeWidgetAlpha_290690(...) calls (D_0047D670 and -1.0f land in different FPU
   register/order than retail). Tried hoisting D_0047D670 into a temp
   before each call to force evaluation order -- no change, same 8 bad.
   Looks like an ABI argument-slot scheduling tie-break, not a spelling. */
#include "types.h"

extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void MenuCharaAbilityInfoBoxSetup_29afe0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6);
extern f32 D_0047D5D0;
extern const f32 D_0047D670 __attribute__((section(".sdata")));
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482370;

s32 MenuCharaAbilityListCloseState_2b4910(void)
{
    UiFadeWidgetAlpha_290690(D_00482360, 0x121, 0.0f, D_0047D670, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482360, 0x123, 0.0f, *(volatile f32 *)&D_0047D670, -1.0f);
    MenuCharaAbilityInfoBoxSetup_29afe0(D_00482370, 0, 0x1AA, 0x1A9, 0x5D, 0x146, D_0047D5D0);
    StateMachineSetState_28ede0(D_0048235C, 0x4B, 0);
    return 1;
}
