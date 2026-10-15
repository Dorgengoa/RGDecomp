#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Q;

typedef struct {
    u8 pad0[4];
    u8 name[0x1C];
    Q *unk20;
} P;

typedef struct {
    u8 pad0[0x14];
    s16 unk14;
    s16 unk16;
    u8 pad18[2];
    s16 unk1A;
} T2;

extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void MenuGridCursorRequestSe_28e9e0(s32, s32);
extern T2 *UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern s32 UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern P *UiFindWidget_290460(s32, s32);
extern void UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuCycleCharaSel_3537c0(s32, s32);
extern void *strcpy(void *, void *);

extern u8 D_00462AB0[];
extern f32 D_0047D248;
extern f32 D_0047D288;
extern f32 D_0047D35C;
extern f32 D_0047D60C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_00482F14;
extern u8 D_004B2570[];

s32 MenuTacticsCmdSelectState_3546e0(s32 arg0, s32 arg1)
{
    T2 *t2;
    P *p;
    Q *q;
    s32 r;
    s32 h;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x21, 0);
        t2 = UiEntryListFindByTag_28ea40(D_00482364, 0x21);
        t2->unk14 = D_00482F14;
        t2->unk1A = 0;
        p = UiFindWidget_290460(D_00482360, 0xC6);
        if (p == NULL) {
            return 0;
        }
        q = p->unk20;
        if (q == NULL) {
            return 0;
        }
        q->unk4 = 0x164;
        q->unk6 = 0x16;
        q->unk8 = 0;
        q->unkA = 0;
        q->unkC = 0x80;
        q->unkE = 0x18;
        strcpy(p->name, D_00462AB0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0xC6, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0xC6, D_0047D248, D_0047D60C, -1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0xC6, 0x18, t2->unk16 * 0x15 + 0x12);
    }
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 2, 0);
    h = UiEntryListGetCurrentData_28ec60(D_00482364);
    if (r == 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x9B, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0) {
        MenuGridCursorRequestSe_28e9e0(D_00482364, 0);
        StateMachineSetState_28ede0(D_0048235C, 0x9B, 0);
    } else if (r == 1) {
        UiFadeWidgetColor_2904e0(D_00482360, 0xC6, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D288, D_0047D60C);
        StateMachineSetState_28ede0(D_0048235C, 0x9C, 0);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0xC) != 0) {
        MenuCycleCharaSel_3537c0(h, 0);
    }
    return 1;
}
