#include "types.h"

typedef struct S { s32 x0; s32 x4; u8 pad[0x14]; f32 x1C; } S;
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void *UiEntryListGetCurrentData_28ec60(s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void TextEntrySetState_434410(S *, s32, s32);
extern s16 D_00484128;
extern u8 D_004B2570[0x40];

s32 TextEntryDialogInputState_433090(S *arg0, s32 arg1)
{
    s32 r;
    u8 *p;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(arg0->x4, 0x6D63, 0);
    }
    r = MenuGridCursorInput_28e170(arg0->x4, D_004B2570, 0, 0);
    p = (u8 *)UiEntryListGetCurrentData_28ec60(arg0->x4);
    if (r == 1) {
        if (*(s16 *)(p + 0x10) == 0) {
            UiFadeWidgetAlpha_290690(arg0->x0, 0xF, 0.0f, arg0->x1C, -1.0f);
            TextEntrySetState_434410(arg0, 0x6D63, 0);
            D_00484128 = 1;
        } else {
            TextEntrySetState_434410(arg0, 0x6D69, 0);
        }
    } else if (r == 2) {
        TextEntrySetState_434410(arg0, 0x6D69, 0);
    }
    return 1;
}
