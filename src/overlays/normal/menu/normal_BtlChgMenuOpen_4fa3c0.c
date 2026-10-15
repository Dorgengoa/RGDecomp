/* === SESSION 93 (2026-09-22): 6 -> MATCH, exact 297 words.  TWO EDITS, and
 * they are the UN-HOISTED COAT plus ONE TOKEN OF TYPE.
 *     Ctx *d = func_1FEDE0();
 *     u8 *n = (u8 *)func_3C2010(d->f18, 1, 1);      <- was `s32 n`
 *     for (i = 0; i < (s32)n; i++) { ... func_3C2420(d->f18, i) ... }
 * i.e. s75's hoisted `World *w` is GONE (retail re-loads d->f18 at both uses,
 * which s75 already proved and priced at "this coat floors at ~3 bad"), and
 * the loop bound is spelled as a POINTER.
 *
 * *** WHY THE TYPE IS THE WHOLE LEVER -- read this before touching any other
 * callee-saved transposition on this board.  mwcc numbers vregs 32.. with the
 * DECLARED LOCALS FIRST, in declaration order, and then temps in IR order; a
 * local with exactly ONE static def is PROMOTED into its defining temp and its
 * declared vreg dies ([[levers.d/mwcc-propagated-temp-colouring]]).  On this
 * unit c, d and n were all single-def call results, so all three arrived at
 * the allocator as HIGH temps 59 / 67 / 71 while `i` and `j` (two defs each:
 * init + increment) kept their low declared vregs 35 / 36.  Simplify removes
 * ascending-index inside a pass and select is that reversed, so 59 < 67 < 71
 * hands out n=$16 d=$17 c=$18 -- ours.  Retail is d=$16 c=$17 n=$18, which is
 * removal n, c, d, i.e. idx(n) < idx(c) < idx(d) -- reachable ONLY by getting
 * `n` back onto a DECLARED vreg (39, and 35 < 39 < 59 < 67 is retail exactly).
 * A POINTER-typed local is not promoted; an s32 one is.
 * MEASURED, all on the un-hoisted coat (build/wf-normal/s93/{g1,g2,g3,g4}.py):
 *  - `if (n < 0) n = 0;` (a real second def) gives RETAIL'S WHOLE MAP at +3
 *    words -- that is the proof of the mechanism, found before the free form.
 *  - the second def must reach THE SAME USE: renaming the bound to r / j / k,
 *    each of which already has two defs elsewhere, is BYTE-IDENTICAL to base.
 *  - TWELVE zero-word integer second defs are BYTE-IDENTICAL to base:
 *    `n = n;`, `n|0`, `n+0`, `(s32)(u32)n`, `~~n`, `if (0) n = 0;`,
 *    `if (n != n) n = 0;`, `while (0)`, `do{}while(0)`, `for(..;..;i++,n=n)`,
 *    `for(..; i < (n = n); ..)` -- the promotion decision is made AFTER folding
 *    and the pointer round trip of mwcc-propagated-temp-colouring is INERT for
 *    integer scalars, exactly as that lever warns.
 *  - all four POINTER spellings are ONE OBJECT and all MATCH: `u8 *` / `void *`
 *    with and without the `n = (u8 *)(s32)n;` round trip.  THE ROUND TRIP IS
 *    NOT NEEDED -- the TYPE alone keeps the web.
 *  - `#pragma opt_dead_assignments off` is 15 here, with or without a named n.
 * Instruments: s93/{q1,ral0}.py read the graph; s93/g1.py's arms are dumped
 * with `GDBS=ra91f.gdb GDBJ=raf python ra91.py <name>=arms/<name>.c`.
 * Everything below predates this session and is retained; note that every
 * "declaration order is inert" verdict in it is explained by the promotion --
 * those decks were permuting DEAD vregs. */
