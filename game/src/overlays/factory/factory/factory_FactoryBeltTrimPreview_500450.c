/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltTrimPreview_500450 1
#include "port/game_protos.h"
#line 1
/* ====================================================================
 * SESSION 57 (2026-09-03), tag fg57 / bulk tag ba57b.  CLOSED -- BYTE-IDENTICAL
 * (md5 d34e38690160, 94 w).  Arming pair 005069e0 = MATCH / 1a0e9c68216b and
 * 005032d0 = MATCH / 29791c8bcf44; the same bulk run reproduced A000_ident =
 * 409c28db0188 / 2, s37's G1 = 92255b97b41d / 2, s56's S_plain_frome_sbj =
 * 4eb60dc86cff / 4 and `s16 j` = 08947337bb73 / 98 w.
 *
 * === THE LEVER: `best` IS A .lit4 POOL LITERAL, AND THE EXTERN WAS A HAZARD ===
 *     best = 3.402823466e+38f;      (0x0047D1EC = 0x7F7FFFFF = FLT_MAX)
 *     e->f08 = 1;                   <- the store must now be written FIRST
 *     j = 0;
 * `extern f32 D_0047D1EC` made `lwc1 $f21` a GLOBAL load that the store
 * `sh v0,8(s0)` could not be scheduled past (a possible alias), so the store
 * was never free at the top of the block and the j-init always reached the
 * delay slot first.  The literal has no alias hazard; the store is free from
 * the block's first cycle, and with the store written before `j = 0` it is
 * scheduled first and `daddu s1,zero,zero` sinks into the slot -- retail.
 * The .lit4 word itself lands at retail's displacement (-0x7F84) because the
 * block starts at the lwc1 (right after the second jal): there is nowhere for
 * the literal to hoist to.  The sweeper's raw score is therefore MATCH here
 * with no .lit4 note only after t_lit4's retarget; judge at the link.
 * ⚠ The literal makes the {j, store} order LIVE again: b-s-j, s-b-j, s-j-b
 * and the for-loop form are all MATCH, b-j-s / j-b-s / j-s-b are the 2-bad
 * transposition.  s23/s49/s56's "the triple is normalised" was true only
 * under the extern.  Also measured: `extern const f32` is 95 w (lui-addressed),
 * `extern const ... section(".sdata")` is the old object (the s52 alias class
 * does not remove the hazard here), `j = e->f08 - 1` with the literal is 1 bad.
 * Batch: 29 arms, build/fg57/s57/mk57_0450.py, log build/fg57/logs/
 * s57_f0450.txt.  Full detail: memory levers.d/factory-session57-levers.md.
 ==================================================================== */
