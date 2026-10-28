/* rgp:protos */
#define RGP_SELF_MenuInvGridSelectState_2af690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Win {
    u8 pad0[0x14];
    s16 m14;
    s16 m16;
} Win;

typedef struct Sel {
    u8 pad0[0x10];
    s16 m10;
    s16 m12;
} Sel;

typedef struct Scn {
    u8 pad0[0x26];
    s16 m26;
} Scn;

typedef struct Ctx {
    u8 pad0[0xC];
    Scn *mC;
    u8 pad10[0x8];
    s32 m18;
} Ctx;

typedef struct Menu {
    u8 pad0[0x14];
    s32 m14;
} Menu;

typedef struct Party {
    u8 pad0[0x10];
    s8 m10;
} Party;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D760;
extern s32 D_0048235C;
extern s32 D_00482360;
extern Menu *D_00482364;
extern Party *D_00482374;
extern s16 D_00482488;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;
extern u8 D_004B2570[];

s32 MenuInvGridSelectState_2af690(s32 arg0, s32 arg1) {
    s32 sp50[4] __attribute__((aligned(16)));
    Win *win;
    s32 n;
    s32 h;
    s32 res;
    Sel *sel;
    Ctx *ctx;
    s32 go;
    s32 who;

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 0, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 7, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D760, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D760, -1.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x70, 1, 1);
        win = ((Win *)UiEntryListFindByTag_28ea40(D_00482364, 7));
        if (win->m16 == 0) {
            win->m14 = 0;
            UiSetWidgetPos_290f60(D_00482360, 0x70, 0x115, 0x51);
        } else if (win->m16 == 1) {
            UiSetWidgetPos_290f60(D_00482360, 0x70, win->m14 * 100 + 0xE3, 0xA1);
        }
        ctx = ((Ctx *)GetGameData_1fede0());
        n = win->m14 + win->m16 - 1;
        if (n < 0) {
            n = 2;
        }
        h = ((s32)InvFindByCategoryIndex_3c86e0(ctx->m18, 3, 0, n, 0, 0));
        MenuItemInfoWidgetsCache_2a65f0(sp50);
        MenuItemInfoPopupShow_2a33e0(D_00482374, h, 0x1AA, 0x1A9, sp50, 0x68, 0x15E, -1, 2.0f);
    }
    res = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    sel = ((Sel *)UiEntryListGetCurrentData_28ec60(D_00482364));
    go = 0;
    if (res == 2) {
        if (D_00482488 != 0) {
            StateMachineSetState_28ede0(D_0048235C, 0xB1, 0);
        } else {
            D_004824A0 = sel->m10;
            D_004824A4 = sel->m12;
            D_004824A8 = 8;
            ctx = ((Ctx *)GetGameData_1fede0());
            if (ctx->mC->m26 == 1) {
                PartyMenuCursorSet_3c0710(ctx->m18, 0, D_004824A0);
                PartyMenuCursorSet_3c0710(ctx->m18, 1, D_004824A4);
                PartyMenuCursorSet_3c0710(ctx->m18, 2, D_004824A8);
            }
            StateMachineSetState_28ede0(D_0048235C, 0x19, 0);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 8) != 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 8) == 0) {
        who = 0;
        go = 1;
    } else if (PadIsTriggered_1839f0(D_004B2570, 4) != 0) {
        go = 1;
        who = D_00482374->m10 - 2;
    } else {
        if (D_00482364->m14 == 4) {
            PlayMenuSe_289ef0(4);
            win = ((Win *)UiEntryListFindByTag_28ea40(D_00482364, 6));
            win->m14 = 2;
            if (sel->m12 == 0) {
                win->m16 = 0;
            } else {
                win->m16 = 2;
            }
            UiSetWidgetsVisibleById_291110(D_00482360, 0x70, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x15, 0);
        } else if (D_00482364->m14 == 2) {
            PlayMenuSe_289ef0(4);
            win = ((Win *)UiEntryListFindByTag_28ea40(D_00482364, 8));
            if (sel->m10 == 0) {
                win->m14 = 4;
            } else {
                win->m14 = 7;
            }
            UiSetWidgetsVisibleById_291110(D_00482360, 0x70, 0, 1);
            StateMachineSetState_28ede0(D_0048235C, 0x1B, 0);
        }
    }
    if (go != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x70, 0, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 1, 1);
        MenuItemSelectTab_2b3550(who, 0, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
