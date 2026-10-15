#include "types.h"
//PRAGMA

typedef struct {
    s32 a0;
    s32 a4;
    s32 a8;
    s32 aC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s16 x30;
} Desc;

extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiWindowFitToText_28d0c0(Desc *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, u16, s32);
extern void UiSetTextString_28f510(s32, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(s32, s32, s32);
extern void UiSetSpriteW_28fbf0(s32, s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void *memset(void *, s32, u32);
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u16 D_00482554;
extern s16 D_0048255C;
extern u8 D_004B2570[];

s32 MenuPartyPageMsgBoxState_2b3f80(s32 arg0, s32 arg1)
{
    Desc d;
    s32 x;

    if (arg1 != 0) {
        memset(&d, 0, sizeof(Desc));
        d.a0 = UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0);
        d.a4 = UiGetWidgetText_28f620(D_00482360, 0x21E, 0);
        d.x10 = 0x3C;
        d.x18 = 0x1C;
        if (D_0048255C == 2) {
            d.x14 = 0x28;
            d.x1C = 0x24;
            UiSetWidgetsVisibleById_291110(D_00482360, 0x221, 1, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x222, 1, 1);
            UiSetWidgetPos_290f60(D_00482360, 0x221, -0x1E, 0);
            UiSetWidgetPos_290f60(D_00482360, 0x222, -0x1E, 0);
            UiSetSpriteW_28fbf0(D_00482360, 0x222, 0x14A, 1);
            UiSetSpriteX_28fcd0(D_00482360, 0x222, 0x1C4, 2);
            UiSetTextString_28f510(D_00482360, 0x221, MsgTableLookup_28aa30(D_00481BBC, 0x48), 0);
        } else {
            d.x14 = 0xC;
            d.x1C = 8;
        }
        x = 0;
        if (D_0048255C == 1) {
            x = -0x6E;
        }
        d.x20 = 0x42;
        d.x24 = x + 0x42;
        d.x28 = 0x1B1;
        d.x2C = 0x176;
        d.x30 = 4;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x21E, 1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    } else if ((u32)(MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0) - 1) < 2U) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x222, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x221, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
        StateMachineSetState_28ede0(D_0048235C, D_00482554, 0);
    }
    return 1;
}
