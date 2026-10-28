/* rgp:protos */
#define RGP_SELF_normal_TransSaveErrorState_519e90 1
#include "port/game_protos.h"
#line 1
/* === SESSION 86 (2026-09-22): 3 BAD -> MATCH.  The three-way `w` test is a
 * SWITCH whose case 0 stores and BREAKS, followed by `goto out`:
 *     switch (D_00484800) { case 0: D_00484800 = 1; break; case 1: goto live; }
 *     goto out;
 * The if-chain let mwcc prove $2 == 1 at the `w != 0` exit and tail-merge it
 * PAST the shared `li` (s63's reading was right); the switch's join block has
 * two preds, so the exit branches to the `li` and threads it into the `b`'s
 * slot, and the single branch-thread copy is no longer spent on the bnez.
 * `case 0: goto zero;` with the store block laid out just above `out:` is the
 * SAME object.  `case 1` listed first is +3 words.  Decks s86/d1.py, d2.py. */
/* === SESSION 83 (2026-09-21, SOLO): STILL 3 BAD / 88 words.  s82's named
 * cross is BUILT and NEGATIVE -- retire it.  Deck build/wf-normal/s83/a1.py.
 * s82 found this unit's first +1 (`f660_returns`) and said it needed a -1;
 * s80/s81 had measured exactly one -1 (DROP the `const` on D_004B2570) but
 * never crossed the two, because f660_returns did not exist until s82.
 * ARMED: `m570` alone 87 w, `f660_returns` alone 89 w -- both halves live.
 *     f660_returns x m570    88 w, 9 bad
 *     both_return  x m570    88 w, 10 bad
 *     store_returns x m570   87 w
 *     f660_returns x cF4 x m570 / x cF0 x m570   89 w
 * Three new exact-length objects, none under the base 3.  The const axis is
 * now closed against BOTH of this unit's +1 shapes as well as both attractors.
 * NEW LENGTH HALVES HUNTED, all null: a `switch` for the six-way chain is +7;
 * `s32 w`, `s32 v`, `volatile s8 D_00484800`, and a named `m` for
 * `D_004847F0 | D_004847F4` are BYTE-IDENTICAL.
 * !! `D_004847F4 | D_004847F0` (the `|` operands swapped) is 5 bad, and it is
 * the ARMING CASE FOR A NEW TRAP: its `text=` hash is IDENTICAL to the base's
 * because objdump on an UNLINKED .o prints a relocated immediate as 0, so
 * rs2.texthash CANNOT SEE which symbol a gp-relative access names.  A
 * "byte-identical" verdict from that hash is only a verdict on the
 * NON-RELOCATED fields; always read `bad` beside it. */
/* === SESSION 82 (2026-09-21, SOLO): STILL 3 BAD / 88 words.  No move, but the
 * residue is NOT what this file has been treating it as, and the corrected
 * reading names a different next arm.  Deck build/wf-normal/s82/j1.py; the
 * reloc-aware lister is build/wf-normal/s82/bad3.py.
 * THE THREE WORDS, read properly (words 61/64/65, 0x00519F84):
 *     retail  beql $3,$0,.L00519FE0 | sb $2 | b .L00519FE4 | LI $2,1 |
 *             jal func_2F6660 | nop | BNEZ $2,.L00519FE0 | NOP
 *     ours    ...                  | sb $2 | b .L00519FE4 | NOP     |
 *             jal func_2F6660 | nop | BNEZL $2,.L00519FE4 | LI $2,1
 * 0x00519FE0 is the SHARED `li $2,1` of the common `return 1`.  Retail BRANCHES
 * TO IT from the func_2F6660 test (plain `bnez`, empty slot) and pays for that
 * with its own `li $2,1` in the earlier `b`'s delay slot.  We CLONE the block
 * into an ANNULLED `bnezl` slot and branch past it.  That is
 * [[levers.d/mwcc-branch-likely-duplication]] -- clone iff the target has != 1
 * predecessor -- so the axis is the PREDECESSOR COUNT of the shared return,
 * not a colour, not a const and not the s63 attractor pair.
 * j1.py sweeps it, 8 arms, ARMED (four arms change the length, two are new
 * exact-length objects):
 *     store_returns (`D_00484800 = 1; return 1;`)        4
 *     B_goto_out    (s63's attractor B)                  4
 *     store_via_one, f660_eq0                            BYTE-IDENTICAL
 *     both_return, f660_returns                          +1 word
 *     w_eq0_block, w_eq0_return                          +6 words
 * !! `f660_returns` (`if (func_2F6660() != 0) return 1;`) is a clean +1 and it
 * is the shape that removes one predecessor from 0x00519FE0.  It is the first
 * NAMED +1 this unit has; it needs a -1 partner, and nothing on this unit is a
 * known -1 yet.  s81's const cross and s75's colour arms are both retired. */
