/* === SESSION 91 (2026-09-22): 18 BAD -> MATCH, exact 494 words, CLOSED.
 * In config/ocunits/normal.txt; NORMAL.BIN relinked BYTE-IDENTICAL at 649
 * units.  Decks build/wf-normal/s91/{d1,d2,d3,d4}.py.  THREE edits, and the
 * first came off an ALLOCATOR INPUT no session on this board had ever moved
 * on purpose: the SPILL COST.
 *
 * THE FINDING.  s90 dumped mwcc's own interference graph and proved the
 * 13-word flag/obj transposition is ONE ADJACENT PAIR in the simplify order,
 * then failed to reach it with a 1,936-cell exhaustive DEGREE sweep and a
 * 30,000-vector random DEGREE search.  s91/{csrch,csrch2,jsrch}.py searched
 * the OTHER input to the optimistic-spill pick, `cost / degree`, and the
 * answer is exact, unique, and not a degree at all:
 *
 *   cost(obj = vreg 42)  8 -> 3..5    AND    cost(flag = vreg 46)  3 -> >= 6
 *
 * and it is INVARIANT under every single-node degree change inside every
 * node's payable bounds -- which is precisely why s82-s90's degree searches
 * could not have found it.  `cost` is node word 3 = mwcc's reference count
 * for the web; d1.py calibrates it as a PLAIN count of defs + uses with NO
 * loop weighting, and a def of a small CONSTANT does not count:
 *     scn   2 loads + 11 uses           = 13   (dump: 13)
 *     obj   2 call-result defs + 6 uses =  8   (dump:  8)
 *     flag  3 uses, both defs constant  =  3   (dump:  3)
 * d1 also shows what is NOT payable: a coalesced copy (`fq = flag;`) and a
 * constant-folded use are BOTH invisible to the graph -- byte-identical dumps,
 * same node count, same costs.  s52's "mwcc coalesces it" is now visible at
 * the graph level, and that retires the copy axis for cost.
 *
 * EDIT 1 + 2 (18 -> 5), d2.py.  mwcc does NOT split disjoint live ranges --
 * obj's two ranges are ONE vreg with the two counts added -- so the only way
 * to move a cost without moving an instruction is to change which references
 * share a web:
 *   * `obk` for obj's SECOND live range: cost 8 -> 4 + 4, degree unchanged.
 *   * `ok` spelled `flag`: one variable for two disjoint roles, cost 3 -> 7.
 * Crossed, that is arm k6 -- 5 bad at exact 494 words, and the dump shows obj
 * at $s6 and flag at $s1, retail's map exactly.  Either half ALONE is a
 * REGRESSION (k1 32, k2 26, k3 67, k4/k5 71): this is a two-edit cross, the
 * shape levers.d/two-edit-cross-beats-count-ranking describes.
 *
 * EDIT 3 (5 -> MATCH), d4.py.  What was left was a caller-saved permutation of
 * the four guard temps W2=wid2*2 H2=hgt*2 NW=-wid2 NH=-hgt.  All four are
 * pass-1 nodes, so their select order is exactly descending vreg index and the
 * whole residue is their CREATION order; each can be HOISTED into a named
 * local before the j-loop or written INLINE in the guard.  The 22-cell grid
 * over that choice (and over the hoist order):
 *     hoist NW and NH, inline W2 and H2      1 bad  <- installed
 *     hoist NW only / NW,W2 / NW,H2          5
 *     base: hoist W2 and NH                  5
 *     hoist NH only / NH,NW                  6
 *     none hoisted / W2 / H2 / W2,NW / H2,NW 7
 *     all four, W2,H2, W2,H2,NW, ...         9
 * !! the obvious symmetry argument is WRONG: the wid pair is already correct
 * with W2 hoisted and NW inline, so "mirror it, hoist H2" reads 9, worse than
 * base.  Both NEGATIONS hoisted and both MULTIPLIES inline is the answer, and
 * only the grid finds it.
 *
 * !! THE LAST WORD IS A `.lit4` SCORER NOTE, NOT A DEFECT.  n_obytecheck reads
 * 1 bad at 0x005178D0 (`lwc1 $f2,-0x7F28($gp)` = the 0.7f pool entry, which we
 * already write as a literal): the scorer cannot resolve an offset into this
 * object's own .lit4, and n_olink retargets it.  The LINK is the verdict, and
 * it says BYTE-IDENTICAL.  See levers.d/mwcc-float-literal-pool.
 * Everything below predates this session. */
