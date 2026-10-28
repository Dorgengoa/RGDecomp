#include "types.h"

struct Chr {
    VC_VPTR_MEMBER;   
       
       
       
     
    s32 f50() { return VCM0(s32, 0x50); }
};
struct G740 { u8 pad[0x11]; s8 m11; u8 pad12[0x2A]; s32 m3C; u8 m40; };
struct Inf { u8 pad[0x26]; s16 m26; };
struct Scn { u8 pad[0xC]; Inf *mC; u8 pad10[8]; s32 m18; };
struct Pos { u8 pad[0x10]; s16 m10; s16 m12; s16 m14; s16 m16; };
struct Tmp { u8 pad[0x10]; };

extern "C" f32 D_0047D5D0;
extern "C" f32 D_0047D994;
extern "C" f32 D_0047D998;
extern "C" f32 D_0047D99C __attribute__((section(".sdata")));
extern "C" s16 D_0047FB20;
extern "C" s16 D_0047FB24;
extern "C" s16 D_0047FB28;
extern "C" s16 D_0047FB2C;
extern "C" s32 D_0048470C;
extern "C" s32 D_00484710;
extern "C" s32 D_00484720;
extern "C" G740 *D_00484740;
extern "C" u8 D_004B2570[];

extern "C" {
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
Scn *GetGameData_1fede0(void);
s32 MenuGetMode_2a4e30(G740 *);
void MenuItemCategoryTabsLayout_288ac0(s32, s32, s32, s32, s32, s32);
void MenuItemGridMarkInUse_2a4860(G740 *, s32);
void MenuFillItemGrid_2a4b40(G740 *, s32);
void MenuFillItemCounts_2a3d90(G740 *, s32);
Pos *UiEntryListFindByTag_28ea40(s32, s32);
Chr *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
void TransMenuItemFetchWidgetRefs_37bdb0(Tmp *);
void MenuItemInfoPopupShow_2a33e0(G740 *, Chr *, s32, s32, Tmp *, s32, s32, s32, f32);
s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
Pos *UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void PartyMenuCursorSet_3c0710(s32, s32, s16);
s32 PadIsTriggered_1839f0(void *, s32);
void MenuSetSelItem_2a02e0(G740 *, Chr *);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
}

extern "C" s32 TransMenuItemGridSelectState_37fb00(s32 pad0, s32 arg1)
{
    Tmp sp70 __attribute__((aligned(16)));
    s32 h;
    Chr *c;
    Scn *scn;
    s32 x;
    s32 r;
    s32 k;
    s32 y;
    Pos *p;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0xB, 0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 1.0f, D_0047D994, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7604, 1.0f, D_0047D994, -1.0f);
        scn = GetGameData_1fede0();
        k = D_00484740->m11;
        h = MenuGetMode_2a4e30(D_00484740);
        MenuItemCategoryTabsLayout_288ac0(D_00484710, 0x75FA, 0x75FF, 0x75FE, k, h);
        MenuItemGridMarkInUse_2a4860(D_00484740, 0x7600);
        MenuFillItemGrid_2a4b40(D_00484740, 0x7602);
        MenuFillItemCounts_2a3d90(D_00484740, 0x7603);
        p = UiEntryListFindByTag_28ea40(D_00484720, 0xB);
        c = InvFindByCategoryIndex_3c86e0(scn->m18, h, k, p->m14, p->m16, 0);
        TransMenuItemFetchWidgetRefs_37bdb0(&sp70);
        MenuItemInfoPopupShow_2a33e0(D_00484740, c, 0x762E, 0x762D, &sp70, 0x68, 0x15E, -1, D_0047D5D0);
    } else {
        r = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 6, 0);
        p = UiEntryListGetCurrentData_28ec60(D_00484720);
        scn = GetGameData_1fede0();
        y = p->m12;
        x = p->m10;
        k = D_00484740->m11;
        h = MenuGetMode_2a4e30(D_00484740);
        c = InvFindByCategoryIndex_3c86e0(scn->m18, h, k, x, y, 0);
        if (r == 1) {
            if (c != 0) {
                StateMachineSetState_28ede0(D_0048470C, 0x22, 0);
            }
        } else if (r == 2) {
            D_0047FB20 = p->m10;
            D_0047FB24 = p->m12;
            D_0047FB28 = D_00484740->m11;
            D_0047FB2C = MenuGetMode_2a4e30(D_00484740);
            if (scn->mC->m26 == 1) {
                PartyMenuCursorSet_3c0710(scn->m18, 0x17, D_0047FB20);
                PartyMenuCursorSet_3c0710(scn->m18, 0x18, D_0047FB24);
                PartyMenuCursorSet_3c0710(scn->m18, 0x19, D_0047FB28);
                PartyMenuCursorSet_3c0710(scn->m18, 0x1A, D_0047FB2C);
            }
            UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 0.0f, -0.5f, -1.0f);
            UiFadeWidgetAlpha_290690(D_00484710, 0x7604, 0.0f, -0.5f, -1.0f);
            StateMachineSetState_28ede0(D_0048470C, 0x21, 0);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            if (c != 0) {
                MenuSetSelItem_2a02e0(D_00484740, c);
                D_00484740->m3C = c->f50();
                StateMachineSetState_28ede0(D_0048470C, 0x36, 0);
            }
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0) {
            if (c != 0) {
                MenuSetSelItem_2a02e0(D_00484740, c);
                D_00484740->m40 = 2;
                UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 0.0f, D_0047D99C, -1.0f);
                StateMachineSetState_28ede0(D_0048470C, 0x2D, 0);
            }
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
            UiSetWidgetsVisibleById_291110(D_00484710, 0x7609, 1, 1);
            UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 0.0f, D_0047D99C, -1.0f);
            UiFadeWidgetAlpha_290690(D_00484710, 0x7609, 1.0f, D_0047D998, -1.0f);
            StateMachineSetState_28ede0(D_0048470C, 0x30, 0);
        }
    }
    return 1;
}
