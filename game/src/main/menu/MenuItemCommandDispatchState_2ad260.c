/* rgp:protos */
#define RGP_SELF_MenuItemCommandDispatchState_2ad260 1
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
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 *D_00482374;
extern u8 D_00482398;
extern s16 D_004823B0;
extern s32 D_004823D8;
extern s32 D_004823E4;
extern s8 D_00482498;

s32 MenuItemCommandDispatchState_2ad260(void)
{
    s16 v;
    u8 *p;
    u8 *q;
    s32 h;

    if (MenuItemCmdFadeSequenceStep_2adce0(0x84) != 0) {
        v = *(s16 *)(D_00482374 + 0x42);
        if (v == 0 || v == 5) {
            *(s8 *)(D_00482374 + 0x40) = 2;
            StateMachineSetState_28ede0(D_0048235C, 0x36, 0);
        } else if (v == 1) {
            if (ItemIsKind3_3d4630(MenuGetSelItem_2a02d0(D_00482374)) != 0) {
                StateMachineSetState_28ede0(D_0048235C, 0x46, 0);
            } else {
                StateMachineSetState_28ede0(D_0048235C, 0x43, 0);
            }
        } else if (v == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x1D, 0);
        } else if (v == 4) {
            if (*(*(u8 **)(((u8 *)GetGameData_1fede0()) + 0x20) + 0x24C) & 1) {
                D_004823B0 = 0x3E8;
                StateMachineSetState_28ede0(D_0048235C, 4, 0);
            } else {
                p = ((u8 *)GetGameData_1fede0());
                if (p == NULL) {
                    return 0;
                }
                h = ((s32)InvFindInCategoryRange_3c8370(*(s32 *)(p + 0x18), *(s32 *)(D_00482374 + 0x6C), 0, -1, 0, 0));
                if (h != 0) {
                    q = ((u8 *)InvObjCastToItem4B0_3d3cd0(h, 0, 0, 0));
                    if (q != NULL) {
                        if (*(s16 *)(*(u8 **)(q + 0x18) + 2) > 0) {
                            D_00482498 = 1;
                            StateMachineSetState_28ede0(D_0048235C, 0xB2, 0);
                        } else {
                            StateMachineSetState_28ede0(D_0048235C, 0xAE, 0);
                        }
                    }
                }
            }
        } else if (v == 3) {
            p = ((u8 *)GetGameData_1fede0());
            if (*(*(u8 **)(p + 0x20) + 0x24C) & 1) {
                D_004823B0 = 0x3E8;
                StateMachineSetState_28ede0(D_0048235C, 4, 0);
            } else if (WorldDataMgrNoRequestPending_3eef10(*(s32 *)(p + 8)) != 0 && D_00482398 != 0) {
                q = ((u8 *)UiEntryListFindByTag_28ea40(D_00482364, 3));
                UiSetSpriteFlags_290bd0(D_00482360, 0x76, (long long)(0x208), 1, *(s16 *)(q + 0x14) + *(s16 *)(q + 0x16) * 8, 0);
                StateMachineSetState_28ede0(D_0048235C, 0x94, 0);
                UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
                UiSetWidgetsVisibleById_291110(D_00482360, 0x36, 1, 1);
                UiSetWidgetPos_290f60(D_00482360, 0x36, 0x50, -0x26);
                UiSetTextString_28f510(D_00482360, 0x36, MsgTableLookup_28aa30(D_004823D8, 0x40A), 0);
                UiSetTextCenteredX_28f300(D_00482360, 0x36, 0xE8, 0);
                *(s32 *)(D_00482374 + 0x2C) = -1;
                *(s32 *)(D_00482374 + 0x30) = -1;
                SoundPlayDefault_1b9ae0(D_004823E4, 1, 0);
            }
        }
    }
    return 1;
}
