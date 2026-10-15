#include "types.h"


typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
} E2af;

extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 PadIsRepeatTriggered_183dd0(void *, s32);
extern u8 *GetGameData_1fede0(void);
extern void PlayMenuSe_289ef0(s32);
extern void UiSelFrameCalcTileCounts_28d9d0(void *);
extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(u8 *, void *, s32, s32);
extern E2af *UiEntryListFindByTag_28ea40(u8 *, s32);
extern void UiEntryListSelectByTag_28ea90(u8 *, s32, s32);
extern E2af *UiEntryListGetCurrentData_28ec60(u8 *);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuItemInfoPopupShow_2a33e0(u8 *, s32, s32, s32, void *, s32, s32, s32, f32);
extern void MenuItemInfoWidgetsCache_2a65f0(void *);
extern void MenuItemSelectTab_2b3550(s32, s32, s32);
extern void PartyMenuCursorSet_3c0710(s32, s32, s16);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern f32 D_0047D760;
extern s32 D_0048235C;
extern s32 D_00482360;
extern u8 *D_00482364;
extern u8 *D_00482374;
extern s16 D_00482488;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;
extern u8 D_004B2570[0x400];
extern u8 D_004DB430[0x400];

s32 MenuInvGridSelectState_2af060(s32 pad0, s32 arg1)
{
    E2af *e;
    E2af *t;
    u8 *g;
    s32 h;
    s32 r;
    s32 flag;
    s32 v;
    s32 sp50[4];

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 1, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 8, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D760, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D760, -1.0f);
        e = UiEntryListFindByTag_28ea40(D_00482364, 8);
        UiSelFrameSetRect_28db40(D_004DB430, 0x78, (e->f4 + e->f14 * e->f8) - 0x24, (e->f6 + e->f16 * e->fA) - 0x27, 0x28, 0x2E, 0x62, 0x49);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB430);
        h = InvFindByCategoryIndex_3c86e0(*(s32 *)(GetGameData_1fede0() + 0x18), 4, 0, e->f14, e->f16, 0);
        MenuItemInfoWidgetsCache_2a65f0(sp50);
        MenuItemInfoPopupShow_2a33e0(D_00482374, h, 0x1AA, 0x1A9, sp50, 0x68, 0x15E, -1, 2.0f);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    t = UiEntryListGetCurrentData_28ec60(D_00482364);
    flag = 0;
    if (r == 2) {
        if (D_00482488 != 0) {
            StateMachineSetState_28ede0(D_0048235C, 0xB1, 0);
        } else {
            D_004824A0 = t->f10;
            D_004824A4 = t->f12;
            D_004824A8 = 7;
            g = GetGameData_1fede0();
            if (*(s16 *)(*(u8 **)(g + 0xC) + 0x26) == 1) {
                PartyMenuCursorSet_3c0710(*(s32 *)(g + 0x18), 0, D_004824A0);
                PartyMenuCursorSet_3c0710(*(s32 *)(g + 0x18), 1, D_004824A4);
                PartyMenuCursorSet_3c0710(*(s32 *)(g + 0x18), 2, D_004824A8);
            }
            StateMachineSetState_28ede0(D_0048235C, 0x1C, 0);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 8) != 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 8) == 0) {
        v = 0;
        flag = 1;
    } else if (PadIsTriggered_1839f0(D_004B2570, 4) != 0) {
        flag = 1;
        v = *(s8 *)(D_00482374 + 0x10) - 2;
    } else if (*(s32 *)(D_00482364 + 0x14) == 1) {
        PlayMenuSe_289ef0(4);
        if (t->f10 < 4) {
            e = UiEntryListFindByTag_28ea40(D_00482364, 6);
            e->f14 = t->f10;
            e->f16 = 2;
            if (e->f14 > 2) {
                e->f14 = 2;
            }
            StateMachineSetState_28ede0(D_0048235C, 0x15, 0);
        } else {
            e = UiEntryListFindByTag_28ea40(D_00482364, 7);
            e->f16 = 1;
            if (t->f10 < 6) {
                e->f14 = 0;
            } else {
                e->f14 = 1;
            }
            StateMachineSetState_28ede0(D_0048235C, 0x18, 0);
        }
    }
    if (flag != 0) {
        MenuItemSelectTab_2b3550(v, 0, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
