/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndItemRowsCascade_4ea700 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* === SESSION 43 (2026-09-07, SOLO): 45 bad -> MATCH.  FOUR EDITS, and the
 * ORDER they were found in is the method -- each one changed the coat and the
 * next one only becomes visible afterwards.
 * FOUND BY: build/wf-normal/s43/opscan.py said `addu:5->4  daddu:3->4`, i.e.
 * ONE of our daddu should be an addu -- a TYPE fact, not a colouring one.
 *  1. DECLARATION ORDER `i, r, y` (i FIRST).  45 -> 34.  The unit's own header
 *     named "declaration-order permutations of (r, i, y)" as the next arm and
 *     it was right: three of the six orders give 34, three give 45.
 *  2. TWO SPELLINGS OF ONE ADDRESS ([[levers.d/insect-cse-two-spellings]],
 *     [[levers.d/mwcc-index-cast-defeats-cse]]).  Retail RECOMPUTES the row
 *     base for the store block -- `sll $3,$18,4 / addu $7,$19,$3` at
 *     0x004EA7EC -- and stores through $7 while $16 still holds the copy the
 *     `r->fB4 >= 5.0f` test used.  A second local `N *w` spelled with a
 *     `(u32)i` INDEX CAST breaks the CSE; the same expression WITHOUT the cast,
 *     `i << 4` and `16 * i` are all byte-identical to having no second local.
 *  3. `s16 *pc = &r->fC8;` -- the out-parameter named
 *     ([[levers.d/insect-outparam-named-copy]]).  ⚠⚠ THREE THINGS ABOUT IT:
 *     - alone it is ONE WORD SHORT; edit 2 alone is ONE WORD LONG.  They are a
 *       CROSS ([[levers.d/two-edit-cross-beats-count-ranking]]): 34 -> 15.
 *     - it must be derived from `r` (the FIRST spelling), not from `w`: retail
 *       emits `addiu $8,$16,0xC8`.  From `w` it is 15, from `r` 13.
 *     - it must be HOISTED ABOVE the `if`, with the guard reading `*pc`:
 *       13 -> 4.  Declared inside the block mwcc folds `*pc = 1` back to
 *       `sh $4,0xC8($16)` and materialises $8 only for the call; declared
 *       above, $8 lands in the branch's DELAY SLOT, which is retail's.
 *       `if (r->fC8 == 0)` with pc hoisted gives the SAME object as `if (*pc == 0)`.
 *  4. `y = (i + 1) * 42;` written BEFORE the row-address assignment (so `w`
 *     becomes a bare declaration + a statement).  4 -> MATCH.  Retail emits
 *     `sll $4,$5,3` (the y chain) before `sll $3,$18,4` (the row address);
 *     source order is the whole lever.  Three spellings of it all MATCH.
 * ⚠ The header below's "MEASURED NULL: hoisting `r = ...` to the top of the
 * loop body -- REGRESSION 45 -> 58" still binds; that is a different edit. */
