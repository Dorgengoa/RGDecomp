/* === SESSION 92 (2026-09-22): 10 BAD -> MATCH, exact 363 words.  MERGED and
 * NORMAL.BIN RELINKED BYTE-IDENTICAL.  s91 made the FLOAT register file
 * readable but could not AIM it; this session built the missing half and the
 * unit fell in four decks.
 *
 * THE INSTRUMENT (build/wf-normal/s92/irf.py).  bg30/ir15.py hardcodes
 * events[0]/events[1] and the GPR register names, so a float vreg could never
 * be tied to an instruction.  irf.py takes the LAST color_graph/apply_colors
 * for the REQUESTED class and names every operand in its OWN class's file.
 * Block 23 reads out the webs directly:
 *     60 mtc1 a1 = 92.0f   62 madd = py's products   64 mtc1 a0 = 106.0f
 *     65 add = py's sum    67 msub = px's products   69 add = px's sum
 *     70 trunc (s32)px     71 trunc (s32)py
 * ** EVERY float node here has COST 0 and leaves simplify in pass 1 or 2, so
 * no optimistic spill ever fires and s91's SPILL-COST lever is INERT on the
 * FPR class.  The colouring is exactly `select order = DESCENDING VREG INDEX
 * + lowest-free`, i.e. a pure CREATION-ORDER fact.
 *
 * THE ASK (s92/fsrch.py, 1760 of 40320 permutations hit; six pairwise order
 * constraints, four of them the opposite of base):
 *     vreg(92.0f) > vreg(py products) AND > vreg(px products)
 *     vreg(py sum) > vreg(px sum) AND > vreg((s32)px)
 * i.e. the 92.0f SEED must be created after BOTH product terms, and py's SUM
 * after px's sum AND px's conversion.  Both are reachable by SPLITTING each
 * sum in two (the product term into a variable, the constant folded in
 * after), which is why s86's 67-arm seed-position sweep could not get there:
 * it moved the seed but never split the sum.
 *
 * THE FOUR EDITS.
 *  1. c1/g1 (10 -> 10, NEW object): the split.  The whole float map of loop 1
 *     is RETAIL'S -- verified on the graph, all eight webs.  The ten words
 *     move to two new facts.
 *  2. c2/h3 (10 -> 9): px's product term into its OWN local `pt`.  mwcc puts
 *     a variable that is BOTH destination and operand in SLOT 1, so
 *     `py = 106.0f + py` emits `add.s $f0,$f2,$f0` where retail has
 *     `add.s $f0,$f0,$f2`; breaking the self-accumulation fixes the slot.
 *     !! `92.0f + px` and `px + 92.0f` are the SAME OBJECT -- the slot is not
 *     the source's operand order.
 *  3. c3/k7 (9 -> 8): py's half needs the same, and a SECOND new local is ONE
 *     WORD SHORT (362 vs 364).  Reuse `ox`, which is dead once `o.x` is
 *     stored: `ox = 106.0f + py; q->f02 = (s16)(s32)ox;`.  LOOP 1 IS NOW
 *     BYTE-IDENTICAL.
 *  4. c4/m1 (8 -> MATCH): the last eight words were loop 2's $f20/$f21
 *     transposition.  Loop 1 shares loop 2's px/py locals (s31) and whichever
 *     it TOUCHES FIRST takes $f20; the graph shape touches `py` first, base
 *     touched `px`.  The two locals are interchangeable inside loop 1 (loop 2
 *     re-initialises both), so SWAP WHICH LOCAL CARRIES WHICH VALUE in loop 1
 *     -- loop 1's instruction stream is unchanged and loop 2 comes right.
 *     Landing the 106 sum in `oy` instead of `ox` is the same object. */