/* === SESSION 91 (2026-09-22): STILL 6 BAD -- and the UN-HOISTED (10-bad) coat
 * now has an EXACT ask read out of mwcc's own allocator, plus a WIDE armed
 * null on the degrees.  Decks build/wf-normal/s91/{d5,d6}.py, instrument
 * build/wf-normal/s91/{ra91,ral,rsw,dsrch,psrch}.py.
 *
 * 1. THE SPILL-COST LEVER THAT CLOSED normal_TransMenuMinimapMarkersDrawMaybe_5174d0 DOES NOT REACH HERE.
 *    Every callee-saved node on this unit has cost 0 and NO optimistic spill
 *    fires at all (every node leaves in simplify pass 1 or 2), so `cost/degree`
 *    is never consulted.  This unit is pure creation order + degree.
 *
 * 2. THE MECHANISM, exactly.  On the un-hoisted coat (s91/ra/unh.ra.json,
 *    select 240/240, simplify replay == dump):
 *        c = vreg 59  deg 67      d = vreg 67  deg 28      n = vreg 71  deg 28
 *        i = vreg 35  deg 27      pv = vreg 125 deg 26      K = 25
 *    ALL THREE of c, d, n leave in the SAME simplify pass, and within a pass
 *    mwcc scans ASCENDING index, so removal is c, d, n; the select list is that
 *    reversed and lowest-free hands out n=$16 d=$17 c=$18 -- ours, exactly.
 *    Retail is c=$17 d=$16 n=$18 (and pv=$18, j reusing d's $16), which is the
 *    removal order n, then c, then d.  Since c(59) < d(67) ascending, that is
 *    ONE condition and one only:
 *
 *        `n` MUST LEAVE SIMPLIFY ONE PASS EARLIER THAN c AND d
 *        (deg 28 -> below K = 25, i.e. four fewer live neighbours).
 *
 * 3. THE REACHABLE ASKS (s91/dsrch.py, 1- and 2-node over every live node
 *    inside its payable bounds).  NOTHING at one node, anywhere.  Two families:
 *        deg(c) +2   AND  deg(d) +3..+10       [8 cells]
 *        deg(i) -3..-7 AND deg(n) -3..-8       [30 cells]
 *    s91/psrch.py says the same thing from the other side: of the six creation
 *    orders of {c,d,n}, exactly two give retail's map, and both need `n`
 *    created FIRST -- which the source cannot do, because n is the result of a
 *    call that takes d.  So the lever is the PASS, not the index.
 *
 * 4. !! WIDE ARMED NULL: THE GRAPH IS RIGID (s91/d6.py).  Eight source shapes
 *    on the un-hoisted coat -- `n` at function scope, `d` at function scope,
 *    both, `n > i` for `i < n`, `k` folded into the subscript, `pv`/`pr` at
 *    function scope, `i` and `j` merged into ONE variable, and the whole
 *    if/else INVERTED -- produce an IDENTICAL callee-saved table: same node
 *    count 240, same degrees 30/28/28/67/29/27/26, same colours, same passes.
 *    Declaration scope, statement order, name merging and branch inversion do
 *    not move a single degree on this unit.  Do not sweep them again; the next
 *    arm has to change WHAT IS LIVE ACROSS WHAT.
 *
 * 5. !! mwcc is C89-strict about declaration placement: the else block opens
 *    with `Ctx *d = ...; s32 n = ...;` as DECLARATIONS, so any arm that turns
 *    the first of them into a statement (or inserts one before them) fails to
 *    compile with a misleading `undefined identifier 'n'` further down.  Three
 *    d6 arms died that way; declare at function scope instead.
 *
 * 6. !! the headers below QUOTE THE CODE verbatim (s75 prints the exact hoist),
 *    so a deck that edits the whole file hits the COMMENT first and silently
 *    builds a source that does not compile.  Split on the last comment
 *    terminator and edit the body only.
 * Everything below predates this session. */