/* === SESSION 81 (2026-09-21, SOLO): STILL 3 BAD / 88 words.  s80's +1/-1
 * CONST CROSS IS BUILT ON BOTH ATTRACTORS AND IT IS NEGATIVE.
 * Deck build/wf-normal/s81/k1.py.  s80 measured four +1 const arms on this
 * unit (D_004847FC / D_004847F0 / D_004847F4 lead, D_004847D0 as `void *const`)
 * and one -1 (drop the `const` on D_004B2570) but never crossed them.  Crossed
 * now, against BOTH of s63's attractors (A = `return 1` at the `w != 0` exit =
 * the shipped base, 3 bad @61/64/65;  B = `goto out` there, 4 bad @58-61,
 * which fixes exactly the words A breaks):
 *     A x cF4 x m570   7      B x cF4 x m570   8
 *     A x cF0 x m570   8      B x cF0 x m570   9
 *     A x cD0 x m570  17      B x cD0 x m570  18
 *     A x cFC x m570  60      B x cFC x m570  60
 * EIGHT NEW EXACT-LENGTH OBJECTS, none under the base 3; every +N x +N x -1
 * triple is 89 words.  The const axis does not reach the tail merge.  Dated
 * armed null -- do not rebuild this cross.
 * TWO BOARD-WIDE AXES, both null here:
 *  * the INSECT-s95 REGISTER BINDING (g1.py,
 *    [[levers.d/mwcc-register-binding-exit-seed]]): EVERY binding r2-r20 is
 *    BYTE-IDENTICAL on this unit -- the only one of 14 open units where even
 *    the callee-saved bindings are free AND inert.  Armed two ways.
 *  * the [[levers.d/caller-saved-colour-follows-scheduler]] two-arm probe
 *    (h1.py): `optimization_level 2` + `opt_propagation off` + `schedule on`
 *    reproduces the base BYTE-IDENTICALLY (7030c0d6) -- the lever's POSITIVE
 *    signature.  The level knob changes only the schedule here.
 *    `optimization_level 3`/`4` == default; 0/1/2 are +52/+40/+24 words. */
/* SESSION 45 (n45G/n45H/n45I): 88/88 words, THREE bad, ~25 arms, NO CLOSE.
 * The residue is ONE decision taken twice, at 0x00519F84/F90/F94:
 *   retail  b .L00519FE4 | addiu $2,$0,0x1     (the `return 1` constant
 *           RE-MATERIALISED in the delay slot, jumping PAST the shared
 *           `addiu $2,$0,1` that sits at .L00519FE0)
 *           jal func_2F6660 | nop | bnez $2,.L00519FE0 | nop
 *   ours    b 154 | NOP                        (mwcc knows `v0` still holds the
 *           `1` it built for `w == 1`, so it elides the re-materialisation)
 *           jal | nop | bnezl v0,154 | li v0,1  (threaded instead)
 * Both differences have the SAME root: our `1` is one value-number, retail's
 * are two.  Ã¢Å¡Â Ã¢Å¡Â  MEASURED INERT (all collapse onto object cd2c31a8): `(s8)1` on
 * the store, `w` as s32, reading `D_00484800` directly instead of `w`,
 * `if (w != 1)` inverted outer, a `s32 r = 1; return r;` local, `out:` written
 * as `r = 1; return r;`, decl order, and the nested / `&&` spellings of the
 * live: block.  LENGTH-WRONG: `w == 0` first (+6), nested `w != 0` outer (+2),
 * `return 1` in place of `goto out` (+3), `w - 1 == 0` (+2), `D_00484800 = w+1`
 * (+2), and `goto out` in place of the `b != 0` block's `return 1` (-1).
 * NEXT: that last one is the only measured -1 on the unit, so it is a CROSS
 * HALF -- look for a +1 partner ([[two-edit-cross-beats-count-ranking]]). */
