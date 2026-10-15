#include "types.h"

typedef struct B3941c0 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    u8 pad20[0x14];
} B3941c0;

typedef struct C3941c0 {
    u8 pad0[0x18];
    s32 unk18;
} C3941c0;

extern void EventCondRefreshAllMaybe_1fe4f0(void);
extern C3941c0 *GetGameData_1fede0(void);
extern void StreamPlayMwv_207340(s32, s32, f32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiWindowFitToText_28d0c0(B3941c0 *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern void UiSetTextPos_28f5d0(void *, s32, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(void *, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(void *, s32, s32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void InvAddItemRepeat_3c47b0(s32, s32, s32, s32);
extern void memset(void *, s32, s32);
extern s32 D_00483470;
extern s32 D_0048347C;
extern u8 D_004B2570[];
extern u8 D_004E9550[];
extern u8 D_004E9570[];

s32 SeventhMysteryReward_3941c0(s32 pad0, s32 arg1)
{
    B3941c0 b;

    if (arg1 != 0) {
        UiSetTextPos_28f5d0(D_004E9550, 10, 0xAC, 0xC8, 0);
        UiSetTextString_28f510(D_004E9550, 10, MsgTableLookup_28aa30(D_0048347C, 0x390), 0);
        UiSetTextPos_28f5d0(D_004E9550, 10, 0x69, 0x28, 1);
        UiSetTextString_28f510(D_004E9550, 10, MsgTableLookup_28aa30(D_0048347C, 0x391), 1);
        memset(&b, 0, 0x34);
        b.w0 = UiGetWidgetSprite_28fe10(D_004E9550, 10, 0);
        b.w4 = UiGetWidgetText_28f620(D_004E9550, 10, 1);
        b.w10 = 0x50;
        b.w14 = 0x32;
        b.w18 = 0x28;
        b.w1C = 0x24;
        UiWindowFitToText_28d0c0(&b, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E9550, 10, 1, 1);
        UiSetWidgetPos_290f60(D_004E9550, 10, 0, 0);
        StreamPlayMwv_207340(0x321, 0, 1.0f);
    } else if ((u32)(MenuGridCursorInput_28e170(D_004E9570, D_004B2570, 0, 0) - 1) < 2) {
        InvAddItemRepeat_3c47b0(GetGameData_1fede0()->unk18, 0x410A, 0, 1);
        EventCondRefreshAllMaybe_1fe4f0();
        StateMachineSetState_28ede0(&D_00483470, 0x7539, 0);
    }
    return 1;
}
