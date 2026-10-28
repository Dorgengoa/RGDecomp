/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuTryLeaderChange_502250 1
#include "port/game_protos.h"
#line 1
/* === SESSION 93 (2026-09-22): 12 -> MATCH, exact 85 words.  s90's PARK IS
 * REFUTED, and its degree proof was sound but aimed at the wrong input.
 * THREE EDITS:
 *   1. the declaration list reordered to  w, o, e, r, i, n, ctx, best
 *   2. `u8 *n = (u8 *)func_3C2010(ctx->f18, 1, 1);`  with `i < (s32)n`
 *   3. `ctx = func_1FEDE0();  ctx = (Ctx *)(s32)ctx;`   (zero instructions)
 *
 * *** THE MECHANISM.  mwcc numbers vregs 32.. with the DECLARED LOCALS first,
 * in declaration order, then temps in IR order, and a local with exactly ONE
 * static def is PROMOTED into its defining temp, its declared vreg dying
 * ([[levers.d/mwcc-propagated-temp-colouring]]).  Here `i` (36) and `best`
 * (38) have two defs each and kept their vregs; `ctx` and `n` were single-def
 * call results and arrived as LATE TEMPS 41 and 45.  Simplify removes
 * ascending index inside a pass and select is that reversed, so the whole map
 * was fixed by 38 < 41 < 45 -- best=$18 ctx=$17 n=$16.  Retail is best=$16
 * ctx=$17 n=$18, i.e. idx(i) < idx(n) < idx(ctx) < idx(best), the exact
 * reverse -- and that is a DECLARATION-ORDER fact the moment the two webs stop
 * being promoted.  s90's "deg(best) headroom is 1, 40,000 bump vectors cannot
 * reach it" is correct AND irrelevant: no degree had to move at all.
 *
 * ** THE TWO UN-PROMOTION FORMS ARE NOT INTERCHANGEABLE (s93/g5.py):
 *   - a call returning s32 -> a POINTER local: the cast IN THE INITIALISER is
 *     enough (`u8 *n = (u8 *)f()`), because the propagator will not fold an
 *     integer->pointer cast.
 *   - a call already returning a POINTER: the initialiser cast FOLDS
 *     (`ctx = (Ctx *)(s32)func_1FEDE0()` reads 11, a new object but not a
 *     match).  It needs the SEPARATE second def, the round trip.
 * ** ARMING, and it retires every declaration deck this file has carried:
 *   - the declaration reorder ALONE is BYTE-IDENTICAL to base (4b320351) --
 *     s89's 42 arms were permuting DEAD vregs, exactly as s90 suspected.
 *   - `n` alone (order + pointer) 11; `ctx` alone at the old order 23.
 *     Only the three-edit cross matches.  [[two-edit-cross-beats-count-ranking]]
 * Everything below predates this session. */