/* === SESSION 88 (2026-09-22): STILL 6 BAD.  TWO ARMED NULLS.
 *  - s88/b1.py: THE -2 PARTNER THIS HEADER HAS ASKED FOR SINCE s82 EXISTS AND
 *    IT DOES NOT WORK.  s82: "`bind r16..r19` is LIVE but costs +2 WORDS, so
 *    it can only be spent against a -2 ... a -2 is the whole ask here."
 *    s87/e2 found two without looking: `opt_treetransformation off` and
 *    `opt_addtogetherconstantpartsoftreeexpressions off` are ONE object at
 *    295 w.  Crossed with r16/r17/r18/r19 (and with opt_rotateloops and
 *    opt_dead_assignments on top): 15 cells, EVERY ONE at EXACT 297 words and
 *    EVERY ONE 288-290 BAD against a base of 6.  Armed both halves alone.
 *    ==> a pragma's length delta is NOT a length half -- it is a
 *    whole-function rewrite, not a local edit.  The ask on this unit is now a
 *    SOURCE-side -2, and only that.
 *  - s88/dsweep.py: the declaration-order axis, 13 arms over {c,i,j,k,r}.
 *    !! ZERO REACH -- all 13 are BYTE-IDENTICAL to base (6c83d2c7).  This
 *    unit's five locals are not ranked by declaration order at all, so the
 *    null is a statement about the AXIS, not about the coat.
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): STILL 6 BAD.  TWO ARMED NULLS.
 *  - s87/h1.py works the 10-BAD COAT (the loop reading `d->f18`), which s75
 *    says is the only coat with a path to 0.  Its residue is the 3-cycle
 *    retail c=$17 d=$16 n=$18 against ours c=$18 d=$17 n=$16, and s75's
 *    mechanism says a plain `daddu $x,$2,$0` call-return copy is handed out
 *    DESCENDING in creation order while a web of another class takes $18
 *    first.  TEN spellings meant to take `n` out of the plain-copy class --
 *    `n=0` then assign, decl split from def, an identity cast, u32, s16, `n`
 *    declared in the OUTER scope, `i = i + 1`, `n > i`, `n-1` with `i <= n` --
 *    are FOUR objects and NONE under 10.  `s16 n` is +1 word.
 *  - s87/e2.py: the whole 68-name `opt_*` table, armed both ways.  Five live
 *    columns, none better: `opt_rotateloops off` 8 (20fbe55e, a new cross
 *    half), `opt_dead_assignments off` 11, treetransformation and
 *    addtogetherconstantparts -2 words, common_subs / propagation +.
 * Everything below predates this session. */
/* === SESSION 86 (2026-09-22): STILL 6 BAD.  s86/b1.py: c's and d's first def
 * moved INTO the using expression (`func_3C2010((c = func_1FEDE0())->f18,..)`,
 * `World *w = (d = func_1FEDE0())->f18;`): all ONE OBJECT with base -- a
 * call-result web is created at the copy after the jal whatever the spelling. */
/* === SESSION 82 (2026-09-21, SOLO): STILL 6 BAD / 297 words.  No move.  One
 * dated armed null and one priced gap.  Deck build/wf-normal/s82/i1.py.
 * The s75 header's reading is CONFIRMED word for word by the reloc-aware
 * lister (build/wf-normal/s82/bad3.py): words 48/50/52/53/71/73 are retail
 * keeping `d` in $16 and RE-LOADING d->f18 into $4 at both uses, against our
 * hoisted `w` in $18 with $16 taking `n`.
 * THE ONLY ALLOCATOR KNOB THIS BOARD HAS is s81's register binding
 * ([[levers.d/mwcc-register-binding-exit-seed]]), and on this unit
 * `bind r16..r19` is LIVE but costs +2 WORDS (s81 g1.log), so it can only be
 * spent against a -2.  i1.py prices the `const` ladder looking for one:
 *     add const  D_0047D5D0 +1   D_00481BBC +2   D_00484454+D_00481BBC +5
 *     drop const D_004B2570 / D_00527820 / D_00527020, singly and all three:
 *                BYTE-IDENTICAL
 *     (`const Pair D_004804D0[2]` does not compile -- it is written.)
 * ==> the const axis on this unit is POSITIVE-ONLY.  There is still NO -2 on
 * this unit, so the binding cross cannot be built; the header's `d` defined
 * last is -3 and does not pair either.  A -2 is the whole ask here. */