/* normal 0x004EA700 -- walks the four normal_D_00527000 slots; a slot that is live
 * (>0, or the sentinel -0xFF) shows its icon, and once its bar has run past
 * 5.0 the follow-up label is placed and latched at +0xC8.
 *
 * SESSION 39 (n39b): length-wrong(+2 words) -> exact 98/98 words.  Two
 * defects, both read straight off the retail addressing:
 *  1. func_1B9520 really does take SIX arguments here.  ⚠ THE MERGED-SIGNATURE
 *     ORACLE IS WRONG ON THIS CALLEE: 26 merged declarations across the corpus
 *     say FOUR, (h, s32, s32, f32), and they are all byte-identical -- but at
 *     THIS call site retail leaves $7 = the row pointer and $8 = &row->fC8
 *     live into the `jal`, set up at 0x004EA7E4/0x004EA7F4 and clobbered by
 *     nothing in between.  MEASURED, not argued: with the 0x10 stride below,
 *     the FOUR-arg form is 2 words SHORT (0x180 vs 0x188) and the SIX-arg form
 *     is EXACT.  A merged caller that passes 4 proves only that ITS path needs
 *     4 -- the oracle bounds arity from BELOW, never from above.
 *  2. The per-slot record stride is 0x10, not 0x18: retail computes the row
 *     base as `sll $4,$18,4 / addu $16,$19,$4` (p + 16*i) and then uses
 *     ABSOLUTE displacements 0xB4/0xBC/0xC0/0xC4/0xC8 off it.  The rows
 *     therefore OVERLAP (row i's 0xC4 is row i+1's 0xB4), so no plain
 *     `Row rows[4]` member can spell it -- a 0x16-byte struct pads to 0x18.
 *     Spelled here as a cast of the parent type at a 16-byte stride, which
 *     is what reproduces retail's displacements exactly.  This also moves
 *     `f104` back to 0x104; the old 0x18 stride had pushed it to 0x124.
 *
 * RESIDUE, 45 bad at exact length: a three-way CALLEE-SAVED PERMUTATION and
 * nothing else -- retail colours (r,e,i) = ($16,$17,$18) where r is the row
 * pointer, e = &normal_D_00527000[i], i the loop counter; ours colours them
 * ($18,$16,$17).  p is $19 in both.  Every remaining bad word is one of those
 * three registers substituted, plus the resulting schedule slip of the
 * `addiu $8,$16,0xC8` (retail puts it in the `bnez` delay slot at 0x004EA7E4,
 * ours in the `jal` delay slot at 0x004EA858).
 * MEASURED NULL: hoisting `r = (N *)((u8 *)p + i * 16);` to the top of the
 * loop body, above the normal_D_00527000 guard -- REGRESSION, 45 -> 58 bad; reverted.
 * Per [[mwcc-callee-saved-creation-order]] the emitted first-definition order
 * is i < e < r in BOTH ours and retail, so the 69.7% `first` rule PREDICTS
 * retail's colouring and does not explain ours -- this unit sits in that
 * model's ~30% minority. Next arms to try: declaration-order permutations of
 * (r, i, y), and giving `e` an explicit named local. */
typedef struct N {
    u8  pad000[0x14];
    u8  f014[0xA0];                 /* 0x014 */
    f32 fB4;                        /* 0x0B4 */
    u8  padB8[0x4];
    f32 fBC;                        /* 0x0BC */
    f32 fC0;                        /* 0x0C0 */
    f32 fC4;                        /* 0x0C4 */
    s16 fC8;                        /* 0x0C8 */
    u8  padCA[0x104 - 0xCA];
    s16 f104;                       /* 0x104 */
} N;

extern s32   normal_D_00527000[];
extern void *D_004843E0;          /* gp - 0xD90 */

/*rgp*/
/*rgp*/
/*rgp*/

void normal_MenuBattleEndItemRowsCascade_4ea700(N *p)
{
    s32  i;
    N   *r;
    s32  y;

    for (i = 0; i < 4; i++) {
        if (normal_D_00527000[i] > 0 || normal_D_00527000[i] == -0xFF) {
            UiGetWidgetAlpha_290770(p->f014, (i + 1) * 3);
            r = (N *)((u8 *)p + i * 16);
            if (r->fB4 >= 5.0f) {
                if (normal_D_00527000[i + 1] > 0 || normal_D_00527000[i + 1] == -0xFF) {
                    UiFadeWidgetAlpha_290690(p->f014, (i + 2) * 3, 1.0f, 0.125f, -1.0f);
                    if (i + 1 < 4) {
                        s16 *pc = &r->fC8;

                        if (*pc == 0) {
                            N *w;

                            y = (i + 1) * 42;
                            w = (N *)((u8 *)p + (u32)i * 16);
                            w->fC0 = (f32)(y + 0xC);
                            w->fBC = (f32)(y + 0xE);
                            w->fC4 = -6.0f;
                            *pc = 1;
                            if (p->f104 != 1) {
                                SoundPlayScaledVolume_1b9520(D_004843E0, 0x20, 0, 1.0f);
                            }
                        }
                    }
                }
            }
        }
    }
}
