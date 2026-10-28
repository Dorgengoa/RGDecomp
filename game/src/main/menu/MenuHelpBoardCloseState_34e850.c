/* rgp:protos */
#define RGP_SELF_MenuHelpBoardCloseState_34e850 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x1E0 vs retail 0x1DC, close. */
#include "types.h"

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
extern f32 D_0047D4B0;
extern f32 D_0047D5E4;
extern u8 D_0047F6E8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482EAC;
extern u8 D_00482EB8;

s32 MenuHelpBoardCloseState_34e850(s32 pad0, s32 arg1)
{
    s32 sp2C;
    s32 sp28;
    s32 temp_16;
    u8 var_2;

    if (arg1 != 0) {
        if (D_00482EB8 != 0) {
            MenuResLoad_299400();
        } else {
            var_2 = 1;
            D_0047F6E8 = var_2;
        }
    } else if (D_0047F6E8 == 0) {
        var_2 = MenuResLoadPoll_2992f0() != 0;
        D_0047F6E8 = var_2;
    }
    MenuOptionsHelpCloseSlideStep_34fd00();
    if (D_00482EAC == 3) {
        UiMoveWidget_290e00(D_00482360, 1, -0x40, -0x40, 3, D_0047D5E4, 0.0f);
        UiMoveWidgetUniform_290f50(D_00482360, 0x20F, 0x200, 0x4B, D_0047D4B0, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x20F, 0.0f, -0.0625f, -1.0f);
        D_00482EAC = 4;
    } else if (D_00482EAC == 4) {
        UiGetWidgetPos_2910a0(D_00482360, 1, &sp2C, &sp28);
        if ((sp2C == -0x40) && (sp28 == -0x40) && (D_0047F6E8 != 0)) {
            temp_16 = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x212, 0));
            UiSetSpriteSizeUvSize_28f670(D_00482360, 0x212, 0x40, 0x40, 0x40, 0x40, 0);
            if (temp_16 != 0) {
                UiLayoutPanelFrame_28d580(temp_16, 0, 0, 0x186, 0x12C, 0);
            }
            UiSetWidgetVisible_290010(D_00482360, 0x20F, 0, -1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 0, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21C, 0, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21D, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 2, 0);
        }
    }
    return 1;
}