/* === SESSION 75 (2026-09-21, SOLO): 10 -> 6 BAD, exact 297 words, ONE arm --
 * and the three-cycle this file has carried since s19 is now HALF SOLVED.
 * THE ARM: hoist the World pointer into its own web --
 *     Ctx *d = func_1FEDE0();
 *     World *w = d->f18;            <- NEW
 *     s32 n = func_3C2010(w, 1, 1);
 * with the i-loop reading `func_3C2420(w, i)` instead of `func_3C2420(d->f18, i)`.
 * `c` is now $17 = RETAIL'S, and with it the WHOLE j-loop and the entire tail
 * go byte-exact: 0x4FA454, 5DC, 5EC, 600, 828, 838 all fixed (six words).
 *
 * ÃƒÂ¢Ã‹Å“Ã¢â‚¬Â¦ THE TRANSFERABLE FACT -- THE ACCESS FORM AT THE USE SITE PICKS THE COLOURS.
 * Nothing about declaration order, statement order or interference moved this
 * unit in six sessions.  What moved it is WHETHER THE LONG-LIVED POINTER WEB IS
 * A CALL RESULT OR A LOAD RESULT.  In the old coat all three webs (c, d, n) were
 * `daddu $x,$2,$0` copies of a call return and mwcc handed them out DESCENDING
 * in creation order (c=$18 d=$17 n=$16).  Make the long-lived one a `lw` result
 * instead and it leaves that class: it takes $18 and the two call results fall
 * into $17/$16 -- which is retail's `c`.  See
 * [[levers.d/mwcc-callee-saved-creation-order]]: the corpus fit's `call`
 * feature is real, and THE LEVER THAT TOGGLES IT IS THE USE SITE, not the decl.
 *
 * ÃƒÂ¢Ã…Â¡Ã‚Â ÃƒÂ¢Ã…Â¡Ã‚Â  BUT THE NEW COAT IS STRUCTURALLY WRONG WHERE THE OLD ONE WAS RIGHT, and it
 * CANNOT REACH 0.  Retail does NOT hoist: it loads d->f18 straight into the
 * argument register at 0x4FA480 (`lw $4,0x18($2)`) and RE-LOADS it inside the
 * loop, that reload being what the `bnel` duplicates into its delay slot at
 * 0x4FA4E4 (`lw $4,0x18($16)`).  We emit `daddu $4,$18,$0` at both places.  So
 * of the 6 remaining words THREE (0x480, 0x490, 0x4E4) are inherent to the
 * hoist and only THREE are the surviving {w,n} transposition:
 *     retail  c=$17  d=$16  n=$18        ours  c=$17  w=$18  n=$16
 * ==> this coat floors at ~3 bad; the 10-bad coat is the one with a path to 0.
 * Both are recorded; the 6 is installed because it is the better score.
 *
 * ÃƒÂ¢Ã‹Å“Ã¢â‚¬Â¦ THE WHOLE d/n/w SPELLING AXIS IS EXACTLY TWO OBJECTS (build/wf-normal/s75/
 * a2.py, 12 cells): 891f774f (6 bad, the loop reads `w`) and 9b6301d4 (10 bad,
 * the loop reads `d->f18`).  Byte-identical to the 6: `w` with no `d` at all
 * (`func_1FEDE0()->f18`), an identity cast on `w`, defs split from decls, the
 * decl trio in n/w/d order, and `n > i` for `i < n`.  Byte-identical to the 10:
 * `w` used for the CALL ARGUMENT ONLY with the loop reloading (mwcc folds the
 * named temp straight into $4), with or without the cast.  `w` defined AFTER
 * `n` is +4 words.  ==> do not sweep this region's spelling again; the only
 * open question is the {w,n} pair and the only new input left is a FOURTH
 * callee-saved web.
 * ALSO NULL this session (build/wf-normal/s75/a1.py): `n` derived from `c`
 * instead of `d` (11 bad); the same with `d` defined last (-3 words); seeding
 * `n` from the DISCARDED top `func_3C2010(c->f18,1,1)` return is byte-identical
 * to base (s50's dead-elimination null re-confirmed) AND its cross with
 * `#pragma opt_dead_assignments off` is identical to that pragma alone (15
 * bad), so the seed never survives, pragma or no pragma.  Bogus-pragma control
 * byte-identical.
 *
 * ÃƒÂ¢Ã…Â¡Ã‚Â ÃƒÂ¢Ã…Â¡Ã‚Â  TRAP #135 (s75, cost: one destroyed source file): `open(P,"w").write(s)`
 * TRUNCATES BEFORE IT ENCODES, so a UnicodeEncodeError on a ÃƒÂ¢Ã‹Å“Ã¢â‚¬Â¦ or ÃƒÂ¢Ã…Â¡Ã‚Â  in a header
 * string leaves the source file EMPTY and the traceback looks like a no-op.
 * Write headers as BYTES (`open(P,"wb").write(text.encode("utf-8"))`).  This
 * file was rebuilt from build/n_sweep_normal_FUN_004fa3c0.bak (pre-s50) plus
 * the s50 `pr` arm and re-verified by OBJECT HASH (9b6301d4 base / 891f774f
 * the new coat) before the headers went back on. */
