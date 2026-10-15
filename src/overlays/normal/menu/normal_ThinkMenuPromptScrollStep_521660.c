/* === SESSION 72 (2026-09-21, SOLO): **MATCH**.  s48 had BOTH halves right and
 * they only cross under one pragma:
 *   (a) the grouping is `(X + D_0048495C) + 64.0f` on BOTH sites (s48's, then
 *       recorded as +1 word and NOT installed);
 *   (b) the 64.0f seed NAMED in a local `s`, assigned INSIDE each `if` body;
 *   (c) `#pragma opt_dead_assignments off` at file scope.
 * Without (c) the name is folded onto the temp -- that is why s48's 13 seed
 * arms were ONE OBJECT and why its verdict "the seed's register is NOT
 * reachable from a named local" read as true.  It is reachable; the pass that
 * folds it is opt_dead_assignments.  (c) also fills the mtc1 hazard `nop` that
 * made (a) +1 word on its own.
 * ARMED grid (build/wf-normal/s72/t4.py, 32 cells): every /base cell of the
 * new grouping is LEN 0x14c vs 0x148, `n1=- n2=s/dassign_off` is 4,
 * `n1=s n2=sa` 3, `n1=s n2=a` still length-wrong -- the pragma alone on the
 * SHIPPED grouping is byte-identical to base (7074f48d).  `opt_unroll_count
 * off` fails to build; bogus name == base.
 * Same lever as normal_TransMenuTopState_514e10 this session.
 * See [[levers.d/mwcc-opt-propagation-pragma]], [[levers.d/mwcc-fpr-decl-order-highest-first]].
 */
/* === SESSION 54 (2026-09-12, SOLO): STILL 5 BAD / 82 words.  MECHANISM FOUND,
 * and it is a CROSS: no single spelling holds both halves.
 * Retail's shape at BOTH `if` bodies is
 *     add.s $f0,<other band>,$f0      then   add.s $f0,<64.0f>,$f0
 * i.e. the inner sum is (band + D_0048495C) with D_0048495C as the ACCUMULATOR
 * and the literal added LAST; mwcc canonicalises a float constant to the `fs`
 * slot, so `(b+c)+64.0f` and `64.0f+(b+c)` are ONE tree and both are right.
 * mwcc gives the ACCUMULATOR (the `ft` chain) $f0 and hands each `fs` operand
 * the next FPR.  The two halves we can reach:
 *   BASELINE  `band + (64.0f + c)`  -> RIGHT FPRs (c=$f0, 64=$f1, band=$f2),
 *             WRONG pairing (it adds 64 to c first).  5 bad.
 *   f1/f4     `band + c + 64.0f` / `64.0f + (band + c)` (ONE object) -> RIGHT
 *             pairing, FPRs INVERTED (c=$f1, 64=$f0) because the final add
 *             coalesces its destination with the CONSTANT's register instead
 *             of the sum's.  7 bad at site A; at site B it is +1 word (a `nop`
 *             after the mtc1, mdiff shows the rest is structurally IDENTICAL).
 * ⚠⚠ 24 arms over three decks, do not re-run:
 *  a_521660.py  (5) whole-expression rewrites, both sites together.
 *  a_521660b.py (16) EIGHT associations x each site INDEPENDENTLY:
 *      f1 bc64, f2 cb64, f3 b_(c64), f4 64_(bc), f5 64bc, f6 c64b, f7 c_(64b),
 *      f8 (cb)64.  Best cells: A_f6 5/2b019366 and B_f7 5/fe471fd2 (ties on a
 *      new object), A_f7 8 bad but with ZERO FPR substitutions, B_f5 gets site
 *      2's REGISTERS exactly right (a=$f1, c=$f0, 64=$f2) and only swaps the
 *      `lwc1`/`mtc1` ORDER -- that is the other live cross half.
 *  a_521660c.py (11) named temps (`t = band + c; ... = 64.0f + t;` and every
 *      variant, plus reusing the dead `d`): every one COLLAPSES onto the f1/f4
 *      or the f2/f8 object.  A temporary does not decouple the pairing from
 *      the FPR assignment.
 */
