/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListStepCb_4f46b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off

/* insmenu 0x004F46B0 (2024 bytes, 506 instructions) -- the map screen
 * per-frame pad handler.  BYTE-IDENTICAL (lane L9, 2026-08-26).
 *
 * Four measured levers took this from 5 words LONG to MATCH:
 *
 * 1. #pragma opt_loop_invariants off.  Both `for (i = 0; i < 0x14; i++)`
 *    scans hoist the constant 1 of `found = 1;` into a register at loop
 *    entry (`li v1,1` + `move a2,v1`), which is ONE WORD LONG per loop.
 *    Retail rematerialises it inside the loop.  #pragma optimization_level 3
 *    produces the byte-identical object; removing both is 2 words long.
 *    NOT reachable from the local's TYPE -- s64/u64/u32 on `found` are all
 *    INERT (same object sha1) against the hoisting baseline.
 * 2. A 0/1 flag that retail materialises with `daddiu $x, $0, 0x1` is a
 *    `u8` local tested BARE (`if (flag)`), not an s32 tested `!= 0`.
 *    An s32 gives `addiu` and is one wrong word per site.  The pattern was
 *    read off insmenu_InsectVsTeamListTitleUpdate_4f5400, which is byte-identical, carries the
 *    same 0x193/0x1F6/0x1F7 chain and declares `u8 hit;`.  BOTH halves are
 *    needed: u8 alone breaks the length, the bare test alone is INERT.
 * 3. The callee's parameter must be u8 too -- `func_37B970(..., u8 c)`.
 *    With an s32 third parameter the u8 flag is widened at the call site.
 * 4. `if (func_2F6660() != 0) { return 1; }` compiles to beqzl + b + li,
 *    two words long; the whole remainder wrapped in `if (... == 0) { }`
 *    with ONE trailing `return 1;` gives retail's `bnel .. / addiu $2,$0,1`.
 *
 * Other structure that the listing pins:
 * - the three `info` fields are read into named locals so all three `lw`s
 *   batch before the compare chain and $4/$5 survive into func_37B970;
 * - `field10` is a BITFIELD byte (`dsll32 28 / dsrl32 31` is bit 3), the
 *   same declaration insmenu_InsectVsRegSavePanelLayout_4efd90 uses;
 * - the `D_00484354 != 0` and `ok` tests have the SHORT arm as the else --
 *   retail's `beql` targets the insmenu_InsectVsTeamListConfirm_4f4f00 call, so that call is
 *   the else block and the scan loop is the fall-through.
 *
 * No .lit4 and no .rodata: objdump -h shows .text 0x7e8 alone, so this unit
 * needs no link plumbing and is admissible to config/ocunits/insmenu.txt as
 * soon as whoever owns that file wants it. */

typedef struct Rec Rec;
struct Rec {
    u8 pad00[0x10];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 pad11[0xCF];
};

typedef struct Info Info;
struct Info {
    s32 field0;
    s32 field4;
    s32 field8;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad00[8];
    Rec  field08[0x14];
    Info *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    Ctx *field24;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0xA];
    s16 fieldA;
    u8  padC[2];
    s16 fieldE;
    u8  pad10[2];
    s16 field12;
    u8  pad14[2];
    s16 field16;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];
extern s32 insmenu_D_004FA1B4[4];
extern s32 insmenu_D_004FA1BC[4];