/* === SESSION 91 (2026-09-22): STILL 10 BAD -- and this unit is the reason the
 * FLOAT register file is now readable.  Decks build/wf-normal/s91/{d7,d8}.py.
 *
 * 1. !! THE TEN WORDS ARE A FLOAT RESIDUE, AND THE INSTRUMENT COULD NOT SEE IT.
 *    build/bg30/ra12.gdb (the gdb dump of mwcc's own allocator) filtered on
 *    `cls != 0` and dumped ONLY the GPR file, so every float residue on every
 *    board was invisible to it.  build/wf-normal/s91/ra91f.gdb removes that one
 *    line and tags each event with its class; class 1 is the FPR file.
 *    s91/ralf.py loads a class and fits the mask.  VALIDATED ON SEVEN UNITS,
 *    select lowest-free and the simplify replay both EXACT:
 *       004f4050 80/80   004fb280 106/106  005174d0 163/163  004eb6c0 69/69
 *       004fa3c0 18/18   004ed370  20/20   00516e20  11/11
 *    The FPR file is the SAME algorithm with mask $f0..$f31 ASCENDING and
 *    K = 32 (`0..30` misses one colour on 005174d0, so $f31 is in the mask;
 *    an even-only mask misses badly, so single precision uses all 32).
 *
 * 2. THE RESIDUE, at 0x004F4224 -- the px/py computation in the i-loop:
 *      ours    madd.s $f1,$f24,$f4 | add.s $f1,$f0,$f1 | mtc1 $5,$f2 |
 *              msub.s $f0,$f24,$f3 | add.s $f0,$f2,$f0 | trunc.w.s $f0,$f0
 *      retail  madd.s $f2,$f24,$f4 | add.s $f0,$f0,$f2 | mtc1 $5,$f1 |
 *              msub.s $f2,$f24,$f3 | add.s $f1,$f1,$f2 | trunc.w.s $f1,$f1
 *    Retail gives BOTH the madd and the msub result the same scratch $f2 and
 *    lands each sum on its CONSTANT's register; we land each sum on its
 *    PRODUCT's.  The four trunc/swc1/mfc1 words that follow are the schedule
 *    consequence of that choice, not an independent defect.
 *
 * 3. THE LENGTH PINS THE SHAPE (d7.py, 6 arms).  The first region's asymmetric
 *    spelling looks wrong beside the second region's named dx/dy pair, and it
 *    is not: EVERY symmetric rewrite is ONE WORD SHORT (0x5A8 vs 0x5AC) --
 *    named dx/dy in either order, both halves as `K + expr` in either order,
 *    the constant on the right.  `px = 92.0f; py = 106.0f + ...; px = px + ...`
 *    is what buys retail's 363rd word.  Naming dx/dy while KEEPING the px seed
 *    is byte-identical to base.
 *
 * 4. !! ARMED NULL ON THE LOCAL ORDER (d8.py, 12 arms, SIX distinct objects
 *    10/11/13/15/19/20 -- ample reach, base best):
 *      swap the products inside py's sum                15
 *      ...and inside px's too                           15
 *      constant on the right of py's add                base
 *      px's subtraction as `+ -`                        base
 *      the o.x/o.z stores hoisted above the pair        base
 *      py seeded the way px is                          11
 *      py's parentheses dropped                         LEN +1
 *      px's parentheses dropped                         19
 *      both dropped                                     20
 *      `* 0.125f` for `/ 8.0f`                          13
 *      px before py / the seed between them             LEN -1
 *    ==> the float creation order here is NOT set by this statement's own
 *    operand or statement order.  The next arm has to come from the graph:
 *    dump class 1 (s91/ra91f.gdb), tie the vregs to the madd/msub with an
 *    IR decoder (build/bg30/ir15.py, which needs a class-aware port), and run
 *    s91/psrch.py or s91/dsrch.py against retail's map.
 * Everything below predates this session. */
/* === SESSION 88 (2026-09-22): STILL 10 BAD.  ONE ARMED NULL, and it draws a
 * BOUNDARY around the lever that closed 00524850 the same session.
 * s88/h1.py, 23 arms: the SHARED FUSED TEMP.  bad3 says retail puts BOTH
 * fused products in $f2 -- ONE web reused -- while we put them in $f1 and
 * $f0.  s79 had "a named fused temp `ft` (folded)" and the `py` double
 * assignment (the 11-bad attractor 5ab2eccd) as two separate nulls; this
 * crosses them: {no temp, a fresh `ft`, reuse `t`, reuse `tt`, reuse `dy`,
 * reuse `dx`} x {py single / py double} x {both add operand orders}.
 * ONLY TWO OBJECTS COME OUT -- af66dd2d (10) and 5ab2eccd (11) -- and the
 * temp column is INERT in every cell.
 * ==> !!!! levers.d/mwcc-double-assignment-address DOES NOT GENERALISE TO
 * FLOAT ARITHMETIC.  A variable assigned twice survives as two webs when the
 * two assignments are INTEGER ADDRESS arithmetic (index, then base); a float
 * temp written twice is copy-propagated away and the two products stay
 * distinct webs.  Do not re-run the shared-temp idea on an FPR residue.
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): STILL 10 BAD.  THE UPDATE-ORDER AXIS IS AN
 * ARMED NULL at the double-assignment coat (s70's px/py-order sweep predates
 * it; this is the re-price).  s87/f1.py, 32 arms = {py update, px update}
 * order x {seed order} x {seeds before / after the divides} x
 * {`x = x + E` / `x += E`} for both variables: EIGHT distinct objects and
 * BASE (10) is still the best.  Every seeds-BEFORE-the-divides cell is
 * length-wrong (-2 or -1 word); px-update-first is 21; py-seed-first is 11
 * (5ab2eccd, the second attractor s79 already recorded).
 * !! `x += E` and `x = x + E` are FULLY INERT here -- each of the eight
 * objects contains all four spelling combinations.
 * Everything below predates this session. */
