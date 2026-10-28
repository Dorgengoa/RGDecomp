/* rgp:protos */
#define RGP_SELF_TransMenuItemMsgPopupState_37be30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s16 unk30;
} Buf0037BE30;

typedef struct {
    u8 pad0[0x100];
} Templ004B2570;

/*rgp*/             /* extern */
/*rgp*/    /* extern */
/*rgp*/                      /* extern */
/*rgp*/   /* extern */
/*rgp*/                   /* extern */
/*rgp*/                   /* extern */
/*rgp*/                    /* extern */
/*rgp*/                    /* extern */
/*rgp*/                   /* extern */
/*rgp*/              /* extern */
void memset(void *, s32, s32);                      /* extern */
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern Templ004B2570 D_004B2570;
extern s32 D_004E9230[0x100];

s32 TransMenuItemMsgPopupState_37be30(s32 arg0, s32 arg1) {
    Buf0037BE30 sp10 __attribute__((aligned(16)));
    s32 temp_2;

    if (arg1 != 0) {
        memset(&sp10, 0, 0x34);
        sp10.unk0 = ((s32)UiGetWidgetSprite_28fe10(D_00484710, 0x764E, 0));
        sp10.unk4 = ((s32)UiGetWidgetText_28f620(D_00484710, 0x764E, 0));
        sp10.unk10 = 0x3C;
        sp10.unk14 = 0xC;
        sp10.unk18 = 0x1C;
        sp10.unk1C = 8;
        sp10.unk20 = 0x62;
        sp10.unk24 = 0x49;
        sp10.unk28 = 0x186;
        sp10.unk2C = 0x12C;
        sp10.unk30 = 4;
        UiWindowFitToText_28d0c0(&sp10, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x764E, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00484710, 0x764E, 1.0f);
        UiEntryListSelectByTag_28ea90(D_00484720, 0xF, 0);
    } else {
        temp_2 = MenuGridCursorInput_28e170(D_00484720, &D_004B2570, 0, 0);
        if ((temp_2 == 1) || (temp_2 == 2) || (PadIsTriggered_1839f0(&D_004B2570, 0x10) != 0) || (PadIsTriggered_1839f0(&D_004B2570, 0x80) != 0)) {
            UiSetWidgetsVisibleById_291110(D_00484710, 0x764E, 0, 1);
            StateMachineSetState_28ede0(D_0048470C, 0x37, 0);
        }
    }
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