/* === SESSION 90 (2026-09-22): STILL 12 BAD, and the residue is now a PARK
 * WITH A PROOF, taken from mwcc's OWN interference graph rather than from any
 * fit.  build/wf-normal/s90/{ra90,ral,rasweep,head,park,simp3}.py dump the
 * graph, the simplify/select list and the final colours out of the RUNNING
 * compiler under gdb (bg30/ra12.gdb, retargeted at NORMAL and at .c sources)
 * and replay the whole algorithm: select lowest-free 42/42 and the simplify
 * order reproduced EXACTLY on this unit.
 *
 * WHAT THE DUMP SAYS THE CARRIERS ARE.  Declared locals are numbered in
 * DECLARATION order from vreg 32 (dead ones skipped -- three unused locals
 * added at the front shift nothing), temps after them:
 *     w = 33   o = 34   i = 36   best = 38          (declared vregs)
 *     ctx = 41, n = 45                              (TEMPS -- their declared
 *     vregs 32 and 35 are DEAD, degree 0)
 * ctx and n are copy-propagated out of their declared vregs, so NO
 * declaration order can rank them: s89/d2's 42 arms were permuting two dead
 * nodes.  Only `best` and `i` are reachable from the declaration list, which
 * is exactly the three-regime behaviour s89 measured on `best` alone.
 *
 * THE ASK, EXACTLY.  Retail's map is produced by ONE select order --
 * best, ctx, n, i, o, w -- which needs simplify to remove {w,o,i,n} in one
 * pass, ctx in the NEXT and best in the one after.  On the dumped graph that
 * is deg(ctx) +3 AND deg(best) +4, and nothing smaller, on either coat.
 *   - ctx +3 IS reachable: `func_3C1600(ctx->f18, o->fC, 1)` with `w` dropped
 *     keeps ctx live to the end and takes it 29 -> 33 (s90/r1.py ctx_tail).
 *   - best +4 IS NOT.  best's degree 33 = 20 physical + 13 vregs, and of the
 *     28 vregs it does not already interfere with, 27 are DEAD (degree 0);
 *     the only live one is `r`.  HEADROOM 1, ceiling 34, the order needs 37.
 *   - park.py: 40,000 degree-bump vectors inside every node's payable bounds,
 *     retail's order reached ZERO times.
 * ==> PARKED at 12.  Only an edit that adds LIVE VALUES spanning `best` can
 * revive it, and that changes the word count.  Do not sweep orders, pragmas,
 * bindings or declaration lists on this unit again.
 * ⚠ two ARMED NULLS from this session's name-partition deck (s90/w1.py, the
 * one front-end input s58 leaves open): dropping `w` as a NAME is 15 bad
 * (20 at the b0 coat), `w` as its own statement 20/23, `w` assigned at the o
 * call 27/29, `o` renamed to `e` byte-identical, `w` hoisted and used
 * everywhere is ONE WORD SHORT.  The name partition is not the lever. */
/* === SESSION 89 addendum -- THREE MORE DATED, ARMED NULLS ON THE ctx<->n
 * TRANSPOSITION, all measured AT THE 12-BAD COAT:
 *  - s89/p2.py: the whole 68-name opt_* table x {off,on}, 136 arms.  ONE
 *    object except two length-wrong movers (`opt_common_subs off` +1 w,
 *    `opt_repositioncode on` -1 w).  Armed both ways: the bogus name reads
 *    == base, and the six value-taking names (opt_unroll_count,
 *    opt_full_unroll_limit, opt_unroll_instr_count, opt_pointer_analysis on,
 *    opt_generateconditionalassignments on) fail to compile = positive proof
 *    the table is looked up (probe-traps #139, the insect s64 arming recipe).
 *  - s89/d3.py: ALL SIX declaration orders of the trio {ctx, n, best} held
 *    CONTIGUOUS AT THE FRONT, x three tails (18 arms): ONE OBJECT, 16 bad,
 *    minus1=s0.  ==> on this unit declaration order is a POSITION effect on
 *    `best` ALONE, not an ORDER effect: the trio's internal order is inert,
 *    and so is every other local's slot (s89/d2, 42 arms).
 *  - s89/b1.py: the REGISTER-BINDING axis re-priced (s81/g1's board-wide null
 *    was taken at the 16-bad coat).  30 arms, armed twice (bogus pragma and
 *    `bind r2`, both == base).  r4..r15 and r20/r21 are byte-identical;
 *    `bind r3` is 17; r16..r19 cost +2 w and SHIFT the whole callee-saved
 *    assignment up one register WITHOUT changing the relative order
 *    (n < ctx < best in every cell).  The binding cannot transpose a pair.
 * ==> the ctx<->n / best<->n order survives every column this board has.
 * The allocator model (levers.d/mwcc-allocator-decompiled) reads the coats as
 *     base   select n,ctx,best  => creation best,ctx,n  (= SOURCE order)
 *     b0     select best,n,ctx  => creation ctx,n,best
 *     retail select best,ctx,n  => creation n,ctx,best
 * i.e. retail creates `n` FIRST and `best` LAST, which no declaration order
 * and no statement order on this unit produces.  The next arm has to change
 * the INTERFERENCE GRAPH or the COALESCING, not any order. */
