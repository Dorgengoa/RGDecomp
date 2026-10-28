/* rgp:protos */
#define RGP_SELF_MenuItemSectionEnter_2b3400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;

void MenuItemSectionEnter_2b3400(void) {
    s32 sp2C;
    s32 sp28;
    u8 *p;

    if (D_004824A8 < 6) {
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
        return;
    }
    if (D_004824A8 == 6) {
        p = UiEntryListFindByTag_28ea40(D_00482364, 6);
        GetGridCellPosOffset_28ecd0(p + 4, &sp2C, &sp28, 0x62, 0x49);
        UiSetWidgetPos_290f60(D_00482360, 0x227, sp2C, sp28);
        StateMachineSetState_28ede0(D_0048235C, 0x14, 0);
    } else if (D_004824A8 == 7) {
        p = UiEntryListFindByTag_28ea40(D_00482364, 8);
        GetGridCellPosOffset_28ecd0(p + 4, &sp2C, &sp28, 0x62, 0x49);
        UiSetWidgetPos_290f60(D_00482360, 0x227, sp2C, sp28);
        StateMachineSetState_28ede0(D_0048235C, 0x1A, 0);
    } else {
        p = UiEntryListFindByTag_28ea40(D_00482364, 7);
        GetGridCellPosOffset_28ecd0(p + 4, &sp2C, &sp28, 0x62, 0x49);
        UiSetWidgetPos_290f60(D_00482360, 0x227, sp2C, sp28);
        StateMachineSetState_28ede0(D_0048235C, 0x17, 0);
    }
    *(s16 *)(p + 0x14) = D_004824A0;
    *(s16 *)(p + 0x16) = D_004824A4;
}
