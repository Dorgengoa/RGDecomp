/* rgp:protos */
#define RGP_SELF_factory_FactoryRectFrameDraw_50a4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* ** SESSION 40 (2026-09-02), tag fg40: CLOSED, BYTE-IDENTICAL, EXACT LENGTH.
 * 13 -> 6 -> 7 -> MATCH in one armed run (005069e0 = MATCH, 00509f10 = bad 11
 * / md5 977182cbe9b7 in the SAME dv_osbuild invocation).  Object md5
 * c254e3f836e2, reproduced twice in that run (J3 and J6 are the same object).
 *
 * ** THE LEVER: THE DECLARED PARAMETER ORDER OF A PROTOTYPE SETS ARGUMENT
 * EMISSION ORDER, AND INTERLEAVING INT WITH FLOAT PARAMETERS IS
 * REGISTER-NEUTRAL ON THIS ABI.**  Integer arguments fill a0-a3,t0-t3 and
 * float arguments fill $f12-$f19 from two INDEPENDENT counters, so moving a
 * float ahead of an int in the declaration cannot change which register any
 * argument lands in -- it changes ONLY the order mwcc emits the setup moves.
 * Retail's two callees take their trailing INTEGER parameters AFTER all their
 * FLOAT parameters; ours declared ints-then-floats, so mwcc emitted the whole
 * integer group first.  Writing the prototypes as retail declared them (and
 * permuting the eight call sites to match) reproduces retail's interleave at
 * every call site.  This is EXACTLY the defect the s34 header named -- 'retail
 * INTERLEAVES the mov.s float moves with the daddu integer moves and ours
 * emits the integer group first' -- and it is why ~120 recorded cells (s34's
 * 351-cell pairwise decl axis, s35's 109 schedule cells, the 92-cell knob
 * sweep) all read INERT: EVERY ONE OF THEM HELD THE PROTOTYPE FIXED.
 *
 * Decomposition, all in the armed run: 00509f10's prototype alone 13 -> 6;
 * 0050a180's alone 13 -> 7; both -> MATCH.  The DEFINITION's own parameter
 * order is INERT (13, byte-identical to baseline) -- only the CALLEE
 * prototypes matter, so it is left as retail's C would most plainly read.
 * See [[factory-session40-levers]].
 *
 * ** THE DEFINITION IS WRITTEN INTS-LAST TOO.**  Its own parameter order is
 * codegen-INERT here (measured: 13, byte-identical to the ints-first
 * baseline), so this unit alone cannot evidence it -- but its CALLER
 * factory_FactoryDraw_50a710 can, and there the ints-last declaration is the one
 * that reproduces retail (548 -> 95 bad, exact length).  So ints-last is the
 * evidenced signature and both files now agree on it.
 */


/* factory.bin overlay, 0x0050A4C0 -- 147 words, EXACT LENGTH, 13 bad
 * (SESSION 34 took it 57 -> 13; it had never been ground before).
 *
 * THE AXIS IS FPR DECLARATION ORDER, AND IT NEEDS PAIRWISE SWAPS.
 * [[mwcc-fpr-decl-order-highest-first]] holds here, but a single-relocation
 * hill climb bottoms out at 22 and calls the family dead: every single move of
 * `E` and every single move of `C` from the 22-bad order is WORSE (26..53),
 * while SWAPPING THE TWO is 22 -> 13.  All 36 pairwise swaps were then swept
 * again at 13 and none improves.  Sweep order for this class:
 *   whole-list single relocations (build/fg34/greedy.py) -> statement order
 *   -> ALL PAIRWISE SWAPS (build/fg34/pairswap.py) -> repeat.
 * Landed path 57 -> 54 (C last) -> 50 (D) -> 47 (B) -> 46 (E) -> 45 (t2)
 * -> ... -> 38 -> 37 (q2/t2 statement swap) -> 32 -> 27 -> 22 -> 13 (E<->C).
 *
 * ONE STATEMENT-ORDER CELL PAID: `q2 = q + E;` BEFORE `t2 = t - E;` (37 from
 * 38, and it unlocked three more decl cells).  MEASURED WORSE at 13, do not
 * re-run: swapping A/B (15), swapping s2/u2 (37), swapping q2/t2 back (59),
 * hoisting C into the A/B block (22), hoisting D (32), sinking C to just
 * before D (21), `E = 2.0f * p;` at the top (100), s2/u2 hoisted (LENGTH).
 * The tail decls q2/s2/u2 are INERT at every slot (one object) -- they reuse
 * registers their sources vacate, so they are not in the allocation list.
 *
 * ! RESIDUE, 13 words, and EVERY REGISTER NOW MATCHES RETAIL
 * (v=$f20 u=$f21 s=$f22 p=$f23 A=$f24 t=$f25 E=$f26 B=$f27 D=$f28 C=$f29
 * q=$f30, and t2/q2/s2/u2 reuse t/A/s/u exactly as retail does).  What is
 * left is PURE SCHEDULING of the argument setup -- retail INTERLEAVES the
 * `mov.s $f1x` float moves with the `daddu a3/t0/t1` integer moves and ours
 * emits the integer group first:
 *   0x0050A578  retail f14,f15,[jal],f13-in-slot   ours f13,f14,[jal],f15
 *   0x0050A5C8  retail f12,t0,f13,t1,f14           ours t0,t1,f12,f13,f14
 *   0x0050A650  retail f17 then f16                ours f16 then f17
 *   0x0050A674  retail a3,f12,t0                   ours a3,t0,f12
 * Note the FIRST call (0x0050A548) already has retail's f14,f15,[jal],f13
 * order, so the axis is not a global knob -- it is which float value is ready
 * last.  Closing this needs a SCHEDULE lever, not another ordering sweep.
 */

