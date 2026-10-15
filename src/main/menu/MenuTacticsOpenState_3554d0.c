#include "types.h"
#pragma optimization_level 3

typedef struct Ent5 { s32 id; s32 a; s32 b; s32 c; s32 d; } Ent5;
typedef struct Tab4 { Ent5 e[4]; } Tab4;
typedef struct H3 { s16 v[3]; } H3;

extern u8 *GetGameData_1fede0();
extern s32 SceneSoundGetSlot0HandleCur_207df0();
extern f32 UiPageScrollBarLayout_289710(u8 *, s32, s32, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSlideInWidgetPair_28d010(s32, s32, s32);
extern void MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
extern u8 *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern u8 *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSetWidgetParent_2911a0(s32, s32, s32);
extern void MenuTacticsAbilityListRefreshMaybe_355d20(u8 *, s32, s32);
extern void MenuCharaSelTabsLayoutMaybe_356160(u8 *, s32, s32);
extern void MenuCharaSelTabsLayoutMaybe_356600(u8 *, s32, s32);
extern void MenuTacticsMemberLabelSpritesMaybe_356920(u8 *, s32);
extern void MenuTacticsMemberFaceSprites_356ad0(u8 *, s32);
extern void MenuTacticsMemberIconLayoutMaybe_356c80(u8 *, s32);
extern void MenuTacticsMemberStatValues_356d50(u8 *, s32);
extern void MenuTacticsMemberGaugesRefresh_356f90(u8 *, s32);
extern s16 PartyMenuCursorGet_3c0760(s32, s32);
extern void PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyFindSlotOfId_3c3070(s32, s32);
extern s32 D_00453C30[];
extern u16 D_00462A28[];
extern f32 D_0047D35C;
extern f32 D_0047D5EC;
extern f32 D_0047D610;
extern f32 D_0047D61C;
extern s16 D_0047F7A0;
extern s16 D_0047F7A2;
extern s16 D_0047F7A4;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_0048236C;
extern u8 *D_0048237C;
extern s16 D_00482F14;
extern s32 D_00482F18;
extern s32 D_00482F1C;
extern f32 D_00482F20;
extern u8 D_004B2570[];

#define G18 (*(s32 *)(g + 0x18))

s32 MenuTacticsOpenState_3554d0(s32 arg0, s32 arg1) {
    u16 t; u8 *e0; u8 *e2; H3 hv; s32 n; u8 *o; u8 *g; s32 cur; Tab4 tab; u8 *r; s32 j; u8 *w; s32 i; u8 *e1; s32 id; Ent5 *e;

    if (arg1 != 0) {
        UiSetWidgetVisible_290010(D_00482360, 0xBB, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0xBB, 0x200, 0x42);
        UiMoveWidgetUniform_290f50(D_00482360, 0xBB, 0x42, 0x42, 0, D_0047D61C);
        UiFadeWidgetAlpha_290690(D_00482360, 0xBB, 1.0f, 0.0625f, 0.0f);
        D_00482F18 = SceneSoundGetSlot0HandleCur_207df0();
        UiSetWidgetPos_290f60(D_00482360, 0xBC, 6, 5);
        UiSetWidgetColor_2905b0(D_00482360, 0xBC, 0.0f, 0.0f, 0.0f, D_0047D61C);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1F, 1);
        MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
        UiSetWidgetPos_290f60(D_00482360, 0xC1, 0x10, 0x7B);
        hv.v[0] = D_0047F7A0;
        hv.v[1] = D_0047F7A2;
        hv.v[2] = D_0047F7A4;
        g = GetGameData_1fede0();
        UiSetWidgetPos_290f60(D_00482360, 0xD4, hv.v[PartyFindSlotOfId_3c3070(G18, *(s16 *)(G18 + 0x18E))], -3);
        UiSlideInWidgetPair_28d010(0x18, 0xF, D_00482360);
        UiFadeWidgetAlpha_290690(D_00482360, 0x41, 1.0f, D_0047D610, -1.0f);
        { s32 t2 = PartyCountMembers_3c2010(G18, 1, 1); n = t2; }
        for (i = 0; i < 3; i++) {
            id = (u16)(i + 0x1A1);
            for (j = 0; (t = D_00462A28[j]) != 0; j++) {
                UiSetWidgetParent_2911a0(D_00482360, (u16)(i + t), id);
            }
            if (i < n) {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 1, 1);
            } else {
                UiSetWidgetsVisibleById_291110(D_00482360, id, 0, 1);
            }
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0xC6, 0, 1);
        MenuTacticsMemberIconLayoutMaybe_356c80(D_0048237C, 0xD2);
        MenuTacticsMemberFaceSprites_356ad0(D_0048237C, 0xF5);
        MenuTacticsMemberLabelSpritesMaybe_356920(D_0048237C, 0xF8);
        MenuTacticsMemberGaugesRefresh_356f90(D_0048237C, 0xEF);
        MenuTacticsMemberStatValues_356d50(D_0048237C, 0xEC);
        PartyCountReserve_3c1c20(G18, 1, 1);
        D_00482F14 = 0;
        if (*(s16 *)(*(u8 **)(g + 0xC) + 0x26) == 1) {
            D_00482F14 = PartyMenuCursorGet_3c0760(G18, 5);
        }
        if (n - 1 < D_00482F14) {
            D_00482F14 = 0;
        }
        MenuCharaSelTabsLayoutMaybe_356600(D_0048237C, 0xD1, D_00482F14);
        MenuCharaSelTabsLayoutMaybe_356160(D_0048237C, 0xBE, D_00482F14);
        MenuTacticsAbilityListRefreshMaybe_355d20(D_0048237C, D_00482F14, 0);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x1A6, 0.0f);
        e0 = UiEntryListFindByTag_28ea40(D_00482364, 0x1F);
        e1 = UiEntryListFindByTag_28ea40(D_00482364, 0x21);
        e2 = UiEntryListFindByTag_28ea40(D_00482364, 0x23);
        *(s16 *)(e0 + 0xC) = *(s16 *)(e1 + 0xC) = *(s16 *)(e2 + 0xC) = n - 1;
        *(s16 *)(e0 + 0x14) = D_00482F14;
        *(s16 *)(e2 + 0x1A) = 0;
        *(f32 *)(D_0048237C + 0x6C) = UiPageScrollBarLayout_289710(D_0048237C, 0x1A5, 0xAA, 6, *(s16 *)(D_0048237C + 0x70), 0);
        UiSetWidgetPos_290f60(D_00482360, 0x1A5, 0x178, 0x33);
        D_00482F1C = 0;
        D_00482F20 = 0.0f;
        UiSetWidgetsVisibleById_291110(D_0048236C, 1, 0, 1);
        w = UiFindWidget_290460(D_00482360, 0xC8);
        cur = *(s16 *)(*(u8 **)(g + 0xC) + 0x24);
        if (w != 0) {
            r = *(u8 **)(w + 0x20);
            o = *(u8 **)(w + 0x28);
            if (r != 0) {
                tab = *(Tab4 *)D_00453C30;
                for (i = 0; i < 4; i++) {
                    e = &tab.e[i];
                    if (cur == e->id) {
                        *(s16 *)(r + 0x8) = e->a;
                        *(s16 *)(r + 0xA) = e->b;
                        *(s16 *)(r + 0xC) = e->c;
                        *(s16 *)(r + 0x4) = e->c;
                        *(s16 *)(r + 0x6) = e->d;
                        *(s16 *)(r + 0xE) = e->d;
                        *(s32 *)(o + 4) = MsgTableLookup_28aa30(D_00481BBC, i + 0x4E);
                    }
                    UiSetTextString_28f510(D_0048236C, 3, MsgTableLookup_28aa30(D_00481BBC, i + 0x4E), i);
                }
            }
        }
        UiSetTextString_28f510(D_00482360, 0xC7, MsgTableLookup_28aa30(D_00481BBC, 0x5E), 0);
    }
    if (D_00482F1C == 0) {
        D_00482F20 = D_00482F20 + D_0047D5EC;
        if (!(D_00482F20 < D_0047D35C)) {
            D_00482F20 = D_0047D35C;
            D_00482F1C = 1;
        }
    } else if (D_00482F1C == 1) {
        D_00482F20 = D_00482F20 - D_0047D5EC;
    }
    UiSetWidgetColor_2905b0(D_00482360, 0x41, D_00482F20, D_00482F20, D_00482F20, 1.0f);
    if (D_00482F20 <= 1.0f && D_00482F1C == 1) {
        D_00482F20 = 1.0f;
        UiSetWidgetColor_2905b0(D_00482360, 0x41, 1.0f, 1.0f, 1.0f, 1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x96, 0);
    }
    UiSetWidgetPos_290f60(D_00482360, 0xC9, 0x8A, 0);
    return 1;
}
