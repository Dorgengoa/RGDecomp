#pragma opt_propagation off
#include "types.h"

extern s32 UiGetWidgetSprite_28fe10(s32, u16, s32);
extern void UiGetWidgetAbsPos_290fc0(s32, u16, s32 *, s32 *);
extern u16 D_0047FB04;

void SaveMsgBoxGetYesNoCursorPos_3770b0(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3)
{
    s32 spArr[2];
    u8 *temp_5;
    s32 *pp;

    if (arg0 != 0) {
        spArr[0] = UiGetWidgetSprite_28fe10(arg0, D_0047FB04, 9);
        spArr[1] = UiGetWidgetSprite_28fe10(arg0, D_0047FB04, 0xA);
        UiGetWidgetAbsPos_290fc0(arg0, D_0047FB04, arg2, arg3);
        pp = &spArr[arg1];
        temp_5 = (u8 *)*pp;
        if (temp_5 != NULL) {
            *arg2 += *(s16 *)(temp_5 + 0);
            *arg3 += *(s16 *)(temp_5 + 2);
        }
        *arg2 -= 0x1E;
        *arg3 -= 2;
    }
}
