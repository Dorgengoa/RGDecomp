/* rgp:protos */
#define RGP_SELF_MenuMemberListCloseState_342530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s16 D_00482D04;
extern s32 D_00482364;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5E4;
extern f32 D_0047D614;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482D24;

s32 MenuMemberListCloseState_342530(s32 arg0, s32 arg1)
{
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    if (arg1 != 0) {
        UiGetWidgetPos_2910a0(D_00482360, 0x187, &sp2C, &sp28);
        UiMoveWidget_290e00(D_00482360, 0x187, 0x264, sp28, 3, D_0047D614, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x187, 0.0f, 0.0625f, 1.0f);
        D_00482D04 = 0;
        GameDataUnlockByMinGaugeLevelMaybe_3e4110(((s32)GetGameData_1fede0()), 0, 0, 0);
    }
    MenuMemberListCloseSlideStep_3426a0();
    UiGetWidgetPos_2910a0(D_00482360, 0x19, &sp24, &sp20);
    if (sp24 == -0x12 && sp20 == 0xC) {
        UiPlaceRowWidgetPairMaybe_28cf40(0, 3, 0x19, 0x10, D_00482360);
    }
    if (D_00482D24 == 3) {
        UiMoveWidget_290e00(D_00482360, 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        D_00482D24 = 4;
    } else if (D_00482D24 == 4) {
        UiGetWidgetPos_2910a0(D_00482360, 1, &sp1C, &sp18);
        if (sp1C == -0x40 && sp18 == -0x40) {
            { u8 *p = UiEntryListFindByTag_28ea40(D_00482364,0x19); *(s16 *)(p+0x1A)=0; *(s16 *)(p+0x16)=0; }
            StateMachineSetState_28ede0(D_0048235C, 2, 0);
        }
    }
    return 1;
}
