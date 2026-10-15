#include "types.h"

typedef struct {
    s32 p;
    s32 q;
    s32 pad[2];
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 x;
    s32 e;
    s32 f;
    s32 g;
    s16 h;
} Box;

extern void *GetGameData_1fede0(void);
extern void PlayMenuSe_289ef0(s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiWindowFitToText_28d0c0(Box *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern s32 UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(s32, s32, s32);
extern void UiSetSpriteW_28fbf0(s32, s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuMsgWindowSetSkin_295220(s32, s32);
extern void *memset(void *, s32, u32);
extern s16 D_00482340;
extern s32 D_00482350;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_004823A4;
extern s16 D_004823B0;
extern s32 D_004823D8;
extern u8 D_00482424;
extern u8 D_004B2570[];

s32 MenuNoticeMsgBoxState_294df0(s32 arg0, s32 arg1)
{
    Box bx;
    s32 g;
    s16 id;
    s32 n;
    s32 r;

    if (arg1 != 0) {
        g = (s32)GetGameData_1fede0();
        id = 0x1F40;
        if (D_004823B0 == 0x3EA) {
            id = 0x1F46;
        } else if (D_004823B0 == 0x3E9) {
            id = 0x1F43;
        } else if (D_004823B0 == 6 && !(*(u8 *)(*(s32 *)(g + 0x20) + 0x24C) & 1)) {
            MenuMsgWindowSetSkin_295220(0x21E, 0);
            id = 0x1F42;
        } else if (D_004823B0 == 0x3E7) {
            id = 0x1F45;
        } else if (D_004823B0 == 0x44C) {
            id = 0x44C;
        } else if (D_004823B0 == 0x4B0) {
            id = 0x4C3;
        }
        UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, id), 0);
        memset(&bx, 0, 0x34);
        bx.p = UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0);
        bx.q = UiGetWidgetText_28f620(D_00482360, 0x21E, 0);
        bx.a = 0x3C;
        bx.c = 0x1C;
        if (D_004823B0 == 0x3E7) {
            bx.b = 0x28;
            bx.d = 0x24;
            UiSetWidgetsVisibleById_291110(D_00482360, 0x221, 1, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x222, 1, 1);
            UiSetWidgetPos_290f60(D_00482360, 0x221, 4, -0x1F);
            UiSetWidgetPos_290f60(D_00482360, 0x222, 4, -0x1F);
            UiSetSpriteW_28fbf0(D_00482360, 0x222, 0x14C, 1);
            UiSetSpriteX_28fcd0(D_00482360, 0x222, 0x1C6, 2);
            UiSetTextString_28f510(D_00482360, 0x221, MsgTableLookup_28aa30(D_004823D8, 0x1F44), 0);
        } else {
            bx.b = 0xC;
            bx.d = 8;
        }
        n = 0;
        if (D_00482424 != 0) {
            n = 0x19;
        }
        bx.x = (s32)(98.0f + (f32)n);
        bx.e = 0x49;
        bx.f = 0x186;
        bx.g = 0x12C;
        bx.h = 4;
        UiWindowFitToText_28d0c0(&bx, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x21E, 1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    } else {
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 1, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    if ((u32)(r - 1) < 2) {
        g = (s32)GetGameData_1fede0();
        if (r == 2 && D_004823B0 == 6 && !(*(u8 *)(*(s32 *)(g + 0x20) + 0x24C) & 1)) {
            return 1;
        }
        PlayMenuSe_289ef0(5);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x222, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x221, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
        if (D_004823B0 == 0x4E20) {
            StateMachineSetState_28ede0(&D_00482350, 0xA4, 0);
            D_004823B0 = 4;
            return 1;
        }
        if (D_004823B0 >= 0x3E8) {
            StateMachineSetState_28ede0(&D_00482350, 0x12, 0);
        } else {
            if (D_004823B0 == 6 && !(*(u8 *)(*(s32 *)(g + 0x20) + 0x24C) & 1)) {
                MenuMsgWindowSetSkin_295220(0x21E, 1);
                D_004823A4 = 2;
                D_00482340 = 7;
            } else if (D_004823B0 == 0x3E7) {
                D_004823B0 = 6;
            }
            StateMachineSetState_28ede0(&D_00482350, 2, 0);
        }
    }
    }
    return 1;
}
