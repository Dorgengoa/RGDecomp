#include "types.h"

typedef struct T_0039e410 {
    u8 pad0[0x12];
    s16 f12;
} T_0039e410;

extern u8 D_004E96D0[];
extern u8 D_004E96B0[];
extern u8 D_004B2570[];
extern s32 D_0048369C;
extern s32 D_00483690;
extern f32 D_0047D7CC;
extern void UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern T_0039e410 *UiEntryListGetCurrentData_28ec60(void *);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);

s32 CompleteCheckCategorySelectState_39e410(s32 a, s32 flag)
{
    s32 r;
    T_0039e410 *t;
    s32 x;
    if (flag != 0) {
        UiEntryListSelectByTag_28ea90(D_004E96D0, 0x7531, 0);
        UiFadeWidgetAlpha_290690(D_004E96B0, 7, 1.0f, D_0047D7CC, -1.0f);
        goto one;
    }
    r = MenuGridCursorInput_28e170(D_004E96D0, D_004B2570, 4, 0);
    t = UiEntryListGetCurrentData_28ec60(D_004E96D0);
    if (r == 1) {
        x = MsgTableLookup_28aa30(D_0048369C, t->f12 + 0xA);
        UiSetTextString_28f510(D_004E96B0, 8, x, 0);
        UiFadeWidgetAlpha_290690(D_004E96B0, 7, 0.0f, D_0047D7CC, -1.0f);
        StateMachineSetState_28ede0(&D_00483690, 0x7534, 0);
    } else if (r == 2) {
        StateMachineSetState_28ede0(&D_00483690, 0x7533, 0);
    }
one:
    return 1;
}