/* ====================================================================
 * SESSION 56 (2026-09-03), tag fg56 / bulk tags ba56p ba56t ba56u.  STILL
 * 2 / 409c28db0188, 94 w -- RE-DERIVED at start.  ⚠⚠ THIS UNIT IS NO LONGER
 * AN ARMING UNIT: it was the second arming unit from s50 and it is UNDER SWEEP
 * here (probe-traps #93 fired on exactly this in s50).  The pair used all
 * session is 005069e0 = MATCH / 1a0e9c68216b AND 005032d0 = MATCH /
 * 29791c8bcf44, held in every tree-based run.
 * RECORDED-LIVE DELIVERY CELLS, established this session because this unit had
 * none: w0450/V_ppnull_frome_bsj_p0 = 92255b97b41d / 2 (which reproduces
 * s37's G1 md5 exactly) and z0450/S_plain_frome_sbj = 4eb60dc86cff / 4, both
 * through bulkarm AND swb56 with the pair held.
 *
 * === THE RESIDUE, RE-DERIVED FROM THE OBJECTS ===
 *   retail  w50 sh    v0,8(s0)        ours  w50 daddu s1,zero,zero
 *           w51 b     +96                   w51 b     +96
 *           w52 daddu s1,zero,zero          w52 sh    v0,8(s0)
 * A pure TRANSPOSITION (residue-transposition-class): the same two
 * instructions round the pre-header `b`, and whichever the scheduler leaves
 * LAST sinks into the delay slot.  Every register is already retail's.
 *
 * === SWEPT THIS SESSION: 959 SOURCE ARMS + 6,592 PRAGMA ARMS ===
 * Scored by the RESIDUE ITSELF (build/fg56/s56/slotscan.py), not by the bad
 * count (probe-traps #94): which instruction is IN the pre-header delay slot.
 *   ★ 0 of 959 source arms have retail's occupant.  Floor stays 2.
 * Pass 1, 424 arms / 56 objects: the declaration order EXHAUSTIVELY (all 121
 * single moves of the 11 locals, all 55 pairwise swaps, the full reversal, 8
 * groupings) = 6 objects, best 6 bad; 7 store spellings x 4 j-init spellings x
 * all 6 permutations of the pre-header triple; 7 loop shapes; the index-cast
 * axis in BOTH directions; the exit lattice.  Pass 2, 535 arms / 40 objects:
 * `best` pinned at the access, 9 j-init spellings, a 4th unfoldable
 * pre-header statement at every position, the call result pinned.
 * The pragma surface (3,280 names x 2 polarities, re-derived not inherited):
 * 34 NOBUILD, 6,558 scored, 14 LIVE, ZERO better.  `no_branch_likely on` --
 * the pragma that closed insect's delay-slot park -- is 96 w here.
 *
 * === ★★★ WHAT ACTUALLY MOVES, AND WHY IT STILL CANNOT REACH RETAIL ===
 * (a) The six source permutations of {best, j = 0, store} give exactly TWO
 *     objects and the split is ENTIRELY `best` BEFORE vs AFTER the store
 *     (b..s = the 2-bad baseline, s..b = 1a7e720f7a68 / 5).  The {j, store}
 *     order really is normalised -- s23's claim, now on 30 cells across 5
 *     store spellings instead of 3.
 * (b) The ONE thing that moves the j-init INTO the delay slot is a DEPENDENCE
 *     of j on the STORED VALUE together with the store written FIRST:
 *       S_plain_frome_sbj -> addiu v0,1 / sh / mov.s / lwc1 / b / addiu s1,v0,-1
 *     which is retail's slot OCCUPANT -- but `lwc1 $f21` (best) sinks BELOW
 *     the store, so the store lands two words high (4 bad).  Pinning `best`
 *     at the access does not stop it.
 * (c) And the occupant can never be retail's word anyway: any dependence that
 *     evaluates to 0 is FOLDED (`e->f08 & 0`, `e->f08 * 0`, `1 - 1`), and any
 *     dependence that survives emits `addiu`/`sra`/`subu`/`xori`/`sltu` --
 *     never `daddu s1,zero,zero`.  The two requirements are contradictory.
 *
 * === RE-CONFIRMED WITH A DENOMINATOR (not inherited) ===
 * The index-first address form is necessary in BOTH loops, and the
 * mwcc-index-cast-defeats-cse axis runs both ways here: reverting loop 1 to
 * `&o->f2AC[i]` costs 7 bad, loop 2 to `&e->f00[j]` costs 12, both 15.  The
 * exit lattice is 2^N per site and every arm is worse: a shared `goto Lfail`
 * tail is 50 bad, two separate `if` guards 10, `!(a && b)` 4.
 *
 * Generators build/fg56/s56/mk56_0450{,b}.py; logs build/fg56/logs/
 * s56_z0450.txt, s56_w0450.txt, s56_prag0450.txt.  Full detail:
 * memory levers.d/factory-session56-levers.md.
 ==================================================================== */