/* === SESSION 90 (2026-09-22): STILL 18 BAD, and the flag/obj transposition
 * now has an EXACT, SMALL ask read out of mwcc's OWN allocator.
 * build/wf-normal/s90/{ra90,ral,head,park}.py dump the interference graph, the
 * simplify/select list and the final colours from the RUNNING compiler under
 * gdb and replay the algorithm: **select lowest-free 163/163, simplify replay
 * == dump**, so a colour argument on this unit is now safe to reason from.
 *  - `flag` (the `li s6,1` at idx 127) is vreg 46, select position 9;
 *    `obj` is vreg 42, select position 1.
 *  - SWAPPING THOSE TWO SELECT POSITIONS PRODUCES RETAIL'S MAP EXACTLY, with
 *    every other callee-saved register unchanged.  The whole 13-word
 *    transposition is ONE ADJACENT PAIR in the simplify order.
 *  - This unit is NOT blocked the way normal_BtlChgMenuTryLeaderChange_502250 is: every
 *    callee-saved node here has degree HEADROOM 27-43 (the number of live
 *    vregs it does not already interfere with), so the order IS payable in
 *    principle.  What is missing is the source edit.
 *  - NOT FOUND YET (and these are searches over degrees, not over C): the 2-D
 *    exhaustive sweep of both nodes' full payable degree range (1,936 cells,
 *    36 distinct orders) and a 30,000-vector random search over all 14
 *    callee-saved nodes both miss, best 3 registers off.  14 dimensions is
 *    far too sparse for 30k samples -- treat this as "not found".
 *  ⚠ ALSO FOUND: this unit SPILLS, so mwcc runs color_graph TWICE, and
 *    bg30/alloc13.py (which takes events[0]/events[1]) reads the FIRST round's
 *    all -1 colours and prints "0 / 161 dumped colours, 161 mismatches".  Use
 *    s90/ral.py, which takes the LAST color_graph and the LAST apply_colors.
 *  ==> next arm: drive s90/rasweep.py with SOURCE arms and read the select
 *  order, instead of scoring.  Everything below predates this session. */
/* === SESSION 88 (2026-09-22): STILL 18 BAD.  TWO ARMED NULLS, and the one
 * this unit's header has been ASKING FOR since s82 is now CLOSED NEGATIVE.
 *  - s88/a1.py: THE LENGTH CROSS.  s87/c1 priced the binding column's length
 *    (callee-saved PAIR +2 w, TRIPLE +3, `bind r23` +1) and s87/e2 priced the
 *    pragma column's (`opt_dead_code off` -2 w, `opt_rotateloops off` -1 w);
 *    neither half is usable alone.  Crossed, 18 cells: THE ARITHMETIC WORKS --
 *    every cell lands at EXACT 494 words -- and EVERY CELL IS 248 TO 362 BAD.
 *    Armed (bogus == base, `bind r2` == base, each pragma alone reproduces
 *    s87's length).  ==> A PRAGMA'S LENGTH DELTA IS NOT A LENGTH HALF: the
 *    binding is a LOCAL edit, an optimiser pass is a whole-function rewrite,
 *    so the sum has the right word count and none of the map.  Pair a binding
 *    only with a SOURCE-side length half.  Do not re-open this cross.
 *  - s88/dsweep.py: the DECLARATION-ORDER axis re-priced at this coat, 26
 *    adjacent-swap / move-to-front / move-to-end arms over the 42 locals.
 *    ELEVEN distinct objects (22, 24, 26, 26, 29, 29, 30, 33, 38, 50, 56, 61,
 *    64) so the sweep has ample reach -- and BASE (18) is the best of them.
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): STILL 17/18 BAD.  TWO ARMED NULLS, on the two
 * axes this unit's own header named as the only ones left.
 *  - s87/c1.py: MULTI-REGISTER register bindings, the arm
 *    levers.d/mwcc-register-binding-exit-seed lists as unexplored (s81 ran the
 *    13 SINGLE bindings board-wide).  22 combos: every callee-saved PAIR
 *    (r16/r17 ... r22/r23) is +2 words and every TRIPLE +3 -- the extra
 *    save/restore -- and every caller-saved pair/triple (r2..r8, r12..r15,
 *    r24, r25) is BYTE-IDENTICAL, because this unit's whole residue is
 *    callee-saved.  `bind r23` alone is +1 word and a new object.  Armed:
 *    bogus pragma == base, `bind r2` == base.  ==> the binding axis, single
 *    and multi, is CLOSED on this unit.  It SHIFTS; the residue is a
 *    TRANSPOSITION, and a shift cannot produce one.
 *  - s87/e2.py: the whole 68-name `opt_*` table spelled `off` (s50 swept a
 *    handful on top of the installed `opt_lifetimes off`).  Six live columns,
 *    none better: opt_optimizecontrolflow 20, opt_loop_invariants 318,
 *    opt_dead_code -2 w, opt_rotateloops -1 w, common_subs / propagation +.
 * Everything below predates this session. */
/* === SESSION 86 (2026-09-22): STILL 18 BAD.  s86/g1.py: `flag = 0` after the
 * call (-1 w), inside the argument, as the argument, the first call's `flag`
 * as literal 1: identical or length-wrong.  `u8 flag` is a new object at 18,
 * `s16 flag` +1 w. */