#include "types.h"
/* normal 0x00519E90 -- two halves under one guard.  The six-way dispatch is an
 * if/else-if CHAIN in SOURCE order, not a switch: every converted `bnel`
 * carries the NEXT GUARD'S CONSTANT rather than a case body's work, which is
 * the recorded discriminator.  Ã¢Å¡Â  `$4` is never read -- the first parameter
 * leaves no trace here.
 *
 * Ã¢Å¡Â Ã¢Å¡Â  PARKED at 3 WORDS, RIGHT LENGTH -- deliberately NOT in
 * config/ocunits/normal.txt, because a right-length wrong unit produces a
 * DIFFERING image that the link's length guard passes.
 * The whole first half (56 words, the six-way chain) is exact.  The residue is
 * words 61/64/65 and it is ONE class: retail re-materialises `addiu $2,$0,1`
 * in a `b`'s delay slot and keeps a PLAIN `bnez` with a `nop`, where mwcc
 * shares the `1` the `w == 1` compare already put in `$2` and converts the
 * branch to `bnezl` carrying a duplicate.  That is the recorded
 * branch-likely-conversion class (shared-return predecessor count) reached
 * from both sides at once.  ~18 spellings across four probe builds
 * (scripts/n_oprobe.py): six tail block orders, four join/return
 * arrangements, an explicit result variable, `goto` vs `return` at each of the
 * three guards.  x03..x06 sit at 4 bad; y01/z01/z04 at 3; everything else is
 * LONG.  Do not spend more spellings.
 *
 * One of the 55 unnamed functions; see scripts/n_unnamed.py.
 *
 * (session gr11) NEW ARM TRIED: `extern volatile s8 D_00484800` (lever #3,
 * hoping it would defeat the value-numbering that produces the `bnezl`
 * re-materialisation). Rebuilt at 3 bad words, byte-for-byte the SAME
 * residue -- INERT, reverted. Lever #3 is about a STORE being pinned; this
 * residue is a READ-side branch-likely conversion, so it does not apply
 * here. Do not retry it on this unit.
 *
 * (session s33 / ag19e90) Re-opened per instructions to find a NEW angle,
 * not another spelling sweep. CONFIRMED optimization_level 0-4 already
 * fully swept in nc32g/nf32a/nf32g (see lines 18-25 above) -- did not
 * retry. 9 genuinely new arms tried, ALL rebuilt at 88 words / same 3-bad
 * residue (INERT) unless noted:
 *  1. `#pragma opt_common_subs off` SCOPED to just the w==1/w!=0/goto-out
 *     block (not whole-function). Confirmed pragma scoping DOES take
 *     effect mid-function here (a control test wrapping the WHOLE body in
 *     the same pragma reproduced the documented 103-word overshoot) --
 *     so this is a real negative, not a placement artifact.
 *  2. `#pragma scheduling off` scoped to the same block -- INERT.
 *  3. `#pragma peephole off` scoped to the same block -- INERT.
 *  4. `#pragma no_branch_likely on` scoped to the same block, and widened
 *     to also cover the first `live:` guard's `bnez` -- INERT both times.
 *     IMPORTANT FINDING: unlike opt_common_subs, `no_branch_likely` is
 *     evaluated PER-PROCEDURE, not per-statement -- it only changes
 *     anything when placed before the function's own signature line
 *     (reproduces the documented 95-word overshoot there); placed after
 *     the opening `{`/locals it is a no-op even though the pragma is
 *     "active" text-wise. Do not waste arms trying to scope this pragma
 *     narrower inside the body; it cannot be scoped that way in this
 *     compiler.
 *  5. else-if chain instead of if/goto/if/goto for the w==1 / w!=0 split
 *     -- byte-identical INERT (same object).
 *  6. `volatile s8 w` (previously only the GLOBAL D_00484800 was tried
 *     volatile, per gr11 above; the LOCAL had not been) -- 91 words, LONG.
 *  7. Reading `D_00484800` directly twice (dropping local `w` entirely,
 *     two separate global loads instead of one load + two compares) --
 *     INERT, same residue.
 *  8. Pointer indirection: `s8 *pw = &D_00484800;` then `*pw` at all three
 *     sites instead of the named local -- 89 words, LONG (1 over).
 *  9. `if (!(w ^ 1))` in place of `if (w == 1)` -- 90 words, LONG.
 * None of these closes it or moves the residue. The mechanism recorded
 * above (mwcc shares $2's value across the compare and the return-1
 * exit, retail doesn't) looks like a hard-coded value-numbering decision
 * inside mwcc's peephole/scheduler that no exposed pragma or source
 * reshaping reaches. Left PARKED at 3 bad / 88 words (unchanged). */
