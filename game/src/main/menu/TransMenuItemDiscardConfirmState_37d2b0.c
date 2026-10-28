/* rgp:protos */
#define RGP_SELF_TransMenuItemDiscardConfirmState_37d2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047D93C;
extern f32 D_0047D970;
extern f32 D_0048323C;
extern s8 D_00483250;
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern u8 D_004B2570[];
extern u8 D_004E9230[];

s32 TransMenuItemDiscardConfirmState_37d2b0(s32 arg0, s32 arg1) {
    s32 r;
    s32 h;

    if (arg1 != 0) {
        h = MenuGetSelItem_2a02d0(D_00484740);
        if (h == 0) {
            return 0;
        }
        {
            s32 g = D_00484740;
            s16 *p = *(s16 **)(h + 0x10);
            TransMenuItemDiscardDialogSetText_37d5d0(*p, *(s32 *)(g + 0x3C));
        }
        UiSetWidgetsVisibleById_291110(D_00484710, 0x761E, 1, 1);
        UiSetWidgetPos_290f60(D_00484710, 0x761E, 0x80, 0xA0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x761E, 1.0f, D_0047D970, 0.0f);
        D_00483250 = 1;
        MenuYesNoHighlightMaybe_380560(1, D_00484710, 0x7620);
        UiSetWidgetPos_290f60(D_00484710, 0x7621, 0xA0, 0x3D);
        UiEntryListSelectByTag_28ea90(D_00484720, 0xF, 0);
    } else {
        r = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 0, 0);
        UiEntryListGetCurrentData_28ec60(D_00484720);
        if (r == 1) {
            if (D_00483250 == 0) {
                h = MenuGetSelItem_2a02d0(D_00484740);
                if (h == 0) {
                    return 0;
                }
                ItemConsume_3d41b0(h, *(s32 *)(D_00484740 + 0x3C), 0, 0);
                MenuShowMoneyAndItemCounts_2a32d0(D_00484740, 0x754A, 0x7549);
            }
            StateMachineSetState_28ede0(D_0048470C, 0x2C, 0);
        } else if (r == 2) {
            StateMachineSetState_28ede0(D_0048470C, 0x2C, 0);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
            if (D_00483250 == 1) {
                PlayMenuSe_289ef0(4);
            }
            D_00483250 = 0;
            MenuYesNoHighlightMaybe_380560(0, D_00484710, 0x7620);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
            if (D_00483250 == 0) {
                PlayMenuSe_289ef0(4);
            }
            D_00483250 = 1;
            MenuYesNoHighlightMaybe_380560(1, D_00484710, 0x7620);
        }
    }
    PhaseAdvanceWrapPi_28b630(&D_0048323C, D_0047D93C);
    {
        f32 t = 8.0f * Sinf_128fd0(D_0048323C);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7621, (s32)(t + (f32)((D_00483250 + 1) * 0x50)), 0x3D, 0.25f, 0);
    }
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