/* === SESSION 89 (2026-09-22): 16 -> 12 BAD, exact 85 words.  ONE EDIT, on
 * the TAIL, and the residue is now a PURE two-way callee-saved transposition
 * (12 words, ours best=$18 n/o=$16, retail best=$16 n/o=$18).
 *
 * THE EDIT.  retail does not `return 1` / `return 0`; it MATERIALISES a 0/1
 * in $3 on three paths and converts at ONE merge point:
 *     68 beql $16,$2,L384 | 69 [annul] $3=0      <- r = 0, the TAKEN side
 *     70..73 call setup, jal func_3C1600, delay
 *     74 addiu $3,$0,1                           <- r = 1
 *     75 bnel $2,$3,L384  | 76 [annul] $3=0      <- and $3 IS the compare
 *                                                   operand, which is why r
 *                                                   stays caller-saved
 *     77 L384: sltu $2,$0,$3                     <- return r != 0
 * so the (previously unused) `s32 r` is a real variable and BOTH tests stay
 * statement-level `if`s.  Any `&&` or `== 1` in a VALUE context makes mwcc
 * materialise ARITHMETICALLY instead (xor/sltu, xori/sltiu) -- 20 bad, a
 * strictly worse object (s89/t1, 7 arms).
 *
 * ★ THE BRANCH-POLARITY RULE that took the last two words (s89/t5):
 *   mwcc branches AROUND the then-block, so the 2-word annulled-exit form
 *   (`beql` + the assignment in the annulled slot) is only available to the
 *   ELSE side.  `if (A) {r=0;} else if (B) {r=1;} else {r=0;}` puts r=0 on
 *   the FALL-THROUGH and costs 4 words for the first test (bnel | [annul]
 *   dup | b out | [delay] r=0) -- 86 words.  INVERT IT and the same object
 *   is 85 words and 12 bad:
 *       if (best != X) { if (f() == 1) r = 1; else r = 0; } else { r = 0; }
 *       return r != 0;
 *   Same family as levers.d/mwcc-or-operand-return-shapes' operand 1.
 *   `!(best == X)` is byte-identical to `best != X`.
 *
 * ★★ THE DECLARATION-ORDER COLUMN IS NOT NULL HERE -- s88 read it on the BAD
 * COLUMN and called it `3 objects, base best`.  Read on the REGISTER MAP
 * (s89/colmap.py, s89/csweep.py) it has FOUR objects and one of them puts
 * `best` in retail's $16:
 *     decl `s32 best;` FIRST  ->  best=$16@7 ctx=$18@8 n/o=$17@16 i=$19@18
 *     base (best 7th)         ->  best=$18@5 ctx=$17@8 n/o=$16@16 i=$19@18
 *     best 2nd/3rd/4th        ->  best=$19@4
 * i.e. best-first is on the RIGHT side of half the defect (idx 5/7/31 all
 * become retail's) and the transposition MOVES to ctx<->n.  It scores WORSE
 * (16 at this coat) and is still the better structural coat.
 *
 * ⚠⚠ THE CTX<->N PAIR IS THE WHOLE REMAINING ASK AND IT IS FENCED:
 *   s89/d2   42 arms, best pinned first, ctx and n through every slot: ONE
 *            object.  Declaration order moves `best` ONLY.
 *   s89/s1   11 structural arms (while/gt loop forms, n widths, !ctx, w
 *            hoisted, e retyped, o via e, n in the for-init, the f42D0 deref
 *            spelled twice): one mover and it is WORSE (n_inline_bound).
 *   s89/s2   optimization_level 0..4, `register` on each of the 7 locals,
 *            n as s16/u16, `i != n`: all inert on the pair.
 *   s89/p1   93 of the 136 opt_* x {off,on} arms: ONE object.
 *   s89/x1   best=-1 at every statement position x both decl coats: movers,
 *            all worse.  s89/x2: every tail shape x the b0 coat: inert.
 * CALIBRATION, and it is why this is hard: normal_FieldHudStep_4f56d0 is MERGED and
 * byte-identical with the SAME idiom (`q = func_1FEDE0()`, `n = ...`, a
 * func_3C2420 loop) and its map is n=$16 q=$17 i=$18 p=$19 -- mwcc's natural
 * answer for this shape is OURS.  retail's 00502250 inverts the pair against
 * descending first-def (ctx@8 -> $17, n@16 -> $18), so the lever is NOT
 * first-def and is not any of the columns above.
 * Everything below predates this session. */