/* === SESSION 52 (2026-09-08, SOLO): still 17 bad / 494 w.  The axis s50 said
 * the next arm had to reach -- "change the INTERFERENCE, not the order" -- was
 * tried and is a MEASURED NEGATIVE.  `obj` has TWO disjoint live ranges (the
 * func_32A920 result, then the func_32A8F0 result), so it is the textbook
 * [[insect-session55-levers]] LIVE-RANGE SPLIT candidate.  SPLITTING IT IS
 * WORSE AND THE DECL SLOT IS INERT: 11 arms -- second range renamed with the
 * new name at 4 declaration slots, first range renamed at 4 slots, BOTH ranges
 * renamed so the name `obj` disappears entirely (2 orders), and the split
 * crossed with a `flag2 = flag;` copy at the last use -- ALL COLLAPSE ONTO ONE
 * OBJECT, 73761e67, 22 bad.  The split does move the map (it turns the clean
 * flag/obj transposition into a 3-cycle: retail s6 -> ours s5 8w, retail s1 ->
 * ours s6 5w, retail s5 -> ours s1 5w) so the sweep provably has reach; it
 * moves it AWAY.  A `flag2 = flag;` copy at the func_324340 use ALONE is a
 * different object (72553610) at the same 17 with an IDENTICAL census, i.e.
 * mwcc coalesces it -- the coalescing channel [[insect-session56-levers]]
 * calls the last unswept allocator input is a null on this unit too.
 * Do not re-sweep the split, its decl slot, or the copy. */
/* === SESSION 50 (2026-09-08, SOLO): STILL 17 BAD / 494 words, and the
 * flag/obj CREATION-ORDER axis is now closed from BOTH ends.
 *  * `flag = 1;` REALLY IS AT THE LOOP-BODY TOP.  Moving its first definition
 *    below `obj`'s (the only thing [[mwcc-callee-saved-creation-order]] says
 *    could give retail's map) is ONE WORD SHORT, and the mdiff of that arm
 *    shows retail carrying `addiu $17,$0,0x1` at 0x005176CC -- i.e. retail
 *    emits `flag = 1` exactly where we do.  Same for `flag = 1;` after the
 *    `ent` guard.  A duplicate `flag = 1;` added inside the obj guard, and
 *    `flag = 1;` written last of the four openers, are inert / +2.
 *  * THE PRAGMA CHANNEL REACHES FOUR DISTINCT OBJECTS AT 17 AND THE CENSUS IS
 *    IDENTICAL IN ALL FOUR (s6>s1:8 s1>s6:5 v1>a1:1 a1>v1:1 $f3>$f5 $f5>$f3):
 *    base 93f8c8a9, `opt_dead_assignments off` 212133b6,
 *    `opt_pulloutconstants off` e6dfd94e, both fd5603bb -- all on top of the
 *    installed `opt_lifetimes off`.  Crossing either pragma with either
 *    flag-move is still exactly one word short.
 *    (`opt_loop_invariants off` is 318, `opt_optimizecontrolflow off` 19.)
 * => The flag/$22 vs obj/$17 transposition survives 4 objects x 6 source
 * positions.  It is not a creation-order edit and not a pragma; the next arm
 * has to change the INTERFERENCE.  Do not re-sweep either axis. */
/* SESSION 45: 494/494 w, 17 bad, and mboard.py says the OPCODE STREAM IS
 * IDENTICAL -- ZERO structural hunks.  The entire residue is one two-web GPR
 * transposition: retail `flag`=$17 / `obj`=$22, ours the other way round.
 * WARN FOURTEEN declaration-position arms (`flag` moved above obj/ent/scn/ctx/
 * e/ini/sel/g/h/cam, `obj` moved below flag/ok/hgt) ALL COLLAPSE ONTO ONE
 * OBJECT.  The declaration SLOT is inert here, so this is creation order /
 * interference, not decl order -- the axis this unit's own header has been
 * grinding for three sessions is closed.  Change what is LIVE, not where it
 * is declared. */
