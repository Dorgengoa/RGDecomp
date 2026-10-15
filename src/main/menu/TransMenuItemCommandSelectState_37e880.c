#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 GetWorldDataMgr_1fedf0(void);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern s32 UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern s32 UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern s32 MenuItemIsDisabled_2a0270(s32, s32);
extern void MenuSetSelItem_2a02e0(s32, s32);
extern void MenuItemCmdSetRowHighlight_2a1800(s32, s32, s32, s32, s32);
extern s32 MenuGetMode_2a4e30(s32);
extern s32 InvMoveItemToCategoryMaybe_3c59b0(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern s32 ItemIsUnheldFlaggedMaybe_3d4420(s32);
extern s32 ItemHasCountFlag_3d44e0(s32);
extern s32 ItemIsWeapon_3d46c0(s32);
extern void WorldDataRequestKind_3f0960(s32, s32);
extern f32 D_0047D970;
extern f32 D_0047D988;
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern u8 D_004B2570[];

s32 TransMenuItemCommandSelectState_37e880(s32 arg0, s32 arg1)
{
    s32 p;
    s32 i;
    s32 r;
    s32 m;
    s16 k;
    s32 h;
    s32 g;
    s32 o;
    s32 c;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0xC, 0);
        MenuItemCmdSetRowHighlight_2a1800(D_00484740, 0x760A, 0x7609, *(s16 *)(UiEntryListFindByTag_28ea40(D_00484720, 0xC) + 0x16), *(s16 *)(D_00484740 + 0x42));
        p = UiEntryListFindByTag_28ea40(D_00484720, 0xC);
        if (p != 0) {
            for (i = 0; i < *(s16 *)(p + 0xE) + 1; i++) {
                UiFadeWidgetAlpha_290690(D_00484710, (i + 0x7652) & 0xFFFF, 1.0f, D_0047D970, -1.0f);
            }
        }
        UiFadeWidgetAlpha_290690(D_00484710, 0x760A, 1.0f, D_0047D970, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7609, 1.0f, D_0047D970, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x762B, 1.0f, D_0047D988, -1.0f);
    }
    r = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 4, 0);
    m = UiEntryListGetCurrentData_28ec60(D_00484720);
    if (r == 1) {
        k = *(s16 *)(D_00484740 + 0x42);
        h = MenuGetMode_2a4e30(D_00484740);
        g = UiEntryListFindByTag_28ea40(D_00484720, 0xB);
        o = (s32)GetGameData_1fede0();
        c = InvFindByCategoryIndex_3c86e0(*(s32 *)(o + 0x18), h, *(s8 *)(D_00484740 + 0x11), *(s16 *)(g + 0x14), *(s16 *)(g + 0x16), 0);
        if (c == 0) {
            return 0;
        }
        MenuSetSelItem_2a02e0(D_00484740, c);
        if (k == 0) {
            switch (*(s16 *)(m + 0x12)) {
            case 0:
                if (h == 0) {
                    if (InvMoveItemToCategoryMaybe_3c59b0(*(s32 *)(o + 0x18), c, 1, -1, 0, 0, 0, 1) == 0) {
                        break;
                    }
                } else if (h == 1) {
                    if (InvMoveItemToCategoryMaybe_3c59b0(*(s32 *)(o + 0x18), c, 0, -1, 0, 0, 0, 1) == 0) {
                        break;
                    }
                }
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            case 1:
                *(s8 *)(D_00484740 + 0x40) = 2;
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            case 2:
                if (MenuItemIsDisabled_2a0270(D_00484740, c) == 0) {
                    s32 t = GetWorldDataMgr_1fedf0();
                    if (**(s16 **)(t + 0x28) != 1) {
                        WorldDataRequestKind_3f0960(t, 1);
                    }
                    StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                }
                break;
            case 3:
                if (ItemIsUnheldFlaggedMaybe_3d4420(c) != 0) {
                    StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                }
                break;
            case 4:
                if (ItemHasCountFlag_3d44e0(c) != 0) {
                    StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                }
                break;
            case 5:
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            }
        } else if (k == 1) {
            switch (*(s16 *)(m + 0x12)) {
            case 0:
                if (h == 0) {
                    if (InvMoveItemToCategoryMaybe_3c59b0(*(s32 *)(o + 0x18), c, 1, -1, 0, 0, 0, 1) == 0) {
                        break;
                    }
                } else if (h == 1) {
                    if (InvMoveItemToCategoryMaybe_3c59b0(*(s32 *)(o + 0x18), c, 0, -1, 0, 0, 0, 1) == 0) {
                        break;
                    }
                }
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            case 1:
                if (ItemIsWeapon_3d46c0(c) != 0) {
                    StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                }
                break;
            case 2:
                if (ItemIsUnheldFlaggedMaybe_3d4420(c) != 0) {
                    StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                }
                break;
            case 3:
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            case 4:
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            }
        } else if (k == 3) {
            switch (*(s16 *)(m + 0x12)) {
            case 0:
            case 1:
                break;
            case 2:
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            case 3:
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            }
        } else if (k == 4) {
            switch (*(s16 *)(m + 0x12)) {
            case 0:
                if ((h != 0 || InvMoveItemToCategoryMaybe_3c59b0(*(s32 *)(o + 0x18), c, 1, -1, 0, 0, 0, 1) != 0) && (h != 1 || InvMoveItemToCategoryMaybe_3c59b0(*(s32 *)(o + 0x18), c, 0, -1, 0, 0, 0, 1) != 0)) {
                    StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                }
                break;
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                *(s8 *)(D_00484740 + 0x40) = 2;
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            case 5:
                StateMachineSetState_28ede0(D_0048470C, 0x26, 0);
                break;
            }
        }
    } else if (r == 2) {
        StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
    }
    return 1;
}
