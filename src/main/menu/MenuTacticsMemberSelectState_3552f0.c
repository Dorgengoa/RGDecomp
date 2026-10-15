#include "types.h"

extern s32 PadIsTriggered_1839f0(void *arg0, s32 arg1);
typedef struct Self Self;
extern Self *GetGameData_1fede0(void);
extern s32 MenuGridCursorInput_28e170(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern void MenuGridCursorRequestSe_28e9e0(s32 arg0, s32 arg1);
extern void UiEntryListSelectByTag_28ea90(s32 arg0, s32 arg1, s32 arg2);
extern void *UiEntryListGetCurrentData_28ec60(s32 arg0);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiFadeWidgetAlpha_290690(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void UiSetWidgetsVisibleById_291110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void MenuCycleCharaSel_3537c0(void *arg0, s32 arg1);
extern void MenuCursorBobUpdate_355a70(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void PartyMenuCursorSet_3c0710(s32 arg0, s32 arg1, s64 arg2);
extern s32 PartyCountMembers_3c2010(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_0047D610;
extern f32 D_0047D618;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_00482F14;
extern s32 D_00482F24;
extern u8 D_004B2570[];

typedef struct Sub { u8 pad[0x26]; s16 f26; } Sub;
struct Self { u8 pad[0xC]; Sub *fC; u8 pad10[8]; volatile s32 f18; };

s32 MenuTacticsMemberSelectState_3552f0(s32 arg0, s32 arg1)
{
    Self *self;
    s32 r;
    void *obj;
    s16 v;

    self = GetGameData_1fede0();
    PartyCountMembers_3c2010(self->f18, 1, 1);
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x1F, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x1A6, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 1.0f, D_0047D610, -1.0f);
        obj = UiEntryListGetCurrentData_28ec60(D_00482364);
        *(s16 *)((u8 *)obj + 0x10) = D_00482F14;
        MenuCursorBobUpdate_355a70(obj, 0, 0, 0x40, 1);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    obj = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (r == 2) {
        D_00482F24 = 0;
        v = *(s16 *)((u8 *)obj + 0x10);
        D_00482F14 = v;
        if (self->fC->f26 == 1) {
            PartyMenuCursorSet_3c0710(self->f18, 5, v);
        }
        StateMachineSetState_28ede0(D_0048235C, 0x97, 0);
    } else if (r == 1 || PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0) {
        if (PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        }
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A6, 0.0f, D_0047D618, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x99, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0xC) != 0) {
        MenuCycleCharaSel_3537c0(obj, 1);
    }
    return 1;
}