#include "types.h"
/* SESSION 41 (n41t, SOLO): 22 -> 17 bad, exact 494 words, still open.
 * ONE LINE: `#pragma opt_lifetimes off`.  ARMED -- a bogus pragma name and
 * `opt_lifetimes on` both reproduce the 22-bad object exactly.
 *
 * WHAT IT BOUGHT, and why it matters more than the 5 words.  The 18-word
 * cluster this header calls "the loop-body callee-saved colouring" was a
 * THREE-CYCLE (retail e=$16, flag=$17, ent=$21, obj=$22; ours e=$16, ent=$17,
 * obj=$21, flag=$22).  Under the pragma `ent` lands on retail's $21 and the
 * residue collapses to a PLAIN TRANSPOSITION of `flag` and `obj` -- 13 words,
 * and the shape [[mwcc-callee-saved-creation-order]] is actually fitted on.
 * The sessions 32/37 creation-order decks (156-arm whole-list decl sweep,
 * 96-arm four-statement permutation, the ini/flag/ok merge) were all run in
 * the OLD coat, where no creation-order edit could reach a 3-cycle: they are
 * nulls about that coat, not about the axis ([[two-edit-cross-beats-count-ranking]]).
 *
 * RESIDUE NOW 17 = three clean transpositions:
 *   13 w  flag/obj.  Ours flag=$22, ent=$21, obj=$17; retail flag=$17,
 *         ent=$21, obj=$22.  $17 is `ini`'s register and both objects reuse it
 *         after ini dies at `func_425440`; the only question is WHICH web
 *         takes it.  Ours is monotone in first-definition order (flag, ent,
 *         obj -> $22, $21, $17, i.e. later first-def -> lower register, the
 *         corpus rule); retail's map needs the order obj, ent, flag, which our
 *         nesting cannot produce -- `obj` is defined three guards inside
 *         `ent`'s.
 *    2 w  the bw2/nhgt `mtc1` transposition (0x00517A50 / 0x00517A6C).
 *    2 w  `sll $5,$16,1` vs `sll $3,$16,1` (0x00517998 / 0x005179A8).
 * RE-SWEPT AT THE NEW COAT, ALL NULL OR WORSE (do not re-run):
 *   - all 24 permutations of the four loop-body-opening statements: 17 is the
 *     BEST cell and the flag/obj transposition is INVARIANT across all 24.
 *   - `obj = 0;` and `ent = 0;` defaults before `flag = 1;`: byte-identical
 *     (dead-code eliminated, so they create no web).
 *   - flag/obj declared first / last / adjacent, obj before ent: inert;
 *     `obj` declared first is 61.
 *   - merging `flag` into `ini` (25) or into `ok` (31) -- the pragma does NOT
 *     rescue that arm; merging `obj` into `g` is 2 words short.
 *   - `u8 flag` reads 17 with a BETTER substitution census (13) and is a
 *     FALSE lead: it turns `addiu $22,$0,1` into `daddiu` and adds an
 *     `andi 0xFF` ([[mwcc-daddiu-unsigned-narrow]]).  `s16 flag` is long.
 *   - crossed with dead_assignments off / no_register_coloring / scheduling
 *     off / repositioncode off / pulloutconstants off: 17, no change to the
 *     census.  propagation off, common_subs off and peephole off are long;
 *     optimization_level 3 undoes the pragma (back to 22).
 *   - the y-test `||` swap this header's session 38 note left untested in
 *     isolation is now tested: 23, WORSE.  The x-test swap alone is 17 with a
 *     DIFFERENT residue (the 2-word `sll` pair goes away and four FPR
 *     substitutions appear instead) -- a live but not better cell.
 */
#pragma opt_lifetimes off

