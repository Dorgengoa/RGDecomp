/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveConfirmState_4f6fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6FB0 (1,632 bytes, 408 instructions, 64 calls) -- the
 * two-or-three-way page selector: an optional rebuild pass guarded by the
 * second parameter, then func_28E100 asks which button was pressed and the
 * answer is dispatched onto the same page index.
 *
 * ALL FOUR DISPATCHES ARE if/else-if CHAINS, NOT switches.  Classifying every
 * conditional branch by its delay slot (build/im_ds.py): each converted `bnel`
 * carries THE NEXT GUARD'S CONSTANT (addiu $2, $0, 0x2 ahead of the == 2
 * test), never a case body's store.  So the cases run in SOURCE order, not the
 * reversed order a switch compare chain would need.  m2c renders three of them
 * as switch; every one of those is the right length and the wrong bytes.
 *
 * GUARD POLARITY: mwcc branches away to the else and falls through into the if
 * body, so each condition here is read off which block is the fall-through.
 * m2c inverts four of them (w->f14 != 0, D_00484370 == 0 twice, mode != 2) and
 * each inversion is invisible to the length guard.
 *
 * The FIRST parameter is never read.  There is no caller inside the overlay,
 * so its type and even its presence are unconstrained by anything measured --
 * only $5 is used, which fixes the flag as the second argument.
 */

typedef struct Widget Widget;
struct Widget {
    u8  pad00[4];
    u8  f04;                /* &w->f04 is what func_28ECD0 fills */
    u8  pad05[0xF];
    s16 f14;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

extern s16 D_00484364;      /* gp - 0xE0C: the page index */
extern u8  D_00484370;      /* gp - 0xE00 */
extern u8  D_00484360;      /* gp - 0xE10 */
extern s32 D_00481BBC;      /* gp - 0x35B4 */
extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern f32 D_0047D3C8;
extern f32 D_0047D460;
extern f32 D_0047D488;
extern f32 D_0047D49C;

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
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSaveConfirmState_4f6fb0(s32 arg0, s32 rebuild)
{
    s32 sp2C;
    s32 sp28;
    Widget *w;
    s32 mode;
    s32 hit;

    if (rebuild != 0) {
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x5F, 1, 1);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x5F, 1.0f);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x5F, 0x28, 0xBA);
        w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88C3));
        mode = D_00484364;
        if (mode == 0) {
            UiSetTextString_28f510(insmenu_D_004FA180, 0x61, MsgTableLookup_28aa30(insmenu_InsectVsGetMsgTable_4f3320(), 0x64A), 0);
            if (w != 0) {
                w->f14 = 0;
            }
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x7A, 0);
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x46, 1);
        } else if (mode == 1) {
            UiSetTextString_28f510(insmenu_D_004FA180, 0x61, MsgTableLookup_28aa30(insmenu_InsectVsGetMsgTable_4f3320(), 0x64B), 0);
            if (w != 0) {
                w->f14 = 1;
            }
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x7A, 1);
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x46, 0);
        } else if (mode == 2) {
            UiSetTextString_28f510(insmenu_D_004FA180, 0x61, MsgTableLookup_28aa30(insmenu_InsectVsGetMsgTable_4f3320(), 0x654), 0);
            if (w != 0) {
                w->f14 = 1;
            }
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x7A, 1);
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x61, 0x46, 0);
        }
        UiSetTextString_28f510(insmenu_D_004FA180, 0x61, MsgTableLookup_28aa30(D_00481BBC, 0x52), 1);
        UiSetTextString_28f510(insmenu_D_004FA180, 0x61, MsgTableLookup_28aa30(D_00481BBC, 0x53), 2);
        GetGridCellPosOffset_28ecd0(&w->f04, &sp2C, &sp28, 0, 0);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x62, sp2C, sp28);
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88C3, 0);
    }
    hit = MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, D_004B2570, D_004B27E0, 0);
    if (hit == 1) {
        w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88C3));
        if (w != 0) {
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x5F, 0, 1);
            mode = D_00484364;
            if (mode == 0) {
                if (w->f14 == 0) {
                    D_00484370 = 1;
                    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
                    UiEntryListResetRectByTag_28eb10(insmenu_D_004FA1A0, 0x88B9);
                    StateMachineSetState_28ede0(&D_004842E8, 0x88BE, 0);
                } else {
                    StateMachineSetState_28ede0(&D_004842E8, 0x88C4, 0);
                }
            } else if (mode == 1) {
                if (w->f14 == 0) {
                    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
                    if (D_00484360 != 0) {
                        InsectVsTeamInfoLayoutMaybe_379400(RecordGetNameSlot_430580(*(void **)((u8 *)GetGameData_1fede0() + 0x24), 0), 0);
                    }
                    D_00484360 = 0;
                    if (D_00484370 != 0) {
                        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BA, 0.0f, D_0047D3C8, -1.0f);
                        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88BA, 0xC8, 0, D_0047D460, 0);
                        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BC, 0.0f, D_0047D3C8, -1.0f);
                        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C1, -0x12, 0xC, D_0047D488, 0);
                        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C0, -0xF, 0xF, D_0047D488, 0);
                        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C1, 0.0f, D_0047D49C, -1.0f);
                        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C0, 0.0f, D_0047D49C, -1.0f);
                    }
                    StateMachineSetState_28ede0(&D_004842E8, 0x88C5, 0);
                } else if (D_00484370 != 0) {
                    UiEntryListResetRectByTag_28eb10(insmenu_D_004FA1A0, 0x88B9);
                    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88B9, 0);
                    StateMachineSetState_28ede0(&D_004842E8, 0x88BA, 0);
                } else {
                    StateMachineSetState_28ede0(&D_004842E8, 0x88C4, 0);
                }
            } else if (mode == 2) {
                if (w->f14 == 0) {
                    PlayMenuSeThunk_289ef0(6);
                    insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
                    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
                    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CAA, 0.0f, D_0047D3C8, 0.0f);
                    insmenu_InsectVsSaveHighlightOption_4f6bb0(-1);
                    StateMachineSetState_28ede0(&D_004842E8, 0x88C5, 0);
                } else {
                    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BD, 0);
                    StateMachineSetState_28ede0(&D_004842E8, 0x88C2, 0);
                }
            }
        }
    } else if (hit == 2) {
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x5F, 0, 1);
        mode = D_00484364;
        if (mode == 2) {
            UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BD, 0);
            StateMachineSetState_28ede0(&D_004842E8, 0x88C2, 0);
        } else if (D_00484370 != 0) {
            UiEntryListResetRectByTag_28eb10(insmenu_D_004FA1A0, 0x88B9);
            UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88B9, 0);
            StateMachineSetState_28ede0(&D_004842E8, 0x88BA, 0);
        } else {
            StateMachineSetState_28ede0(&D_004842E8, 0x88C4, 0);
        }
    }
    return 1;
}
