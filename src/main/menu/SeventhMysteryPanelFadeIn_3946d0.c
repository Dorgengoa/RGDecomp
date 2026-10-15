#pragma opt_dead_assignments off
#include "types.h"

extern void StateMachineSetState_28ede0(void *arg0, s32 arg1, s32 arg2);
extern f32 *UiGetWidgetColor_2904b0(void *arg0, s32 arg1);
extern void UiFadeWidgetColor_2904e0(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void UiSetWidgetColor_2905b0(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
extern f32 D_0047D35C;
extern f32 D_0047D7D0;
extern u8 D_00483470;
extern u8 D_004E9550[0x400];

s32 SeventhMysteryPanelFadeIn_3946d0(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        UiSetWidgetColor_2905b0(D_004E9550, 5, D_0047D35C, D_0047D35C, D_0047D35C, -1.0f);
        UiFadeWidgetColor_2904e0(D_004E9550, 5, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D7D0);
    }
    if (*UiGetWidgetColor_2904b0(D_004E9550, 5) <= 1.0f) {
        StateMachineSetState_28ede0(&D_00483470, 0x7536, 0);
    }
    return 1;
}