/* === SESSION 88 (2026-09-22): STILL 16 BAD.  The DECLARATION-ORDER axis is
 * re-priced at this coat (s88/dsweep.py, 18 arms over the eight locals):
 * THREE objects, 16 / 19 / 21, base best.  Armed by the three movers.
 * bad3 reads the residue exactly and it is a clean TWO-WAY CALLEE-SAVED
 * TRANSPOSITION: ours best=$18 n=$16 o=$16, retail best=$16 n=$18 o=$18.
 * Under levers.d/mwcc-callee-saved-creation-order (LARGER first-def index
 * takes the LOWER register) retail's `best` must be created AFTER `n` -- and
 * s86/f1 already measured every source position of `best = -1` with the
 * colours REFUSING TO MOVE, so `best`'s vreg is not created at its statement.
 * The next arm has to move a CREATION, not a statement.
 * Everything below predates this session. */
/* === SESSION 86 (2026-09-22): STILL 16 BAD.  `best = -1` moved after ctx /
 * before n / after n / into the for-init / into an argument (s86/f1.py): all
 * WORSE (22-26) and the COLOURS DO NOT MOVE (best stays $18, n $16) -- only the
 * schedule does.  Reusing n / i / e as `o`'s variable (f2.py) is byte-identical
 * (webs are split per def-use).  Creation order is not this unit's axis. */
/* === SESSION 81 (2026-09-21, SOLO): STILL 16 BAD / 85 words.  THE NAMED NEXT
 * ARM IS BUILT AND IT IS NEGATIVE -- retire it.  Deck build/wf-normal/s81/e1.py.
 * s75 named it: "the load-result web here is `w`, and introducing it costs +2,
 * so the lever cannot be applied at exact length until a -2 partner that is not
 * a spelling change turns up."  The -2 partner has existed since s75 itself
 * (`if (func_3AE1A0(e))`, the bare flag test); s75 only ever crossed the +2
 * with the FLAT TAIL (-1) x `!= 0` (-1), never with the -2.  Built now:
 *     w_above x f_bare   85 words   69 bad
 *     w_below x f_bare   85 words   70 bad
 * Both exact length, both RE-COLOUR THE WHOLE UNIT -- the same signature as
 * s75's own 68-bad cross.  THREE independent exact-length crosses now say the
 * `w` load-result web is a DEAD AXIS here.  Do not re-open it.
 * NEW length halves measured: `func_3AE1A0(e) > 0` is -1 (a third -1, joining
 * s75's `!= 0`); `func_3AE1A0(e) & 1` is a NEW EXACT-LENGTH OBJECT at 19 bad.
 * `void *const D_00484454` is +2, confirming s80.
 * TWO BOARD-WIDE AXES ALSO RUN ON THIS UNIT AND BOTH ARE NULL HERE:
 *  * the INSECT-s95 REGISTER BINDING (build/wf-normal/s81/g1.py,
 *    [[levers.d/mwcc-register-binding-exit-seed]]): `bind r3` is a new
 *    exact-length object at 17 bad, r4-r8/r12/r20 byte-identical, r16-r19 +2.
 *    Armed two ways (bogus name == base, `bind r2` == base).
 *  * the [[levers.d/caller-saved-colour-follows-scheduler]] two-arm probe
 *    (h1.py): `optimization_level 2` + `opt_propagation off` + `schedule on`
 *    reproduces this unit's base BYTE-IDENTICALLY (6d55d46c).  That is the
 *    lever's POSITIVE signature: the level knob changes only the SCHEDULE
 *    here, so the colours are a scheduler consequence and no source-order
 *    edit can reach them.  `optimization_level 3`/`4` == default. */
