/* rgp:protos */
#define RGP_SELF_TransMenuItemCmdPopupOpenState_37c300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484710;
extern void *D_00484720;
extern void *D_00484770;
extern void *D_0048470C;
extern f32 D_0047D970;

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

s32 TransMenuItemCmdPopupOpenState_37c300(s32 unused, s32 en)
{
    u8 *w;
    s16 *r;

    if (en != 0) {
        UiSetWidgetsVisibleById_291110(D_00484710, 0x762A, 1, 1);
        w = UiGetWidgetSprite_28fe10(D_00484710, 0x762A, 0);
        if (w == 0) {
            return 0;
        }
        UiLayoutWindowFrame_28b8e0(w, 0xE8, 0x59, 3);
        *(s16 *)(w + 0x8C) = 0;
        *(s16 *)(w + 0x84) = 0;
        UiSetTextString_28f510(D_00484710, 0x762A, MsgTableLookup_28aa30(D_00484770, 0x3E8), 0);
        UiSetTextString_28f510(D_00484710, 0x762A, MsgTableLookup_28aa30(D_00484770, 0x3E9), 1);
        UiSetTextString_28f510(D_00484710, 0x762A, MsgTableLookup_28aa30(D_00484770, 0x3EA), 2);
        UiSetWidgetPos_290f60(D_00484710, 0x762A, 0xB3, 0xAE);
        UiFadeWidgetAlpha_290690(D_00484710, 0x762A, 1.0f, D_0047D970, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00484720, 0xE, 1);
        r = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00484720));
        UiSetWidgetPos_290f60(D_00484710, 0x762C, r[0], r[1]);
        UiSetWidgetPos_290f60(D_00484710, 0x7609, 0, 0);
        UiSetSpriteW_28fbf0(D_00484710, 0x7609, 0xE1, 0);
        UiSetSpritePos_28fd10(D_00484710, 0x7609, 0xB8, 0xB2, 0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7609, 1.0f, D_0047D970, -1.0f);
    }
    StateMachineSetState_28ede0(D_0048470C, 0x31, 0);
    return 1;
}
