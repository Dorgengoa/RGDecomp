#include "types.h"

extern void *GetGameData_1fede0(void);
extern void MenuItemCategoryTabsLayout_288ac0(s32, s32, s32, s32, s32, s32);
extern void UiSlideInWidgetPair_28d010(s32, s32, s32);
extern void UiLayoutPanelFrame_28d580(s32, s32, s32, s32, s32, s32);
extern void UiSelFrameCalcTileCounts_28d9d0(void *);
extern void UiSelFrameInit_28da30(void *, s32, s32);
extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuShowMoneyAndItemCounts_2a32d0(s32, s32, s32);
extern s32 MenuItemInfoPopupShow_2a33e0(s32, s32, s32, s32, void *, s32, s32, s32, f32);
extern void MenuFillItemCounts_2a3d90(s32, s32);
extern void MenuFillItemGrid_2a4b40(s32, s32);
extern void MenuSetMode_2a4e40(s32, s32);
extern void TransMenuItemFetchWidgetRefs_37bdb0(void *);
extern void TransMenuItemTabLayoutMaybe_37f0c0(s32);
extern s16 PartyMenuCursorGet_3c0760(s32, s32);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern char *strcpy(char *, const char *);
extern char D_00463B98[];
extern char D_00463BA8[];
extern s32 D_004659E8[];
extern s32 D_00465A18[];
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D920;
extern f32 D_0047D9A0;
extern f32 D_0047D9A4;
extern f32 D_0047D9A8;
extern f32 D_0047D9AC;
extern s16 D_0047FB20;
extern s16 D_0047FB24;
extern s16 D_0047FB28;
extern s16 D_0047FB2C;
extern s32 D_00483244;
extern f32 D_00483248;
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s8 D_0048472C;
extern s32 D_00484740;
extern u8 D_004E9230[];

typedef struct {
    s32 a, b, c, d;
} Tmp;