/* === SESSION 52 (2026-09-08, SOLO): still 10 bad.  The s50 header's closing
 * instruction -- "the lever has to change the INTERFERENCE, not the order" --
 * was acted on and the most obvious interference edit is a MEASURED NEGATIVE.
 * Reusing `c` for the else-branch's second `func_1FEDE0()` instead of the
 * separate `Ctx *d` (a live-range SPLIT of `c`, semantically identical since
 * func_1FEDE0 is argument-free and is already called twice) is TWO WORDS SHORT
 * (0x49c vs 0x4a4): mwcc then colours the whole function with THREE
 * callee-saved GPRs where retail uses four.  `d` must stay a separate name.
 * A `Ctx *ct = c;` copy at the tail use is byte-identical to the baseline
 * (9cb0e868) -- mwcc coalesces it, so the copy/coalescing channel is a null
 * here as well.  The three-cycle (retail c=$17 d=$16 n=$18 with pv reusing
 * n's $18; ours c=$18 d=$17 n=$16 with pv reusing d's $17) is unchanged. */
/* s50 addendum -- the three-cycle survived 23 MORE cells, ALL ONE OBJECT
 * (9cb0e868): pv/pr hoisted to function scope, j before i, i last, c last,
 * r first, pr with no pv local, pr declared before pv, and FOUR
 * DOMINATING-DEFINITION seeds that capture the DISCARDED return value of the
 * top `func_3C2010(c->f18, 1, 1)` into `n` (and `c = d` for `d`) -- mwcc
 * dead-code-eliminates every one of them, so no web is created and
 * [[mwcc-dominating-def-colouring]]'s "the seed must not be dead" caveat is
 * re-confirmed here.  `r = -1;` hoisted above the if/else is one word SHORT.
 * The 95-column pragma screen (build/wf-normal/s50/pragwide.py) is also a
 * null: `opt_rotateloops off` 12, `opt_dead_assignments off` 15, everything
 * else length-wrong or == base. */
