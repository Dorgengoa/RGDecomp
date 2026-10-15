#include "types.h"

typedef struct {
    u8 pad0[0x26];
    s16 unk26;
} Sub;

typedef struct {
    u8 pad0[0xC];
    Sub *unkC;
    u8 pad10[0x18 - 0x10];
    s32 unk18;
} Ctx;

typedef struct {
    u8 pad0[0x6C];
    s8 unk6C;
} Obj;

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[0x10 - 0xE];
    s16 unk10;
    u8 pad12[0x1A - 0x12];
    s16 unk1A;
} Elem;

extern s32 PadIsTriggered_1839f0(void *, s32);
extern Ctx *GetGameData_1fede0(void);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern s32 MenuGridCursorRequestSe_28e9e0(s32, s32);
extern Elem *UiEntryListFindByTag_28ea40(s32, s32);
extern s32 UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Elem *UiEntryListGetCurrentData_28ec60(s32);
extern s32 StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern s32 UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern s32 MenuWidgetPulseColor_340d40(Obj *, s32, s32);
extern s32 MenuPartyIconsMarkLearnableMaybe_340de0(Obj *, s32);
extern s32 MenuCycleCharaSel_341220(Elem *, s32);
extern s32 MenuCursorBobUpdate_342e70(Elem *, s32, s32, s32, s32);
extern s32 PartyMenuCursorSet_3c0710(s32, s32, s16);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern f32 D_0047D65C;
extern f32 D_0047D668;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Obj *D_00482378;
extern s16 D_00482D04;
extern s16 D_00482D10;
extern s32 D_00482D24;
extern u8 D_004B2570[0x400];

s32 MenuMemberListSelectState_342780(s32 pd0, s32 arg1) {
    s32 temp_3;
    s16 temp_5;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_16_3;
    s32 temp_16_4;
    s32 temp_20;
    Ctx *temp_17;
    Elem *temp_18;
    Elem *temp_18_2;
    Elem *temp_19;
    Elem *temp_2;

    temp_17 = GetGameData_1fede0();
    if (arg1 != 0) {
        D_00482D04 = 0;
        UiEntryListSelectByTag_28ea90(D_00482364, 0x17, 0);
        arg1 = temp_17->unk18;
        temp_16_2 = PartyCountMembers_3c2010(arg1, 1, 1);
        temp_16_3 = temp_16_2 + PartyCountReserve_3c1c20(arg1, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x19E, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 1.0f, D_0047D65C, -1.0f);
        temp_20 = D_00482378->unk6C;
        temp_19 = UiEntryListFindByTag_28ea40(D_00482364, 0x18);
        temp_18 = UiEntryListFindByTag_28ea40(D_00482364, 0x19);
        temp_2 = UiEntryListGetCurrentData_28ec60(D_00482364);
        temp_2->unk10 = temp_20;
        temp_3 = (s16) (temp_16_3 - 1);
        temp_18->unkC = temp_3;
        temp_19->unkC = temp_3;
        temp_2->unk8 = temp_3;
        MenuCursorBobUpdate_342e70(temp_2, 0, 0, 0, 1);
        MenuPartyIconsMarkLearnableMaybe_340de0(D_00482378, 0x19C);
    }
    MenuWidgetPulseColor_340d40(D_00482378, 0x19C, 0);
    temp_16_4 = MenuGridCursorInput_28e170(D_00482364, &(*(s8 *)D_004B2570), 2, 0);
    temp_18_2 = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (temp_16_4 == 2) {
        D_00482D10 = temp_18_2->unk10;
        if (temp_17->unkC->unk26 == 1) {
            PartyMenuCursorSet_3c0710(*(s32 *)((u8 *)temp_17 + 0x18), 6, D_00482D10);
        }
        D_00482D24 = 0;
        StateMachineSetState_28ede0(D_0048235C, 0x6F, 0);
    } else if (temp_16_4 == 1 || PadIsTriggered_1839f0(&(*(s8 *)D_004B2570), 0x4000) != 0) {
        if (PadIsTriggered_1839f0(&(*(s8 *)D_004B2570), 0x4000) != 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        }
        UiFadeWidgetAlpha_290690(D_00482360, 0x19E, 0.0f, D_0047D668, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x70, 0);
    } else if (PadIsTriggered_1839f0(&(*(s8 *)D_004B2570), 0xC) != 0) {
        MenuCycleCharaSel_341220(temp_18_2, 1);
        UiEntryListFindByTag_28ea40(D_00482364, 0x19)->unk1A = 0;
    }
    return 1;
}
