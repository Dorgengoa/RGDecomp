/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemSelectOpen_38f5c0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_0047FBD4;
extern s16 D_0047FBD8;
extern void *D_00482374;
extern s32 D_00483304;
extern s32 D_00483310;
extern s16 D_00483334;

s32 InsectCageMenuItemSelectOpen_38f5c0(void *arg0, s32 arg1)
{
    s32 sp3C;
    s32 sp38;
    s32 temp_2;
    s32 var_6;
    void **temp_2_2;

    D_0047FBD4 = -1;
    D_0047FBD8 = -1;
    D_00483334 = 6;
    UiSetWidgetsVisibleById_291110(arg1, 0x753A, 0, 1);
    UiSetWidgetsVisibleById_291110(arg1, 0x7616, 1, 1);
    UiSetWidgetsVisibleById_291110(arg1, 0x7544, 0, 1);
    InsectCageMenuSetCursorVisible_389d00(0);
    InsectCageMenuSetDrawFlag_390a80(1, 0);
    InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
    InsectCageMenuSetDrawFlag_390a80(2, 1);
    InsectCageMenuSetDrawFlag_390a80(7, 1);
    InsectCageMenuSetStateFlagMaybe_390aa0(7, 1);
    InsectCagePreviewModelSetup_389370(InsectCageMenuGetCursorObj_390f70(), 1);
    InsectCageMenuFormatMsgForCursor_388430(D_00483304 + 0xE00, 0x4B0);
    temp_2 = ScreenGetWidth_390d10();
    var_6 = temp_2 >> 1;
    if (temp_2 < 0) {
        var_6 = (s32)(temp_2 + 1) >> 1;
    }
    UiSetTextCenteredX_28f300(arg1, 0x7616, var_6, 0);
    temp_2_2 = ((void **)UiEntryListFindByTag_28ea40(*(s32 *)((u8 *)D_00482374 + 0x4), 3));
    if (temp_2_2 != NULL) {
        *(s16 *)((u8 *)arg0 + 0x0) = *(s16 *)((u8 *)(*temp_2_2) + 0x2);
        *(s16 *)((u8 *)arg0 + 0x2) = *(s16 *)((u8 *)(*temp_2_2) + 0x4);
        *(s16 *)((u8 *)arg0 + 0x4) = *(s16 *)((u8 *)(*temp_2_2) + 0x6);
        *(s16 *)((u8 *)arg0 + 0x6) = *(s16 *)((u8 *)(*temp_2_2) + 0x8);
    }
    InsectCageMenuItemPanelShowMaybe_38fc60(1);
    InsectCageMenuItemGridRefresh_38f790(D_00483310, arg0, 0);
    InsectCageMenuItemCellCb_38f4f0(arg0);
    InsectCageMenuItemCursorBobCb_38f4a0(arg0);
    UiGetWidgetTargetPos_290d90(GetMenuWidgetRoot_390d70(), 0x227, &sp3C, &sp38);
    UiSetWidgetPos_290f60(GetMenuWidgetRoot_390d70(), 0x227, sp3C, sp38);
    return 1;
}
