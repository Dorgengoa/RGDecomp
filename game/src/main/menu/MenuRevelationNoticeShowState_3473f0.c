/* rgp:protos */
#define RGP_SELF_MenuRevelationNoticeShowState_3473f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_004823D8;

s32 MenuRevelationNoticeShowState_3473f0(s32 arg0, s32 arg1)
{
    (void) arg0;
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x64, 1.0f);
        UiSetTextString_28f510(D_00482360, 0x64, MsgTableLookup_28aa30(D_004823D8, 0x103A), 0);
        UiSetTextCenteredX_28f300(D_00482360, 0x64, 0x79, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x64, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x64, 0x83, 0xDE);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x77, 0);
    return 1;
}
