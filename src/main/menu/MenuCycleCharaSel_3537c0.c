#include "types.h"

typedef struct {
    u8 pad0[0x6C];
    f32 unk6C;
    s16 unk70;
    s16 unk72;
} Menu003537C0;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[4];
    s16 unk16;
    u8 pad18[2];
    s16 unk1A;
} Win003537C0;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Sys003537C0;

s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsRepeatTriggered_183dd0(void *, s32);
Sys003537C0 *GetGameData_1fede0(void);
f32 UiPageScrollBarLayout_289710(Menu003537C0 *, s32, s32, s32, s32, s32);
void MenuGridCursorRequestSe_28e9e0(s32, s32);
Win003537C0 *UiEntryListFindByTag_28ea40(s32, s32);
Win003537C0 *UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiMoveWidgetUniform_290f50(s32, f32, s32, s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void MenuTacticsAbilityListSetRowRange_3542e0(void);
void MenuTacticsAbilityListRefreshMaybe_355d20(Menu003537C0 *, s32, s32);
void MenuCharaSelTabsLayoutMaybe_356160(Menu003537C0 *, s32, s32);
void MenuCharaSelTabsLayoutMaybe_356600(Menu003537C0 *, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
extern f32 D_0047D34C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu003537C0 *D_0048237C;
extern s16 D_00482F14;
extern u8 D_004B2570[0x400];

s32 MenuCycleCharaSel_3537c0(s32 arg0, s32 arg1) {
    s32 n;
    u8 *pad;
    s32 changed;
    Win003537C0 *w;

    n = PartyCountMembers_3c2010(GetGameData_1fede0()->unk18, 1, 1);
    pad = D_004B2570;
    UiEntryListGetCurrentData_28ec60(D_00482364);
    changed = 0;
    if (PadIsTriggered_1839f0(pad, 0x8004) != 0) {
        if (D_00482F14 > 0) {
            D_00482F14--;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 0x8004) == 0) {
            D_00482F14 = n - 1;
            changed = 1;
        }
    } else if (PadIsTriggered_1839f0(pad, 0x2008) != 0) {
        if (D_00482F14 < n - 1) {
            D_00482F14++;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 0x2008) == 0) {
            D_00482F14 = 0;
            changed = 1;
        }
    }
    if (changed) {
        if (PadIsTriggered_1839f0(pad, 0xA000) == 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        }
        MenuCharaSelTabsLayoutMaybe_356600(D_0048237C, 0xD1, D_00482F14);
        MenuCharaSelTabsLayoutMaybe_356160(D_0048237C, 0xBE, D_00482F14);
        MenuTacticsAbilityListRefreshMaybe_355d20(D_0048237C, D_00482F14, 0);
        D_0048237C->unk6C = UiPageScrollBarLayout_289710(D_0048237C, 0x1A5, 0xAA, 6, D_0048237C->unk70, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x1A5, 0x178, 0x33);
        D_0048237C->unk72 = 0;
        w = UiEntryListFindByTag_28ea40(D_00482364, 0x23);
        w->unk16 = 0;
        w->unk1A = 0;
        w = UiEntryListGetCurrentData_28ec60(D_00482364);
        w->unk10 = D_00482F14;
        MenuTacticsAbilityListSetRowRange_3542e0();
        if (D_0048237C->unk70 <= 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0xC6, 0, 1);
            if (arg1 != 0) {
                StateMachineSetState_28ede0(D_0048235C, 0x96, 0);
            } else {
                StateMachineSetState_28ede0(D_0048235C, 0x99, 0);
                UiMoveWidgetUniform_290f50(D_00482360, D_0047D34C, 0x38, 0x11A, -0x28, 0);
                UiMoveWidgetUniform_290f50(D_00482360, D_0047D34C, 0x37, 0x11D, -0x25, 0);
            }
        }
    }
    return 1;
}
