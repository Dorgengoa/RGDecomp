#include "types.h"
#pragma optimization_level 3

struct Q *GetGameData_1fede0();
s32 SceneSoundGetSlot0HandleCur_207df0();
f32 UiPageScrollBarLayout_289710(s8 *, s32, s32, s32, s32, s32);
void UiSlideInWidgetPair_28d010(s32, s32, s32);
void MenuGridCursorInput_28e170(s32, void *, s32, s32);
s8 *UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
s8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiMoveWidgetUniform_290f50(s32, f32, s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuSetMemberValueTextMaybe_3405a0(s8 *, s32);
void MenuCharaAbilityPageFill_3406a0(s8 *, s32, s32);
void MenuSetTabStyleMaybe_340a40(s8 *, s32, s32);
void MenuPartyIconsMarkLearnableMaybe_340de0(s8 *, s32);
void MenuPartyRowLayoutMaybe_340f00(s8 *, s32);
s16 PartyMenuCursorGet_3c0760(s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 WorldDataMgrNoRequestPending_3eef10(s32);
extern f32 D_0047D35C;
extern f32 D_0047D65C;
extern f32 D_0047D660;
extern f32 D_0047D66C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s8 *D_00482378;
extern s16 D_00482D04;
extern f32 D_00482D08;
extern s16 D_00482D0C;
extern s16 D_00482D10;
extern s32 D_00482D14;
extern s32 D_00482D1C;
extern f32 D_00482D20;
extern u8 D_004B2570[0x400];

struct Q;
typedef struct Q { u8 pad[0xC]; s8 *c; u8 pad2[8]; s32 h; } Q;
#define F(p, T, o) (*(T *)((s8 *)(p) + (o)))

s32 MenuMemberListOpenState_3429f0(void *self, s32 init) {
    s8 *p;
    Q *q;
    s32 a;
    s32 b;
    f32 one;

    if (init) {
        D_00482360 = F(D_00482378, s32, 0x5C);
        D_0048235C = F(D_00482378, s32, 0x64);
        D_00482364 = F(D_00482378, s32, 0x60);
        D_00482D14 = SceneSoundGetSlot0HandleCur_207df0();
        UiSetWidgetVisible_290010(D_00482360, 0x187, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x187, 0x200, 0x4A);
        UiMoveWidgetUniform_290f50(D_00482360, D_0047D660, 0x187, 0x41, 0x4A, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x187, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x189, 0x10, 0x5A);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x17, 1);
        MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x122, 0);
        if (p == 0) return 0;
        F(p, s16, 0xC6) = 0x8B;
        F(p, s16, 0x26) = 0x8B;
        F(p, s16, 0xE2) = 0xCA;
        F(p, s16, 0x82) = 0xCA;
        F(p, s16, 0x42) = 0xCA;
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x12D, 0);
        if (p == 0) return 0;
        F(p, s16, 0x26) = 0x9B;
        F(p, s16, 0x42) = 0xD2;
        UiSetSpriteX_28fcd0(D_00482360, 0x12B, 0x1E, 5);
        UiSetSpriteX_28fcd0(D_00482360, 0x12C, 0x12, 5);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x19F, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x19F, 0x64, 0x146);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x19F, 0.0f);
        UiSlideInWidgetPair_28d010(0x19, 0x10, D_00482360);
        UiFadeWidgetAlpha_290690(D_00482360, 0x41, 1.0f, D_0047D65C, -1.0f);
        MenuPartyRowLayoutMaybe_340f00(D_00482378, 0x19C);
        UiSetWidgetPos_290f60(D_00482360, 0x19C, 0x19, 0x1E);
        q = GetGameData_1fede0();
        if (q == 0) return 0;
        a = PartyCountMembers_3c2010(q->h, 1, 1);
        b = PartyCountReserve_3c1c20(q->h, 1, 1);
        D_00482D10 = 0;
        if (F(q->c, s16, 0x26) == 1) {
            D_00482D10 = PartyMenuCursorGet_3c0760(q->h, 6);
        }
        if (a + b - 1 < D_00482D10) {
            D_00482D10 = 0;
        }
        MenuSetTabStyleMaybe_340a40(D_00482378, 0x19B, D_00482D10);
        F(D_00482378, s8, 0x6C) = D_00482D10;
        UiSetWidgetsVisibleById_291110(D_00482360, 0x1AB, 0, 1);
        MenuCharaAbilityPageFill_3406a0(D_00482378, D_00482D10, 0);
        MenuSetMemberValueTextMaybe_3405a0(D_00482378, D_00482D10);
        F(D_00482378, f32, 0x70) = UiPageScrollBarLayout_289710(D_00482378, 0x19A, 0xA8, 6, F(D_00482378, s16, 0x74), 0);
        UiSetWidgetPos_290f60(D_00482360, 0x19A, 0x180, 0x30);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x18D, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x19E, 0, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x19E, 0.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x18E, 0x140, 0x12);
        F(UiEntryListFindByTag_28ea40(D_00482364, 0x19), s16, 0x16) = 0;
        D_00482D1C = 0;
        D_00482D08 = 0.5f;
        D_00482D20 = 0.0f;
        D_00482D0C = 1;
        D_00482D04 = 0;
    }
    if (D_00482D1C == 0) {
        D_00482D20 = D_00482D20 + D_0047D66C;
        if (!(D_00482D20 < D_0047D35C)) {
            D_00482D20 = D_0047D35C;
            D_00482D1C = 1;
        }
    } else if (D_00482D1C == 1) {
        D_00482D20 -= D_0047D66C;
    }
    UiSetWidgetColor_2905b0(D_00482360, 0x41, D_00482D20, D_00482D20, D_00482D20, 1.0f);
    one = 1.0f;
    if (D_00482D20 <= one && D_00482D1C == 1) {
        D_00482D20 = one;
        UiSetWidgetColor_2905b0(D_00482360, 0x41, one, one, one, one);
        if (WorldDataMgrNoRequestPending_3eef10(F(GetGameData_1fede0(), s32, 8)) != 0) {
            MenuPartyIconsMarkLearnableMaybe_340de0(D_00482378, 0x19C);
            StateMachineSetState_28ede0(D_0048235C, 0x6E, 0);
        }
    }
    return 1;
}
