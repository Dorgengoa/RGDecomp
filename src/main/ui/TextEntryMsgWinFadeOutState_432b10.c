#include "types.h"

extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern f32 UiGetWidgetAlpha_290770(s32 arg0, s32 arg1);
extern void UiSetWidgetsVisibleById_291110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void TextEntrySetState_434410(void *arg0, s32 arg1, s32 arg2);
extern void TextEntryMarkStarCells_4357b0(s32 arg0, s32 arg1, s32 arg2);

s32 TextEntryMsgWinFadeOutState_432b10(void *arg0, s32 arg1)
{
    if (arg1 != 0) {
        TextEntryMarkStarCells_4357b0((s32)arg0, -1, -1);
        UiFadeWidgetAlpha_290690(*(s32 *)((u8 *)arg0 + 0x0), 0x13, 0, *(f32 *)((u8 *)arg0 + 0x1C), -1.0f);
    }
    if (UiGetWidgetAlpha_290770(*(s32 *)((u8 *)arg0 + 0x0), 0x13) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(*(s32 *)((u8 *)arg0 + 0x0), 0x13, 0, 1);
        TextEntrySetState_434410(arg0, 0x6D62, 0);
    }
    return 1;
}