/* (session s63, 2026-09-15) RE-READ THE RESIDUE FROM THE OBJECT, not from the
 * earlier headers -- the mechanism recorded above is RIGHT about the cause but
 * WRONG about the shape, and one of its numbers is wrong.
 *
 * ** THE RESIDUE IS ONE DECISION, AND IT IS A TAIL-MERGE TARGET. **
 * Word-for-word (probe build/wf-normal/s63/nmprobe.s63.c, arm nm_a00, which
 * reproduces the shipped source EXACTLY at 88 words / 3 bad):
 *
 *   word   ours                        retail
 *    55    addiu $2,$0,1               addiu $2,$0,1      (the `w == 1` const)
 *    56    beq   $3,$2,->live          beq   $3,$2,->live
 *    58    beql  $3,$0,->84            beql  $3,$0,->84    <- SAME
 *    59    sb    $2,-0x970($28)        sb    $2,-0x970($28)  <- SAME (annulled)
 *    60    b     ->85                  b     ->85           <- SAME
 *    61    nop                    !!   addiu $2,$0,1        <- the ONE defect
 *    64    bnel  $2,$0,->85       !!   bnez  $2,->84
 *    65    addiu $2,$0,1          !!   nop
 *
 * So our CONTROL STRUCTURE at 58/59/60 is already retail's, exactly.  Both
 * sides spend the .L00519FE0 join block's ONE branch-thread copy of
 * `addiu $2,$0,1` ([[levers.d/mwcc-branch-likely-duplication]], s43 rule:
 * one copy, earliest branch whose slot the filler left empty).  Retail spends
 * it on the `b` at word 60; we spend it on the `bnez` at word 64, converting
 * that branch to `bnel`.  The reason word 60 is not a candidate for us is that
 * mwcc TAIL-MERGED our `w != 0` exit straight to .L00519FE4 (word 85, PAST the
 * shared `li`) because $2 demonstrably still holds the `1` the `w == 1`
 * compare built at word 55; retail merged the same exit to .L00519FE0 (word
 * 84) and only then threaded.  Ã¢â€¡â€™ The lever this unit needs is whatever stops
 * that one tail merge from picking the post-`li` label.  It is NOT a
 * branch-polarity, block-order or guard-spelling fact -- see below.
 *
 * Ã¢Å¡Â Ã¢Å¡Â  CORRECTION to the NEXT line above: `goto out` in place of the `w != 0`
 * block's `return 1` is **NOT -1**.  Measured (nm_a02): EXACT 88 words, 4 bad
 * @58 59 60 61.  The recorded "-1" is wrong, so the CROSS-HALF plan built on
 * it ([[two-edit-cross-beats-count-ranking]]) has no basis.  Do not chase it.
 *
 * ** TWO ATTRACTORS, AND EVERY SPELLING FALLS INTO ONE OF THEM. **
 *   A (= a00, 3 bad @61/64/65): the `w != 0` exit is written `return 1`.
 *   B (= a02, 4 bad @58-61):    the `w != 0` exit is written `goto out`.
 * B is retail's own four instructions with the two ONE-INSTRUCTION arms
 * SWAPPED -- ours makes the `w != 0` return-1 arm the annulled/likely arm
 * (`bnel ->85 / li`, then `b ->84 / sb`), retail makes the `w == 0` STORE arm
 * the annulled one (`beql ->84 / sb`, then `b ->85 / li`).  B fixes 64/65 and
 * breaks 58/59/60; A is the reverse.  Nothing lands between them.
 *
 * 22 FRESH SOURCE ARMS, all collapsing onto A or B (probe arms named):
 *   -> B: a02 `goto out`; a06 `if (w==0) store;` + fallthrough goto;
 *         a10/a11 third label `zero:` with the store as the branch TARGET,
 *         at both block positions; a12 `if (!w)`; a13 explicit if/else;
 *         a15 store and compare sharing a named `s8 one` local;
 *         a16 if/else with a dummy else arm.
 *   -> A: a14 `return 1` + `zero:` label; a22 `if (w)` truth test;
 *         a23 `*(volatile s8 *)&D_00484800 = 1` (the volatile STORE -- gr11
 *         only ever tried the volatile LOAD; this is a distinct, new null);
 *         a24 compare constant forced through its own `s32 k` local.
 *   LENGTH-WRONG: a04/a07 `if (w==0){store;goto out;} return 1;` (+6 -- the
 *         third `return 1` stops the six-way dispatch sharing the epilogue,
 *         the +6 is in the DISPATCH, not in this block); a20 two labelled
 *         return-1 blocks (88w but 6 bad, BOTH defects at once); a21 same
 *         with the ret1 block between live: and out: (+6); a25 result local
 *         assigned on both paths (+5); a01/a03/a05 pointer indirection (+1).
 *
 * ** THE PRAGMA AXIS IS NOW A WIDE, ARMED NULL: 19 pragmas, all inert. **
 * `opt_propagation`, `opt_optimizecontrolflow`, `opt_dead_assignments`,
 * `opt_prelinearize`, `opt_movepostops`, `opt_marknonregtemps`,
 * `opt_lifetimes`, `opt_repositioncode`, `opt_serializeassignments`,
 * `opt_arithtransformation`, `opt_pulloutconstants`,
 * `opt_optimizenonregaccess`, `opt_strength_reduction`, `opt_dead_code`,
 * `opt_scalarizeliveranges`, `opt_rotateloops`, `opt_loop_invariants` -- each
 * `off`, each around the baseline arm -- all 88 words / 3 bad, byte-identical
 * to a00.  ARMED: `opt_common_subs off` in the same harness reproduces the
 * s33-recorded 103-word overshoot exactly.
 *
 * Ã¢Å¡Â Ã¢Å¡Â Ã¢Å¡Â  METHODOLOGY TRAP FOUND HERE, applies to EVERY multi-pragma probe TU in
 * this project: **`#pragma <name> on` DOES NOT RESTORE.**  The first run of
 * the sweep closed each arm with `#pragma <name> on`; from the
 * `opt_serializeassignments` arm onward EVERY later arm read a uniform
 * 96 words (+8) regardless of its own pragma -- a leak, not a result.  Wrap
 * each arm in `#pragma push` / `#pragma pop` instead; re-run that way, the
 * same arms read 88/3 and the arming control still fires.  See
 * [[levers.d/mwcc-pragma-push-pop-restore]].
 *
 * NEXT: the only unexplored handle is the TAIL MERGE itself -- something that
 * makes mwcc unable to prove $2 == 1 at the `w != 0` exit without adding a
 * word.  Source spelling (22 arms), guard polarity/block order (8 arms),
 * volatile on both the load and the store, and 19 optimizer pragmas are all
 * measured nulls.  Do not re-sweep any of those axes. */

