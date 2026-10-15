#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    char name[0x40];
} Ent00398AB0;

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[2];
    s16 unkE;
    u8 pad10[6];
    s16 unk16;
    u8 pad18[2];
    s16 unk1A;
} Win00398AB0;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} Sys00398AB0;

s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
Sys00398AB0 *GetGameData_1fede0(void);
void PlayMenuSe_289ef0(s32);
s32 MsgTableLookup_28aa30(s32, s32);
Win00398AB0 *UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
s32 UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
s32 UiGetWidgetTextLineAdvance_28f380(s32, s32, s32);
s32 UiGetWidgetTextHeight_28f3d0(s32, s32, s32);
void UiSetTextString_28f510(s32, s32, s32, s32);
void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
f32 InfoEdgeScrollBarLayout_398f80(s32, s32, s32);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
extern f32 D_0047D580;
extern f32 D_0047D5A8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern f32 D_00483594;
extern s32 D_004835A8;
extern Ent00398AB0 *D_004835AC;
extern s32 D_004835B0;
extern u8 D_004B2570[0x400];

s32 InfoEdgeEntryViewState_398ab0(s32 arg0, s32 arg1) {
    Sys00398AB0 *sys;
    s32 i;
    Win00398AB0 *w;
    s32 skip;
    s32 a;
    s32 b;
    s32 c;
    s32 r;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0xF, 1);
        sys = GetGameData_1fede0();
        for (i = 0; i < 9; i++) {
            UiSetTextString_28f510(D_00482360, 0x216, 0, i);
            UiSetTextString_28f510(D_00482360, 0x214, 0, i + 1);
            UiSetSpriteSizeUvSize_28f670(D_00482360, 0x218, 0, 0, 0, 0, i);
        }
        UiSetTextString_28f510(D_00482360, 0x215, 0, 0);
        w = UiEntryListFindByTag_28ea40(D_00482364, 0xE);
        skip = w->unk16 + w->unk1A;
        for (i = 0; i < D_004835A8; i++) {
            if (StateFlagTest_3ccd70(sys->unk10, D_004835AC[(u32)i].unk6) != 0) {
                if (skip <= 0) {
                    UiSetTextString_28f510(D_00482360, 0x214, (s32)D_004835AC[i].name, 0);
                    UiSetTextString_28f510(D_00482360, 0x215, MsgTableLookup_28aa30(D_004835B0, D_004835AC[i].unk4), 0);
                    UiSetWidgetPos_290f60(D_00482360, 0x215, 0, 0);
                    StateFlagSet_3ccb70(sys->unk10, D_004835AC[i].unk8, 1, 0);
                    break;
                } else {
                    skip--;
                }
            }
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0x213, 0, 1);
        a = UiGetWidgetTextHeight_28f3d0(D_00482360, 0x215, 0);
        b = UiGetWidgetTextLineAdvance_28f380(D_00482360, 0x215, 0);
        c = (a - b * 10) / b;
        if (c < 0) {
            c = 0;
        }
        w = UiEntryListFindByTag_28ea40(D_00482364, 0xF);
        w->unkA = b;
        w->unkE = c;
        D_00483594 = InfoEdgeScrollBarLayout_398f80(0xF0, 0xA, c + 0xA);
        UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, 0);
    } else {
        r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 1, 0);
        UiEntryListGetCurrentData_28ec60(D_00482364);
        if ((u32)(r - 1) < 2) {
            PlayMenuSe_289ef0(6);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 1, 1);
            UiFadeWidgetAlpha_290690(D_00482360, 0x219, 1.0f, D_0047D5A8, D_0047D580);
            StateMachineSetState_28ede0(D_0048235C, 0xA7, 0);
        }
    }
    return 1;
}
