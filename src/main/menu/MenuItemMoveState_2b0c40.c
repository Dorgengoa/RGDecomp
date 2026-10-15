#include "types.h"

typedef struct {
    s32 w[24];
} Blk;

typedef struct {
    s32 w[6];
} Tmp;

extern void *GetGameData_1fede0(void);
extern void UiSetItemIconSprite_288490(s32, s32, s32, s32, s32, s32);
extern void PlayMenuSe_289ef0(s32);
extern s32 UiEntryListGetCurrentData_28ec60(s32);
extern void GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiGetWidgetSubItemValue_28ef00(s32, s32, s32);
extern void UiSetSubItemDrawSize_28f060(s32, s32, s32, s32, s32);
extern s32 UiGetWidgetSubItem_28f2b0(s32, s32, s32);
extern void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern void UiSetSpriteFlags_290bd0(s32, s32, s32, s32, s32, s32);
extern s32 UiWidgetIsMoving_290d30(s32, s32);
extern void UiMoveWidget_290e00(s32, s32, s32, s32, s32, f32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuShowItemCount_2a02f0(s32, s32, s32, s32, s32);
extern void MenuItemPageRefresh_2a03d0(s32, s32, s32, s32, s32, s32, s32);
extern void MenuShowMoneyAndItemCounts_2a32d0(s32, s32, s32);
extern s32 MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, void *, s32, s32, s32, f32);
extern void MenuItemMoveToSlot_2a3880(s32, s32, s32, s32, s32);
extern s32 MenuGetMode_2a4e30(s32);
extern void MenuItemInfoWidgetsCache_2a65f0(void *);
extern s32 MenuGetItemAtCell_2a7000(s32, s32);
extern void MenuCageBaitIconUpdate_2a7370(s32, s32);
extern s32 InvMoveItemMaybe_3c5b10(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
extern f32 D_0047D430;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;

s32 MenuItemMoveState_2b0c40(s32 arg0, s32 arg1)
{
    s32 x;
    s32 y;
    Tmp tmp;
    Blk blk;
    s32 m;
    s32 c;
    s32 g;
    s32 idx;
    s32 p;
    s32 n;
    s32 r;
    s32 res;
    s32 h;
    s32 k3c;
    s32 t11;
    s32 k;

    m = UiEntryListGetCurrentData_28ec60(D_00482364);
    GetGridCellPosOffset_28ecd0(m, &x, &y, -0x3C, -0x1A);
    c = MenuGetItemAtCell_2a7000(*(s8 *)(D_00482374 + 0x11), m);
    g = (s32)GetGameData_1fede0();
    idx = *(s16 *)(m + 0x10) + *(s16 *)(m + 0x12) * 8;
    if (arg1 != 0) {
        UiSetSubItemDrawSize_28f060(D_00482360, 0x77, 0, 0, idx);
        p = UiGetWidgetSubItem_28f2b0(D_00482360, 0x79, 0);
        if (p == 0) {
            return 0;
        }
        n = UiGetWidgetSubItemValue_28ef00(D_00482360, 0x77, idx);
        if (n > 1) {
            *(s64 *)(p + 8) = n;
            *(s16 *)(p + 0x1C) = 0xA;
            *(s16 *)(p + 0x1E) = 0x10;
        } else {
            *(s16 *)(p + 0x1E) = 0;
            *(s16 *)(p + 0x1C) = 0;
        }
        k = *(s8 *)(D_00482374 + 0x11);
        if (*(s32 *)(D_00482374 + 0x20) == k && idx == *(s32 *)(D_00482374 + 0x24)) {
            *(s16 *)(p + 0x1E) = 0;
            *(s16 *)(p + 0x1C) = 0;
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7B, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x7B, x, y);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x79, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x79, x + 0xB, y + 0xF);
        UiMoveWidget_290e00(D_00482360, 0x7B, x + 0xB, y + 0xF, 1, D_0047D430, 3.0f);
        k = *(s8 *)(D_00482374 + 0x11);
        r = MenuGetMode_2a4e30(D_00482374);
        if (r == 9) {
            k = 0;
        }
        r = InvMakeIdFromCategory_3c88b0(*(s32 *)(g + 0x18), r, k, *(s16 *)(m + 0x10), *(s16 *)(m + 0x12));
        k3c = *(volatile s32 *)(D_00482374 + 0x3C);
        blk = *(Blk *)(D_00482374 + 0x10);
        res = InvMoveItemMaybe_3c5b10(*(s32 *)(g + 0x18), blk.w[9], r, k3c, 0, 0, 0, 1);
        if (res == 3 || (u32)(res - 7) < 2) {
            UiSetSpriteSizeUvSize_28f670(D_00482360, 0x74, 0, 0, 0, 0, idx);
            UiSetSpriteSizeUvSize_28f670(D_00482360, 0x76, 0, 0, 0, 0, idx);
            h = UiFindWidget_290460(D_00482360, 0x7A);
            if (h == 0) {
                return 0;
            }
            UiSetItemIconSprite_288490(D_00482374, h, *(s16 *)(*(s32 *)(c + 0x10) + 0x2C), 0x28, 0x2D, 1);
            UiSetSpriteFlags_290bd0(D_00482360, 0x7A, 8, 1, 0, 0);
            h = UiGetWidgetSprite_28fe10(D_00482360, 0x76, 0);
            if (h == 0) {
                return 0;
            }
            h += idx << 5;
            UiSetSpritePos_28fd10(D_00482360, 0x7A, *(s16 *)h + 0x1B, *(s16 *)(h + 2) + 0x1B, 0);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x7A, 1, 1);
            UiMoveWidget_290e00(D_00482360, 0x7A, -0xB, -0xF, 1, D_0047D430, 3.0f);
            UiMoveWidget_290e00(D_00482360, 0x79, x, y, 1, D_0047D430, 3.0f);
            goto eight;
        }
        if (res == 0) {
            MenuShowItemCount_2a02f0(D_00482374, 0x76, 0x74, 0x77, *(s32 *)(D_00482374 + 0x24));
            UiSetWidgetsVisibleById_291110(D_00482360, 0x79, 0, 1);
            if (n > 1) {
                UiSetSubItemDrawSize_28f060(D_00482360, 0x77, 0xA, 0x10, idx);
            }
            StateMachineSetState_28ede0(D_0048235C, 0xE, 1);
            PlayMenuSe_289ef0(6);
            goto end;
        }
eight:
        PlayMenuSe_289ef0(8);
        return 1;
    }
    if (UiWidgetIsMoving_290d30(D_00482360, 0x7B) == 0) {
        GetGameData_1fede0();
        MenuItemMoveToSlot_2a3880(D_00482374, 0x7B, 0x7C, *(s16 *)(m + 0x10), *(s16 *)(m + 0x12));
        MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
        UiSetWidgetPos_290f60(D_00482360, 0x7A, 0, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x7B, x, y);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x79, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7A, 0, 1);
        c = MenuGetItemAtCell_2a7000(*(s8 *)(D_00482374 + 0x11), m);
        idx = *(s16 *)(m + 0x10) + *(s16 *)(m + 0x12) * 8;
        MenuItemInfoWidgetsCache_2a65f0(&tmp);
        MenuItemInfoPopupShow_2a33e0(D_00482374, c, 0x1AA, 0x1A9, &tmp, 0x68, 0x15E, idx, 2.0f);
        MenuCageBaitIconUpdate_2a7370(c, 1);
        if (*(s8 *)(D_00482374 + 0x1C) == 0) {
            StateMachineSetState_28ede0(D_0048235C, 0xF, 1);
        } else {
            MenuShowItemCount_2a02f0(D_00482374, 0x76, 0x74, 0x77, *(s32 *)(D_00482374 + 0x24));
            StateMachineSetState_28ede0(D_0048235C, 0xE, 1);
        }
        MenuShowMoneyAndItemCounts_2a32d0(D_00482374, 0x31, 0x30);
    }
end:
    return 1;
}
