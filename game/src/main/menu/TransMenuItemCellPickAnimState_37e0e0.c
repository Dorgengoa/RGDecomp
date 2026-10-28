/* rgp:protos */
#define RGP_SELF_TransMenuItemCellPickAnimState_37e0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S37e0e0 {
    u8 pad00[0x1C];
    u8 m1C;
} S37e0e0;

extern void *D_00484720;
extern void *D_00484710;
extern void *D_0048470C;
extern S37e0e0 *D_00484740;
extern f32 D_0047D81C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemCellPickAnimState_37e0e0(s32 unused, s32 en)
{
    s32 a;
    s32 b;
    s16 *r;
    s32 x;
    s32 y;

    if (en != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0xB, 0);
        r = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00484720));
        x = r[0] + r[8] * r[2] + 0x33;
        y = r[1] + r[9] * r[3] + 0x11;
        MenuItemCellPickSetup_2a3bc0(D_00484740, 0x7607, 0x7608, 0x7603, r[8], r[9]);
        MenuShowItemCount_2a02f0(D_00484740, 0x7602, 0x7600, 0x7603, r[8] + r[9] * 8);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7607, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00484710, 0x7607, 1.0f);
        UiSetWidgetPos_290f60(D_00484710, 0x7607, x + 0xB, y + 0xF);
        UiMoveWidget_290e00(D_00484710, 0x7607, x, y, 1, D_0047D81C, 3.0f);
        PlayMenuSe_289ef0(7);
    }
    r = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00484720));
    x = r[0] + r[8] * r[2] + 0x33;
    y = r[1] + r[9] * r[3] + 0x11;
    UiGetWidgetPos_2910a0(D_00484710, 0x7607, &a, &b);
    if (a == x) {
        if (b == y) {
            D_00484740->m1C = 1;
            StateMachineSetState_28ede0(D_0048470C, 0x37, 1);
        }
    }
    return 1;
}
