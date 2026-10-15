#include "types.h"

typedef struct Info {
    s32 f0;
    s32 f4;
    u8 pad8[8];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s16 f30;
    s16 f32;
} Info;

typedef struct Ctx {
    u8 pad0[0x7A4];
    s16 f7A4;
    u8 pad7A6[2];
    s32 f7A8;
} Ctx;

extern s32 GetGameData_1fede0(void);
extern void PlayMenuSe_289ef0(s32);
extern s32 MsgTableLookup_28aa30(s32, s16);
extern void UiWindowFitToText_28d0c0(Info *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuMsgWindowSetSkin_295220(s32, s32);
extern void MenuItemHideWidgets_2a5a60(s32);
extern void RevelationBoardBeginPlace_3498d0(Ctx *, s32);
extern void RevelationBoardSetPlaceCell_34cdf0(Ctx *, s32);
extern void *memset(void *, s32, s32);
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;
extern Ctx *D_0048238C;
extern s32 D_004823D8;
extern s16 D_00482E20;
extern s16 D_00482E2C;
extern u8 D_004B2570[];

s32 RevelationPlaceResultMsg_346280(s32 pad, s32 arg1)
{
    Info info;
    s32 id;
    s32 r;
    s32 n;
    f32 fv;

    if (arg1 != 0) {
        GetGameData_1fede0();
        id = 0x1004;
        if (D_0048238C->f7A4 == -2) {
            id = 0xFA0;
        }
        MenuMsgWindowSetSkin_295220(0x21E, 0);
        UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, id), 0);
        memset(&info, 0, 0x34);
        info.f0 = UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0);
        info.f4 = UiGetWidgetText_28f620(D_00482360, 0x21E, 0);
        info.f10 = 60;
        info.f18 = 28;
        info.f14 = 12;
        info.f1C = 8;
        fv = 98.0f;
        info.f20 = fv;
        info.f24 = 0x49;
        info.f28 = 0x186;
        info.f2C = 300;
        info.f30 = 4;
        UiWindowFitToText_28d0c0(&info, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x21E, 1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    } else {
    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 1, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    if (r == 1 || r == 2) {
        PlayMenuSe_289ef0(5);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
        MenuMsgWindowSetSkin_295220(0x21E, 1);
        if (D_0048238C->f7A4 == -2) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0xB5, 0, 1);
            UiSetWidgetVisible_290010(D_00482360, 0x65, 0, -1);
            UiSetWidgetVisible_290010(D_00482360, 0x7E, 0, -1);
            UiSetWidgetVisible_290010(D_00482360, 0x8A, 0, -1);
            MenuItemHideWidgets_2a5a60(D_00482374);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x227, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x8A, 0);
        } else {
            n = 2;
            if (D_0048238C->f7A4 == 3) {
                n = 1;
            }
            RevelationBoardBeginPlace_3498d0(D_0048238C, n);
            if (n == 1 || n == 2) {
                RevelationBoardSetPlaceCell_34cdf0(D_0048238C, D_0048238C->f7A8);
                D_00482E20 = 1;
                if (n == 2) {
                    D_00482E20 = 2;
                }
                D_00482E2C = 0;
                StateMachineSetState_28ede0(D_0048235C, 0x8E, 0);
            }
        }
    }
    }
    return 1;
}
