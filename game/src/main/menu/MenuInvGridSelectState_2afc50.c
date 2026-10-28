/* rgp:protos */
#define RGP_SELF_MenuInvGridSelectState_2afc50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rec { u8 pad0[0x10]; s16 m10; s16 m12; s16 m14; s16 m16; } Rec;
typedef struct Mgr { u8 pad0[0x14]; s32 m14; } Mgr;
typedef struct Sel { u8 pad0[0x10]; s8 m10; } Sel;
typedef struct Hdr { u8 pad0[0x26]; s16 m26; } Hdr;
typedef struct Own { u8 pad0[0xC]; Hdr *mC; u8 pad10[8]; s32 m18; } Own;
typedef struct Box { s32 a, b, c, d; } Box;

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
/*rgp*/
/*rgp*/
extern f32 D_0047D760;
extern s32 D_0048235C;
extern s32 D_00482360;
extern Mgr *D_00482364;
extern Sel *D_00482374;
extern s16 D_00482488;
extern s16 D_004824A0;
extern s16 D_004824A4;
extern s16 D_004824A8;
extern u8 D_004B2570[0x40];
extern u8 D_004DB430[0x40];

s32 MenuInvGridSelectState_2afc50(s32 arg0, s32 arg1)
{
    s32 sp6C;
    s32 sp68;
    Box box __attribute__((aligned(16)));
    Rec *r;
    Own *own;
    Rec *p;
    s32 h;
    s32 st;
    s32 go;
    s32 sel;
    s32 v;

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0x78, 1, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 6, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D760, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D760, -1.0f);
        r = ((Rec *)UiEntryListFindByTag_28ea40(D_00482364, 6));
        GetGridCellPosOffset_28ecd0((u8 *)r + 4, &sp6C, &sp68, -0x25, -0x29);
        UiSelFrameSetRect_28db40(D_004DB430, 0x78, sp6C, sp68, 0x2A, 0x30, 0x62, 0x49);
        UiSelFrameCalcTileCounts_28d9d0(D_004DB430);
        h = ((s32)InvFindByCategoryIndex_3c86e0(((Own *)GetGameData_1fede0())->m18, 2, 0, r->m14, r->m16, 0));
        MenuItemInfoWidgetsCache_2a65f0(&box);
        MenuItemInfoPopupShow_2a33e0(D_00482374, h, 0x1AA, 0x1A9, &box, 0x68, 0x15E, -1, 2.0f);
    }
    st = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    r = ((Rec *)UiEntryListGetCurrentData_28ec60(D_00482364));
    go = 0;
    if (st == 2) {
        if (D_00482488 != 0) {
            StateMachineSetState_28ede0(D_0048235C, 0xB1, 0);
        } else {
            D_004824A0 = r->m10;
            D_004824A4 = r->m12;
            D_004824A8 = 6;
            own = ((Own *)GetGameData_1fede0());
            if (own->mC->m26 == 1) {
                h = own->m18;
                PartyMenuCursorSet_3c0710(h, 0, D_004824A0);
                h = own->m18;
                PartyMenuCursorSet_3c0710(h, 1, D_004824A4);
                PartyMenuCursorSet_3c0710(own->m18, 2, D_004824A8);
            }
            StateMachineSetState_28ede0(D_0048235C, 0x16, 0);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 8) != 0 && PadIsRepeatTriggered_183dd0(D_004B2570, 8) == 0) {
        sel = 0;
        go = 1;
    } else if (PadIsTriggered_1839f0(D_004B2570, 4) != 0) {
        go = 1;
        sel = D_00482374->m10 - 2;
    } else if (D_00482364->m14 == 2) {
        PlayMenuSe_289ef0(4);
        p = ((Rec *)UiEntryListFindByTag_28ea40(D_00482364, 8));
        p->m14 = r->m10;
        StateMachineSetState_28ede0(D_0048235C, 0x1B, 0);
    } else if (D_00482364->m14 == 8) {
        PlayMenuSe_289ef0(4);
        p = ((Rec *)UiEntryListFindByTag_28ea40(D_00482364, 7));
        p->m14 = 0;
        v = r->m12;
        p->m16 = v;
        if (v > 1) p->m16 = 1;
        StateMachineSetState_28ede0(D_0048235C, 0x18, 0);
    }
    if (go != 0) {
        MenuItemSelectTab_2b3550(sel, 0, 1);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
