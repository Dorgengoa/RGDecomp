/* rgp:protos */
#define RGP_SELF_MenuItemCmdPopupOpenState_2ac400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482360;
extern void *D_00482364;
extern void *D_004823D8;
extern void *D_0048235C;
extern f32 D_0047D6D0;

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

s32 MenuItemCmdPopupOpenState_2ac400(s32 unused, s32 en)
{
    u8 *w;
    s16 *r;

    if (en != 0) {
        MenuCageBaitIconUpdate_2a7370(0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x89, 1, 1);
        w = UiGetWidgetSprite_28fe10(D_00482360, 0x89, 0);
        if (w == 0) {
            return 0;
        }
        UiLayoutWindowFrame_28b8e0(w, 0xE8, 0x59, 3);
        *(s16 *)(w + 0x8C) = 0;
        *(s16 *)(w + 0x84) = 0;
        UiSetTextString_28f510(D_00482360, 0x89, MsgTableLookup_28aa30(D_004823D8, 0x3E9), 0);
        UiSetTextString_28f510(D_00482360, 0x89, MsgTableLookup_28aa30(D_004823D8, 0x3EA), 1);
        UiSetTextString_28f510(D_00482360, 0x89, MsgTableLookup_28aa30(D_004823D8, 0x3EB), 2);
        UiSetWidgetPos_290f60(D_00482360, 0x89, 0xB3, 0xAE);
        UiFadeWidgetAlpha_290690(D_00482360, 0x89, 1.0f, D_0047D6D0, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 5, 1);
        r = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00482364));
        UiSetWidgetPos_290f60(D_00482360, 0x1A8, r[0], r[1]);
        UiSetWidgetPos_290f60(D_00482360, 0x7D, 0, 0);
        UiSetSpriteW_28fbf0(D_00482360, 0x7D, 0xE1, 0);
        UiSetSpritePos_28fd10(D_00482360, 0x7D, 0xB8, 0xB2, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x7D, 1.0f, D_0047D6D0, -1.0f);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x3A, 0);
    return 1;
}