extern s8    D_00484800;
extern s16   D_004847FC;
extern s32   D_004847F0;
extern s32   D_004847F4;
extern void *D_004847D0;
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveErrorState_519e90(void *a, s32 b)
{
    s16 v;

    if (b != 0) {
        D_00484800 = 0;
        normal_TransSaveYesNoCursorBob_5188c0(0, 1, 0);
        normal_TransSaveProgressWindowShow_519e50(1, 0);
        v = D_004847FC;
        if (v == 8) {
            normal_TransSaveShowMsg_519ff0(0xA);
        } else if (v == 5) {
            normal_TransSaveShowMsg_519ff0(0xB);
        } else if (v == 4) {
            normal_TransSaveShowMsg_519ff0(0xD);
        } else if (v == 6) {
            normal_TransSaveShowMsg_519ff0(0xF);
        } else if (v == 0xD) {
            normal_TransSaveShowMsg_519ff0(0xE);
        } else if (v == 0xF) {
            normal_TransSaveShowMsg_519ff0(0xC);
        } else {
            normal_TransSaveShowMsg_519ff0(0xB);
        }
        return 1;
    }
    switch (D_00484800) {
    case 0: D_00484800 = 1; break;
    case 1: goto live;
    }
    goto out;
live:
    if (GetPauseStep_2f6660() != 0) {
        goto out;
    }
    if (PadIsTriggered_1839f0(&D_004B2570, D_004847F0 | D_004847F4) == 0) {
        goto out;
    }
    normal_TransSaveShowMsg_519ff0(-1);
    normal_TransSaveHighlightOption_519e70(-1);
    normal_TransSavePanelFade_518700(2);
    StateMachineSetState_28ede0(D_004847D0, 6, 0);
out:
    return 1;
}