/* === SESSION 52 (2026-09-08, SOLO): still 5 bad.  [[mwcc-const-sdata-load-hoist]]
 * -- the lever that closed normal_BtlChgMenuCursorBob_503750 this session -- DOES NOT APPLY
 * HERE, and the reason is worth recording because the residues look identical:
 * this unit's residue IS two gp `lwc1`s sitting on the wrong side of the 64.0f
 * `mtc1`, but D_0048495C is READ-ONLY in this function, so there is no
 * read/write alias barrier to remove.  `const`+`.sdata` on D_0048495C, and
 * `.sdata` alone, are BYTE-IDENTICAL to the baseline (6ed2a14c).
 * 8 arms; the rest all go LENGTH-WRONG (0x14c vs 0x148): const+.sdata on
 * D_00484964 too (+1), s48's `(X + A) + 64.0f` grouping alone or crossed with
 * it, and const+.sdata on the WRITTEN globals D_0048078C/D_00484960 with the
 * writes routed through `*(f32*)&X` casts (three distinct objects, all +1).
 * The +1 is s48's already-recorded unfilled `mtc1` hazard nop.  The residue is
 * still the FPR-allocation fact this file's s48 header names. */
/* === SESSION 48 (2026-09-08, SOLO): SCORE UNCHANGED at 5, but the GROUPING IS
 * NOW NAMED and s47's "the association axis is EXHAUSTED" is only true of the
 * SCORE.  Retail's expression on BOTH blocks is
 *     (X + D_0048495C) + 64.0f
 * (block 1 X = D_00484960, block 2 X = D_0048078C).  Installed that way:
 *   - BLOCK 1 becomes STRUCTURALLY EXACT -- its two `add.s` stop being
 *     transposed and the whole block differs only in FPR numbering;
 *   - BLOCK 2 reproduces retail's LOAD ORDER instruction for instruction
 *     (`lwc1 X / lui / lwc1 A / mtc1 64.0f`), which no other grouping does.
 * The arm is +1 WORD -- an unfilled `mtc1` hazard `nop` -- so it scores WORSE
 * (len 0x14c vs 0x148) and is NOT installed.  It is recorded because it
 * reduces the residue to ONE named class:
 *
 * ⚠ THE REMAINING DEFECT IS FPR ALLOCATION.  Retail creates the 64.0f SEED
 * vreg FIRST, so it takes the HIGHEST free FPR (block 1 $f1 with $f2 live,
 * block 2 $f2); we create it LAST and it takes $f0, pushing both operand
 * loads up one register and leaving the mtc1 shadow unfilled
 * ([[mwcc-fpr-decl-order-highest-first]], [[mwcc-float-zero-seed-web]]).
 *
 * MEASURED NULL at the NEW grouping (13 arms, a_21660{j,k,m}.py) -- every one
 * is ONE OBJECT (f7e8e87d): `f32 s = 64.0f;` at the case top / per-if /
 * before both ifs, reusing the dead `d` as the seed, a function-scope `k`,
 * hoisting D_0048495C into a local, `f32 d` declared first, `d` inlined as
 * `2.0f * dt` twice, both assignments routed through a temp, and the guard
 * written `D_00484964 >= X`.  The seed's register is NOT reachable from a
 * named local; do not re-sweep that axis.
 * Cross halves for a future session: b1=(X+A)+64 alone is 7; b1=(X+64)+A x
 * b2=(X+A)+64 is 8; the full-new arm is +1.  KEEP OUT OF ocunits. */
