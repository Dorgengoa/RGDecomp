/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyConfirmState_50cbe0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 53 (2026-09-08, SOLO): CLOSED.  45 bad / 156 words -> MATCH,
 * object b036adec.  THREE edits, and ALL THREE WERE READ OFF A MERGED TWIN --
 * `normal_ShopMenuSellConfirmState_50fb60`, 156 words, 0.936 opcode-multiset overlap, found by
 * the NEW board-wide clone census `build/wf-normal/s53/clone.py` (the s52
 * process lesson mechanised: pair every open unit with a MERGED unit of the
 * same masked retail opcode stream, then read that unit's C).
 *
 * (1) THE FLAG BLOCK AS A FLAT else-if CHAIN, in the twin's spelling:
 *         } else if (func_1839F0(D_004B2570, 0x8000) != 0) { ...0... }
 *           else if (func_1839F0(D_004B2570, 0x2000) != 0) { ...1... }
 *     where ours was a NESTED `if (... 0x8000) == 0) { if (0x2000) }else{}`.
 *     45 -> 21, the single biggest edit on the unit.  (Promoting the chain to
 *     the OUTER `n == 2` chain instead is the SAME object -- the nesting depth
 *     is inert, the `== 0` vs `!= 0` polarity is not.)
 * (2) THE FLOAT TAIL, again the twin's:
 *         f = 8.0f * func_128FD0(D_00484648);
 *         ... (s32)(f + (D_00484650 * 80 + 0x2C))
 *     instead of `f = func_128FD0(...)` with `(s32)((8.0f * f) + (f32)(...))`.
 *     The 8.0f folded INTO the local, and NO `(f32)` cast on the integer part.
 *     45 -> 39 alone; it is what fixes the four `$f0>$f1` substitutions, and
 *     retail 0x0050CDE8 builds the 0x41000000 literal BEFORE loading the flag
 *     byte, which is the tell.  Crossed with (1): 15.
 * (3) THE BLOCK ORDER of the 0x753E / 0x7541 pair, 15 -> MATCH:
 *         if (*e->f10 == 0x4173 || func_3D4660(e) != 0) { ...0x7541... }
 *         else { func_289EF0(0x20); D_00484630 = 0; ...0x753E... }
 *     Retail 0x0050CCD8 `beql $2,$0,.L0050CCF8` makes the 0x7541 call the
 *     FALL-THROUGH and the 0x753E block the TAKEN target, and the outer
 *     `beql $3,$2` at 0x0050CCC8 jumps INTO the 0x7541 block with its
 *     `lw $4,-0xBAC($28)` duplicated into the delay slot
 *     ([[mwcc-branch-likely-duplication]]).
 *     ⚠⚠ ONLY THE `||` FORM REACHES IT.  The `&&` conjunction with an else,
 *     the two-`goto` form and the nested-goto form are ALL byte-identical to
 *     the 15-bad baseline -- mwcc normalises those three onto one object and
 *     the `||` onto another.  `if (A || B) X; else Y;` and
 *     `if (A || B) { X; goto post; } Y; post:;` are the same object.
 *     ⚠ this edit was MEASURED INERT at the 45-bad coat and only became live
 *     after (1)+(2) -- [[two-edit-cross-beats-count-ranking]].
 *
 * MEASURED INERT: the twin's callee SIGNATURES (`u16` widget ids on
 * func_290690/func_290F50, `u32` mask on func_1839F0, `s32` return from
 * func_28EC60) are byte-identical here as a bundle.  Dropping
 * `#pragma usefloatacc off` is +2 words -- keep it.
 */
/* ===== LANE nd, session 19 -- 2 words LONG -> RIGHT LENGTH (156), 45 bad
 * (was 93).  TWO levers landed:
 *  1. `#pragma usefloatacc off`.  retail is `mtc1/mul.s/.../add.s` at
 *     0x0050CDF8; we contracted to `mtc1 zero/adda.s/madd.s`.  retail does NOT
 *     have the contraction, which is exactly what the pragma is for.  Worth
 *     2 words, and it closed the LENGTH.
 *  2. GUARD POLARITY on the D_00484650 test.  retail is
 *     `bnel $2,$0,.L0050CD1C` -- it branches AWAY to the short 0x753D arm and
 *     FALLS THROUGH into the big widget block, so the source is
 *     `if (D_00484650 == 0) { big } else { 753D }`.  Worth 48 bad words.
 * RESIDUE: 45 bad at the right length, still block LAYOUT around
 * 0x0050CD50-0x0050CDD4 (a second arm pair whose successor order differs).
 * 3 round trips spent. */
