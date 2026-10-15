#include "types.h"

typedef struct {
    u8 pad0[8];
    s16 x8;
    u8 padA[6];
    s16 x10;
    s16 x12;
} Grp;

typedef struct {
    u8 pad0[0x26];
    s16 x26;
} Sub;

typedef struct {
    u8 pad0[0xC];
    Sub *xC;
    u8 pad10[8];
    s32 x18;
} Info;

extern Info *GetGameData_1fede0(void);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern Grp *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuPartySlotLayoutMaybe_29c970(s32, s32);
extern s8 *MenuGetCursorPos_29fae0(s32);
extern void MenuCursorBobUpdate_2ba9f0(Grp *, s32, s32, s32, s32);
extern void PartyMenuCursorSet_3c0710(s32, s32, s16);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern f32 D_0047D6D0;
extern f32 D_0047D6D4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern s16 D_0048253E;
extern s16 D_0048254C;
extern s16 D_00482550;
extern s32 D_00482564;
extern u8 D_004B2570[];

s32 MenuPartyMemberSelectState_2ba7c0(s32 pad0, s32 arg1)
{
    s8 *s;
    Grp *g;
    Info *info;
    s32 cat;
    s32 a;
    s32 b;
    s32 t;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x10, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x117, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x117, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x117, 1.0f, D_0047D6D0, -1.0f);
        s = MenuGetCursorPos_29fae0(D_00482370);
        g = UiEntryListGetCurrentData_28ec60(D_00482364);
        g->x10 = s[0];
        g->x12 = s[1];
        MenuCursorBobUpdate_2ba9f0(g, 0, 0, 0x40, 1);
        D_0048253E = s[1];
        MenuPartySlotLayoutMaybe_29c970(D_00482370, 0xD9);
        UiSetWidgetVisible_290010(D_00482360, 0x14F, 0, -1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x133, 0, 1);
    }
    cat = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    g = UiEntryListGetCurrentData_28ec60(D_00482364);
    info = GetGameData_1fede0();
    a = PartyCountMembers_3c2010(info->x18, 1, 1);
    b = PartyCountReserve_3c1c20(info->x18, 1, 1);
    if (g->x12 == 0) {
        g->x8 = a - 1;
    } else if (g->x12 == 1) {
        g->x8 = b - 1;
    }
    if (cat == 2) {
        D_00482564 = 0;
        t = g->x10;
        D_0048254C = t;
        D_00482550 = g->x12;
        if (info->xC->x26 == 1) {
            PartyMenuCursorSet_3c0710(info->x18, 3, D_0048254C);
            PartyMenuCursorSet_3c0710(info->x18, 4, D_00482550);
        }
        StateMachineSetState_28ede0(D_0048235C, 0x4C, 0);
    } else if (cat == 1) {
        StateMachineSetState_28ede0(D_0048235C, 0x4E, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x117, 0.0f, D_0047D6D4, -1.0f);
    }
    return 1;
}