/* === SESSION 86 (2026-09-22): STILL 10 BAD.  build/wf-normal/s86/e1.py: the
 * px=92 / py=106 seeds at EVERY legal position x {single, double, +=} update
 * spellings, 67 arms, 19 objects: base (10) is the best; the py double
 * assignment is 5ab2eccd (11) at every seed position, so the seed position is
 * not the axis.  Retail py=$f0 px=$f1 fused temps=$f2 still unreached. */
/* === SESSION 79 (2026-09-21, SOLO): 19 BAD -> 10, still exact 363 words.
 * Loop 1 only.  Four edits, each measured, and s70's own diagnosis
 * ("the unit needs a +1 that buys a hazard nop") turned out to be the WRONG
 * frame: the missing word was never bought, it was a REGISTER MAP.
 *
 *  1. *** THE DIVIDES GO IN SOURCE ORDER `ox` THEN `oy`, and the fused pair for
 *     `py` is spelled `(sn * ox) + (cs * oy)` -- cs*oy SECOND, because mwcc
 *     evaluates the SECOND operand of a commutative `+` FIRST and that operand
 *     is the one that lands in the `mula.s` (levers.d/
 *     mwcc-commutative-add-operand-order).  Retail's mula is `cs*oy`, so
 *     `cs*oy` must be written second; that alone puts `o.z`'s lwc1 first,
 *     `f3 = oy`, `f4 = ox` and words 0x41F8-0x4224 byte-identical.
 *  2. *** `py` IS EVALUATED FIRST AND `px` SECOND, with the `o` writeback
 *     BETWEEN the two fused pairs and the q stores, `q->f00` before `q->f02`.
 *     This is the `wb_mid` shape s70 found and rejected for being one word
 *     short -- it is one word short ONLY while the register map is wrong.
 *  3. *** `px = 92.0f;` AS ITS OWN STATEMENT, BEFORE the `py` statement, and
 *     `px = px + ((cs * ox) - (sn * oy));` after it.  TWO EDITS IN ONE:
 *      (a) a variable ASSIGNED TWICE is not folded
 *          (levers.d/mwcc-double-assignment-address, s78) -- 18 -> 10;
 *      (b) it makes `px` the FIRST of the px/py pair to be TOUCHED in the
 *          function, which is what colours LOOP 2's callee-saved pair.  Every
 *          py-first shape transposes loop 2's $f20/$f21 at six sites (8 bad)
 *          however good loop 1 is; `px = 92.0f;` fixes that without moving a
 *          single loop-2 word.  levers.d/mwcc-fpr-decl-order-highest-first:
 *          first-touched takes the HIGHER register.
 *  4. the named constant `c92 = 92.0f;` reaches the same 18-bad coat but is
 *     STRICTLY WORSE than the double assignment and needs the pragma; dropped.
 *
 * !! `#pragma opt_dead_assignments off` is INERT on the installed shape (arm A9
 * gives the IDENTICAL object af66dd2d) even though it was load-bearing on every
 * intermediate coat -- it is NOT installed.  A pragma verdict is only valid for
 * the SOURCE SHAPE it was measured on (levers.d/mwcc-peephole-branch-stub).
 * !! s70's "loop 1 must REUSE loop 2's px/py" is CONFIRMED the hard way: giving
 * loop 1 its own `ax`/`ay` is 51 bad in eight cells (build/wf-normal/s79/c4).
 *
 * WHAT IS LEFT: 10 words, ONE class, 0x4224-0x4258.  Retail allocates
 * $f0 = py, $f1 = px, $f2 = THE SHARED FUSED TEMP (reusing 8.0f's register) and
 * coalesces each `add.s` into the CONSTANT's register (`add.s $f0,$f0,$f2`);
 * we put each fused temp in $f1/$f0 and coalesce into it, leaving c92 in $f2.
 *   * the `py = 106.0f; py = py + FY;` double assignment DOES produce retail's
 *     coalescing (the add lands in the constant's register) but numbers the
 *     pair $f1/$f0 instead of $f0/$f2: a SECOND attractor at 11 (5ab2eccd),
 *     reached by `+=`, by `FY + py` and by the pragma arm alike.
 *   * af66dd2d (10) is reached by SEVEN distinct spellings incl. a named fused
 *     temp `ft` (folded), the dx/dy mirror, the constant on the right and the
 *     reversed add -- the source-level address of this residue is exhausted at
 *     this coat.  Decks build/wf-normal/s79/{b1,b3,b5,b7,b9,c3..c9,d1}.
 * NOT MERGED.
 */