/* ====================================================================
 * SESSION 52 (2026-09-03), tag fg52 (secondary lane; 005050c0 CLOSED this
 * session on a STORE'S ALIAS CLASS -- `extern const` + section attribute lets
 * the scheduler move a gp store).  STILL 2 / 409c28db0188, re-derived with
 * the arming pair 005069e0 = MATCH and 005032d0 = 7 / d7c9a6c54435.  The
 * same axis on THIS unit's `e->f08` store is INERT: `const Ent *e` with all
 * three stores through `*(s16 *)&e->f08` (Q1), a const cast on the first
 * store only (Q2), and `Ent *__restrict e` (Q4) are all 409c28db0188 -- the
 * const alias class is OBJECT-based (a declared const global), not carried
 * by a pointee type or restrict.  `if (j < n) do {...} while (j < n)` (P1)
 * = 96 w / fc19daef8ca1 (+2, beq=3).  Logs build/fg52/logs/s52_0450_b1.log.
 ==================================================================== */
/* ====================================================================
 * SESSION 49 (2026-09-03), tags fg49/fg49b/fg49c/fg49k.  Board unchanged 400/409 = 97.80% / 91.88%.  Baseline RE-DERIVED at start; arming pair held in EVERY scoring run (005069e0 = MATCH / 1a0e9c68216b, 00509f10 = bad 11 / 977182cbe9b7); every batch carried a cmp-verified identity arm AND a recorded-live delivery cell that reproduced its recorded md5.  Full detail: memory levers.d/factory-session49-levers.md; arms build/fg49/arms/s49/, generators build/fg49/s49/, logs build/fg49/logs/s49_*.log.
 *
 * === factory_FactoryBeltTrimPreview_500450: STILL 2 / 409c28db0188.  Seven more cells on the pre-header delay slot, ALL NULL ===
 * `j = 0; e->f08 = j + 1;` INERT (folded); `for (e->f08 = 1, j = 0; ...)` and `for (j = 0, e->f08 = 1; ...)` INERT
 * (the comma-form for-init is normalised like the statement forms -- fifth and sixth permutations to give one object);
 * `s16 j;` 08947337bb73 98 w (+4); store before `best = D_0047D1EC;` 1a7e720f7a68 5 (= s23's regression).
 * Delivery control s37 G1 reproduced 92255b97b41d / 2.  C++ (whole file extern "C"): BYTE-IDENTICAL.
 * ==================================================================== */