/* === SESSION 50 (2026-09-08, SOLO): 21 -> 10 BAD, exact 297 words, ONE arm,
 * and the unit is now EXACT ON EVERY STRUCTURAL SCREEN: relscan CLEAN, opscan
 * d=0, the new dslot.py says all 58 delay slots match, mdiff has zero hunks.
 * THE ARM: name the row in a local --
 *     Pair *pr = &D_004804D0[k];   ... func_290F60(..., pr->x, pr->y);
 * in the j-loop, with `k = D_00484460;` still first.  Found by the RELOCATION
 * stream + the delay-slot screen, which agreed on ONE fact: retail's loop body
 * BEGINS with `lw $5,-0xD10($28)` (k) and the `bnel` DUPLICATES that load into
 * its delay slot; ours began with `sll` (the pv index) and duplicated that
 * instead, so the gp read was one short (relscan 0x00484460 retail 6 -> ours 5)
 * and opscan read lw:19->18 / sll:11->12.  Ten OTHER loop spellings are ONE
 * OBJECT with the old baseline (k declared in the loop, pv first, pv as a decl
 * initialiser, D_00484460 inlined at both uses, pointer arithmetic for pv, a
 * do/while, an index cast, opt_rotateloops off, opt_markcounterloops off):
 * naming the ROW is the whole lever, not naming the index.
 *
 * WARN RESIDUE = 10 words, and it is the SAME CLEAN THREE-CYCLE the file has
 * carried since s19, unchanged by the new coat:
 *     retail  c=$17  d=$16  n=$18  (i=$19, pv reuses n's $18, j=$16)
 *     ours    c=$18  d=$17  n=$16  (i=$19, pv reuses d's $17)
 * RE-SWEPT AT THE NEW COAT and still ONE OBJECT (9cb0e868), 11 cells: all six
 * declaration orders of the hoisted trio, the trio declared LAST, d/n split
 * from their initialisers, `s32 n;` declared before `Ctx *d`, and
 * `n = func_3C2010((d = func_1FEDE0())->f18, 1, 1)`.  Ours is the corpus rule
 * ([[mwcc-callee-saved-creation-order]]: larger first-def -> lower register);
 * retail VIOLATES it on two of the three pairs (c<n and d<n), which is the
 * documented ~30% floor.  Do not sweep declaration order again -- the lever,
 * if it exists, has to change the INTERFERENCE, not the order. */
/* === SESSION 42 (2026-09-07, SOLO): STILL 21 BAD / 297 words, 13 new arms,
 * all BYTE-IDENTICAL to the baseline.  What the session establishes:
 * THE RESIDUE IS A CLEAN THREE-CYCLE over the callee-saved trio -- retail
 * holds d=$16, c=$17, n=$18; we hold n=$16, d=$17, c=$18 (census
 * s0>s1:6 s1>s2:3 s2>s0:3, 12 of the 19 rename words).
 * ÃƒÂ¢Ã…Â¡Ã‚Â ÃƒÂ¢Ã…Â¡Ã‚Â  ALL SIX DECLARATION ORDERS of c/d/n give the BYTE-IDENTICAL OBJECT, so
 * on this unit declaration order is fully DOMINATED by first-definition order
 * ([[levers.d/mwcc-gpr-decl-order-map]]) -- do not sweep it again.
 * Also byte-identical: seven spellings of the j-loop body (pv before k, k
 * block-scoped, pv as a decl-initialiser, the index inlined); the two arms
 * that read the u16 by VALUE instead of through a pointer are 1 word long.
 * The remaining lever must change WHICH VALUE IS CREATED FIRST, not how it is
 * declared.  See [[levers.d/normal-session42-levers]]. */
/* r2d (session 19): STILL 21 BAD, RIGHT LENGTH.  D_0047D5D0 is the pool
 * literal 0.2f; the `0.2f` spelling was MEASURED and is byte-NEUTRAL here
 * (21 -> 21), so the file keeps the extern.  The residue is nowhere near that
 * load, and this is the negative half of the pool lever: it pays only where
 * retail HOISTS the load past something.
 * THE CALLEE-SAVED 3-CYCLE IS NOW AN EXHAUSTIVE NEGATIVE.  `d` and `n` were
 * hoisted out of the guarded block to the function's declaration list and ALL
 * SIX permutations of {c, d, n} were swept in one round trip: every arm, plus
 * the hoisted base, produced the BYTE-IDENTICAL object fa6202fe.  7 cells, ONE
 * object.  Hoisting them out of the block is itself inert, which independently
 * re-confirms the recorded block-scoping null.
 * => mwcc's callee-saved assignment here is NOT declaration-order driven
 * (ours is descending by DEFINITION order: c=$18, d=$17, n=$16; retail is
 * c=$17, d=$16, n=$18), and declaration order is the whole search space named
 * by levers.d/insect-scheduler-tiebreak.  PARKED for good; needs a lever that
 * reaches the allocator, not a spelling. */
