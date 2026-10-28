/* rgp:protos */
#define RGP_SELF_TextEntryDialogInputState_433090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { s32 x0; s32 x4; u8 pad[0x14]; f32 x1C; } S;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