/* === SESSION 47 (2026-09-07, SOLO): 60 -> 5 BAD on 82 words, exact length.
 * FOUR facts, three of them read straight off the retail listing:
 *
 *  1. ★ THE SWITCH CASE ORDER IS 1, 2, 0 -- not 0, 2, 1.  Retail TESTS
 *     0, 2, 1 (`beql` INTO each arm) but lays the BODIES out case 1 at
 *     0x00521694 and case 2 at 0x005216B8: mwcc emits switch bodies in SOURCE
 *     order and tests in REVERSE ([[m2c-switch-arm-order]]).  Alone this is
 *     -1 word (0x144), so it only reads as right in a CROSS.
 *  2. The first tail block is SYMMETRIC with the second:
 *     `x = (s32)D_0048078C; if (x == -1) { x = 0; }`.  Retail's two blocks are
 *     identical 12-word shapes (`lwc1/cvt.w.s/mfc1 $6` straight into ARG3,
 *     then `bnel $6,$2` with the D_00484920 load DUPLICATED into the delay
 *     slot, [[mwcc-branch-likely-duplication]]).  s38 measured this spelling
 *     as +2 words and stopped; +2 crossed with fact 1's -1 is +1, and only
 *     fact 3 closes the length.  ⚠ THIS RETIRES s38's "do not re-try" note --
 *     it was a HALF, not a null ([[two-edit-cross-beats-count-ranking]]).
 *     It also removes the read-before-write UB the old spelling had.
 *  3. Both wrap expressions REGROUP:
 *     `D_0048078C = D_00484960 + (64.0f + D_0048495C);` and the mirror.
 *     Ten groupings were swept on each block independently and then CROSSED
 *     (34 arms): `64.0f + (a + b)` (the draft) is length-WRONG once facts 1+2
 *     are in, `(64.0f + a) + b` is exact at 8, `a + (64.0f + b)` is 6 on
 *     block 1 and 7 on block 2, and the CROSS of the two 6/7 halves is 5.
 *     The `+` operand order inside the parens is INERT (mwcc canonicalises
 *     commutative adds, [[mwcc-commutative-add-operand-order]]).
 *  4. Fact 3 also deletes a hazard `nop` at 0x00521724 that the draft had:
 *     retail fills the mtc1 shadow with an independent `add.s`
 *     ([[normal-mfc1-hazard-nop]]).
 *
 * ⚠ RESIDUE, 2 structural words + 3 renames at 0x0052171C-0x00521720.  Retail:
 *   `lwc1 $f1,-0x49E4 / lui $3,0x4280 / lwc1 $f0,-0x814 / mtc1 $3,$f2`
 * ours:
 *   `lwc1 $f0 / lui v1 / mtc1 v1,$f1 / lwc1 $f2`
 * -- the D_0048495C load belongs BETWEEN the lui and the mtc1; our 64.0f seed
 * materialises one slot early.  The ADDS now match retail exactly.
 *
 * MEASURED NULLS (ARMED, baseline object 6ed2a14c and several arms moved it):
 *  - `#pragma fast_fptosi` on/off and `#pragma trunc` on/off are INERT here.
 *    ⚠ NOTE FOR THE BOARD: at the intermediate 8-bad state we emitted
 *    `trunc.w.s` where retail has `cvt.w.s` (`.word 0x46000024`); fact 3 fixed
 *    it as a side effect, so the fptosi pragma is NOT the lever for that
 *    opcode -- the EXPRESSION SHAPE is.
 *  - naming D_0048495C or 64.0f in a local (block-scoped, if-scoped, or as
 *    `f32 s = 64.0f`), `64.0F`, `(f32)64`, and swapping the inner operands are
 *    ALL ONE OBJECT with the baseline.  A `k = D_0048495C` hoisted above the
 *    whole case is +13.
 *  - `#pragma schedule off` (+6 w) and `peephole off` (+4 w) are catastrophic.
*  - ★ THE GROUPING LATTICE IS EXHAUSTED AT 5.  All TWELVE associations of
 *    {X, 64.0f, D_0048495C} were swept on each block alone and then crossed
 *    (78 arms total).  The floor is 5 and FOUR DISTINCT OBJECTS reach it
 *    (6ed2a14c, fe471fd2, 2b019366, e1988a1c) -- b1 in {g4,g5} x b2 in
 *    {g4,g5,g10,g11} and b1 in {g8,g9} x b2 in the same set.  Installed is
 *    b1=g4 x b2=g4.  ⚠ `D_0048495C + (64.0f + X)` on BLOCK 1 (b1_g10) is 8 bad
 *    but subs=1 -- a nearly RENAME-FREE residue, i.e. a different and possibly
 *    more tractable defect shape if the seed lever is ever found.
 *    Do not re-sweep the association axis; sweep the SEED's neighbour instead.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* SESSION 31: LENGTH-WRONG (84 vs retail 82, ours was LONG) -> EXACT LENGTH,
 * 60 bad, and therefore scoreable for the first time.  Same lever as
 * normal_SpaceMenuCursorRight_512800: the seed-then-overwrite deck's INVERSE direction,
 * `V = B; if (C) { V = A; }` rewritten as `if (!(C)) { V = B; } else
 * { V = A; }` (mkelse31.py).
 * KEEP OUT OF config/ocunits/normal.txt.
 * SESSION 38 (n38h): the `if (x != -1) { x = (s32)D_0048078C; } else { x = 0; }`
 * spelling reads x UNINITIALIZED (UB) -- retail's actual asm at L00521734 is
 * unconditional `x = (s32)D_0048078C; if (x == -1) x = 0;` (bnel/daddu shared-
 * exit pattern, no read-before-write).  MEASURED NULL: installing the
 * logically-correct unconditional-assign spelling REGRESSES the length by
 * +2 words (84 vs correct 82) -- do not re-try this exact rewrite.  The
 * true defect is upstream: our object's FIRST bad word is at 0x521664 (the
 * word right after the prologue's `addiu $29,$29,-0x10`), where we emit
 * `addiu $3,$0,1` (materializing the case-1 dispatch constant) a full
 * instruction ahead of even `sd $31,0($29)` -- i.e. the whole three-way
 * switch dispatch is scheduled differently from retail's (which loads the
 * state byte first, then interleaves each case's constant with its own
 * beql check).  This reads as a pure GPR-scheduling artifact around the
 * switch lowering, not the tail's x variable.  Untried: perturbing which
 * local (d vs x) is declared first, since neither was probed this session. */