/* ÃƒÂ¢Ã…Â¡Ã‚Â  PARKED at 21 words of 297 (1,188 bytes).  NOT in config/ocunits/normal.txt.
 * STRUCTURE IS CORRECT: right length, all 45 calls in order, EVERY n_ogap gap
 * exact.  The 21 are one 3-CYCLE in the callee-saved assignment and everything
 * else cascades from it:
 *     retail  c=$17  d=$16  n=$18
 *     ours    c=$18  d=$17  n=$16
 * `c` has the longest live range (to the last statement) and retail gives it
 * the MIDDLE register while giving the shortest-lived value the highest; we
 * hand them out descending in definition order.  Once `c` takes $18 the j-loop
 * has to place `j` and `pv` in the wrong two registers as well.
 * Measured and byte-for-byte identical: declaration order n/c/d, block-scoping
 * `d` and `n` inside the guarded arm, and swapping `k` and `pv` in the loop
 * body.  Three attempts -> parked per the rule in overlay-c-pipeline.md. */
#include "types.h"
/* normal 0x004FA3C0 -- the gameplay scene's entry/refresh.  1,188 bytes.
 *
 * D_004804D0 is an array of {s16 x; s16 y;} -- splat names its second half
 * D_004804D2 separately, but `addiu $2,$28,-0x4C9E` + the SAME `$16` scale is
 * the .y of the same element, not a second array.
 * `andi $4, $2, 0xFF` on a call result is the callee returning u8. */
typedef struct Pair  { s16 x; s16 y; } Pair;
typedef struct World { u8 pad000[0x18E]; s16 f18E; } World;
typedef struct Node  { u8 pad00[0x26]; s16 f26; } Node;
typedef struct Ctx   { u8 pad00[0xC]; Node *f0C; u8 pad10[0x18 - 0x10]; World *f18; } Ctx;
typedef struct Obj   { u8 pad000[0x44C]; s16 f44C; s16 f44E; } Obj;

extern const u8 D_004B2570[];
extern const u8 D_00527820[];
extern const u8 D_00527020[];

extern s32   D_00484448;
extern Obj  *D_00484454;
extern u8    D_00484470;
extern s16   D_00484468;
extern s32   D_0048446C;
extern s32   D_0048444C;
extern s16   D_00484464;
extern s32   D_00484440;
extern s32   D_00484460;
extern u8    D_0048445C;
extern s16   D_004804DC;
extern u16   D_004804C0[4];
extern Pair  D_004804D0[2];
extern void *D_00481BBC;
extern f32   D_0047D5D0;