/* === SESSION 70 (2026-09-20, SOLO): 177 BAD -> 19, STILL EXACT 363 WORDS.
 * EVERY n_ogap GAP IS NOW EQUAL and all eight callee-saved FPRs match retail;
 * the only register diffs left are the caller-saved $f0/$f4/$f5 temps inside
 * loop 1.  Six edits, each measured, in order of what they bought:
 *
 *  1. -8   *** THE WHILE LOOP IS A ROTATED `goto` LOOP.  Retail's back edge is
 *     `daddu $17,$2,$0 / bnel $17,$0,.L004F42D0 / lw $5,0xC($17)` -- it copies
 *     the call result to the NAMED local, tests THAT, and hoists the body's
 *     first load into the ANNULLED slot.  `while ((en = f(&it)) != 0)` tests
 *     $2 and spends the slot on the copy, so the body's `lw $5,0xC($17)` is
 *     emitted at the loop top and EVERY WORD FROM 0x42D0 TO THE END SHIFTS BY
 *     ONE.  185 bad -> 57.  The spelling that reaches it:
 *         goto cond;
 *         for (;;) { <body> cond: en = f(&it); if (en == 0) { break; } }
 *     `for(;;){en=f(); if(!en) break; ...}` and `while(1)` are NOT it (they
 *     lose a word elsewhere); the DUPLICATED-call forms are +6.
 *  2. ***  THE DEAD `sq $2,0xC0($29)` NEEDS `volatile Vec v0;`.  Retail stores
 *     the loop-1 qword to BOTH 0xC0 (never read) and 0xF0.  mwcc dead-stores
 *     the 0xC0 one away: a chained assign, a split assign, two independent
 *     loads, the reversed chain, a `*(volatile __int128 *)` CAST, a u128
 *     typedef and three union/16-aligned aggregate types are ALL byte-identical
 *     (the cast-to-volatile does NOT keep the store).  Only the DECLARATION
 *     `volatile Vec v0;` + a split assignment does: that is the +1 that made the
 *     length exact.  (`volatile` here also leaves the slot map intact --
 *     it@0x118 o@0x100 v2@0xF0 lv@0xE0 base@0xD0 v0@0xC0 v1@0xB0.)
 *  3. -30  *** LOOP 1 REUSES THE SAME `px`/`py` LOCALS AS LOOP 2.  Loop 1 had
 *     the two coordinates INLINE in the `q->f00`/`q->f02` stores; naming them
 *     `px`/`py` -- the very locals loop 2 uses -- is 55 -> 25 and it is what
 *     UNDID THE CALLEE-SAVED FPR TRANSPOSITION: before it, ours coloured
 *     [lv.x,lv.z][py,px][sn,cs][dy,dx] where retail has
 *     [py,px][lv.x,lv.z][sn,cs][dy,dx], a clean two-PAIR swap worth 31 words
 *     (14 of them in the prologue, where the colour decides whether the entry
 *     `lwc1`s can interleave with the `swc1` saves).
 *     !! THE DECLARATION-ORDER AXIS IS A MEASURED NULL ON THIS UNIT: the f32
 *     block moved above the aggregates, `ang`/`px`/`py` hoisted or sunk, eight
 *     group permutations and `f32 lv[4]` in five positions are all
 *     byte-identical (only a full reversal differs, and it is worse).  This is
 *     the kind of unit levers.d/mwcc-fpr-decl-order-highest-first's REFUTATION
 *     note describes -- STATEMENT order is the live axis.
 *  4. -3   *** THE 6th CALL IS A C++ VIRTUAL CALL (`jalr $25`).  `lw $25,0xC0($4)
 *     / lw $25,0xB8($25) / jalr $25` with `this` UNADJUSTED: mwcc puts the vptr
 *     AFTER the leading data, so `struct Cam { u8 pad00[0xC0]; virtual ... };`
 *     is the layout, and 0xB8 is index (0xB8-8)/4 = 44.  A separate
 *     non-polymorphic base `struct Cam : CamBase` gives the IDENTICAL object.
 *     Indices 23/45/46 are each +1.  The original header's "no C++ vptr layout
 *     produces this" is RETRACTED.
 *  5. -2   loop 2's `dy` operand order: `(sn * ox) + (cs * oy)`, not
 *     `(cs * oy) + (sn * ox)` -- mwcc evaluates the SECOND operand of a
 *     commutative `+` first (levers.d/mwcc-commutative-add-operand-order).
 *  6. -2   loop 1's constant `sh` order is 0x8,0xA,0x4,0x6,0xC,0xE (we had
 *     0x4,0xC,0x6,0xE); and `q->f02` is stored before `q->f00` (-1).
 *
 * WHAT IS LEFT: 19 words, ONE CLASS, all inside loop 1 (0x41F8-0x4268).
 * Retail divides o.z FIRST, evaluates py's fused pair first
 * (`mula cs,oy / madd sn,ox`), then px's (`mula cs,ox / msub sn,oy`), then
 * BOTH `cvt.w.s`, then the `o.x`/`o.z` writeback, then two `mfc1 / nop / sh`
 * pairs.  Ours finishes px completely (add, cvt, mfc1, sh) before starting py.
 *   * ARMED NULL 1: the 32-cell statement/operand lattice (division order x
 *     px/py order x operand order inside each x store order) bottoms out at
 *     THIS object, 19.  Every py-FIRST cell is 28-31 because it re-transposes
 *     $f24/$f25 (cs/sn) -- a SWAP-pass beam, and no compensating edit found.
 *   * ARMED NULL 2: naming the integer conversions (`i0 = (s32)px;` etc, s32 and
 *     s16, both orders), a `volatile Box *` store, and redundant `(f32)` casts
 *     on loop 1's two sites are all inert or +1 (single-use names are forwarded
 *     before allocation).
 *   * !!! RETAIL'S SHAPE IS THE `wb_mid` ONE -- `o.x = ox; o.z = oy;` BEFORE the
 *     two q stores -- and it reproduces the whole block (both cvt, both swc1,
 *     then the mfc1/sh pairs) but is EXACTLY ONE WORD SHORT, every one of 24
 *     cells at 0x5a8: our scheduler hoists the first `mfc1` up as filler so the
 *     SECOND `mfc1 / nop / sh` hazard nop never appears
 *     (levers.d/normal-mfc1-hazard-nop is about guard polarity and does not
 *     apply -- there is no branch here).  The three loop-2 cast patterns are
 *     QUANTISED (0x574 / 0x594-0x598 / 0x5a4-0x5a8) so none of them is the +1,
 *     and reverting the clamp idiom or the pragma to pay for it is 244 bad.
 *     ==> THE UNIT NEEDS A +1 THAT BUYS A HAZARD NOP.  That is the whole task.
 * PRAGMA TABLE RE-PRICED at this coat: 22 names both ways + 5 levels, a bogus
 * name control, ARMED -- a CLEAN NULL.  `opt_loop_invariants off` is still
 * LOAD-BEARING (+1; removing it is 0x5a8) even though the goto rewrite made the
 * hoist it disables disappear; `optimization_level 3`/`4` equal the default
 * (0/1/2 are long), `opt_pointer_analysis on` does not compile, and
 * `scheduling off` is INERT.  Sweeps in build/wf-normal/s70/.  NOT MERGED.
 */
