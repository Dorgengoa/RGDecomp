/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellGridState_510860 1
#include "port/game_protos.h"
#line 1
/* ******* CLOSED s29 (2026-09-04) -- BYTE-IDENTICAL, 464 B, on ONE WORD.
 * The `return 1;` inside the `func_3D4360 && func_3D4420` arm became
 * `goto done;` (the `done: return 1;` label was already here from s25).
 * Mechanism: [[mwcc-branch-likely-duplication]] FIX 3 read backwards, the same
 * one that closed normal_ShopMenuSellItemStatusLayout_50ef80 in s28 -- mwcc threads only the FIRST
 * predecessor of a shared `return K` block, and an explicit `return 1` at an
 * EARLIER exit makes that exit its own block, stealing the threaded slot from
 * the site retail threads.
 * !! WHY s25's 11 ARMS MISSED IT: s25 swept the exit statement AT THE DEFECT
 * SITE (0x00510990, the normal_FUN_0050F650(1) fall-through) and recorded
 * `goto done` INERT.  The paying site is the OTHER one, three statements
 * earlier.  An N-exit unit is a per-site lattice, and a sweep that only
 * touches the site the residue points at has width 1
 * ([[mwcc-mixed-exit-statements]]).
 * Found by the s29 POOL-WIDE exit screen (build/wf-normal/s29/mkexit29.py):
 * one arm per `return K` site per unit across all 65 open drafted units,
 * 101 arms in one round trip.  Armed on normal_ShopMenuSellItemStatusLayout_50ef80 (base MATCH /
 * the goto reverted = 2 bad, distinct objects). */
#include "types.h"
/* normal 0x00510860 -- the 0x7534 confirm dialog's per-frame poll.  The second
 * parameter is the "opening" flag (retail's guard is `beqz $5`, so the unused
 * first parameter must still be declared); D_00484680 is a 0x3C-frame timeout
 * that fires normal_ShopMenuSellCellHintShow_50f650(1) exactly once on the frame it reaches 0x3C.
 * Answer 1 looks the picked cell's item up and accepts it only when BOTH
 * func_3D4360 and func_3D4420 pass -- one `&&`, which is what gives operand 1
 * the `beql` whose ANNULLED slot holds the else-block's `addiu $4,$0,1` and
 * operand 2 the plain `beqz` into a real one-instruction block
 * ([[normal-guard-pair-or]], read on the `&&` side).
 * Answer 2 compares a float against MAIN's pool entry at gp-0x7D00; the arm
 * that RUNS when the compare holds is the `else`, so the guard is spelled `>`.
 *
 * SESSION 25 PARK: RIGHT LENGTH, 2 bad, on the FIRST build.  The single
 * defect is ONE WORD at 0x00510990: after normal_FUN_0050F650(1) retail
 * jumps to the SHARED `addiu $2,$0,1` block (`b .L00510A18 / nop`, delay
 * slot EMPTY) and we branch-CHAIN past it to the epilogue with the 1
 * duplicated into the slot.  Same family as normal_FUN_0050C550's guard 3,
 * which closed on a `||` -- there is no adjacent guard to fold here.
 * MEASURED INERT, 11 arms: an explicit `return 1`, `goto done`, an `else`
 * block, `else` + `goto done`, two plain `if`s instead of `else if`, and a
 * `switch` with and without a trailing `break` (both 2 words LONG).
 * !! Reversing the arms to `if (r == 2) ... else if (r == 1)` is 70 BAD --
 * mwcc does NOT normalise this compare chain's order, which qualifies
 * normal_FUN_00509A80's note that it does.
 * build/wf-normal/s25/v_10860_exit.py / v_10860_sw.py.
 * KEEP OUT OF config/ocunits/normal.txt. */

typedef struct Rec { u8 pad00[0x10]; s16 f10; s16 f12; } Rec;
typedef struct Cfg { u8 pad00[0x11]; s8 f11; } Cfg;
typedef struct Ctx { u8 pad00[0x18]; void *f18; } Ctx;

extern void *D_004845C4;          /* gp - 0xBAC */
extern void *D_004845C8;          /* gp - 0xBA8 */
extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845D0;          /* gp - 0xBA0 */
extern Cfg  *D_004845D4;          /* gp - 0xB9C */
extern void *D_0048467C;          /* gp - 0xAF4 */
extern s32   D_00484680;          /* gp - 0xAF0 */
extern f32   D_0047D470;          /* gp - 0x7D00 */
extern f32   D_0047D4B4;          /* gp - 0x7CBC */
extern u8    D_004B2570[0x10];    /* main-image object; an ADDRESS, and the
                                     size keeps it out of small data */

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

s32 normal_ShopMenuSellGridState_510860(s32 unused, s32 opening)
{
    s32   r;
    Rec  *w;
    void *e;
    s32   t;

    if (opening != 0) {
        UiEntryListSelectByTag_28ea90(D_004845D0, 0x7534, 0);
        UiFadeWidgetAlpha_290690(D_004845C8, 0x40, 1.0f, D_0047D4B4, -1.0f);
        normal_ShopMenuSellCellHintShow_50f650(0);
        D_00484680 = 0;
    }
    r = MenuGridCursorInput_28e170(D_004845D0, D_004B2570, 6, 0);
    w = ((Rec *)UiEntryListGetCurrentData_28ec60(D_004845D0));
    t = D_00484680;
    if (t < 0x3C) {
        t += 1;
        D_00484680 = t;
        if (t == 0x3C) {
            normal_ShopMenuSellCellHintShow_50f650(1);
        }
    }
    if (r == 1) {
        e = InvFindByCategoryIndex_3c86e0(((Ctx *)GetGameData_1fede0())->f18, 0, D_004845D4->f11, w->f10, w->f12, 0);
        if (e == 0) {
            return 0;
        }
        if (ItemIsSellable_3d4360(e) != 0 && ItemIsUnheldFlaggedMaybe_3d4420(e) != 0) {
            D_0048467C = e;
            StateMachineSetState_28ede0(D_004845C4, 0x7545, 0);
            goto done;
        }
        normal_ShopMenuSellCellHintShow_50f650(1);
    } else if (r == 2) {
        if (UiGetWidgetAlpha_290770(D_004845CC, 0x57) > D_0047D470) {
            normal_ShopMenuSellCellHintShow_50f650(0);
            D_00484680 = -0x3C;
        } else {
            StateMachineSetState_28ede0(D_004845C4, 0x7544, 0);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x7E, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x7F, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x80, 0, 1);
        }
    }
done:
    return 1;
}
