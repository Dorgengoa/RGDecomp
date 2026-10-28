/* rgp:protos */
#define RGP_SELF_LeaderSwitchTooFarState_39c150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

typedef struct Item { s16 m0; u8 pad2[2]; s32 m4; } Item;
typedef struct Desc {
    Item *m30;
    Item *m34;
    u8 pad38[8];
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    s32 m50;
    s32 m54;
    s32 m58;
    s32 m5C;
    s16 m60;
    u8 pad62[2];
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
extern void *memset(void *, s32, s32);
extern f32 D_0047FFB0;
extern s32 D_00483600;
extern u8 D_004B2570[];
extern u8 D_004E9610[];
extern u8 D_004E9630[];

s32 LeaderSwitchTooFarState_39c150(s32 arg0, s32 arg1)
{
    Desc d __attribute__((aligned(16)));
    s32 id;
    f32 f;
    Item *it;
    Item *it2;
    s32 x;
    s32 y;
    s32 r;

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_004E9610, 3, 0, 1);
        memset(&d, 0, 0x34);
        d.m30 = ((Item *)UiGetWidgetSprite_28fe10(D_004E9610, 5, 0));
        d.m34 = ((Item *)UiGetWidgetText_28f620(D_004E9610, 5, 0));
        d.m40 = 0x3C;
        d.m48 = 0x1C;
        d.m50 = 0;
        d.m44 = 0x28;
        d.m54 = 0;
        d.m4C = 0x24;
        d.m58 = 0x200;
        d.m5C = 0x1C0;
        d.m60 = 4;
        it = ((Item *)UiGetWidgetText_28f620(D_004E9610, 6, 0));
        ZERO(&id, 4);
        id = it->m4;
        f = D_0047FFB0;
        UiWindowFitToText_28d0c0(&d, &id, 1, (f32 *)(u32)&f);
        it = ((Item *)UiGetWidgetSprite_28fe10(D_004E9610, 5, 5));
        it2 = ((Item *)UiGetWidgetSprite_28fe10(D_004E9610, 5, 0xA));
        x = it->m0 + 0x10;
        y = it2->m0 - 0x10;
        UiSetSpriteX_28fcd0(D_004E9610, 6, x + 0xA, 0);
        UiSetTextX_28f590(D_004E9610, 6, x + 0x26, 0);
        UiSetSpriteX_28fcd0(D_004E9610, 7, x, 0);
        UiSetSpriteX_28fcd0(D_004E9610, 7, x + 0xA, 1);
        UiSetSpriteW_28fbf0(D_004E9610, 7, y - (x + 9), 1);
        UiSetSpriteX_28fcd0(D_004E9610, 7, y, 2);
        UiSetWidgetsVisibleById_291110(D_004E9610, 5, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004E9610, 6, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004E9610, 7, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004E9630, 0x714A, 0);
        MenuGridCursorInput_28e170(D_004E9630, D_004B2570, 0, 0);
    } else {
        r = MenuGridCursorInput_28e170(D_004E9630, D_004B2570, 0, 0);
        UiEntryListGetCurrentData_28ec60(D_004E9630);
        if ((u32)(r - 1) < 2U) {
            UiSetWidgetsVisibleById_291110(D_004E9610, 7, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 6, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 5, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 3, 1, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 2, 1, 1);
            UiSetWidgetsVisibleById_291110(D_004E9610, 1, 1, 1);
            StateMachineSetState_28ede0(&D_00483600, 0x714A, 1);
        }
    }
    return 1;
}