extern void  normal_BtlChgPageResetState_506290(Obj *p);
extern void *func_206A40(void);
extern void *func_42C950(void *a, s32 b);
extern void  normal_BtlChgPageSetStateTable_506230(Obj *p, void *b);
extern void  func_183950(const void *a, s32 b);
extern void  func_183D50(const void *a, s32 b, s32 c, s32 d);
extern Ctx  *func_1FEDE0(void);
extern s32   func_3C2010(World *a, s32 b, s32 c);
extern void *func_3C2420(World *a, s32 b);
extern u8    func_3AE1A0(void *a);
extern void  func_291110(const void *a, u16 id, s32 c, s32 d);
extern void  func_290690(const void *a, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F60(const void *a, u16 id, s32 c, s32 d);
extern void  func_2907A0(const void *a, u16 id, f32 x);
extern void  func_290F50(const void *a, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void  func_290A40(const void *a, u16 id, u32 c, s32 d);
extern void  normal_BtlChgMenuPanelGlowMaybe_4faf20(s32 a, s32 b);
extern void  normal_FieldHudAllySuggestHide_4f09b0(const void *a);
extern void *func_28AA30(void *a, s32 b);
extern void  func_28F510(const void *a, u16 id, void *c, s32 d);
extern s32   func_2F5440(void);
extern void  normal_BtlChgMenuLeaderDownNoticeMaybe_4fa870(void);
extern void  normal_BtlChgPageSetMember_505fa0(Obj *p, s32 b);
extern void *normal_UiPageGetList_289b50(Obj *p);
extern void  func_28EA40(void *a, s32 b);
extern u8    normal_BtlChgMenuGetCommandRow_501230(void);
extern void  normal_BtlChgMenuOpenBurstStart_4fb890(const void *a, s32 b, s32 c);
extern void  normal_BtlChgMenuSetCommandRow_501220(s32 a, s32 b);

void normal_BtlChgMenuOpen_4fa3c0(s32 a, u8 b)
{
    Ctx *c;
    s32 i;
    s32 j;
    s32 k;
    s32 r;

    D_00484448 = a;
    D_00484470 = b;
    D_00484468 = 1;
    D_0048446C = 0;
    D_0048444C = 0;
    D_00484464 = 0;
    normal_BtlChgPageResetState_506290(D_00484454);
    normal_BtlChgPageSetStateTable_506230(D_00484454, func_42C950(func_206A40(), 0xB));
    func_183950(D_004B2570, 0x78);
    func_183D50(D_004B2570, 0xF000, 0xA, 3);
    D_00484440 = 0;
    c = func_1FEDE0();
    func_3C2010(c->f18, 1, 1);
    if (D_00484448 != 1) {
        r = -1;
    } else {
        Ctx *d = func_1FEDE0();
        u8 *n = (u8 *)func_3C2010(d->f18, 1, 1);
        D_00484460 = -1;
        for (i = 0; i < (s32)n; i++) {
            if (func_3AE1A0(func_3C2420(d->f18, i)) == 1) {
                D_00484460 = i;
                if (D_00484470 != 0) {
                    D_004804DC = i;
                }
            }
        }
        func_291110(D_00527820, 1, 1, 1);
        func_290690(D_00527820, 1, 0.0f, -1.0f, 0.0f);
        func_291110(D_00527820, 2, 1, 1);
        func_290690(D_00527820, 2, 0.0f, -1.0f, 0.0f);
        func_291110(D_00527820, 3, 1, 1);
        func_290690(D_00527820, 3, 0.0f, -1.0f, 0.0f);
        func_291110(D_00527820, 4, 1, 1);
        func_290690(D_00527820, 4, 0.0f, -1.0f, 0.0f);
        for (j = 0; j < 4; j++) {
            u16 *pv;
            Pair *pr;
            k = D_00484460;
            pr = &D_004804D0[k];
            pv = &D_004804C0[j];
            func_290F60(D_00527820, *pv, pr->x, pr->y);
            func_2907A0(D_00527820, *pv, 0.0f);
        }
        r = -1;
    }
    normal_BtlChgMenuPanelGlowMaybe_4faf20(r, 0);
    normal_FieldHudAllySuggestHide_4f09b0(D_00527020);
    func_291110(D_00527820, 0x46, 1, 1);
    func_28F510(D_00527820, 0x46, func_28AA30(D_00481BBC, 0x49), 0);
    func_28F510(D_00527820, 0x46, func_28AA30(D_00481BBC, 0x4A), 1);
    if (func_2F5440() == 0) {
        func_290A40(D_00527820, 0x46, 0xFF404040, 0);
    } else {
        func_290A40(D_00527820, 0x46, 0xFF202020, 0);
    }
    func_290F60(D_00527820, 0x46, -0x20, 0x78);
    func_2907A0(D_00527820, 0x46, 0.0f);
    func_290F50(D_00527820, 0x46, 0x12, 0x78, 1, 10.0f);
    func_290690(D_00527820, 0x46, 1.0f, D_0047D5D0, -1.0f);
    D_0048445C = 0;
    if (D_00484470 != 0) {
        normal_BtlChgMenuLeaderDownNoticeMaybe_4fa870();
        func_291110(D_00527820, 0x47, 1, 1);
    } else {
        func_291110(D_00527820, 0x47, 0, 1);
        D_00484454->f44E = 0;
    }
    normal_BtlChgPageSetMember_505fa0(D_00484454, D_00484460);
    func_28EA40(normal_UiPageGetList_289b50(D_00484454), 0x55F2);
    k = D_00484460;
    normal_BtlChgMenuOpenBurstStart_4fb890(D_00527820, D_004804D0[k].x,
                        D_004804D0[k].y - 0xF + normal_BtlChgMenuGetCommandRow_501230() * 25);
    D_00484454->f44C = 1;
    if (c->f0C->f26 == 0) {
        normal_BtlChgMenuSetCommandRow_501220(c->f18->f18E, 0);
    }
}
