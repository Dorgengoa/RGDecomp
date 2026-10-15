#include "types.h"

typedef struct List {
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
    s16 f18;
    s16 f1A;
} List;

typedef struct Win {
    u8 pad[0x14];
    s32 flags;
} Win;

s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsRepeatTriggered_183dd0(void *, s32);
s32 MenuGridCursorInput_28e170(Win *, void *, s32, s32);
void MenuGridCursorRequestSe_28e9e0(Win *, s32);
List *UiEntryListFindByTag_28ea40(Win *, s32);
void UiEntryListSelectByTag_28ea90(Win *, s32, s32);
List *UiEntryListGetCurrentData_28ec60(Win *);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
void UiSetWidgetAlpha_2907a0(s32, s32, f32);
void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void InfoEdgeMenuLoadPoll_3988c0(void);
s32 InfoEdgeFillList_398d90(s16);
f32 InfoEdgeScrollBarLayout_398f80(s32, s32, s32);
void InfoEdgeDebugUnlockAll_399c10(void);
extern f32 D_0047D5A8;
extern f32 D_0047D5D8;
extern s32 D_0048235C;
extern s32 D_00482360;
extern Win *D_00482364;
extern f32 D_00483594;
extern s16 D_00483598;
extern f32 D_0048359C;
extern f32 D_004835A0;
extern u8 D_004835B4;
extern u8 D_004B2570[];

s32 InfoEdgeListSelect_399570(s32 arg0, s32 init) {
    List *w;
    s32 cnt;
    List *l;
    s32 r;

    if (D_004835B4 == 0) InfoEdgeMenuLoadPoll_3988c0();
    if (init != 0) {
        w = UiEntryListFindByTag_28ea40(D_00482364, 0xE);
        cnt = InfoEdgeFillList_398d90(w->f1A);
        D_00483594 = InfoEdgeScrollBarLayout_398f80(0xF0, 9, cnt);
        UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, (s32)((f32)w->f1A * D_00483594));
        l = UiEntryListGetCurrentData_28ec60(D_00482364);
        if (cnt < 10) {
            l->fA = cnt - 1;
            l->fE = cnt - 1;
        } else {
            l->fA = 8;
            l->fE = cnt - 1;
        }
        D_0048359C = 0.5f;
        D_004835A0 = 1.0f;
        if (cnt == 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 0, 1);
            UiSetWidgetAlpha_2907a0(D_00482360, 0x219, 0.0f);
        } else {
            UiSetWidgetAlpha_2907a0(D_00482360, 0x219, 1.0f);
        }
        UiEntryListSelectByTag_28ea90(D_00482364, 0xE, 0);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    l = UiEntryListGetCurrentData_28ec60(D_00482364);
    InfoEdgeDebugUnlockAll_399c10();
    if (r == 1) {
        if (UiGetWidgetAlpha_290770(D_00482360, 0x219) == 0.0f) {
            StateMachineSetState_28ede0(D_0048235C, 0xA8, 0);
            goto end;
        }
        if (D_004835B4 != 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x217, 0, 1);
            UiFadeWidgetAlpha_290690(D_00482360, 0x219, 0.0f, D_0047D5D8, -1.0f);
            StateMachineSetState_28ede0(D_0048235C, 0xA9, 0);
        }
        goto end;
    }
    if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0xA8, 0);
        goto end;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x8000)) {
        if (l->f12 > 0 || l->f16 > 0) MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        if (l->f16 > 0) {
            l->f16 = l->f16 - (s16)(l->fA + 1);
            if (l->f16 < 0) {
                l->f16 = 0;
                l->f12 = 0;
                UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, l->f2, 0);
            }
            InfoEdgeFillList_398d90(l->f16);
        } else {
            l->f16 = 0;
            l->f12 = 0;
            UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, l->f2, 0);
        }
        if (l->f16 < 0) l->f16 = 0;
        UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)l->f16 * D_00483594), 0, D_0047D5A8);
        D_00483598 = l->f12;
        goto end;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x2000)) {
        if (l->f12 < l->fA || l->f16 < l->fE - l->fA) MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        if (l->f16 < l->fE - l->fA) {
            l->f16 = l->f16 + (s16)(l->fA + 1);
            if (l->f16 > l->fE - l->fA) {
                l->f12 = l->fA;
                l->f16 = l->fE - l->fA;
                UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, l->f2 + l->f12 * l->f6, 0);
            }
            InfoEdgeFillList_398d90(l->f16);
        } else {
            l->f12 = l->fA;
            l->f16 = l->fE - l->fA;
            UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, l->f2 + l->f12 * l->f6, 0);
        }
        if (l->f16 < 0) l->f16 = 0;
        UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)l->f16 * D_00483594), 0, D_0047D5A8);
        D_00483598 = l->f12;
        goto end;
    }
    if ((D_00482364->flags & 1) && PadIsTriggered_1839f0(D_004B2570, 0x1000) && !PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000)) {
        if (l->f12 != 0) goto end;
        if (l->f16 != 0) goto end;
        if (l->fE <= 0) goto end;
        MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        l->f12 = l->fA;
        l->f16 = l->fE - l->fA;
        UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, l->f2 + l->f12 * l->f6, 0);
        InfoEdgeFillList_398d90(l->f16);
        UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, (s32)((f32)l->f16 * D_00483594));
        D_00483598 = l->f12;
        if (l->f16 < 0) l->f16 = 0;
        goto end;
    }
    if ((D_00482364->flags & 2) && PadIsTriggered_1839f0(D_004B2570, 0x4000) && !PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000)) {
        if (l->f12 != l->fA) goto end;
        if (l->f16 != l->fE - l->fA) goto end;
        if (l->fE <= 0) goto end;
        MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        l->f12 = 0;
        l->f16 = 0;
        UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, l->f2 + l->f12 * l->f6, 0);
        InfoEdgeFillList_398d90(l->f16);
        UiSetWidgetPos_290f60(D_00482360, 0x21B, 0, (s32)((f32)l->f16 * D_00483594));
        D_00483598 = l->f12;
        if (l->f16 < 0) l->f16 = 0;
    }
end:
    return 1;
}
