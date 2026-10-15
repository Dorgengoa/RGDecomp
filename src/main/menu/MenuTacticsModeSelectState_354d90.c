#include "types.h"

extern void PlayMenuSe_289ef0(s32 arg0);
extern s32 MenuGridCursorInput_28e170(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern void *UiEntryListGetCurrentData_28ec60(s32 arg0);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetColor_2904e0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void UiSetWidgetColor_2905b0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
extern void OptionsSetTacticsMode_3d5f50(s32 arg0, s32 arg1);
extern void *GetGameData_1fede0(void);

extern f32 D_0047D5FC;
extern f32 D_0047D608;
extern f32 D_0047F7B0;
extern f32 D_0047F7B4;
extern f32 D_0047F7B8;
extern f32 D_0047F7BC;
extern s32 D_0048235C;
extern s32 D_00482364;
extern s32 D_0048236C;
extern s16 D_00482F10;
extern u8 D_004B2570[0x400];

s32 MenuTacticsModeSelectState_354d90(void)
{
    f32 sp30[4];
    s32 temp_17;
    void *temp_16;
    void *temp_a;

    temp_17 = MenuGridCursorInput_28e170(D_00482364, &(*(u8 *)D_004B2570), 5, 0);
    temp_16 = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (temp_17 == 2) {
        D_00482F10 = 0;
        PlayMenuSe_289ef0(6);
        StateMachineSetState_28ede0(D_0048235C, 0x9E, 0);
    } else if (temp_17 == 1) {
        D_00482F10 = 1;
        sp30[0] = D_0047F7B0;
        sp30[1] = D_0047F7B4;
        sp30[2] = D_0047F7B8;
        sp30[3] = D_0047F7BC;
        PlayMenuSe_289ef0(3);
        temp_a = GetGameData_1fede0();
        OptionsSetTacticsMode_3d5f50(*(s32 *)((u8 *)temp_a + 0xC), *(s32 *)((u8 *)sp30 + *(s16 *)((u8 *)temp_16 + 0x12) * 4));
        UiSetWidgetColor_2905b0(D_0048236C, 2, D_0047D608, D_0047D608, D_0047D608, -1.0f);
        UiFadeWidgetColor_2904e0(D_0048236C, 2, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D5FC);
        StateMachineSetState_28ede0(D_0048235C, 0x9E, 0);
    }
    return 1;
}