#include "types.h"
#pragma opt_dead_assignments off
/* normal 0x00521660 -- the two scrolling bands at 0x0048078C / 0x00484960:
 * state 1 counts the delay down, state 2 scrolls both and wraps each one 64
 * past the other.  The dispatch is a `switch` on the s8 state. */
extern f32   D_0048078C;          /* gp - 0x49E4 */
extern f32   D_00480790;          /* gp - 0x49E0 */
extern void *D_00484920;          /* gp - 0x850  */
extern s8    D_00484958;          /* gp - 0x818  */
extern f32   D_0048495C;          /* gp - 0x814  */
extern f32   D_00484960;          /* gp - 0x810  */
extern f32   D_00484964;          /* gp - 0x80C  */

extern void func_28F590(void *p, s32 id, s32 x, s32 k);

void normal_ThinkMenuPromptScrollStep_521660(f32 dt)
{
    s32 x;
    f32 d;
    f32 s;

    switch (D_00484958) {
    case 1:
        D_00480790 -= dt;
        if (D_00480790 <= 0.0f) {
            D_00484958 = 2;
            D_00480790 = 0.0f;
        }
        break;
    case 2:
        d = 2.0f * dt;
        D_0048078C -= d;
        D_00484960 -= d;
        if (D_0048078C <= D_00484964) {
            s = 64.0f;
            D_0048078C = (D_00484960 + D_0048495C) + s;
        }
        if (D_00484960 <= D_00484964) {
            s = 64.0f;
            D_00484960 = (D_0048078C + D_0048495C) + s;
        }
        break;
    case 0:
        break;
    }
    if (D_00484958 != 0) {
        x = (s32)D_0048078C;
        if (x == -1) {
            x = 0;
        }
        func_28F590(D_00484920, 0x7533, x, 0);
        x = (s32)D_00484960;
        if (x == -1) {
            x = 0;
        }
        func_28F590(D_00484920, 0x7533, x, 1);
    }
}
