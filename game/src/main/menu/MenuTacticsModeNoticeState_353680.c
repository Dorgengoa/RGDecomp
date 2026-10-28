/* rgp:protos */
#define RGP_SELF_MenuTacticsModeNoticeState_353680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Desc {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s16 f30;
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
extern void memset(void *arg0, s32 arg1, s32 arg2);
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern u8 D_004B2570[];

s32 MenuTacticsModeNoticeState_353680(s32 pad0, s32 arg1)
{
    Desc d __attribute__((aligned(16)));

    if (arg1 != 0) {
        memset(&d, 0, 0x34);
        d.f0 = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x21E, 0));
        d.f4 = ((s32)UiGetWidgetText_28f620(D_00482360, 0x21E, 0));
        d.f10 = 0x3C;
        d.f14 = 0xC;
        d.f18 = 0x1C;
        d.f1c = 8;
        d.f20 = 0x42;
        d.f24 = 0x42;
        d.f28 = 0x1B1;
        d.f2c = 0x118;
        d.f30 = 4;
        UiWindowFitToText_28d0c0(&d, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x21E, 1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    } else {
        if ((u32)(MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0) - 1) < 2U) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x21E, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x9A, 0);
        }
    }
    return 1;
}
