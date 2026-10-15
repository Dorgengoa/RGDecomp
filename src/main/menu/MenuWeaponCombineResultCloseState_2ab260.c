#include "types.h"

extern void *GetGameData_1fede0(void);
extern void ReturnZero_207fe0(void);
extern void UiSelFrameAnimStep_28d820(void *arg0, s32 arg1);
extern void UiEntryListSelectByTag_28ea90(s32 arg0, s32 arg1, s32 arg2);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void UiSetWidgetsVisibleById_291110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(void *arg0);
extern void MenuWeaponCombineAutoHideTick_362700(void *arg0);
extern void InvClearNewFlagsMaybe_3c3490(s32 arg0);
extern const f32 D_0047D72C __attribute__((section(".sdata")));
extern f32 D_0047D730;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern void *D_00482374;
extern void *D_00482384;
extern u8 D_004DB430[];

s32 MenuWeaponCombineResultCloseState_2ab260(s32 arg0, s32 arg1)
{
    s32 arg_h1;

    void *temp_16;

    if (arg1 != 0) {
        ReturnZero_207fe0();
        *(s32*)((u8 *)D_00482374 + 0x2C) = -1;
        *(s32*)((u8 *)D_00482374 + 0x30) = -1;
        UiFadeWidgetAlpha_290690(D_00482360, 0x148, 0.0f, D_0047D72C, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x147, 0, 1);
    }
    temp_16 = D_00482384;
    MenuWeaponCombineAutoHideTick_362700(temp_16);
    MenuWeaponCombineAnimTickMaybe_361cd0(temp_16);
    arg_h1 = 0x78;
    UiSelFrameAnimStep_28d820(D_004DB430, arg_h1);
    *(s32*)((u8 *)D_00482384 + 0x7C) = 0;
    *(s8*)((u8 *)D_00482384 + 0x80) = 0;
    *(s8*)((u8 *)D_00482384 + 0x82) = 0;
    InvClearNewFlagsMaybe_3c3490(*(s32 *)((u8 *)GetGameData_1fede0() + 0x18));
    UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
    UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D730, -1.0f);
    UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D730, -1.0f);
    StateMachineSetState_28ede0(D_0048235C, 9, 0);
    return 1;
}
