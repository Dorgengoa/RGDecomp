/* rgp:protos */
#line 1
#include "types.h"

typedef struct G_002b2870 {
    u8 pad0[0xC];
    s32 xC;
    u8 pad10[0x18 - 0x10];
    s32 x18;
} G_002b2870;

extern "C" {
s32 SceneSoundGetSlot0HandleCur_207df0(void);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiLayoutPanelFrame_28d580(s32, s32, s32, s32, s32, s32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, f32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void MenuSetOwnedCageSlotsMaybe_2a7570(void);
void UiSlideInWidgetPair_28d010(s32, s32, s32);
void MenuShowMoneyAndItemCounts_2a32d0(s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiSelFrameInit_28da30(void *, s32, s32);
void UiSelFrameSetGridCell_28db00(void *, s32, s32, s32, s32, s32);
void UiSelFrameCalcTileCounts_28d9d0(void *);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
struct G_002b2870 *GetGameData_1fede0(void);
s16 PartyMenuCursorGet_3c0760(s32, s32);
void MenuSetSelMode_2a4e20(s32, s32);
void UiSetSpriteFlags_290bd0(s32, s32, long long, s32, s32, s32);
void MenuItemTabsAvailUpdate_2b0070(void);
void MenuItemSelectLastTab_2b30d0(void);
void MenuItemSetOpenModeMaybe_2a4ed0(s32, s32);
s16 MenuItemGetOpenModeMaybe_2a4ec0(s32);
void MenuItemSelectTab_2b3550(s32, s32, s32);
void MenuItemPageRefresh_2a03d0(s32, s32, s32, s32, s32, s32, s32);
s32 MenuGetItemAtCell_2a7000(s32, s32);
s32 ItemDefIsKindCId4B0_40e310(s32);
s32 InvObjCastToItem4B0_3d3cd0(s32, int, int, int);
s32 CageRecIsPlaced_3d0d20(s32);
s32 LoadHandleIsReady_28b200(s32);
s32 InvGetItem4B0_3c80c0(s32, s32);
s32 CageRecCountTriggered_3d08c0(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void MenuItemSectionEnter_2b3400(void);
extern s32 D_004824C4;
extern s32 D_00482374;
extern s32 D_00482360;
extern s32 D_0048235C;
extern s32 D_00482364;
extern s32 D_004824C8;
extern f32 D_00482490;
extern s32 D_0048248C;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;
extern u8 D_0048241C;
extern s32 D_004823F8;
extern s16 D_004824B0[3];
extern s8 D_0047EC50;
extern f32 D_0047D6CC;
extern f32 D_0047D66C;
extern f32 D_0047D35C;
extern f32 D_0047D790;
extern s32 D_004659F0[];
extern s32 D_004659F8[];
extern u8 D_004DB430[];
}

extern "C" s32 MenuItemOpenState_2b2870(s32 arg0, s32 init)
{
    s32 *h;
    s32 q;
    s32 m;
    G_002b2870 *g;
    s32 n;
    s32 i;
    bool ok;
    s32 c;
    s32 u;
    s32 j;
    s16 *p;
    s16 old;
    f32 f;

    if (init != 0) {
        D_004824C4 = SceneSoundGetSlot0HandleCur_207df0();
        h = (s32 *)D_00482374;
        D_00482360 = h[0];
        D_0048235C = h[2];
        D_00482364 = h[1];
        UiSetWidgetsVisibleById_291110(D_00482360, 2, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 3, 0, 1);
        q = UiGetWidgetSprite_28fe10(D_00482360, 0x65, 0);
        if (q != 0) {
            UiLayoutPanelFrame_28d580(q, 0, 0, 0x186, 0x12C, 0);
        }
        UiSetWidgetAlpha_2907a0(D_00482360, 0x74, 0.0f);
        UiSetWidgetVisible_290010(D_00482360, 0x65, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x65, 0x200, 0x49);
        UiMoveWidgetUniform_290f50(D_00482360, 0x65, 0x62, 0x49, D_0047D6CC, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x65, 1.0f, 0.0625f, 0.0f);
        MenuSetOwnedCageSlotsMaybe_2a7570();
        UiSlideInWidgetPair_28d010(0x16, 0xD, D_00482360);
        MenuShowMoneyAndItemCounts_2a32d0(D_00482374, 0x31, 0x30);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x2E, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x2D, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x2E, 0x104, -0x19);
        UiSetWidgetPos_290f60(D_00482360, 0x2D, 0x107, -0x16);
        UiMoveWidgetUniform_290f50(D_00482360, 0x2E, 0x104, 0xE, 0.25f, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x2D, 0x107, 0x11, 0.25f, 0);
        UiSetWidgetColor_2905b0(D_00482360, 0x2D, 0.0f, 0.0f, 0.0f, D_0047D6CC);
        D_004824C8 = 0;
        D_00482490 = 0.0f;
        D_0048248C = 0;
        UiSelFrameInit_28da30(D_004DB430, D_00482360, 0x78);
        UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, 0, 0, 0x62, 0x49);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB430);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7B, 0, 1);
        *(u8 *)(D_00482374 + 0x1C) = 0;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7A, 0, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 1);
        m = UiEntryListFindByTag_28ea40(D_00482364, 3);
        D_004824A8 = 0;
        D_004824A4 = 0;
        D_004824A0 = 0;
        g = GetGameData_1fede0();
        if (*(s16 *)(g->xC + 0x26) == 1 && D_0048241C == 0) {
            D_004824A0 = PartyMenuCursorGet_3c0760(g->x18, 0);
            D_004824A4 = PartyMenuCursorGet_3c0760(g->x18, 1);
            D_004824A8 = PartyMenuCursorGet_3c0760(g->x18, 2);
        }
        *(s16 *)(m + 0x14) = D_004824A0;
        *(s16 *)(m + 0x16) = D_004824A4;
        UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, *(s16 *)(m + 0x14), *(s16 *)(m + 0x16), 0x62, 0x49);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x227, 0.0f);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x78, 0.0f);
        *(s16 *)(m + 0xE) = 4;
        MenuSetSelMode_2a4e20(D_00482374, 0);
        *(u8 *)(D_00482374 + 0x1C) = 0;
        *(s32 *)(D_00482374 + 0x20) = -1;
        *(s32 *)(D_00482374 + 0x24) = -1;
        *(s32 *)(D_00482374 + 0x28) = -1;
        *(s32 *)(D_00482374 + 0x2C) = -1;
        *(s32 *)(D_00482374 + 0x30) = -1;
        for (i = 0; i < D_004659F0[0] * D_004659F8[0]; i++) {
            UiSetSpriteFlags_290bd0(D_00482360, 0x76, (long long)(8), 1, i, 0);
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7E, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x7E, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x8A, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x6C, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x6C, 1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x71, 0, 1);
        MenuItemTabsAvailUpdate_2b0070();
        if (D_0048241C != 0) {
            MenuItemSelectLastTab_2b30d0();
        } else {
            MenuItemSetOpenModeMaybe_2a4ed0(D_00482374, 1);
            if (D_004824A8 >= 6) {
                *(s8 *)(D_00482374 + 0x11) = 6;
                MenuItemSelectTab_2b3550(6, ((s16)(unsigned char)MenuItemGetOpenModeMaybe_2a4ec0(D_00482374)), 0);
            } else {
                *(s8 *)(D_00482374 + 0x11) = D_004824A8;
            }
        }
        MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x140, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x140, 0.0f);
    }
    if (D_0048248C == 0) {
        D_00482490 += D_0047D66C;
        if (!(D_00482490 < D_0047D35C)) {
            D_00482490 = D_0047D35C;
            D_0048248C = 1;
        }
    } else if (D_0048248C == 1) {
        D_00482490 -= D_0047D66C;
    }
    f = D_00482490;
    UiSetWidgetColor_2905b0(D_00482360, 0x41, f, f, f, 1.0f);
    ok = true;
    m = UiEntryListFindByTag_28ea40(D_00482364, 3);
    c = MenuGetItemAtCell_2a7000(*(s8 *)(D_00482374 + 0x11), m + 4);
    if (c != 0 && *(s32 *)(c + 0x10) != 0 && ItemDefIsKindCId4B0_40e310(*(s32 *)(c + 0x10)) != 0 && D_0048241C == 0) {
        u = InvObjCastToItem4B0_3d3cd0(c, 0, 0, 0);
        if (u != 0 && CageRecIsPlaced_3d0d20(u) != 0 && ((unsigned char)LoadHandleIsReady_28b200(D_004823F8)) == 0) {
            ok = false;
        }
    }
    if (D_00482490 <= 1.0f && D_0048248C == 1 && ok) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x1A9, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x1A9, 0x68, 0x15E);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x1A9, 0.0f);
        D_00482490 = 1.0f;
        UiSetWidgetColor_2905b0(D_00482360, 0x41, 1.0f, 1.0f, 1.0f, 1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x227, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x227, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x74, 1.0f, D_0047D790, -1.0f);
        g = GetGameData_1fede0();
        for (i = 0; i < 3; i++) {
            u = InvGetItem4B0_3c80c0(g->x18, i);
            if (u != 0) {
                if (CageRecIsPlaced_3d0d20(u) == 0 || CageRecCountTriggered_3d08c0(u) <= 0) {
                    D_004824B0[i] = 0;
                }
            }
        }
        if (D_0047EC50 < 0 && D_0048241C == 0) {
            for (j = 0; j < 3; j++) {
                u = InvGetItem4B0_3c80c0(g->x18, j);
                if (u == 0) {
                    continue;
                }
                if (CageRecIsPlaced_3d0d20(u) == 0 || CageRecCountTriggered_3d08c0(u) <= 0) {
                    D_004824B0[j] = 0;
                }
                if (CageRecIsPlaced_3d0d20(u) != 0 && CageRecCountTriggered_3d08c0(u) > 0) {
                    p = &D_004824B0[j];
                    old = *p;
                    if (old != CageRecCountTriggered_3d08c0(u)) {
                        *p = CageRecCountTriggered_3d08c0(u);
                        D_0047EC50 = j;
                        StateMachineSetState_28ede0(D_0048235C, 0xB, 0);
                        return 1;
                    }
                }
            }
        }
        MenuItemSectionEnter_2b3400();
    }
    return 1;
}