/* normal 0x005174D0 -- FRESH unit, written from nothing in session 32
 * (lane nf32b).  Draws a rotated quad marker for every entity in the
 * iterator that passes the visibility / height-band tests.
 *
 * _gp = 0x00485170.  gp - 0xA04 = D_0048476C (u8 gp extern);
 * gp - 0x7F28 = 0x0047D248 which is INSIDE the mwcc .lit4 pool = 0.7f, so it
 * is spelled as a literal here (see mwcc-float-literal-pool).
 * The 5th integer argument travels in $8 (func_324340, func_13EE40).
 *
 * !! PARKED, lane nf32b, session 32.  RIGHT LENGTH (494 words = 0x7B8),
 * 24 bad words.  890 arms over nine bulk32 decks; every deck carried an
 * identity arm and every identity arm reproduced the then-current count.
 * NOT in config/ocunits/normal.txt.
 *
 * MOVEMENT 493 words / length-wrong -> 494 / 73 -> 38 -> 36 -> 30 -> 24.
 * WHAT EACH EDIT WAS WORTH (all measured, deck logs in
 * build/wf-normal/s32/var/nf32b/deck*.log):
 *
 *  * the quad size must be a NAMED local -- `sz = 16.0f;` then `-sz` / `sz`,
 *    NOT the literal `-16.0f`.  Retail hoists `lui 0x4180 / mtc1 / neg.s
 *    $f31,$f0` to function entry and stores `swc1 $f31` for the four
 *    negative corners, rematerialising `+16.0f` as `lui/sw` inside the loop.
 *    A `-16.0f` literal folds to `lui 0xC180 / sw`: 2 words short, $f31
 *    stays free so `depth` steals a callee-saved FPR instead of spilling to
 *    0xE0, and the frame shrinks 0x1C0 -> 0x1B0.  `nsz = -16.0f;` FOLDS and
 *    is identical to the literal -- it must be a negation of a named 16.
 *  * the rotation loop must copy BOTH elements to temps first (mwcc reloads
 *    them otherwise, +2 words), and it is a TWO-EDIT CROSS: temps assigned
 *    x-then-y AND both products written low-operand-first
 *    (`qx*sn + qy*cs`, `0.7f*(qx*ncs + qy*sn)`).  Either half alone reads
 *    36; the cross reads 30.  Ranking by bad alone deletes the winning half.
 *  * `v` must be a SIXTEEN-byte aggregate (8 w).  With a 12-byte struct
 *    mwcc lays out `it@0x198, v@0x188, q@0x170`; retail is
 *    `it@0x198, q@0x180, v@0x170`.  The aggregate DECLARATION ORDER is an
 *    armed null (12 arms, one object) -- the SIZE is the lever.
 *  * FPR decl order `dx, dy, alpha` (25 w).  Declared-first takes the
 *    highest callee-saved FPR: retail is alpha=f20, dy=f21, dx=f22.
 *  * `s32 ini;` must be declared BEFORE `s16 wid;` (6 w).  A 79-arm
 *    whole-list sweep: ini at ANY of positions 0..32 (or wid at any of
 *    33..39) is ONE object at 24; ini after wid is 30.
 *  * `ncs = -cs;` sunk to immediately before the `for` (2 w), and an
 *    explicit `i = 0;` before the quad initialiser with `for (; i < 4; i++)`
 *    (2 w) -- both are quad-init schedule slots.
 *
 * SESSION 37 (lane n37e): naming the two loop-invariant bound values as
 * explicit `s32 bw2 = wid2 * 2;` / `s32 nhgt = -hgt;` locals (declared right
 * after `hgt`, assigned in that order immediately before the `for (j...)`
 * loop, referenced as `(f32)bw2` / `(f32)nhgt` in the two comparisons) fixed
 * HALF of the old 4-word transposed-temps cluster: 24 -> 22 bad, SAME
 * length (494).  Both are load-bearing: s32 (not f32) type, THIS decl
 * position, THIS assignment order (bw2 before nhgt), and THIS use-site
 * comparison order (x-test before y-test) are all required -- every
 * variation tried below is a confirmed null or regression, do not re-run.
 *
 * RESIDUE, 22 words, three groups:
 *  * 18 w -- the loop-body callee-saved colouring.  Ours e=$16, ent=$17,
 *    obj=$21, flag=$22; retail e=$16, flag=$17, ent=$21, obj=$22, i.e.
 *    retail coalesces `flag` onto `ini`'s $17 and ours coalesces `ent`
 *    there.  mwcc behaves as if `flag`'s web were created LAST of the four
 *    even though its `addiu ..,$0,1` is emitted in retail's own slot.
 *  * 2 w -- the mtc1 casts of the two bound temps are STILL transposed,
 *    just on different register numbers now: ours emits `mtc1 $5,$f0` /
 *    `mtc1 $3,$f16`, retail emits `mtc1 $3,$f0` / `mtc1 $5,$f16` (session 32's
 *    original description, "$4 = wid2*2 / $3 = -hgt", was against the
 *    PRE-session-37 compare-site casts; naming bw2/nhgt moved the cast
 *    location and register numbers but the transposition itself survived).
 *  * 2 w -- `j = 0` is scheduled one slot early (before `out[0].w = 0`
 *    instead of after it).  (Unchanged since session 32; still covered by
 *    the "ten placements" null below -- do not re-run.)
 *
 * ARMED NULLS at this baseline (do not re-derive):
 *  * merging ini/flag/ok into ONE variable, in any subset, and with the
 *    merged variable declared in 7 positions -- 16 arms, ONE object.
 *    One variable is not one web: mwcc splits it straight back.
 *  * the whole-list declaration sweep for `flag`, `ent`, `obj` and `e`
 *    (156 arms) -- one object except where it makes things worse.
 *  * all 24 permutations of the four statements that open the loop body
 *    (96 arms with block-scoped decls crossed in) -- inert or worse.
 *  * `EQ`/`EIt` spelled `s32[]` or `double[]` instead of `u8[]` (72 arms).
 *  * ten placements of an explicit `j = 0;` among the out[] stores, and
 *    two re-orderings of the out[] z/w block -- all inert.
 *  * hoisting the four bounds into named f32 locals in all 24 orders reads
 *    82-83: mwcc parks them in callee-saved FPRs.  Do not do this.
 *  * `if ((ent = f()) != 0)` and `if ((obj = f()) != 0)` each cost a word
 *    (493 / 492) -- retail keeps the separate `daddu $21,$2,$0` + `beqz`.
 *  * SESSION 37 additions, all measured against the 22-bad baseline above:
 *    - swapping the if-order of the x/y out[] bound checks (y-test first):
 *      29 bad, worse.
 *    - swapping the defining order of `wid2`/`hgt` themselves (hgt first):
 *      28 bad, worse; combined with the if-order swap too: 29 bad, worse.
 *    - `bw2`/`nhgt` as named `f32` locals (with the casts folded into the
 *      assignment instead of the compare site): LENGTH WRONG (0x7B4 vs
 *      0x7B8), do not do this.
 *    - swapping assignment order to `nhgt = -hgt; bw2 = wid2 * 2;`: 25 bad,
 *      worse.
 *    - hoisting `bw2 = wid2 * 2; nhgt = -hgt;` up next to where `wid2`/`hgt`
 *      are computed (before `func_1450F0(hw)`) instead of immediately before
 *      the `for (j...)` loop: LENGTH WRONG (0x7C0 vs 0x7B8), do not do this.
 *    - declaring `bw2`/`nhgt` before `wid2`/`hgt`, or after `i`/`j`, instead
 *      of between `hgt` and `i`: both inert (still 22).
 *    - adding harmless `ent = 0;` and/or `obj = 0;` defaults among the four
 *      loop-body-opening statements (to move their apparent creation point
 *      earlier without changing the real assignment): inert (still 22),
 *      tried singly and combined.
 *    - block-scoping `ent`/`obj` as locals declared at their first-use site
 *      (inside `if (h != 0 && e != 0)` / `if (ent != 0)`) instead of
 *      function scope: inert (still 22).
 *    - a redundant `flag = 1;` re-write added immediately before `sel = 0;`
 *      inside the guarded block (on top of the existing unconditional
 *      `flag = 1;` at loop-body entry): inert (still 22), eliminated as
 *      dead code.
 *    - restructuring so `ent`'s real assignment (guarded by `h != 0 &&
 *      e != 0`, with an `ent = 0;` default and the nesting flattened by one
 *      level so `if (ent != 0)` is a separate statement instead of nested
 *      inside the `h`/`e` guard) executes BEFORE `flag = 1;` in source
 *      order -- semantically equivalent (verified: the only behavioural
 *      difference is which "ent = 0 vs skip" path is taken, and it comes
 *      to the same value on the branch retail cares about) but reads 37
 *      bad, much worse -- flattening the guard nesting itself, not just the
 *      creation order, disturbs a lot more than the coloring.  This was the
 *      one genuinely untried creation-order axis the header called out;
 *      it is now a confirmed regression, not merely inert.
 *    Net: cluster 1 (18 w, callee-saved colouring of e/ent/obj/flag) remains
 *    unclosed after 890 (session 32) + ~10 (session 37) arms.  Every
 *    SAFE (behaviour-preserving) way to reorder ent/obj/flag's first-write
 *    relative to each other has now been tried; the only remaining lever
 *    would require either an UNSAFE reorder (dropping the unconditional
 *    `flag = 1;` default, which breaks correctness on the `h == 0` path)
 *    or a spelling axis not yet identified.
 *
 * SESSION 38 (lane n38b): baseline re-confirmed at 494 words / 22 bad
 * before touching anything.  Read levers.d/mwcc-callee-saved-creation-order.md
 * in full first: the corpus-wide fit says the callee-saved colour order is
 * governed by first-definition order with "later first-def -> lower
 * register" (69.7% of pairs, not deterministic).  Applied to this unit's
 * flag/ent/obj triple, our source order (flag first-defined, then ent, then
 * obj) predicts obj should win the lowest register -- but retail actually
 * gives flag the lowest (of the three) and obj the highest, the OPPOSITE of
 * the majority rule.  This triple is one of the model's ~30% minority
 * cases, which is consistent with (and explains) why every source-order
 * permutation already tried by sessions 32 and 37 (156-arm whole-list decl
 * sweep + 96-arm 4-statement permutation, both "inert or worse") failed to
 * reach it: there is no source-order lever this rule predicts would work,
 * because the target coloring already contradicts the model's own
 * direction.  Not re-sweeping this axis further.
 * New arms this session, targeting the 2 w mtc1 transposition specifically:
 *  * swap ONLY the declaration order of bw2/nhgt (nhgt before bw2),
 *    assignment order and use-site order both UNCHANGED: INERT, still 22.
 *  * swap the `||` operand order in BOTH the x-test and the y-test
 *    (`(f32)bw2 < out[j].x || out[j].x < (f32)(-wid2)` and
 *    `(f32)(hgt*2) < out[j].y || out[j].y < (f32)nhgt`): REGRESSION, 28 bad.
 *  * swap the `||` operand order in the x-test ONLY (y-test left as
 *    written): INERT, still 22 -- so the y-test half of the combined swap
 *    above is what carries the regression; not tried alone (round-trip cap
 *    reached at 4).
 * PARKED again at 494 words / 22 bad, unchanged from session 37's exit
 * state.  Next session: try the y-test `||` operand swap ALONE (untested
 * in isolation) before any other new axis; if that is also inert, this
 * unit's residue is very likely fully exhausted for source-level spellings
 * per the creation-order-model argument above and should probably move to
 * the parked-permanently shelf rather than absorb more sessions. */

