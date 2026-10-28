/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuOpen_4f3120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F3120 (276 bytes, 72 instructions, 15 calls) -- bring the
 * insect-menu screen up: clear the seven gp state cells, allocate the screen
 * object and its three sub-allocations, then build the panel.
 *
 * ★ The opening `addiu $2, $0, 0x1` serves BOTH `sh` stores of 1 -- the one at
 * the top and the one in insmenu_InsectVsMenuResRequest_4f35e0's delay slot at the bottom.
 * mwcc shares the constant; writing either store's 1 as its own expression
 * costs nothing extra, but the STORE WIDTHS name the types: sh/sw/sb here are
 * s16 / s32 / u8 and nothing else fits.
 *
 * ★ `lui $6, 0x45 / addiu $6, $6, 0x5260` is `&D_00455260` -- an unsymbolised
 * main-image address taken by ADDRESS.  Written as a cast integer it would
 * compile to lui/ori instead.
 *
 * ★ The `beql $4, $0` at 0x004F31C0 carries `sw $4, -0x106C($28)` in its
 * LIKELY slot, which is the single store after an `if` that reassigns the
 * value -- mwcc duplicates the store into the taken arm.  Two separate stores
 * in the source would emit two.
 *
 * ★ Each `sw $2, <gp>` sits in the NEXT call's delay slot, so every result is
 * banked into its gp cell as its own statement before the following call.
 *
 * ⚠  * CLOSED (L3, 2026-08-26), 69/69 words byte-identical.  It needed TWO things
 * together, and every prior pass held one of them wrong:
 *
 *   1. the TWO-ARM `if` (`if (s != 0) { s = func_436950(); }` with ONE store
 *      after the join), not the early-return form.  That alone is 67 words --
 *      exactly retail's shape minus the two `daddu $4, $2, $0` copies.
 *   2. func_436930 TAKES THE SCREEN POINTER.  $4 still holds `s` at the
 *      `jal func_436930`, so the argument needs no setup -- and that is WHY the
 *      home register is $4 and why mwcc refuses to coalesce the call results
 *      into $2.  The copies are an ARGUMENT-REGISTER PRE-COLOUR, not a
 *      scheduler artefact.  Five prototype spellings (Screen*, void*, an (s32)
 *      cast, the global as the argument, a non-void return) give ONE identical
 *      object at bad = 0.
 *
 * !! Order matters: func_436930(s) on top of the EARLY-RETURN form scores 9.
 * !! RETRACTED, from this file's own previous header: "the early-return form is
 * the only one that buys the FIRST copy" is FALSE.  Measured on the relocated
 * object with build/im03_align.py, the early-return form buys NEITHER copy.
 * Measured null on the two-arm base: the full 117-pragma knob screen (113 of
 * 116 INERT, 3 live and all wrong length), optimization_level 1/2/3,
 * optimize_for_size, the global used as the variable (8 bad, right length), a
 * `register` qualifier, a `void *` staging local, an `else { s = 0; }` arm,
 * `!s`/truthy tests, declaration order, and an `s32` variable.
 *
 * SUPERSEDED PARK NOTE FOLLOWS.
 * PARKED ONE WORD SHORT (68 of 69).  The length guard catches this, so it is
 * safe out of the unit list rather than dangerous in it -- but it is out.
 * Retail copies each call result into a HOME REGISTER before using it
 * (`daddu $4, $2, $0` after both calls, then `sw $4, -0x106C` and a compare on
 * $4); we keep the value in $2 and save the copy.  SIXTEEN structural forms
 * were enumerated in scripts/i_f3120try.py -- the two-arm `if`, an early
 * return storing s / storing 0, a second variable for each arm, both
 * declaration orders, `!s` vs `== 0`, a `goto` join, the test read back off
 * the global, and the store hoisted above the first test.  The early-return
 * form (used here) is the only one that buys the FIRST copy; nothing buys the
 * second.
 * ⚠ And there is no recipe to copy: scripts/i_copyhome.py finds this shape at
 * exactly ONE site in 20,184 listings across main and all five overlays, and
 * it is this function.  ZERO matched units emit it, so the corpus cannot say
 * what source produces it.
 */

typedef struct Screen {
    u8 pad00[0xE6];
    s16 fE6;
} Screen;

extern s16 D_00480450;          /* gp - 0x4D20 */
extern Screen *D_00484104;      /* gp - 0x106C */
extern void *D_004842E0;        /* gp - 0xE90 */
extern void *D_004842F4;        /* gp - 0xE7C */
extern void *D_004842F8;        /* gp - 0xE78 */
extern s32 D_004842FC;          /* gp - 0xE74 */
extern s16 D_00484300;          /* gp - 0xE70 */
extern u8 D_00484304;           /* gp - 0xE6C */
extern s32 D_00484308;          /* gp - 0xE68 */
extern u8 D_0048430C;           /* gp - 0xE64 */
extern u8 D_00484310;           /* gp - 0xE60 */
extern u8 D_00455260[];
extern void *D_00484318;        /* gp - 0xE58 */

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

void insmenu_InsectVsMenuOpen_4f3120(void)
{
    void *m;
    Screen *s;

    D_00480450 = 1;
    D_004842FC = 0;
    D_00484300 = 0;
    D_00484304 = 0;
    D_00484308 = 0;
    D_0048430C = 0;
    D_00484310 = 0;
    D_004842E0 = GetMenuTransdataStack_206a60();
    MemStackReset_14d830(D_004842E0);
    m = GetMenuResGroup_206a40();
    ResGroupUnloadGroup_42b650(m, 1);
    ResGroupUnloadGroup_42b650(m, 3);
    D_004842F4 = MemStackNew_14e230(0x528, D_004842E0);
    D_004842F8 = MemStackNew_14e230(0x78, D_004842E0);
    D_00484318 = MemStackAllocQw_14d950(D_004842E0, 0x2000);
    s = (Screen *)MemStackNew_14e230(0x248, D_004842E0);
    if (s != 0) {
        s = ((Screen *)TextEntryCtor_436950((void *)(s)));
    }
    D_00484104 = s;
    if (s == 0) {
        return;
    }
    TextEntryReset_436930(s);
    TextEntryAllocParts_436860(D_00484104, D_004842E0, D_00455260);
    D_00484104->fE6 = 0;
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    D_00484300 = 1;
    D_00480450 = 1;
    insmenu_InsectVsMenuResRequest_4f35e0();
}