/* === SESSION 75 (2026-09-21, SOLO): STILL 16 BAD / 85 words.  No move, but
 * TWO NUMBERS THIS FILE RELIES ON ARE NOW WRONG AND ARE CORRECTED HERE, and the
 * unit's cross-half ledger is re-priced at the s66 coat.  Sweeps:
 * build/wf-normal/s75/d1.py, d2.py.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  RE-PRICED #1 -- "a cached `World *w = ctx->f18;` local is 2 WORDS SHORT".
 * That is the s24 note and it is what parked the unit.  At this coat the cached
 * world for the LOOP (`w = ctx->f18;` above `n = func_3C2010(w,1,1)` with the
 * loop reading `func_3C2420(w, i)` and the guard reading `w->f42D0`) is
 * **+2 WORDS** (0x15c vs 0x154), not -2, in both placements (above `n`, and
 * between `n` and the loop -- two distinct objects).  The sign is the opposite
 * of the recorded one.  [[levers.d/reprice-retired-units]].
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  RE-PRICED #2 -- s24 records the flat form `r = (func_3C1600(...) == 1);`
 * as THE BASELINE and the branchy `r = 1; if (...) r = 0;` form as +3.  At this
 * coat the flat form is **-1 WORD** (0x150) against the installed `||`-guard
 * tail, and the branchy form is +2 (0x15c).  So the tail is not a settled
 * choice; it is a -1 CROSS HALF.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¹ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦ÃƒÂ¢Ã¢â€šÂ¬Ã…â€œÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ NEW -1 / -2 HALVES FOUND (d2.py), all on the roster scan's flag test:
 *      `if (func_3AE1A0(e) != 0)`   -1 w        `if (func_3AE1A0(e))`   -2 w
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  but `== 1` is RETAIL'S spelling -- retail emits `andi $3,$2,0xFF / addiu
 * $2,$0,1 / bnel $3,$2`, i.e. it really does compare against 1 -- so these are
 * length levers bought by writing something retail did not write.  Use them
 * only as ballast in a cross, never as a fix.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¹ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦ÃƒÂ¢Ã¢â€šÂ¬Ã…â€œÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ THE ONE EXACT-LENGTH CROSS BUILT FROM THEM IS A DISASTER, WHICH IS ITSELF
 * THE RESULT: w2(+2) x flat tail(-1) x `!= 0` flag(-1) lands at exactly 85
 * words and scores **68 bad** -- the whole unit re-colours.  Every other cross
 * of the three collapses to 0x158 (+1) on the base object.  BYTE-IDENTICAL to
 * base (1efe3ebc), i.e. dead axes: `(o->f4B4 & 1) != 0`, `!func_3AE200(o,0)`,
 * `o->fC` for `(o->fC != 0)`, `(w->f42D0 & 1) != 0`, `return r;` for
 * `return r != 0;`, `best = ~0;` for `best = -1;`, `best = (s32)i;`, and
 * commuting the `best == normal_BtlChgPageGetMember_505f90(...)` compare.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¹ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦ÃƒÂ¢Ã¢â€šÂ¬Ã…â€œÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ THE s75 ACCESS-FORM LEVER WAS AIMED AT THIS UNIT AND MISSES ON LENGTH.
 * normal_BtlChgMenuOpen_4fa3c0 closed six words this session by turning its long-lived
 * pointer web from a CALL RESULT into a LOAD RESULT, which is exactly the shape
 * of this unit's residue (`best` is a CONSTANT web at $18 where retail has $16;
 * {n,o} are CALL RESULTS at $16 where retail has $18 -- ours puts the
 * non-call-result web HIGH and the call results LOW, the same pattern
 * 004fa3c0's old coat had).  The load-result web here is `w`, and introducing
 * it costs +2, so the lever cannot be applied at exact length until a -2
 * partner that is not a spelling change turns up.  That is the named next arm.
 */
