#include "types.h"

typedef struct {
    s32 w[24];
} Blk;

typedef struct {
    s32 w[6];
} Tmp;

extern "C" {
extern void *GetGameData_1fede0(void);
extern void UiSetItemIconSprite_288490(s32, s32, s32, s32, s32, s32);
extern void MenuItemCategoryTabsLayout_288ac0(s32, s32, s32, s32, s32, s32);
extern void PlayMenuSe_289ef0(s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern s32 UiEntryListGetCurrentData_28ec60(s32);
extern void GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiGetWidgetSubItemValue_28ef00(s32, s32, s32);
extern void UiSetSubItemDrawSize_28f060(s32, s32, s32, s32, s32);
extern s32 UiGetWidgetSubItem_28f2b0(s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern s32 UiWidgetIsMoving_290d30(s32, s32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 MenuGetSelItem_2a02d0(s32);
extern void MenuSetSelItem_2a02e0(s32, s32);
extern void MenuShowItemCount_2a02f0(s32, s32, s32, s32, s32);
extern void MenuShowMoneyAndItemCounts_2a32d0(s32, s32, s32);
extern s32 MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, void *, s32, s32, s32, f32);
extern void MenuItemMoveToSlot_2a3880(s32, s32, s32, s32, s32);
extern void MenuFillItemCounts_2a3d90(s32, s32);
extern void MenuItemGridMarkInUse_2a4860(s32, s32);
extern void MenuFillItemGrid_2a4b40(s32, s32);
extern s32 MenuGetSelMode_2a4e10(s32);
extern s32 MenuGetMode_2a4e30(s32);
extern void TransMenuItemFetchWidgetRefs_37bdb0(void *);
extern s32 InvMoveItemMaybe_3c5b10(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
extern s32 PartyFindItemHolder_3d4c20(s32);
extern f32 D_0047D81C;
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern s32 D_00484770;
s32 TransMenuItemMoveState_37d850(s32 arg0, s32 arg1);
}


s32 TransMenuItemMoveState_37d850(s32 arg0, s32 arg1)
{
    s32 x;
    s32 y;
    Tmp tmp;
    Blk blk;
    s32 m;
    s32 g;
    s32 c;
    s32 idx;
    s32 p;
    s32 n;
    s32 r;
    s32 res;
    s32 h;
    s32 q;
    s32 s;
    s32 k3c;
    s32 t10;
    s32 t12;
    s32 t11;

    m = UiEntryListGetCurrentData_28ec60(D_00484720);
    GetGridCellPosOffset_28ecd0(m, &x, &y, 0x33, 0x11);
    g = (s32)GetGameData_1fede0();
    t12 = *(s16 *)(m + 0x12);
    t10 = *(s16 *)(m + 0x10);
    t11 = *(s8 *)(D_00484740 + 0x11);
    c = InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), MenuGetMode_2a4e30(D_00484740), t11, t10, t12, 0);
    idx = *(s16 *)(m + 0x10) + *(s16 *)(m + 0x12) * 8;
    if (arg1 != 0) {
        UiSetSubItemDrawSize_28f060(D_00484710, 0x7603, 0, 0, idx);
        p = UiGetWidgetSubItem_28f2b0(D_00484710, 0x7605, 0);
        if (p == 0) {
            return 0;
        }
        n = UiGetWidgetSubItemValue_28ef00(D_00484710, 0x7603, idx);
        if (n > 1) {
            *(s64 *)(p + 8) = n;
            *(s16 *)(p + 0x1C) = 0xA;
            *(s16 *)(p + 0x1E) = 0x10;
        } else {
            *(s16 *)(p + 0x1E) = 0;
            *(s16 *)(p + 0x1C) = 0;
        }
        t11 = *(s8 *)(D_00484740 + 0x11);
        if (*(s32 *)(D_00484740 + 0x20) == t11 && idx == *(s32 *)(D_00484740 + 0x24)) {
            *(s16 *)(p + 0x1E) = 0;
            *(s16 *)(p + 0x1C) = 0;
        }
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7607, 1, 1);
        UiSetWidgetPos_290f60(D_00484710, 0x7607, x, y);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7605, 1, 1);
        UiSetWidgetPos_290f60(D_00484710, 0x7605, x + 0xB, y + 0xF);
        t12 = *(s16 *)(m + 0x12);
        t10 = *(s16 *)(m + 0x10);
        t11 = *(s8 *)(D_00484740 + 0x11);
        r = InvMakeIdFromCategory_3c88b0(*(s32 *)(g + 0x18), MenuGetMode_2a4e30(D_00484740), t11, t10, t12);
        k3c = *(volatile s32 *)(D_00484740 + 0x3C);
        blk = *(Blk *)(D_00484740 + 0x10);
        res = InvMoveItemMaybe_3c5b10(*(s32 *)(g + 0x18), blk.w[9], r, k3c, 0, 0, 0, 1);
        if (res == 3 || (u32)(res - 7) < 2) {
            UiMoveWidget_290e00(D_00484710, 0x7607, x + 0xB, y + 0xF, 1, D_0047D81C, 3.0f);
            UiSetSpriteSizeUvSize_28f670(D_00484710, 0x7600, 0, 0, 0, 0, idx);
            UiSetSpriteSizeUvSize_28f670(D_00484710, 0x7602, 0, 0, 0, 0, idx);
            h = UiFindWidget_290460(D_00484710, 0x7606);
            if (h == 0) {
                return 0;
            }
            UiSetItemIconSprite_288490(D_00484740, h, *(s16 *)(*(s32 *)(c + 0x10) + 0x2C), 0x28, 0x2D, 1);
            h = UiGetWidgetSprite_28fe10(D_00484710, 0x7602, 0);
            if (h == 0) {
                return 0;
            }
            h += idx << 5;
            UiSetSpritePos_28fd10(D_00484710, 0x7606, *(s16 *)h + 0x1B, *(s16 *)(h + 2) + 0x1B, 0);
            UiSetWidgetsVisibleById_291110(D_00484710, 0x7606, 1, 1);
            UiMoveWidget_290e00(D_00484710, 0x7606, -0xB, -0xF, 1, D_0047D81C, 3.0f);
            UiMoveWidget_290e00(D_00484710, 0x7605, x, y, 1, D_0047D81C, 3.0f);
            goto eight;
        }
        if (res == 0) {
            if (MenuGetSelMode_2a4e10(D_00484740) == MenuGetMode_2a4e30(D_00484740)) {
                MenuShowItemCount_2a02f0(D_00484740, 0x7602, 0x7600, 0x7603, *(s32 *)(D_00484740 + 0x24));
            }
            UiSetWidgetsVisibleById_291110(D_00484710, 0x7605, 0, 1);
            if (n > 1) {
                UiSetSubItemDrawSize_28f060(D_00484710, 0x7603, 0xA, 0x10, idx);
            }
            q = MenuGetSelItem_2a02d0(D_00484740);
            if (q == 0) {
                return 0;
            }
            s = *(s32 *)(q + 0x10);
            if (MenuGetMode_2a4e30(D_00484740) == 1 && (!(*(u8 *)(s + 0x18) & 1) || (bool)PartyFindItemHolder_3d4c20(q) != false)) {
                UiSetTextString_28f510(D_00484710, 0x764E, MsgTableLookup_28aa30(D_00484770, 0x3F8), 0);
                StateMachineSetState_28ede0(D_0048470C, 0x25, 0);
            } else if (c != 0) {
                UiSetTextString_28f510(D_00484710, 0x764E, MsgTableLookup_28aa30(D_00484770, 0x3F9), 0);
                StateMachineSetState_28ede0(D_0048470C, 0x25, 0);
            } else {
                StateMachineSetState_28ede0(D_0048470C, 0x37, 1);
            }
        PlayMenuSe_289ef0(6);
            goto end;
        }
        UiMoveWidget_290e00(D_00484710, 0x7607, x + 0xB, y + 0xF, 1, D_0047D81C, 3.0f);
eight:
        PlayMenuSe_289ef0(8);
        return 1;
    }
    if (UiWidgetIsMoving_290d30(D_00484710, 0x7607) == 0) {
        g = (s32)GetGameData_1fede0();
        MenuItemMoveToSlot_2a3880(D_00484740, 0x7607, 0x7608, *(s16 *)(m + 0x10), *(s16 *)(m + 0x12));
        t11 = *(s8 *)(D_00484740 + 0x11);
        MenuItemCategoryTabsLayout_288ac0(D_00484710, 0x75FA, 0x75FF, 0x75FE, t11, MenuGetMode_2a4e30(D_00484740));
        MenuItemGridMarkInUse_2a4860(D_00484740, 0x7600);
        MenuFillItemGrid_2a4b40(D_00484740, 0x7602);
        MenuFillItemCounts_2a3d90(D_00484740, 0x7603);
        UiSetWidgetPos_290f60(D_00484710, 0x7606, 0, 0);
        UiSetWidgetPos_290f60(D_00484710, 0x7607, x, y);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7606, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7605, 0, 1);
        t10 = *(s16 *)(m + 0x12);
        t11 = *(s8 *)(D_00484740 + 0x11);
        t12 = *(s16 *)(m + 0x10);
        c = InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), MenuGetMode_2a4e30(D_00484740), t11, t12, t10, 0);
        idx = *(s16 *)(m + 0x10) + *(s16 *)(m + 0x12) * 8;
        TransMenuItemFetchWidgetRefs_37bdb0(&tmp);
        MenuItemInfoPopupShow_2a33e0(D_00484740, c, 0x1AA, 0x19F, &tmp, 0x68, 0x15E, idx, 2.0f);
        if (c != 0) {
            MenuSetSelItem_2a02e0(D_00484740, c);
        }
        g = D_00484740;
        if (*(s8 *)(g + 0x1C) == 0) {
            StateMachineSetState_28ede0(D_0048470C, 0x38, 1);
        } else {
            if (MenuGetSelMode_2a4e10(g) == MenuGetMode_2a4e30(g)) {
                MenuShowItemCount_2a02f0(D_00484740, 0x7602, 0x7600, 0x7603, *(s32 *)(D_00484740 + 0x24));
            }
            StateMachineSetState_28ede0(D_0048470C, 0x37, 1);
        }
        MenuShowMoneyAndItemCounts_2a32d0(D_00484740, 0x754A, 0x7549);
    }
end:
    return 1;
}