/* ** SESSION 35 (2026-09-02): STILL 13, EXACT LENGTH.  109 NEW MEASURED CELLS,
 * ONE OBJECT.  The residue is confirmed to be SCHEDULE ONLY and the whole
 * "reshape the source" family is now closed on it.
 *
 * ★★ THE RESIDUE IS A SHAPE THAT OCCURS NOWHERE ELSE IN THE PROJECT.  Screen
 * (build/fg35/findsched3.py): a `jal` whose DELAY SLOT is `mov.s $fD` while the
 * argument-setup run before it already emitted a `mov.s $fE` with E > D.  Over
 * ALL 2,284 overlay units, merged and open, that fires SIX times -- FIVE of
 * them inside this function, and exactly ONE in a byte-identical unit,
 * normal_ShopMenuBuyListOpenState_50e740 @0x0050E93C.  That one is a DIFFERENT mechanism (one
 * value feeding two float slots: mwcc materialises it into the LOWEST slot and
 * the copies come out in SOURCE-register order, `mov.s $f15,$f12` then
 * `mov.s $f14,$f13`), so it does not transfer -- here all four args are
 * distinct values.  ⇒ THERE IS NO PRIOR ART FOR THIS SHAPE IN THE PROJECT.
 *
 * ★ THE ARGUMENT EXPRESSIONS ARE NOT WRITTEN INLINE.  The natural reading of
 * this function is a rounded rectangle with the edge expressions at the call
 * sites; written that way (no A/B/C/D/E/t2/q2/s2/u2 locals at all, CSE doing
 * the work) it is EXACT LENGTH and 58 bad -- and the emitted SCHEDULE at every
 * call site is IDENTICAL to the baseline's, word for word.  So inlining moves
 * the register map ONLY.  The named-local form is right; the schedule is not
 * reachable from argument-expression shape.
 *
 * MEASURED INERT at 13 -- all NINE byte-identical to the baseline object
 * (md5 fff3e99ead2a): a fresh copy local for the sinking value at call 1
 * (`B1 = B;`), at call 2 (`C1 = C;`), at both; fresh copies for the values that
 * must NOT sink (`v1 = v; A1 = A;`); the second-def split `C = q; C += p;`;
 * self-assigns `B = B;` and `C = C;`; a copy of the integer argument
 * (`d2 = d;`) at the two `daddu t0` transposition sites; and `u32` instead of
 * `s32` for BOTH callee prototypes' integer parameters.
 * WORSE / LENGTH-BREAKING: `B = t; B -= p;` is +1 WORD (⚠ note the asymmetry --
 * the same split on the ADD, `C = q; C += p;`, folds byte-identically, so a
 * second-def split is free on `+` and costs a word on `-`); hoisting `C` above
 * call 1 is 22, hoisting C and D is 31; inlining f13 at call 1 is 31, at call 2
 * is 40, at both 40.
 *
 * THE KNOB AXIS IS A NULL HERE.  Both polarities of all 46 codegen pragmas
 * (92 arms, build/fg35/knob.py) -- only THREE are live and all three break the
 * LENGTH: `schedule off`, `peephole`-family `opt_common_subs off`, and
 * `floatsp32 off`.  89 of 92 are byte-identical to the baseline.  This is the
 * one unit class the pragma memory nominates the sweep for (exact length,
 * delay-slot residue); it has now been run once and it is spent.
 */

/*rgp*/


/*rgp*/



void factory_FactoryRectFrameDraw_50a4c0(void *a, void *b, void *c,
                          f32 p, f32 q, f32 s, f32 t, f32 u, f32 v,
                          s32 d, s32 e)
{
    f32 A;
    f32 s2;
    f32 C;
    f32 D;
    f32 B;
    f32 E;
    f32 t2;
    f32 q2;
    f32 u2;

    A = u - p;
    B = t - p;
    factory_FactoryRectFrameCorner_509f10(a, b, c, 0, d, e, (float)p, B, v, A);
    C = q + p;
    factory_FactoryRectFrameCorner_509f10(a, b, c, 3, d, e, (float)p, C, v, A);
    D = s + p;
    factory_FactoryRectFrameCorner_509f10(a, b, c, 2, d, e, (float)p, C, v, D);
    factory_FactoryRectFrameCorner_509f10(a, b, c, 1, d, e, (float)p, B, v, D);
    E = 2.0f * p;
    q2 = q + E;
    t2 = t - E;
    factory_FactoryRectFrameEdge_50a180(a, b, c, d, e, (float)p, t2, A, q2, A, v);
    s2 = s + E;
    u2 = u - E;
    factory_FactoryRectFrameEdge_50a180(a, b, c, d, e, (float)p, C, u2, C, s2, v);
    factory_FactoryRectFrameEdge_50a180(a, b, c, d, e, (float)p, q2, D, t2, D, v);
    factory_FactoryRectFrameEdge_50a180(a, b, c, d, e, (float)p, B, s2, B, u2, v);
}