/* PARKED (session gr11, tag gr11; re-tried session gr2-park): LENGTH-
 * CHANGING, 0x278 vs retail's 0x270 (2 words too long).  NOT in
 * config/ocunits/normal.txt.
 *
 * gr2-park tried the gr11-proposed untried arm -- two textual
 * `func_28EDE0(D_004845C4, 0x7541, 0);` call sites (`if (eq) {call 0x7541;}
 * else if (func_3D4660(e)==0) {753E arm} else {call 0x7541;}`) instead of
 * the `goto post;` merge kept below.  RESULT: WORSE, 0x28c vs 0x270 (7 words
 * over, up from 2) -- mwcc did NOT tail-merge the two textual call sites
 * back down to one, it kept both, which is strictly more code than the
 * goto form.  REVERTED; the goto form below is the better of the two known
 * spellings and is what's on disk.  Confirmed via the reference listing
 * that retail reaches the 0x7541 call site either by a `beql` shortcut
 * straight past the func_3D4660 check (the `*e->f10==0x4173` case) or by
 * plain fallthrough out of the func_3D4660 else-arm -- i.e. retail also has
 * only ONE physical call site, reached two ways, so the goto's INTENT is
 * right; the 2-word gap is in exactly how mwcc schedules the merge, not in
 * whether there should be one call site or two.  Next attempt (untried):
 * check whether the two `beql`-and-preload pairs immediately before
 * `.L0050CCE4` in retail (`lw $4,-0xBAC($28)` staged as a delay slot on
 * BOTH incoming paths) implies the source should stage that same load as
 * its own statement (a named `void *ctx4 = D_004845C4;` read once before
 * the if, per lever 18's delay-slot-load family) rather than leaving mwcc
 * to rematerialize D_004845C4 fresh at the goto target. */
#include "types.h"
#pragma usefloatacc off
/* normal 0x0050CBE0 -- the 0x70-family result-post dispatcher: switches on
 * func_28E170's mode over three cases (1/2/default), the case-1 else-arm
 * rebuilds three widgets and posts an event depending on the roster head's
 * marker word, then falls to a shared per-frame height computation. */

typedef struct Meta { u8 pad00[0x14]; s16 f14; u8 pad16[0x1A - 0x16]; s16 f1A; } Meta;
typedef struct Ent  { u8 pad00[0x10]; s16 *f10; } Ent;

extern u8 D_004B2570[];

extern void *D_004845D0;          /* gp - 0xBA0 */
extern s8    D_00484650;          /* gp - 0xB20 */
extern void *D_004845C4;          /* gp - 0xBAC */
extern void *D_004845CC;          /* gp - 0xBA4 */
extern f32   D_0047D4BC;          /* gp - 0x7CB4 */
extern Ent **D_00484644;          /* gp - 0xB2C */
extern u8    D_00484630;          /* gp - 0xB40 */
extern f32   D_0047D3B8;          /* gp - 0x7DB8 */
extern f32   D_00484648;          /* gp - 0xB28 */

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

s32 normal_ShopMenuBuyConfirmState_50cbe0(void)
{
    s32 n;
    Ent *e;
    f32 f;

    n = MenuGridCursorInput_28e170(D_004845D0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(D_004845D0);
    if (n == 1) {
        if (D_00484650 == 0) {
            UiFadeWidgetAlpha_290690(D_004845CC, 0x50, 0.0f, D_0047D4BC, -1.0f);
            UiFadeWidgetAlpha_290690(D_004845CC, 0x67, 0.0f, D_0047D4BC, -1.0f);
            UiFadeWidgetAlpha_290690(D_004845CC, 0x63, 0.0f, D_0047D4BC, -1.0f);
            ShopBuyItem_3ce4e0(D_00484644, ((Meta *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7533))->f14);
            normal_ShopMenuMoneyRefresh_50ac80(0x15, 0x14);
            normal_ShopMenuBuyRowsRefresh_50b5c0(((Meta *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7532))->f1A);
            e = *D_00484644;
            if (*e->f10 == 0x4173 || ItemIsKind2_3d4660(e) != 0) {
                StateMachineSetState_28ede0(D_004845C4, 0x7541, 0);
            } else {
                PlayMenuSe_289ef0(0x20);
                D_00484630 = 0;
                StateMachineSetState_28ede0(D_004845C4, 0x753E, 0);
            }
        } else {
            StateMachineSetState_28ede0(D_004845C4, 0x753D, 0);
        }
    } else if (n == 2) {
        StateMachineSetState_28ede0(D_004845C4, 0x753D, 0);
    } else {
        if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
            if (D_00484650 == 1) {
                PlayMenuSe_289ef0(4);
            }
            D_00484650 = 0;
            normal_ShopMenuYesNoHighlight_509270(0, D_004845CC, 0x65);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
            if (D_00484650 == 0) {
                PlayMenuSe_289ef0(4);
            }
            D_00484650 = 1;
            normal_ShopMenuYesNoHighlight_509270(1, D_004845CC, 0x65);
        }
    }
    PhaseAdvanceWrapPi_28b630(&D_00484648, D_0047D3B8);
    f = 8.0f * Sinf_128fd0(D_00484648);
    UiMoveWidgetUniform_290f50(D_004845CC, 0x66, (s32)(f + (D_00484650 * 80 + 0x2C)), 0x58, 0.25f, 0
);
    return 1;
}