typedef struct Sub {
    u8    pad000[0x4];
    s16   f004;
} Sub;

typedef struct Ctx {
    u8    pad000[0x18];
    Sub  *f018;
} Ctx;

typedef struct Cam {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Cam;

typedef struct Ent {
    u8    pad000[0x18];
    s16   f018;
    u8    f01A;
    u8    pad01B[0x5];
    f32   f020;
    f32   f024;
    f32   f028;
    u8    pad02C[0x14];
    s32   f040;
} Ent;

typedef struct Pos3 {
    f32   x;
    f32   y;
    f32   z;
} Pos3;

typedef struct QuadPt {
    f32   x;
    f32   y;
    f32   z;
    f32   w;
} QuadPt;

typedef struct EQ {
    u8    pad000[0x18];
} EQ;

typedef struct EIt {
    u8    pad000[0xC];
} EIt;

extern u8    D_0048476C;          /* gp - 0xA04 */

extern Ctx  *func_1FEDE0(void);
extern s32   func_207F30(void);
extern void  func_425440(EQ *q, Ctx *e, s16 w, s32 f);
extern void  func_370170(EIt *it, EQ *q);
extern Cam  *func_201A70(void);
extern f32   func_323DD0(void *p);
extern void *func_141B00(void *h);
extern void  func_13E4F0(void *g, s32 a);
extern void  func_13E500(void *g, s32 a);
extern void  func_13E390(void *g, s32 a);
extern void  func_13E4D0(void *g, s32 a);
extern void  func_13E460(void *g, s32 a);
extern void  func_13E400(void *g, s32 a);
extern void  func_13E3E0(void *g, s32 a);
extern void  func_13E2F0(void *g, s32 a);
extern void  func_13E3D0(void *g, s32 a);
extern void  func_13E430(void *g, s32 a);
extern void  func_13E3B0(void *g, s32 a);
extern void *func_201A90(void);
extern Ent  *func_370040(EIt *it);
extern s32   func_3CB120(Sub *a);
extern void *func_1E49B0(void *p, s32 n, s32 *out);
extern void *func_32A920(void *q);
extern void  func_323AF0(void *p, f32 *a, f32 *b);
extern void  func_3242B0(void *p, f32 *x, f32 *y, s32 n);
extern void *func_1DFEF0(void *p);
extern s32   func_134950(void *p, void *q);
extern void *func_32A8F0(void *p);
extern f32   func_32A8D0(void *p);
extern f32   func_32A8E0(void *p);
extern void  func_324340(void *p, QuadPt *v, f32 *a, f32 *b, s32 n);
extern f32   func_128FD0(f32 x);
extern f32   func_128D30(f32 x);
extern f32   func_32A180(void *p);
extern s32   func_1451E0(void *p);
extern s32   func_1451D0(void *p);
extern void  func_1450F0(void *p);
extern void  func_1450C0(void *p);
extern void  func_13F730(void *g, s32 a);
extern void  func_13EC00(void *g, s32 p);
extern void  func_13EE40(void *g, s32 a, s32 b, s32 c, s32 d);
extern void  func_13ED60(void *g, s32 a, s32 b);
extern void  func_13F060(void *g, f32 x, f32 y, f32 z);
extern void  func_13F5B0(void *g);
extern void  func_141A20(void *h);

void normal_TransMenuMinimapMarkersDrawMaybe_5174d0(void *hw, s32 px, s32 py, s32 tex, f32 ang)
{
    f32     hi;
    f32     lo;
    s32     sel;
    f32     bx;
    f32     by;
    f32     ox;
    f32     oy;
    EIt     it;
    EQ      q;
    QuadPt  v;
    QuadPt  quad[4];
    QuadPt  out[4];
    Ctx    *ctx;
    Cam    *cam;
    void   *scn;
    void   *g;
    void   *h;
    void   *ent;
    void   *obj;
    void   *obk;
    Ent    *e;
    f32     dx;
    f32     dy;
    f32     alpha;
    f32     depth;
    f32     scale;
    f32     cs;
    f32     sn;
    f32     ncs;
    f32     qx;
    f32     qy;
    f32     sz;
    f32     nsz;
    s32     ini;
    s16     wid;
    s32     flag;
    s32     wid2;
    s32     hgt;
    s32     nwid;
    s32     nhgt;
    s32     i;
    s32     j;

    ctx = func_1FEDE0();
    wid = ctx->f018->f004;
    ini = 1;
    if (func_207F30() != 0) {
        ini = 0;
    }
    func_425440(&q, ctx, wid, ini);
    func_370170(&it, &q);
    cam = func_201A70();
    if (cam == 0) {
        return;
    }
    scn = cam->f510;
    if (scn == 0) {
        return;
    }
    if (cam->f514 != 0) {
        scn = cam->f514;
    }
    depth = func_323DD0(scn);
    g = func_141B00(hw);
    func_13E4F0(g, 1);
    func_13E500(g, 1);
    func_13E390(g, 0);
    func_13E4D0(g, 1);
    func_13E460(g, 0);
    func_13E400(g, 1);
    func_13E3E0(g, 1);
    func_13E2F0(g, 0);
    func_13E3D0(g, 0);
    func_13E430(g, 1);
    func_13E3B0(g, 0);
    h = func_201A90();

    while ((e = func_370040(&it)) != 0) {
        if ((e->f040 & 1) == 0) {
            continue;
        }
        if (func_3CB120(ctx->f018) != 0) {
            if (D_0048476C != 0 && (e->f01A & 1) == 0) {
                continue;
            }
        } else {
            if (D_0048476C != 0 && (e->f01A & 1) == 0) {
                continue;
            }
        }
        hi = 0.0f;
        flag = 1;
        alpha = 1.0f;
        lo = 0.0f;
        if (h != 0 && e != 0) {
            sel = 0;
            ent = func_1E49B0(h, e->f018, &sel);
            if (ent != 0) {
                obj = func_32A920(scn);
                if (obj != 0) {
                    func_323AF0(obj, &hi, &lo);
                    func_3242B0(scn, &bx, &by, flag);
                    dx = (f32)px + bx;
                    dy = (f32)py + by;
                    if (func_1DFEF0(ent) != 0) {
                        if (func_134950(func_1DFEF0(ent), (u8 *)obj + 0x54) != 0) {
                            obk = func_32A8F0(scn);
                            if (obk != 0) {
                                if (func_134950(func_1DFEF0(ent), (u8 *)obk + 0x54) == 0) {
                                    func_323AF0(obk, &hi, &lo);
                                    alpha = func_32A8D0(scn);
                                    flag = 0;
                                    func_3242B0(scn, &bx, &by, 0);
                                } else {
                                    alpha = 0.0f;
                                }
                            }
                        } else {
                            alpha = func_32A8E0(scn);
                            func_3242B0(scn, &bx, &by, flag);
                        }
                    }
                    dx -= bx;
                    dy -= by;
                }
            }
        }
        v.x = e->f020;
        v.y = e->f024;
        v.z = e->f028;
        if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) {
            continue;
        }
        if (v.y < hi) {
            continue;
        }
        if (lo < v.y) {
            continue;
        }
        func_324340(scn, &v, &ox, &oy, flag);
        cs = func_128FD0(ang);
        sn = func_128D30(ang);
        sz = 16.0f;
        i = 0;
        quad[0].x = -sz;
        quad[0].y = -sz;
        quad[0].z = 0.0f;
        quad[0].w = 0.0f;
        quad[1].x = sz;
        quad[1].y = -sz;
        quad[1].z = 0.0f;
        quad[1].w = 0.0f;
        quad[2].x = -sz;
        quad[2].y = sz;
        quad[2].z = 0.0f;
        quad[2].w = 0.0f;
        quad[3].x = sz;
        quad[3].y = sz;
        quad[3].z = 0.0f;
        quad[3].w = 0.0f;
        ncs = -cs;
        for (; i < 4; i++) {
            qx = quad[i].x;
            qy = quad[i].y;
            quad[i].x = qx * sn + qy * cs;
            quad[i].y = 0.7f * (qx * ncs + qy * sn);
        }
        scale = func_32A180(scn);
        flag = 1;
        wid2 = func_1451E0(hw);
        hgt = func_1451D0(hw);
        func_1450F0(hw);
        func_1450C0(hw);
        out[0].z = 0.0f;
        out[0].w = 0.0f;
        out[1].z = 0.0f;
        out[1].w = 0.0f;
        out[2].z = 0.0f;
        out[2].w = 0.0f;
        out[3].z = 0.0f;
        out[3].w = 0.0f;
        out[0].x = dx + (ox + quad[0].x);
        out[0].y = dy + (oy + quad[0].y);
        out[1].x = dx + (ox + quad[1].x);
        out[1].y = dy + (oy + quad[1].y);
        out[2].x = dx + (ox + quad[2].x);
        out[3].x = dx + (ox + quad[3].x);
        out[2].y = dy + (oy + quad[2].y);
        out[3].y = dy + (oy + quad[3].y);
        nwid = -wid2;
        nhgt = -hgt;
        for (j = 0; j < 4; j++) {
            if (out[j].x < (f32)nwid || (f32)(wid2 * 2) < out[j].x) {
                flag = 0;
            }
            if (out[j].y < (f32)nhgt || (f32)(hgt * 2) < out[j].y) {
                flag = 0;
            }
        }
        if (flag == 0) {
            continue;
        }
        func_13F730(g, 4);
        func_13EC00(g, tex);
        func_13EE40(g, 0x80, 0x80, 0x80, (s32)(depth * (128.0f * scale * alpha)));
        func_13ED60(g, 0, 0);
        func_13F060(g, dx + (ox + quad[0].x), dy + (oy + quad[0].y), 0.0f);
        func_13ED60(g, 0x20, 0);
        func_13F060(g, dx + (ox + quad[1].x), dy + (oy + quad[1].y), 0.0f);
        func_13ED60(g, 0, 0x20);
        func_13F060(g, dx + (ox + quad[2].x), dy + (oy + quad[2].y), 0.0f);
        func_13ED60(g, 0x20, 0x20);
        func_13F060(g, dx + (ox + quad[3].x), dy + (oy + quad[3].y), 0.0f);
        func_13F5B0(g);
    }
    func_141A20(hw);
}