extern u8  D_00484354;      /* gp - 0xE1C */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern s16 D_00484364;      /* gp - 0xE0C */
extern s16 D_0048436C;      /* gp - 0xE04 */
extern f32 D_0047D3BC;

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
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamListStepCb_4f46b0(Panel *p, s32 a1)
{
    Handle *h;
    Info *info;
    Ctx *c;
    Rec *base;
    Widget *w;
    s32 va;
    s32 vb;
    s32 vc;
    s32 id;
    s32 mode;
    u8 flag;
    s32 hit;
    s32 n;
    u8 found;
    s32 i;
    u8 ok;
    s16 v;
    s16 e;

    insmenu_InsectVsLoadSlotCursorBob_4f6810(p, a1, 0);
    info = ((Handle *)GetGameData_1fede0())->field24->field1188;
    va = info->field0;
    vb = info->field4;
    vc = info->field8;
    flag = 1;
    if (va == 6 && vb == 0x3E && vc == 0x26F) {
        flag = 0;
    }
    if (flag) {
        mode = ((short)SaveGetResultStatus_37b970());
        if ((SavePortCardIsReady_37b9b0(1) & 0xFF) == 0 || mode == 6 || mode == 5 || mode == 8) {
            insmenu_InsectVsSaveSetError_4f6e20(8);
            return 1;
        }
    }
    hit = 0;
    if (GetPauseStep_2f6660() == 0) {
    if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0 ||
        (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x2000) != 0)) {
        hit = ((unsigned char)SaveSlotListPageScrollMaybe_37b500(p, 1));
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0 ||
               (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x8000) != 0)) {
        hit = ((unsigned char)SaveSlotListPageScrollMaybe_37b500(p, 0));
    } else if ((insmenu_D_004FA1B4[0] & 1) &&
               ((PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0 &&
                 PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000) == 0) ||
                (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x1000) != 0 &&
                 PadIsRepeatTriggered_183dd0(D_004B27E0, 0x1000) == 0))) {
        if (p->field12 == 0 && p->field16 == 0 && p->fieldE > 0) {
            hit = 1;
            p->field12 = p->fieldA;
            p->field16 = p->fieldE - p->fieldA;
        }
    } else if ((insmenu_D_004FA1B4[0] & 2) &&
               ((PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0 &&
                 PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000) == 0) ||
                (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x4000) != 0 &&
                 PadIsRepeatTriggered_183dd0(D_004B27E0, 0x4000) == 0))) {
        v = p->fieldA;
        if (p->field12 == v) {
            e = p->fieldE;
            if (p->field16 == e - v && e > 0) {
                p->field12 = 0;
                hit = 1;
                p->field16 = 0;
            }
        }
    }
    if (hit != 0) {
        if ((insmenu_D_004FA1BC[0] & 1) == 0) {
            MenuGridCursorRequestSe_28e9e0(insmenu_D_004FA1A0, 0);
        }
        insmenu_InsectVsTeamListMoveCb_4f5050(p);
        SaveUiScrollBarThumbPlace_3777a0(p, 0x890C, 0);
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 ||
        (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x40) != 0)) {
        h = ((Handle *)GetGameData_1fede0());
        id = h->field24->field1188->field8;
        if (id == 0x278) {
            D_00484354 = 0;
            h = ((Handle *)GetGameData_1fede0());
            w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88BD));
            n = 0;
            if (w != 0) {
                n = w->field1A + w->field16;
            }
            base = h->field24->field08;
            if (base != 0) {
                if (base[n].bit0 == 0 || base[n].bit3 != 0) {
                    D_00484354 = 1;
                }
            }
            if (D_00484354 != 0) {
                base = h->field24->field08;
                if (base != 0) {
                    found = 0;
                    for (i = 0; i < 0x14; i++) {
                        if (base[i].bit3 != 0) {
                            found = 1;
                        }
                    }
                    if (found) {
                        insmenu_InsectVsTeamListConfirm_4f4f00(p);
                    }
                }
            } else {
                insmenu_InsectVsTeamListConfirm_4f4f00(p);
            }
        } else if (id == 0x26F) {
            base = ((Rec *)insmenu_InsectVsTeamListGetSelRec_4f93b0());
            if (base != 0) {
                if (base->bit0 && base->bit3 == 0) {
                    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88C0, 0);
                }
            }
        } else if (id != 0x25A && id != 0x264 && id != 0x26F) {
            ok = 0;
            if (D_0048436C == 2) {
                if (id == 0x193) {
                    ok = 1;
                } else if (id == 0x1F6) {
                    ok = 1;
                } else if (id == 0x1F7) {
                    ok = 1;
                }
            }
            if (ok) {
                w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88BD));
                n = 0;
                if (w != 0) {
                    n = w->field1A + w->field16;
                }
                base = h->field24->field08;
                if (base != 0) {
                    if (base[n].bit0) {
                        insmenu_InsectVsTeamListConfirm_4f4f00(p);
                    }
                }
            } else {
                insmenu_InsectVsTeamListConfirm_4f4f00(p);
            }
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x20) != 0 ||
               (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x20) != 0)) {
        c = ((Handle *)GetGameData_1fede0())->field24;
        id = c->field1188->field8;
        if (id == 0x26F) {
            PlayMenuSeThunk_289ef0(6);
            insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
            UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CAA, 0.0f, D_0047D3BC, 0.0f);
            insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
            SaveUiHideWidget_37b460(0x890D);
            StateMachineSetState_28ede0(&D_004842E8, 0x88BB, 0);
        } else if (id == 0x278) {
            base = c->field08;
            if (base != 0) {
                found = 0;
                for (i = 0; i < 0x14; i++) {
                    if (base[i].bit3 != 0) {
                        found = 1;
                    }
                }
                if (!found) {
                    insmenu_InsectVsTeamListCancel_4f4ea0();
                } else {
                    SaveUiHideWidget_37b460(0x890D);
                    D_00484364 = 2;
                    StateMachineSetState_28ede0(&D_004842E8, 0x88CC, 0);
                }
            }
        } else {
            insmenu_InsectVsTeamListCancel_4f4ea0();
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0 ||
               (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x10) != 0)) {
        base = ((Rec *)insmenu_InsectVsTeamListGetSelRec_4f93b0());
        if (base != 0) {
            if (base->bit0 && base->bit3 == 0) {
                UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88C0, 0);
            }
        }
    }
    }
    return 1;
}