/* ====================================================================
 * SESSION 37 (2026-09-02), lane fg37f.  Board 393 -> 396/409 = 96.82% count,
 * 120,424/134,224 = 89.72% bytes.  Arming pair held in EVERY scoring run:
 * factory_FactoryStep_5069e0 = MATCH, factory_FactoryRectFrameCorner_509f10 = bad 11 / md5 977182cbe9b7.
 * "INERT" below means the arm's object md5 EQUALS this unit's baseline md5.
 *
 * === factory_FactoryBeltTrimPreview_500450 (14 cells, baseline 409c28db0188, 2 bad) === NO MOVE
 * G1 `e->f08 = 1; j = e->f08 - 1;` (a memory dependence of j on the store) -- 92255b97b41d, 2 bad, exact length. DUMPED: mwcc forwards the stored 1 and emits `addiu $17,$2,-1` BEFORE the branch and STILL sinks the `sh` into the delay slot. The dependence lands on the REGISTER $2, not on the store.
 * G2 `j = e->f08 * 0;` -- INERT 409c28db0188 (folded away)
 * G3 `j = 1 - e->f08;` -- b6160ef0f618, 2 bad, exact length (second new object, identical defect)
 * G4 `j = *(volatile s16 *)&e->f08 - 1;` -- 4dba6da4e8ab, LENGTH-BREAKING len 0x17c vs 0x178 (+1 word)
 * G5 store then `for (j = 0; j < e->f06; j++)` -- INERT 409c28db0188
 * G6 same + `j` declared FIRST -- INERT 409c28db0188
 * G7 `j` declared FIRST, base statement order -- INERT 409c28db0188
 * G8 `j` declared LAST -- INERT 409c28db0188
 * G9 ONE counter `i` shared by BOTH mutually exclusive loops (s33 region-sharing) -- INERT 409c28db0188
 * G10 `s64 j;` -- ba0e08827bf3, LENGTH-BREAKING len 0x180 vs 0x178 (+2 words)
 * H1 s35 opener lever OUTSIDE the triple: `best = D_0047D1EC;` hoisted above the SECOND call -- 9601a9415d4f, 8 bad
 * H2 `best = D_0047D1EC;` hoisted above BOTH calls -- 100ff89ae4ad, 10 bad
 * H3 `e->f08 = 1;` hoisted BETWEEN the two calls -- 12ae5a3cf66e, 9 bad
 * => the header's named open axis ("a DEPENDENCE that forces the store to be scheduled ahead of j = 0") is now CLOSED: three dependence spellings give three objects and the `sh` sinks into the slot in all of them. The loop-header shape, the counter's declaration position, region sharing and the opener-outside-the-triple axis are all now measured too. Every register is already retail's; only the delay-slot pick is wrong.
 *
 * === INHERITED, NOT RETESTED this session (do not read these as session-37 measurements) ===
 * * the 16 volatile access-site pins across 00500450 / 004fe500 / 004edef0 / 004ee070 from s36 (all inert except 00500450's o->f2AC pin at 7 bad) -- not re-run.
 * * 004f0f30's 15 multiply spellings, its r->f16 pin (14) and its r->f14 * (vol)r->f08 pin (4) from s36 -- not re-run.
 * * 004fe500's s23 guard-shape battery (two ifs 10, split + d >= a->f64 10, else-if chain 8, !(a && b) 6, d >= a->f64 alone 6, goto-fail 32/33, goto-into-second-guard byte-identical) -- not re-run.
 * * 00500450's s23 statement-order battery on the {best, j = 0, store} triple -- not re-run; H1/H2/H3 above extend it OUTSIDE the triple for the first time.
 *
 * === NEW GENERAL LEVER (carry it off this unit) ===
 * A NARROWING TYPE CONVERSION IS NOT FORWARD-SUBSTITUTED, A PLAIN COPY IS. When a residue is "both objects EMIT the copy `daddu rD,rS,$0` but ours reads rS at the use and retail reads rD", widen the SOURCE variable one step (s32 -> s64) so the assignment becomes a narrowing conversion. It closed 004edef0 in one token after s33 had bounded the axis as "the two copy directions are complementary". BOUNDARY, measured the same run: the WIDENING direction (s16 source -> s32 dest) is length-breaking, and the instrument does NOT transfer to a multiply operand-order residue (004f0f30, 4 cells, the known 4-bad object) or to a loop counter (00500450 G10, +2 words). Screen for it with scan.py: the tell is a SINGLE callee-saved substitution that explains 100% of the bad words with the load and the copy both already byte-correct.
 *
 * === NEW GENERAL LEVER #2 ===
 * DO NOT WRITE THE EXIT SHAPE INTO THE C WHEN ONE SIBLING ARM ALREADY HAS ONE. mwcc converts a fall-through exit into the explicit-return form (`b epilogue` + the return constant duplicated into the delay slot) when the SIBLING arm of the same if/else carries a source-level `return`. Deleting the sibling's `return` -- where it is semantically free because the arm is the last statement of its enclosing block -- makes mwcc re-derive BOTH exits, and it reproduces retail's asymmetric split (one chained, one plain) by itself. Closed 004ee070. SCREEN: our object has one MORE chained exit than retail while all the other exits of the same function are byte-correct with empty delay slots. NEGATIVE BOUND: it does not transfer to 004fe500 (F4, 32 bad) because there the shared return block is INLINE between the guard and the body, and making the exit a fall-through RELOCATES it.
 ==================================================================== */

#include "types.h"

/* SESSION 23, lane fz23j -- 2 bad, EXACT LENGTH, UNCHANGED.  Two more cells on
 * the 0x00500518/0x00500520 delay-slot residue (retail sinks `j = 0` into the
 * pre-header `b`; ours sinks the `sh`):
 *  - `*(volatile s16 *)&e->f08 = 1;` -- an access-site volatile cast on the
 *    STORE.  INERT, byte-identical: mwcc still sinks the store into the delay
 *    slot, so a volatile store is NOT pinned against delay-slot motion here.
 *  - source order `j = 0; best = D_0047D1EC; e->f08 = 1;` (loop init FIRST)
 *    -- INERT, byte-identical.  That is the FOURTH source permutation of the
 *    three statements to give the same object.
 *  - source order `j = 0; e->f08 = 1; best = D_0047D1EC;` (best LAST) -> 5 bad:
 *    it drags the `lwc1 $f21` down past the addiu and the mov.s.  Do not.
 * The scheduler fully NORMALISES the {best, j = 0, store} triple, so no source
 * order can reach retail.  The lever must be a DEPENDENCE that forces the
 * store to be scheduled ahead of `j = 0`, or a different loop-header shape.
 */