/* === SESSION 66 (2026-09-20, SOLO): 38 -> 16 BAD at exact length, on a
 * TWO-EDIT CROSS neither half of which helps alone ([[two-edit-cross-beats-count-ranking]]).
 *   half A (-1 word alone, LENGTH-WRONG):  fold guard 2 and guard 3 into ONE
 *     `||` chain with `w = ctx->f18` assigned INSIDE the chain's last operand,
 *     so the short-circuit puts the `lw $17,0x18($17)` exactly where retail has
 *     it.  This is [[mwcc-branch-likely-duplication]]'s FACTORY-s41 fix: mwcc
 *     branch-THREADS ONLY THE FIRST PREDECESSOR of a shared `return 0` block,
 *     so the offending test needs a predecessor AHEAD of it IN THE SAME CHAIN.
 *     After it the whole guard region is byte-exact except register names.
 *   half B (+1 word alone):  the tail as ONE `||` guard returning 0 with a
 *     bare `return 1;` after it, NOT `r = A && B; return r;`.
 * => TWELVE of the 16 remaining words are the ONE callee-saved transposition
 * s53 named: retail best=$16, ctx/w=$17, {n,o}=$18, i=$19 -- PURE FORWARD
 * creation order, lowest free.  Ours is best=$18, {n,o}=$16 with ctx and i
 * AGREEING.  0x2264/0x226C (prologue sq vs `addiu $16,$0,-1` in the jal delay
 * slot), 0x2290, 0x22CC, 0x22D4, 0x22F4, 0x22F8, 0x22FC, 0x2318, 0x233C,
 * 0x2360, 0x2368 are all that one fact.
 * => THE OTHER FOUR are one fact too: 0x2364 / 0x237C / 0x2380 / 0x2384.
 * Retail accumulates the answer in $3 (0 sunk into BOTH likely delay slots,
 * `addiu $3,$0,1` AFTER the call sharing the compare's constant) and
 * normalises with `sltu $2,$0,$3` at a shared join; we return 0/1 in $2.
 * WARN THE ACCUMULATOR FORM IS A FLAT +1 WORD over 9 spellings (r=1 before the
 * ||, if/else, goto-to-join, else-if, and `!= r` to share the constant with
 * the compare): 0x158 every time.  The `return 0; ... return 1;` form is a
 * 6-spelling attractor at 16.  Do not re-run either list.
 * MEASURED NULL this session (build/wf-normal/s66/gen2250{,b..j}.py):
 *  - 30 cells of DECLARATION ORDER x `best = -1;` POSITION on the NEW coat.
 *    WARN declaration order is NOT inert here any more (s53 said it was):
 *    `best` declared before `void *e` is 21, at index 5+ it is 16.  Nothing
 *    swaps the pair; every `best = -1;` position below statement 0 is +6.
 *  - `&&`-as-a-VALUE (9 spellings incl. ternary, `!= 0` outer, `r = A && B`)
 *    is ONE object at 20: a value-context `&&` MATERIALISES operand 1
 *    (`xor/sltu` then `beqz`) where a control-context `||` BRANCHES it.
 * NEXT: the transposition is the whole unit now.  [[mwcc-callee-saved-creation-order]]
 * says the only lever is creation order, and retail's map is pure forward --
 * find what makes mwcc number OUR webs out of order, not another spelling.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* === SESSION 53 (2026-09-08, SOLO): STILL 38 / 85.  18 arms, no move, but the
 * residue is now NAMED and two of the s24 header's three "defects" are RETIRED.
 * READ THIS BEFORE SPENDING ANOTHER ARM (build/wf-normal/s53/a_502250{,b}.py).
 *
 * WHAT THE RESIDUE ACTUALLY IS: a CALLEE-SAVED TRANSPOSITION, `s2>s0` five
 * times.  The map is retail best=$16, ctx=$17, n/o=$18, i=$19 against our
 * n/o=$16, ctx=$17, best=$18, i=$19 -- ctx and i AGREE and only {best} and the
 * {n, o} web swap.  Everything else in this unit is placement noise around it.
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  THIS UNIT IS A COUNTEREXAMPLE TO [[mwcc-callee-saved-creation-order]]'s
 * 69.7% rule, and it is OUR object that OBEYS it: best's first def is at index
 * 5-7, n's at 16, so "LARGER first takes the LOWER register" predicts n=$16 --
 * which is what WE emit and retail does not.  Consistent with that, moving
 * `best = -1;` DOWN the source (the [[mwcc-vreg-creation-source-position]]
 * lever) makes it WORSE at every position and never swaps the pair:
 *   after `n = func_3C2010(...)` 47, after `ctx = func_1FEDE0()` 44,
 *   after the ctx null guard 46.  Declaring `best` LAST is BYTE-IDENTICAL
 *   (declaration order is inert here).
 *
 * RETIRED, both by measurement:
 *  - "defect 2, the guard-2 fold": `if (!func_3AE200(o, 0))` and an
 *    `if (... != 0) {} else { return 0; }` inversion are BOTH BYTE-IDENTICAL
 *    to the baseline.  s38 only ever tried the negation inside a bundle; alone
 *    it is a clean null, so the fold is NOT chosen by the guard's spelling.
 *  - "defect 3, the branchy tail": writing retail's exact shape
 *    (`r = 0; ... r = 1; if (func_3C1600(...) != 1) r = 0; ... return r != 0;`)
 *    is +3 WORDS (0x160 vs 0x154), with or without the guard inversion, with
 *    or without the else.  s24's "+3" still holds at this coat.  The +1/-1
 *    pairing the s24 header proposed is therefore NOT a pairing: the guard
 *    fold costs 0 and the tail costs +3.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¹ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦ÃƒÂ¢Ã¢â€šÂ¬Ã…â€œÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Â ÃƒÂ¢Ã¢â€šÂ¬Ã¢â€žÂ¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€¦Ã‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¦ ONE LIVE CROSS HALF.  Retail 0x00502328 `lw $17,0x18($17)` OVERWRITES ctx
 * with `ctx->f18` and reuses it at 0x0050236C `daddu $4,$17,$0`, so the world
 * IS cached -- but LATE, at the second guard, not at the top (s24 measured the
 * top cache 2 words SHORT and concluded retail does not spell it as a local;
 * that conclusion is WRONG, it is just a later local).  Splitting the guard as
 *     if (o->f4B4 & 1) return 0;
 *     w = ctx->f18;
 *     if ((w->f42D0 & 1) && (o->fC != 0)) return 0;
 * with `func_3C1600(w, ...)` holds 38 at EXACT length but drops the census
 * 10 -> 8 on a NEW object (fd348ab2; 4b45c7c2 with the guard inversion).
 * That is a cross half ([[two-edit-cross-beats-count-ranking]]) -- it needs a
 * partner that reaches the best/n colouring, which nothing here does.
 */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `E_ifelse_L89_els` from the seed/else deck (mkelse31.py)
 *   before: 85 words, 38 bad   after: 85 words, 38 bad   (retail 85 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* PARKED (session s24, tag n24): now at the RIGHT LENGTH (0x154), 38 bad.
 * Was 0x164 (4 words long) for two prior sessions.  The lever that fixed the
 * LENGTH was GUARD POLARITY on the tail plus a FLAT compare:
 *     r = 0;
 *     if (best != normal_BtlChgPageGetMember_505f90(D_00484454))
 *         r = (func_3C1600(ctx->f18, o->fC, 1) == 1);
 * (the old `if (best == ..) r = 0; else { r = 1; if (.. != 1) r = 0; }` kept
 * r LIVE ACROSS the call in $17, a CALLEE-SAVED register, and shared it with
 * the third argument -- retail keeps r in $3 and materialises it AFTER the
 * call, sharing the constant 1 with the compare.)
 *
 * THREE localized defects remain; the length is a net of +1 and -1 so a fix
 * to either one alone BREAKS the length -- they must land together:
 *   1. prologue schedule: ours `jal sq`, retail `sq jal` (same count).
 *   2. @00502310, ours +1: the `func_3AE200(o,0)==0` guard.  Retail FOLDS the
 *      `return 0` into a likely branch straight to the epilogue
 *      (`beql $2,$0,.L00502388 / daddu $2,$0,$0`); ours emits
 *      `bnezl`+`b`+`move v0,zero` as its own block.  mwcc folds exactly ONE of
 *      the two `return 0` guards and shares a block for the other -- retail
 *      folds THIS one and shares for guard 3, ours does the opposite.
 *   3. tail, ours -1: retail is BRANCHY
 *      (`addiu $3,$0,1 / bnel $2,$3,join / daddu $3,$0,$0`); ours is
 *      branchless (`xori`/`sltiu`).  The branchy spelling costs +3, the
 *      `== 1` flat form and the `? 1 : 0` ternary are the SAME OBJECT.
 *
 * MEASURED NULL, and it is the reason this is parked: retail keeps
 * ctx->f18 in $17 across the normal_BtlChgPageGetMember_505f90 call and passes it to
 * func_3C1600 as `daddu $4,$17,$0`, but a cached `World *w = ctx->f18;`
 * local is 2 WORDS SHORT in every combination (4 arms, three objects) --
 * with w the exact length is unreachable, so retail is NOT spelling it as a
 * local.  Next lane: re-derive the VARIABLE STRUCTURE (is ctx itself the
 * world after the guard?) before spending more arms on the tail.
 *
 * SESSION 38 (n38h): tried the three-defect fix combo -- `!func_3AE200(o, 0)`
 * negation for the guard-3 fold plus an explicit `if (==1) r=1; else r=0;`
 * branchy tail instead of the comparison-expression assignment.  MEASURED
 * NULL as a bundle: length regresses to 86 words (+1) with both combined.
 * Isolated `return r;` (dropping the redundant `!= 0`) ALONE is a clean
 * NULL -- byte-identical to the `return r != 0;` baseline.  Did not isolate
 * the guard negation or the branchy-tail changes individually (budget) --
 * next lane could try each alone before assuming both are guilty.
 */
#include "types.h"
/* normal 0x00502250 -- scans the active roster for the first entity flagged
 * "targetable" (func_3AE1A0 bit 0), then validates the current handle:
 * skips if its own flags bit or the world's flag bit (with a live count)
 * blocks it, otherwise reports whether it changed since the last pick and
 * whether func_3C1600 confirms it. */

typedef struct World { u8 pad000[0x42D0]; u8 f42D0; } World;
typedef struct Obj   { u8 pad000[0xC]; s32 fC; u8 pad010[0x4B4 - 0x10]; u8 f4B4; } Obj;
typedef struct Ctx   { u8 pad000[0x18]; World *f18; } Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00484454;      /* gp - 0xD1C */

s32 normal_BtlChgMenuTryLeaderChange_502250(void)
{
    World *w;
    Obj *o;
    void *e;
    s32 r;
    s32 i;
    u8 *n;
    Ctx *ctx;
    s32 best;

    best = -1;
    ctx = ((Ctx *)GetGameData_1fede0());
    ctx = (Ctx *)(s32)ctx;
    if (ctx == 0) {
        return 0;
    }
    n = (u8 *)PartyCountMembers_3c2010(ctx->f18, 1, 1);
    for (i = 0; i < (s32)n; i++) {
        e = PartyGetMemberChara_3c2420(ctx->f18, i);
        if (e == 0) {
            return 0;
        }
        if (CharaIsPartyLeader_3ae1a0(e) == 1) {
            best = i;
        }
    }
    o = ((Obj *)PartyGetSlotChara_3c2fb0(ctx->f18, normal_BtlChgPageGetMember_505f90(D_00484454)));
    if (o == 0) {
        return 0;
    }
    if (CharaCanBeLeader_3ae200(o, 0, 0, 0) == 0 || (o->f4B4 & 1) ||
        (((w = ctx->f18)->f42D0 & 1) && (o->fC != 0))) {
        return 0;
    }
    if (best != normal_BtlChgPageGetMember_505f90(D_00484454)) {
        if (PartySetLeader_3c1600(w, o->fC, 1) == 1) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = 0;
    }
    return r != 0;
}
