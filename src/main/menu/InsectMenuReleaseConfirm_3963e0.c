#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    u16 f30;
    u8 pad32[0xE];
} S20;

typedef struct {
    u8 pad0[0xC];
    s32 fC;
    u8 pad10[0xA0];
} S60;

extern s32 *GetSelectedInsectEntryMaybe_206ad0(void);
extern void MsgFormat_28a9a0(s32, s32, void *, s32);
extern void MsgFormatParamsCtor_28aa00(void *);
extern void UiWindowFitToText_28d0c0(void *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern void UiEntryListGetCurrentData_28ec60(void *);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiSetTextCenteredX_28f300(void *, s32, s32, s32);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void SelectedInsectEntryClearMaybe_397e80(void);
extern void UiWindowFitInit_398170(void *, s32);
extern s32 InsectMenuMsgLookup_398200(s32);
extern void CageRecClearCatch_3d0960(s32);
extern void CageRecUnplace_3d0a70(s32);

extern f32 D_004504F0[][2];
extern f32 D_004504F4[][2];
extern f32 D_0047DADC;
extern s32 D_0047FF48;
extern u8 D_004834F0;
extern f32 D_00483520;
extern f32 D_00483524;
extern s32 D_00483530;
extern s32 D_00483534;
extern s32 D_00483560;
extern u8 D_004B2570[];
extern u8 D_004E95C0[];
extern u8 D_004E95E0[];

s32 InsectMenuReleaseConfirm_3963e0(s32 arg0, s32 arg1) {
    S60 sp60;
    S20 sp20;
    s32 *p;
    s32 r;
    s32 k;

    if (arg1 != 0) {
        if (GetSelectedInsectEntryMaybe_206ad0() == 0) {
            return 0;
        }
        MsgFormatParamsCtor_28aa00(&sp60);
        sp60.fC = *GetSelectedInsectEntryMaybe_206ad0();
        MsgFormat_28a9a0(D_00483534, InsectMenuMsgLookup_398200(0xC), &sp60, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483534, 0);
        UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
        UiSetTextCenteredX_28f300(D_004E95C0, 0x7531, 0x100, 0);
        sp60.fC = D_0047FF48;
        MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(7), &sp60, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7534, D_00483530, 0);
        UiWindowFitInit_398170(&sp20, 0x7534);
        sp20.f14 = 0xC;
        sp20.f18 = 0x58;
        sp20.f1C = 8;
        sp20.f28 = 0x200;
        sp20.f2C = 0x1C0;
        sp20.f10 = 0x11D;
        sp20.f20 = 0xD;
        sp20.f30 |= 8;
        UiWindowFitToText_28d0c0(&sp20, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7534, 1, 1);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7534, 1.0f, D_0047DADC, 0.0f);
        k = 0x7B3;
        D_00483520 = (f32)k + D_004504F0[D_00483560][0];
        D_00483524 = 2064.0f + D_004504F4[D_00483560][0];
    }
    r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004E95E0);
    if (r == 1) {
        p = GetSelectedInsectEntryMaybe_206ad0();
        if (p == 0) {
            return 0;
        }
        CageRecUnplace_3d0a70(p[1]);
        CageRecClearCatch_3d0960(p[1]);
        SelectedInsectEntryClearMaybe_397e80();
        StateMachineSetState_28ede0(&D_004834F0, 0x7537, 0);
    }
    return 1;
}