/* === SESSION 69 (2026-09-20, SOLO): 343 BAD -> 177, STILL EXACT 363 WORDS.
 * The retail listing was read end to end for the first time on this unit.
 * !!! THE TWO SESSION 31 `DEFINING-STATEMENT MOVE` INSTALLS BELOW WERE
 * SEMANTICALLY WRONG, and they were the only reason the draft reached retail's
 * length.  Both moved `ox`/`oy` ABOVE the `func_13BE40(&o, ...)` call THAT
 * WRITES `o`, so every rotation used the PREVIOUS iteration's vector
 * (levers.d/uninit-local-draft-screen.md).  Reverting them is CORRECT and costs
 * 16 words (363 -> 347) -- exactly the s31 pre-install length.  The 16 were then
 * bought back, every step measured:
 *
 *  1. +12  ***  `px`/`py` MUST STAY FLOATS AND BE RE-CONVERTED AT EVERY SITE.
 *     Retail spends `cvt.w.s`+`mfc1` at each of the three `(s16)(s32)px` sites;
 *     we value-numbered `(s32)px` ONCE and kept the INTEGER in $s6/$s7, which is
 *     5 words short per 0x3E site.  A REDUNDANT `(f32)` CAST on 2 of the 3 sites
 *     splits the value number (levers.d/mwcc-identity-cast-splits-cse.md).
 *     Per-site 2^3 grid + variants measured: `(u32)(s32)` == plain, `(f64)` is
 *     LONG, and casting ALL three or NONE collapses back to one conversion
 *     (0x57c).  Only a 2-of-3 split reaches 0x59c.
 *  2. +2   the tail `if (a->f4F0 == -1)` ARMS SWAPPED: retail branch-likelies to
 *     the SIMPLE arm with `a->f4F0 = -1` in the ANNULLED slot and falls through
 *     into the clamp, so the source is `if (a->f4F0 != -1) {clamp} else {simple}`.
 *  3. +2   the inner `if (en->v249() == 0)` ARMS SWAPPED the same way -- retail
 *     lays the `for (k...)` body FIRST, so the source is `if (v249() != 0)`.
 *  4. ***  `lx`/`ly` ARE `.x` AND `.z` OF A SIXTH `Vec`, NOT TWO `f32` LOCALS.
 *     Retail's prologue has `lwc1 $f22,0xE0($29)` / `lwc1 $f23,0xE8($29)` --
 *     reading an UNINITIALISED slot -- and 0xE0/0xE8 is EIGHT apart, which two
 *     f32 locals cannot be.  Declaring `Vec lv;` and using `lv.x`/`lv.z` bought
 *     the entry loads, retail's EIGHT callee-saved FPRs ($f20-$f27), retail's
 *     0x120 frame AND exact length in ONE edit: 343 -> 198.
 *  5. -6   the Vec DECLARATION ORDER sets the slot map.  Retail descending is
 *     it@0x118 o@0x100 v2@0xF0 lv@0xE0 base@0xD0 v0@0xC0 v1@0xB0, so the decl
 *     order is `it, o, v2, lv, base, v0, v1`.  198 -> 192.
 *  6. -15  `cnt = 0;` belongs immediately BEFORE `nd = func_1C4A90(...)`, not
 *     before `func_1C3BC0` -- retail sinks it into that call's delay slot.
 *     192 -> 177, and it closed ogap gaps 0, 2 and 6 at once.
 *
 * WHAT IS LEFT (n_ogap, 363 vs 363): gap12 -1, gap16 +1, gap21 +4, gap22 -5,
 * gap24 -1, gap25 +2.  FOUR NAMED CLASSES AND NOTHING ELSE:
 *  A. gap21/22: mwcc HOISTS the k-loop's `(s16)(s32)(f32)px` conversion into the
 *     loop preheader (4 words) where retail converts inside the if-body (5).
 *     `#pragma opt_loop_invariants off` REPRODUCES RETAIL'S SHAPE EXACTLY (every
 *     ogap gap from 17 to 24 goes equal) and costs +1 net; `optimization_level
 *     3` gives the IDENTICAL object, and level 4 == the default.  No source
 *     spelling found yet -- this is the unit's next lever.
 *  B. gap25 +2: the CLAMP IDIOM (levers.d/normal-session68-levers.md, s2a) --
 *     `tt = a->f4F4; t = tt + D_0047DA44; lim = D_0047D1FC; a->f4F4 = t;
 *      if (!(t < lim))` is exactly -2 and gives retail's three-`lwc1` head and
 *     `bc1t` with the `swc1` in the delay slot.  NOT installed because alone it
 *     makes the length wrong (361) and blocks byte scoring.  INSTALL IT WITH A.
 *  C. gap12 -1: retail has a DEAD `sq $2,0xC0($29)` (the `v0` copy) that mwcc
 *     always dead-stores away for us.  !! ARMED NULL, 6 arms, ALL byte-identical
 *     to the baseline: chained vs split assignment, `volatile __int128`, two
 *     independent stores from `nd->f180`, and the reversed chain.  The two
 *     STRUCT-assignment forms are +8/+6 words (elementwise, not lq/sq).
 *  D. the 6th call is `jalr $v0` for us and `jalr $25` for retail
 *     (`lw $25,0xC0($4)` / `lw $25,0xB8($25)`): still the table-vs-virtual
 *     question the original header names.  Costs bad words, not length.
 *
 * PRAGMA SWEEP, 22 names + 3 optimization levels, ARMED (`peephole off` 0x644,
 * `opt_common_subs off` 0x5e8, `opt_propagation off` 0x59c, `opt_lifetimes off`
 * 213 bad, and a bogus-name control byte-identical): only `opt_loop_invariants
 * off` and `optimization_level 3` move it usefully.  !! `scheduling off` is
 * INERT on this unit -- do not read that as "the schedule is not the residue".
 * The FPR declaration-order sweep (7 orders) is a clean null at 192.
 * Sweeps and the rebuild script in build/wf-normal/s69/.  NOT MERGED.
 */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_ox_L407_T406_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 354 words, ? bad   after: 359 words, ? bad   (retail 363 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_ox_L433_T431_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 347 words, ? bad   after: 354 words, ? bad   (retail 363 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
#pragma opt_loop_invariants off
/* normal 0x004F4050 -- FRESH, session 31 lane a2.
 * The minimap/radar refresh.  Rotates every party member's and every field
 * entity's world position into the 0x2A / 0x2B+i / 0x2E+i / 0x3E widget slots
 * by (cos,sin) of the camera yaw, at 1/8 world scale, centred on (92,106).
 *
 * `jalr $25` x6.  Five go through `lw $25,0x0($17)` -- vptr at offset 0,
 * first virtual at +0x08, so 0xBC/0x3D0/0x3EC/0x3F8 are indices
 * 45/242/249/252.  The SIXTH (`lw $25,0xC0($4)` / `lw $25,0xB8($25)`) has its
 * table pointer at object offset 0xC0 with `this` STILL the object, which no
 * C++ vptr layout produces -- written here as a plain table of function
 * pointers.  If that call reads bad, table-vs-virtual ($v0 vs $t9) is the
 * single arm to try next.
 * This is a .cpp, so `__attribute__((aligned(16)))` is silently dropped -- the
 * three 16-byte copies use the `__int128` cast instead
 * (levers.d/mwcc-aligned16-lq-sq.md).  The DOUBLE `sq` at 0xC0/0xF0 in the
 * first loop is modelled as a named __int128 temp feeding the vector.
 * gp -0x772C = D_0047DA44 (0.1f), gp -0x7F74 = D_0047D1FC (pi). */

struct Ent {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual s32 v045();                   /* -> vtable +0xBC */
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual void s224();
    virtual void s225();
    virtual void s226();
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual void s234();
    virtual void s235();
    virtual void s236();
    virtual void s237();
    virtual void s238();
    virtual void s239();
    virtual void s240();
    virtual void s241();
    virtual s32 v242();                   /* -> vtable +0x3D0 */
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual s32 v249();                   /* -> vtable +0x3EC */
    virtual void s250();
    virtual void s251();
    virtual s32 v252(s32 i);              /* -> vtable +0x3F8 */
    u8  padA[0xC - 4];
    s32 f0C;
};

typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;

typedef struct Node { u8 pad00[0x180]; Vec f180; } Node;

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
} Box;

typedef struct Rec { u8 pad00[0x20]; Box *f20; } Rec;

typedef struct Sub { u8 pad00[0x18E]; s16 f18E; } Sub;

typedef struct Grp { u8 pad00[0xC]; s32 f0C; } Grp;

typedef struct World { u8 pad00[0x4344]; s32 f4344; } World;


/* vptr at +0xC0: mwcc places it AFTER the leading data, so `this` is
 * unadjusted and the entry at 0xB8 is index (0xB8-8)/4 = 44. */
struct Cam {
    u8 pad00[0xC0];
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual f32  v044();
};
typedef struct Cam Cam;

typedef struct Holder { u8 pad00[0x18]; Sub *f18; s32 f1C; } Holder;

typedef struct It { s32 a; s32 b; } It;

typedef struct Ctx { u8 pad00[0x4F0]; s32 f4F0; f32 f4F4; } Ctx;

extern f32 D_0047DA44;              /* gp - 0x772C */
extern f32 D_0047D1FC;              /* gp - 0x7F74 */

extern "C" f32   func_128D30(f32 a);
extern "C" f32   func_128FD0(f32 a);
extern "C" void  func_13BE40(Vec *o, Vec *a, Vec *b);
extern "C" Cam  *func_1C3BC0(World *w, s32 id);
extern "C" Node *func_1C4A90(World *w, s32 id);
extern "C" World *func_1F5BE0(void);
extern "C" Holder *func_1FEDE0(void);
extern "C" Rec  *func_290460(Ctx *a, u16 id);
extern "C" void  func_290690(Ctx *a, u16 id, f32 r, f32 g, f32 b);
extern "C" void  func_2907A0(Ctx *a, u16 id, f32 v);
extern "C" void  func_291110(Ctx *a, u16 id, s32 c, s32 d);
extern "C" Ent  *func_370040(It *it);
extern "C" void  func_370170(It *it, s32 list);
extern "C" s32   func_3C2610(Sub *s, s32 a, s32 b);
extern "C" Grp  *func_3C2700(Sub *s, s32 i);

extern "C" void normal_FieldHudRadarUpdate_4f4050(Ctx *a);

void normal_FieldHudRadarUpdate_4f4050(Ctx *a)
{
    It      it;
    Vec     o;
    Vec     v2;
    Vec     lv;
    Vec     base;
    volatile Vec v0;
    Vec     v1;
    World  *w;
    Cam    *cam;
    Holder *h;
    Node   *nd;
    Grp    *gp;
    Ent    *en;
    Box    *q;
    s32     cnt;
    s32     i;
    s32     k;
    s32     n;
    u16     id;
    f32     ang;
    f32     cs;
    f32     sn;
    f32     dx;
    f32     dy;
    f32     px;
    f32     py;
    f32     pt;
    f32     ox;
    f32     oy;
    f32     t;
    f32     tt;
    f32     lim;

    if (func_290460(a, 0x2D) == 0) {
        return;
    }
    w = func_1F5BE0();
    if (w == 0) {
        return;
    }
    cam = func_1C3BC0(w, w->f4344);
    if (cam == 0) {
        return;
    }
    ang = cam->v044();
    cs = func_128D30(ang);
    sn = func_128FD0(ang);
    h = func_1FEDE0();
    if (h == 0) {
        return;
    }
    cnt = 0;
    nd = func_1C4A90(w, h->f18->f18E);
    if (nd != 0) {
        *(__int128 *)&base = *(__int128 *)&nd->f180;
        q = func_290460(a, 0x2A)->f20;
        q->f00 = 0x5C;
        q->f02 = 0x6A;
        q->f08 = 0x5C;
        q->f0A = 0x48;
        q->f04 = 0xC;
        q->f0C = 0xC;
        q->f06 = 0x1B;
        q->f0E = 0x1B;
    }
    n = func_3C2610(h->f18, 1, 1);
    for (i = 0; i < n; i++) {
        id = (u16)(i + 0x2B);
        q = func_290460(a, id)->f20;
        gp = func_3C2700(h->f18, i);
        if (gp != 0) {
            nd = func_1C4A90(w, gp->f0C);
            if (nd != 0) {
                *(__int128 *)&v0 = *(__int128 *)&nd->f180;
                *(__int128 *)&v2 = *(__int128 *)&v0;
                func_13BE40(&o, &v2, &base);
                ox = o.x / 8.0f;
                oy = o.z / 8.0f;
                px = (sn * ox) + (cs * oy);
                pt = (cs * ox) - (sn * oy);
                py = 92.0f + pt;
                o.x = ox;
                o.z = oy;
                q->f00 = (s16)(s32)py;
                ox = 106.0f + px;
                q->f02 = (s16)(s32)ox;
                q->f08 = 0x5C;
                q->f0A = 0;
                q->f04 = 0x18;
                q->f06 = 0x18;
                q->f0C = 0x18;
                q->f0E = 0x18;
            }
            func_2907A0(a, id, 1.0f);
            func_291110(a, id, 1, 1);
        }
    }
    func_370170(&it, h->f1C);
    goto cond;
    for (;;) {
        nd = func_1C4A90(w, en->f0C);
        if (nd != 0) {
            if (en->v242() == 0) {
                id = (u16)(cnt + 0x2E);
                q = func_290460(a, id)->f20;
                *(__int128 *)&v1 = *(__int128 *)&nd->f180;
                func_13BE40(&o, &v1, &base);
                ox = o.x / 8.0f;
                oy = o.z / 8.0f;
                dx = (cs * ox) - (sn * oy);
                dy = (sn * ox) + (cs * oy);
                px = 92.0f + dx;
                py = 106.0f + dy;
                o.x = ox;
                o.z = oy;
                q->f00 = (s16)(s32)px;
                q->f02 = (s16)(s32)py;
                q->f08 = 0x5C;
                q->f0A = 0x30;
                q->f0C = 0x18;
                q->f04 = 0x18;
                q->f0E = 0x18;
                q->f06 = 0x18;
                if (en->v045() != 0) {
                    lv.x = dx;
                    lv.z = dy;
                    func_291110(a, id, 1, 1);
                    func_290690(a, id, 1.0f, D_0047DA44, -1.0f);
                }
                if (a->f4F0 != -1) {
                    if (en->v249() != 0) {
                        for (k = 0; k < en->v249(); k++) {
                            if (a->f4F0 == en->v252(k)) {
                                q = func_290460(a, 0x3E)->f20;
                                q->f00 = (s16)(s32)(f32)px;
                                q->f02 = (s16)(s32)(f32)py;
                            }
                        }
                    } else {
                        if (a->f4F0 == en->f0C) {
                            q = func_290460(a, 0x3E)->f20;
                            q->f00 = (s16)(s32)(f32)px;
                            q->f02 = (s16)(s32)(f32)py;
                        }
                    }
                }
                cnt++;
            }
        }
cond:
        en = func_370040(&it);
        if (en == 0) {
            break;
        }
    }
    if (cnt == 1) {
        q = func_290460(a, 0x3E)->f20;
        q->f00 = (s16)(s32)(92.0f + lv.x);
        q->f02 = (s16)(s32)(106.0f + lv.z);
    }
    if (a->f4F0 != -1) {
        tt = a->f4F4;
        t = tt + D_0047DA44;
        lim = D_0047D1FC;
        a->f4F4 = t;
        if (!(t < lim)) {
            a->f4F4 = 0.0f;
        }
        func_2907A0(a, 0x3E, func_128FD0(a->f4F4));
    } else {
        a->f4F0 = -1;
        func_2907A0(a, 0x3E, 0.0f);
    }
}