/* SESSION 23, lane fz23a: still 2 bad, EXACT LENGTH.  ONE MORE MEASURED NULL:
 * swapping the two statements to `j = 0; e->f08 = 1;` (store LAST in source)
 * is BYTE-IDENTICAL to `e->f08 = 1; j = 0;`.  mwcc's scheduler normalises the
 * pair, so the pre-header order is NOT a source-order axis; combined with the
 * already-recorded `for` vs `j=0; while` null and the 2->5 regression from
 * hoisting the store above `best`, all three source orders of these three
 * statements are now measured and give two objects, neither of them retail's.
 */

/* RESIDUE (2 bad): 0x00500518/0x00500520 hold `sh $2,0x8($16)` (e->f08 = 1) and
 * `daddu $17,$0,$0` (j = 0) in SWAPPED order.  Retail emits the store then fills
 * the pre-header `b`'s delay slot with j=0; ours sinks the STORE into the slot.
 * INERT: `for (j=0;...)` vs `j = 0; while (...)`.
 * REGRESSED 2 -> 5: moving `e->f08 = 1;` above `best = D_0047D1EC;`.
 * MEASURED POSITIVES this round (20 -> 2): index-first address arithmetic
 * `(T *)(i * sizeof + (s32)base)` instead of `base[i].m` puts the scaled offset
 * in $2 and the base load in $3 (retail's colouring) in BOTH loops (-10 words);
 * folding the two `if (...) return 0;` guards into ONE `||` guard gives retail's
 * `bltzl -> epilogue` with the return value in the delay slot (-8 words).
 */

typedef struct Pt {
    s16 f00;
    s16 f02;
    s16 f04;
} Pt;                                           /* 6 */

typedef struct Ent {
    Pt *f00;
    u8  pad04[0x2];
    s16 f06;
    s16 f08;
    u8  pad0A[0x2];
} Ent;                                          /* 0xC */

typedef struct Obj {
    u8   pad000[0x2AC];
    Ent *f2AC;
    s16  f2B0;
} Obj;


/*rgp*/
/*rgp*/

s32 factory_FactoryBeltTrimPreview_500450(Obj *o, s32 idx, s32 x, s32 y)
{
    Ent *e;
    Pt  *pp;
    s32  i;
    s32  j;
    s32  t;
    f32  bx;
    f32  by;
    f32  best;
    f32  cx;
    f32  cy;
    f32  d;

    if (o->f2AC != 0) {
        for (i = 0; i < o->f2B0; i++) {
            Ent *ep = (Ent *)(i * 12 + (s32)o->f2AC);
            ep->f08 = ep->f06;
        }
    }
    if (idx < 0 || o->f2B0 <= idx) {
        return 0;
    }
    e = &o->f2AC[idx];
    bx = factory_FactoryFineGridCellCenterX_5037c0(o, x);
    by = factory_FactoryFineGridCellCenterZ_503790(o, y);
    best = 3.402823466e+38f;
    e->f08 = 1;
    j = 0;
    while (j < e->f06) {
        pp = (Pt *)(j * 6 + (s32)e->f00);
        t = pp->f02;
        cx = factory_FactoryFineGridCellCenterX_5037c0(o, pp->f00);
        cy = factory_FactoryFineGridCellCenterZ_503790(o, t);
        d = (cx - bx) * (cx - bx) + (cy - by) * (cy - by);
        if (d < best) {
            best = d;
            e->f08 = j;
        }
        j++;
    }
    e->f08 = e->f08 + 1;
    return 1;
}
