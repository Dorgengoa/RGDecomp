/* rgp:protos */
#define RGP_SELF_MenuNoticeMsgPopupState_2a67c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Desc {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void *memset(void *, s32, u32);
extern f32 D_0047D770;
extern f32 D_0047D774;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_004823D8;
extern u8 D_004B2570[0x400];

s32 MenuNoticeMsgPopupState_2a67c0(s32 arg0, s32 arg1) {
    Desc d __attribute__((aligned(16)));

    GetGameData_1fede0();
    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 0, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D770, -1.0f);
        UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_004823D8, 0x3F0), 0);
        memset(&d, 0, 0x34);
        d.x0 = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0));
        d.x4 = ((s32)UiGetWidgetText_28f620(D_00482360, 0x21E, 0));
        d.x10 = 0x50;
        d.x14 = 0x10;
        d.x18 = 0x24;
        d.x18 += 0xE;
        d.x1C = 0xA;
        d.x20 = 0x62;
        d.x24 = 0x79;
        d.x28 = 0x186;
        d.x2C = 0x12C;
        d.x30 = 4;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    } else {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21F, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x21E, 1.0f);
        if ((u32)(MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0) - 1) < 2) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 1, 1);
            UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D774, -1.0f);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21F, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 9, 0);
        }
    }
    return 1;
}