s32 TransMenuItemGridOpenState_37ff00(s32 arg0, s32 arg1)
{
    Tmp tmp;
    s32 g;
    s32 w;
    s32 a;
    s32 b;
    s32 k;
    s32 v;
    s32 e;
    s32 r;
    f32 t;

    if (arg1 != 0) {
        g = (s32)GetGameData_1fede0();
        UiSlideInWidgetPair_28d010(0x753E, 0x7539, D_00484710);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7553, 1.0f, D_0047D9A0, -1.0f);
        MenuShowMoneyAndItemCounts_2a32d0(D_00484740, 0x754A, 0x7549);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7547, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7546, 1, 1);
        UiSetWidgetPos_290f60(D_00484710, 0x7547, 0x104, -0x19);
        UiSetWidgetPos_290f60(D_00484710, 0x7546, 0x107, -0x16);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7547, 0x104, 0xE, 0, 0.25f);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7546, 0x107, 0x11, 0, 0.25f);
        UiSetWidgetColor_2905b0(D_00484710, 0x7546, 0.0f, 0.0f, 0.0f, D_0047D920);
        D_00483244 = 0;
        D_00483248 = 0.0f;
        D_0048472C = 0;
        UiFadeWidgetAlpha_290690(D_00484710, 0x75D1, 0.0f, D_0047D9A4, -1.0f);
        w = UiGetWidgetSprite_28fe10(D_00484710, 0x75F8, 0);
        if (w == 0) {
            return 0;
        }
        UiLayoutPanelFrame_28d580(w, 0, 0, 0x186, 0x12C, 0);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7600, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00484710, 0x7600, 0.0f);
        UiSetWidgetVisible_290010(D_00484710, 0x75F8, 1, -1);
        UiSetWidgetPos_290f60(D_00484710, 0x75F8, 0x200, 0x49);
        UiMoveWidgetUniform_290f50(D_00484710, 0x75F8, 0x62, 0x49, 0, D_0047D920);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75F8, 1.0f, 0.0625f, 0.0f);
        UiSelFrameInit_28da30(D_004E9230, D_00484710, 0x7604);
        UiSelFrameSetRect_28db40(D_004E9230, 0x7604, 0x18, 0x18, 0x2A, 0x30, 0x62, 0x49);
        UiSelFrameCalcTileCounts_28d9d0(D_004E9230);
        D_0047FB28 = 0;
        D_0047FB24 = 0;
        D_0047FB20 = 0;
        D_0047FB2C = 0;
        if (*(s16 *)(*(s32 *)(g + 0xC) + 0x26) == 1) {
            D_0047FB20 = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x17);
            D_0047FB24 = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x18);
            D_0047FB28 = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x19);
            D_0047FB2C = PartyMenuCursorGet_3c0760(*(s32 *)(g + 0x18), 0x1A);
        }
        a = UiFindWidget_290460(D_00484710, 0x75F8);
        if (a == 0) {
            return 0;
        }
        b = UiFindWidget_290460(D_00484710, 0x75FA);
        if (b == 0) {
            return 0;
        }
        MenuSetMode_2a4e40(D_00484740, D_0047FB2C);
        k = D_004659E8[0];
        v = k;
        if (D_0047FB2C == 1) {
            v = D_00465A18[0];
        }
        if (D_0047FB2C == 0) {
            MenuSetMode_2a4e40(D_00484740, 0);
            *(s8 *)(D_00484740 + 0x10) = k;
            strcpy((char *)(a + 4), D_00463BA8);
            strcpy((char *)(b + 4), D_00463BA8);
        } else if (D_0047FB2C == 1) {
            MenuSetMode_2a4e40(D_00484740, 1);
            *(s8 *)(D_00484740 + 0x10) = D_00465A18[0];
            strcpy((char *)(a + 4), D_00463B98);
            strcpy((char *)(b + 4), D_00463B98);
        }
        *(s8 *)(D_00484740 + 0x10) = v;
        *(s8 *)(D_00484740 + 0x11) = D_0047FB28;
        MenuItemCategoryTabsLayout_288ac0(D_00484710, 0x75FA, 0x75FF, 0x75FE, D_0047FB28, D_0047FB2C);
        MenuFillItemGrid_2a4b40(D_00484740, 0x7602);
        MenuFillItemCounts_2a3d90(D_00484740, 0x7603);
        UiEntryListSelectByTag_28ea90(D_00484720, 0xB, 1);
        e = UiEntryListFindByTag_28ea40(D_00484720, 0xB);
        *(s16 *)(e + 0x14) = D_0047FB20;
        *(s16 *)(e + 0x16) = D_0047FB24;
        UiSetWidgetPos_290f60(D_00484710, 0x7632, *(s16 *)(e + 4) + *(s16 *)(e + 0x14) * *(s16 *)(e + 8), *(s16 *)(e + 6) + *(s16 *)(e + 0x16) * *(s16 *)(e + 0xA));
        UiSetWidgetAlpha_2907a0(D_00484710, 0x7632, 0.0f);
        UiSetWidgetAlpha_2907a0(D_00484710, 0x7604, 0.0f);
        r = InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), D_0047FB2C, D_0047FB28, D_0047FB20 + D_0047FB24 * 8, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x762D, 1, 1);
        TransMenuItemFetchWidgetRefs_37bdb0(&tmp);
        MenuItemInfoPopupShow_2a33e0(D_00484740, r, 0x762E, 0x762D, &tmp, 0x68, 0x15E, -1, D_0047D5D0);
        TransMenuItemTabLayoutMaybe_37f0c0(D_0047FB2C);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x760A, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00484710, 0x760A, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7613, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7606, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7607, 0, 1);
        *(s8 *)(D_00484740 + 0x1C) = 0;
        *(s32 *)(D_00484740 + 0x20) = -1;
        *(s32 *)(D_00484740 + 0x24) = -1;
        *(s32 *)(D_00484740 + 0x28) = -1;
    }
    if (D_00483244 == 0) {
        D_00483248 = t = D_00483248 + D_0047D9A8;
        if (!(t < D_0047D35C)) {
            D_00483248 = D_0047D35C;
            D_00483244 = 1;
        }
    } else if (D_00483244 == 1) {
        D_00483248 -= D_0047D9A8;
    }
    UiSetWidgetColor_2905b0(D_00484710, 0x7553, D_00483248, D_00483248, D_00483248, 1.0f);
    if (D_00483248 <= 1.0f && D_00483244 == 1) {
        D_00483248 = 1.0f;
        UiSetWidgetColor_2905b0(D_00484710, 0x7553, 1.0f, 1.0f, 1.0f, 1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7600, 1.0f, D_0047D9AC, -1.0f);
        StateMachineSetState_28ede0(D_0048470C, 0x20, 0);
    }
    return 1;
}
