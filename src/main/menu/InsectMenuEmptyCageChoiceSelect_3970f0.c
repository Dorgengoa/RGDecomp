#pragma opt_dead_assignments off
#include "types.h"

extern u8 *GetSelectedInsectEntryMaybe_206ad0(void);
extern void MsgFormat_28a9a0(s32, s32, void *, s32);
extern void MsgFormatParamsCtor_28aa00(void *);
extern void UiWindowFitToText_28d0c0(void *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern u8 *UiEntryListGetCurrentData_28ec60(void *);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiSetTextCenteredX_28f300(void *, s32, s32, s32);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern void UiSetWidgetVisible_290010(void *, s32, s32, s32);
extern void UiFadeWidgetColor_2904e0(void *, s32, f32, f32, f32, f32, f32);
extern void UiSetWidgetColor_2905b0(void *, s32, f32, f32, f32, f32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void UiWindowFitInit_398170(void *, s32);
extern s32 InsectMenuMsgLookup_398200(s32);

extern f32 D_0047D35C;
extern f32 D_0047DD2C;
extern u8 D_004834F0;
extern s32 D_00483530;
extern u8 D_004B2570[0x400];
extern u8 D_004E95C0[0x20];
extern u8 D_004E95E0[0x20];

s32 InsectMenuEmptyCageChoiceSelect_3970f0(s32 pad0, s32 arg1) {
    s32 b[0x2C];
    s32 a[0x10];
    u8 *p;
    s32 r;

    if (arg1 != 0) {
        p = GetSelectedInsectEntryMaybe_206ad0();
        if (p != NULL) {
            MsgFormatParamsCtor_28aa00(b);
            b[3] = *(s32 *)(p + 0x0);
            b[4] = *(s16 *)(*(u8 **)(*(u8 **)(p + 0x4) + 0x18) + 0x2);
            MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(0xB), b, 1);
            UiSetTextString_28f510(D_004E95C0, 0x7531, D_00483530, 0);
            UiSetWidgetPos_290f60(D_004E95C0, 0x7531, 0, 0xC);
            UiSetTextCenteredX_28f300(D_004E95C0, 0x7531, 0x100, 0);
        }
        UiSetTextString_28f510(D_004E95C0, 0x7534, InsectMenuMsgLookup_398200(1), 0);
        UiWindowFitInit_398170(a, 0x7534);
        a[4] = 0x3C;
        a[5] = 0xC;
        a[6] = 0x1C;
        a[7] = 8;
        a[10] = 0x200;
        a[11] = 0x104;
        UiWindowFitToText_28d0c0(a, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7534, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7532, 0);
    }
    r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    p = UiEntryListGetCurrentData_28ec60(D_004E95E0);
    if (r == 1) {
        if (*(s16 *)(p + 0x12) == 0) {
            UiSetWidgetVisible_290010(D_004E95C0, 0x7533, 0, -1);
            UiSetWidgetVisible_290010(D_004E95C0, 0x7532, 0, -1);
            UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7531, 0);
            StateMachineSetState_28ede0(&D_004834F0, 0x753A, 0);
        } else {
            UiSetWidgetColor_2905b0(D_004E95C0, 0x7532, D_0047D35C, D_0047D35C, D_0047D35C, -1.0f);
            UiFadeWidgetColor_2904e0(D_004E95C0, 0x7532, 1.0f, 1.0f, 1.0f, -1.0f, D_0047DD2C);
            StateMachineSetState_28ede0(&D_004834F0, 0x7538, 0);
        }
    } else if (r == 2) {
        StateMachineSetState_28ede0(&D_004834F0, 0x7537, 0);
    }
    return 1;
}
