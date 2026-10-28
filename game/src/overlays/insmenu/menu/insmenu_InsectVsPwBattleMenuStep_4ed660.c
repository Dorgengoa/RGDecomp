/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPwBattleMenuStep_4ed660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EDA00 (492 bytes, 123 instructions, 19 calls) -- member of the
 * nine-function state-handler family; 0.943 mnemonic-similar to the matched
 * 0x004EC2A0, and written from it.
 *
 * Frame 0x50, so `0x60($29)` is caller+0x10 = argument 11 (mwcc's PS2 EABI
 * passes eight integer arguments in $4..$11 and the rest in eight-byte stack
 * slots from caller_sp+0).  Here argument 11 is the code itself; in 0x004EC2A0
 * the code is argument 10 and argument 11 is a separate pass-through.
 *
 * ★ `if (hit)` -- NOT `if (hit != 0)`.  A `u8` local tested with an explicit
 * `!= 0` makes mwcc re-normalise it with an `andi` at the READ; tested bare it
 * reads the register raw, which is what retail does.  One word, and it also
 * flips the guard above it from the LIKELY form to a plain branch plus `nop`
 * because the join loses its duplicable first instruction.
 *
 * The `mode == 1` arm RETURNS rather than falling through, so the join below
 * still has two predecessors and the branch stays plain.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern s32 insmenu_D_004F9990[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */

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

s32 insmenu_InsectVsPwBattleMenuStep_4ed660(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 p9, s32 p10, s32 code)
{
    Handle *hnd;
    s32 *slot;
    s32 mode;
    s16 idx;
    u8 hit;

    if ((insmenu_InsectVsTopPanelIsVisible_4f2ac0() != 0) || (insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0)) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsPwWatchPanelIsHidden_4f1000() != 0) {
            insmenu_InsectVsPwBattlePanelOpen_4f0fc0();
            insmenu_InsectVsBackGuideShow_4ea030();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsPwWatchPanelIsOpaque_4f1090() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsPwBattlePanelFocus_4f0bc0();
        D_00484304 = 0;
        return 1;
    }

    hnd = ((Handle *)GetGameData_1fede0());
    slot = ((s32 *)RecordGetPayloadIfKind28_430b50(hnd->field24));
    mode = MenuGridCursorInput_28e170(insmenu_D_004FA1A0, D_004B2570, 4, 0);
    idx = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0))->field12;
    if (idx >= 0) {
        if (idx < 3) {
            code = insmenu_D_004F9990[idx];
            *slot = code;
        }
    }
    hit = 0;
    if (mode == 1) {
        D_00484304 = 1;
        RecordSetStateClamped_430db0(hnd->field24, code, 0);
        insmenu_InsectVsPwWatchPanelFadeOut_4f10f0();
        return 1;
    }
    if (mode == 2) {
        hit = 1;
        code = 0x196;
    }
    if (hit) {
        insmenu_InsectVsPwWatchCursorFadeOut_4f0e20();
        insmenu_InsectVsPwWatchPanelDim_4f0f20();
        if (code == 0x190) {
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x22);
        }
        if (code == 0x196) {
            *slot = 0x196;
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x1A);
        }
    }
    return 1;
}
