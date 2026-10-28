/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuOpenBurstUpdate_4fb280 1
#include "port/game_protos.h"
#line 1
/* === SESSION 92 (2026-09-22): 20 BAD -> MATCH, exact 388 words.  MERGED and
 * NORMAL.BIN RELINKED BYTE-IDENTICAL.  TWO EDITS, and the first came from a
 * NEW INSTRUMENT -- `#pragma schedule off` prints THE SCHEDULER'S INPUT
 * (build/wf-normal/s92/pre.py).  !! s69's note on normal_SpaceMenuUpdate_512070 that
 * "`scheduling off` is INERT" was a MISSPELLING: the pragma is `schedule`,
 * and it fires everywhere (this unit 388 -> 421 words).
 *
 * EDIT 1 (20 -> 4).  `id = D_004804C8[3] + i;` hoisted into the EXISTING
 * `u16 id` local, as the statement immediately BEFORE `q2 = &normal_D_005275A0[j]
 * .f02;`.  Read off the scheduler input: the first call's pre-call block
 * arrives as
 *     addiu s1 | lh 0(s0) .. mfc1 a2 | lh 2(s0) .. mfc1 a3 |
 *     lhu 6(gp) addu andi   <- the ID chain, 3rd from last
 *     lui 0x3f00 mtc1 $f12  <- 0.5f, 2nd from last
 *     move a0,s4            <- w, last
 * and BOTH schedulers hoist one of those tails into the float latency at the
 * top: ours hoists the 0.5f pair (freeing $2 for the id scratch and pushing
 * `andi $5,$2` into the delay slot), retail hoists the ID LOAD (so $2 stays
 * busy with 0.5f for 22 instructions, the id chain colours $4 and `daddu
 * $4,$20` takes the delay slot).  Moving the id chain EARLIER in the input is
 * the whole fix, and the caller-saved colours follow for free
 * (levers.d/caller-saved-colour-follows-scheduler).
 * !! THE POSITION AND THE VARIABLE ARE BOTH EXACT.  One statement later (the
 * s87/b2 column) is base; a FRESH `s32 idx` or `u16 idb` at the SAME position
 * is BYTE-IDENTICAL to base.  Only the existing `id` local, one statement up.
 * p3/p4/p5 (further up) are all length-wrong.
 *
 * EDIT 2 (4 -> MATCH).  `(s32)((dx + X) - ox)` for both coordinates -- s43's
 * association, INVERTED.  s87/b4 priced this at 21 against a base of 20 and
 * warned that reading "retail does add.s then sub.s" off the listing was an
 * offset artefact; at the OLD coat that was right, and at THIS one the
 * association is literally the last four words (levers.d/reprice-retired-
 * units).  `dx + X - ox` unparenthesised is the same object; the operand swap
 * `(X + dx) - ox` is 1; one side alone is 2. */
/* === SESSION 88 (2026-09-22): STILL 20 BAD.  The DECLARATION-ORDER axis is
 * re-priced AT THE NEW s87 COAT (s88/dsweep.py, 26 adjacent-swap /
 * move-to-front / move-to-end arms over the 27 locals -- the s37-era note
 * below only swapped `Spr *p2;` against `Box *b;`).  SIX distinct objects,
 * 20 / 24 / 24 / 24 / 24 / 43, and BASE (20) is the best.
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): 22 -> 20 BAD, exact 388 words.  ROOT CAUSE A
 * (words 100/101) IS CLOSED, and it closed on a DATED NULL RE-PRICED.
 *   ONE EDIT:  p2 = &normal_D_005275A0[(s32)j];      (was &normal_D_005275A0[i])
 * Retail computes p2's address from $19 while `i` is $18 (`addiu $2,$18,0x15`
 * two words later), so retail's source indexes p2 with `j`, not `i`.  s37
 * nulled the plain `[j]` spelling as LENGTH-WRONG (0x5f8 vs 0x610) and that
 * is STILL TRUE -- once the source claims i/j identity mwcc commons six more
 * words elsewhere.  THE INDEX CAST BUYS THE REGISTER WITHOUT THE COMMONING
 * (levers.d/mwcc-index-cast-defeats-cse): `[(s32)j]` and `[(u32)j]` are the
 * same new object at EXACT length, 20 bad.  `normal_D_005275A0 + j` = the short one,
 * `+ i` / `[(s32)i]` = base.
 * ROOT CAUSE B (the remaining 20 words, the first func_290F50's pre-call
 * block) -- THREE MORE ARMED NULLS, do not re-run:
 *  - s87/b2.py, 10 arms: the `id` temp (reused `id`, a fresh `u16`, an `s32`),
 *    a named `h = 0.5f` at two positions, a named `ww = w`, `(u16)` on the id,
 *    the operand swap.  THREE objects, ALL 20 -- `id_reuse` (60cfcbc8) and
 *    `id_swap` (ee992759) are new cross halves at the same score.
 *  - s87/b3.py: the WHOLE 68-name boolean `opt_*` table spelled `off`,
 *    ANCHORED BELOW `#pragma optimization_level 3` (probe-traps #133), armed
 *    both ways (bogus == base, `opt_unroll_count off` fails to build).  SEVEN
 *    live columns, none under 20: opt_lifetimes 30, opt_arithtransformation
 *    26, opt_rotateloops 277, and common_subs / propagation / foldconstants /
 *    loop_invariants all length-wrong.  ==> the pragma-ALONE column is closed
 *    on this unit at this coat.  (s72's "ten live columns incl.
 *    opt_treetransformation" was a DIFFERENT coat; here those are inert.)
 *  - s87/b4.py: THE ASSOCIATION.  `(dx + X) - ox` and `(X + dx) - ox` are 21,
 *    the dy half is 21, both halves 22, `+ -ox` is length-wrong.  Reading
 *    "retail does add.s then sub.s where we do sub.s then add.s" off the
 *    listing is a TRAP: the 20-word region is a PERMUTATION with an identical
 *    multiset, so the two streams are OFFSET BY ONE and every local
 *    "retail does X first" reading is an artefact of that offset.
 * Everything below predates this session. */
/* === SESSION 73 (2026-09-21, SOLO): 28 -> 22 bad, exact 388 words.  ALL SIX
 * of this unit's `.lit4` residue words closed, -1 each and exactly additive.
 * Each was a float LITERAL in our source where retail loads the shared MAIN
 * gp pool; written as externs (screen build/wf-normal/s73/lit4back.py, prices
 * build/wf-normal/s73/d3.py):
 *   0.4f -> D_0047D920 (gp-0x7850, TWO sites)   0.1f -> D_0047DA44 (gp-0x772C)
 *   1.2f -> D_0047D354 (gp-0x7E1C)              0.2f -> D_0047D5D0 (gp-0x7BA0)
 *   0.3f -> D_0047D94C (gp-0x7824)
 * Ã¢Å¡Â  the SAME VALUE lives at more than one pool address (0.1f is both
 * D_0047D91C and D_0047DA44; 0.3f is both D_0047D7C4 and D_0047D94C) -- take
 * the symbol from the RETAIL WORD at that address, never from the value.
 * The 22 left are the s72 schedule residue; this unit carries a
 * `#pragma optimization_level`, so probe-traps #133 applies to it.
 * Everything below predates this session. */
#include "types.h"
extern f32   D_0047D920;          /* gp - 0x7850, 0.4f */
extern f32   D_0047DA44;          /* gp - 0x772C, 0.1f */
extern f32   D_0047D354;          /* gp - 0x7E1C, 1.2f */
extern f32   D_0047D5D0;          /* gp - 0x7BA0, 0.2f */
extern f32   D_0047D94C;          /* gp - 0x7824, 0.3f */

/* === SESSION 43 (2026-09-07): 24 -> 22 bad, exact 388 words.  ONE EDIT:
 * the first func_290F50's coordinate arguments are ASSOCIATED as
 * `(s32)(dx + ((f32)normal_D_005275A0[j].f00 - ox))`, not `(s32)((dx + X) - ox)`.
 * That alone fixes the two `sub.s` slots.  Ã¢Å¡Â  `(dx - ox) + X` is LENGTH-WRONG
 * (0x608) and `((f32)X - ox) + dx` is byte-identical to the winner, so the
 * lever is WHERE THE PARENTHESES GO, not operand order.
 * RESIDUE 22, and it is ONE SCHEDULER TIE, not a spelling.  opscan.py says
 * d=0 (the instruction multiset is already retail's) and spscan.py is silent.
 *   retail  lhu $4,-0x4CA2($28) FIRST, the id chain in $4 (`addu $4,$4,$18 /
 *           andi $5,$4,0xFFFF`), 0.5f's `lui $2` kept live 22 instructions,
 *           and `mtc1 $2,$f12` + `daddu $4,$20,$0` at the very end / in the
 *           jal's delay slot.
 *   ours    `lui $2,0x3F00 / mtc1 $2,$f12` FIRST -- which frees $2 for the id
 *           scratch and pushes `andi $5,$2,0xFFFF` into the delay slot.
 * Ã¢Å¡Â  THE SECOND func_290F50 (same statement without the ox/oy subtraction) is
 * BYTE-IDENTICAL with the 0.5f-early idiom, so retail's compiler uses BOTH
 * idioms and the discriminator is the two extra `sub.s` in the first call.
 * NINE MORE ARMS, ALL 22 OR WORSE (do not re-run): the add-operand swap, the
 * `i + K` index swap, an explicit `(u16)` on the id, `0.5` as a double,
 * named `s32 ax/ay`, named `f32 fx/fy`, a `q0 = &..f00` pointer for both
 * calls, negating ox/oy at their definition (26), and emitting call 2 before
 * call 1 (35).  Every one is the same 22-word shift.
 * The remaining 2 words are the unchanged root cause A below. */
#pragma optimization_level 3
/* ARM IDENT8 */
/*
 * s37/n37a diagnosis (388 words, 24 bad -- length already correct, no prior
 * write-up existed before this session). Two root causes, BOTH register/
 * scheduling artifacts around already-byte-identical arithmetic -- no missed
 * mul.s/madd.s contraction anywhere in this unit, all float codegen already
 * matches retail exactly.
 *
 * Root cause A (2 bad words, 0x004FB410/0x004FB414):
 *   `p2 = &normal_D_005275A0[i];` (the line right after the second func_290460 call,
 *   used for the f14/f10/f0C/f24/f18 clamp-and-box-fill block) is indexed by
 *   `i`, but retail computes this address using THE SAME PHYSICAL REGISTER
 *   (s3) that already holds `normal_D_005275A0[j]`'s address earlier in the loop
 *   body -- i.e. retail's `sll v0,s3,2`/`addu v0,v0,s3` vs our
 *   `sll v0,s2,2`/`addu v0,v0,s2`. Since i and j are always numerically equal
 *   here (both start at 0, both incremented once per iteration, never
 *   diverge), this reads as retail's compiler folding the two array
 *   accesses onto one register.
 *   TRIED and NULLED, both regress badly (not just "no improvement" --
 *   active regressions), so do NOT repeat either:
 *     - Rewriting the line as `p2 = &normal_D_005275A0[j];` (literally using j
 *       instead of i): compiles to a SHORTER function, 0x5f8 vs 0x610 bytes
 *       -- mwcc over-commons additional code elsewhere once the source
 *       itself claims i/j identity, so this is not just a relabeled
 *       coincidence retail's compiler reached on its own; do not try this
 *       spelling again.
 *     - Hoisting `p2 = &normal_D_005275A0[i];` to the top of the loop body (before
 *       the q8/q4/q6 block) while leaving the rest of the block alone: also
 *       shortens the function (0x608 vs 0x610). Any statement-position move
 *       of this line changes downstream codegen size, so this is NOT a
 *       free register-only change -- do not retry a plain reposition.
 *     - Replacing p2 with the ALREADY-LIVE pointers that alias the same
 *       fields (*r14 for f14, *r10 for f10, *rC for f0C, normal_D_005275A0[j].f24/
 *       f18 for r24/f18, dropping p2 and rC2 entirely): catastrophic
 *       regression to 238 bad words at the SAME length -- mwcc schedules the
 *       whole block completely differently once p2 stops existing as its
 *       own temp. p2 as a distinct pointer variable is load-bearing for the
 *       surrounding structure; do not remove it.
 *   Whatever produces retail's s3 reuse here is NOT a simple aliasing/CSE
 *   rewrite reachable from this source shape -- untried: a construct that
 *   preserves p2 as its own variable (so the block's size/schedule survives)
 *   but nudges ONLY the register color chosen for its very first assignment
 *   (e.g. an intervening dummy statement, or reordering an unrelated
 *   declaration to shift interference-graph pressure) -- not attempted this
 *   session for lack of a concrete candidate.
 *
 * Root cause B (remaining ~22 bad words, 0x004FB678-0x004FB6DC, the FIRST
 *   func_290F50 call only -- `func_290F50(w, D_004804C8[3] + i, (s32)((dx +
 *   (f32)normal_D_005275A0[j].f00) - ox), (s32)((dy + (f32)*q2) - oy), 0, 0.5f);`):
 *   the actual float arithmetic for this call (add.s/sub.s/cvt.w.s chain)
 *   is IDENTICAL retail vs ours -- every float instruction and its operand
 *   registers match. The ONLY divergence is which GPRs hold two SCALAR
 *   integer temporaries and WHEN:
 *     - the id temp (`D_004804C8[3] + i`, masked to u16 for the call's a1)
 *     - the 0.5f literal's bit pattern before its `mtc1` into $f12
 *     - `w` being moved into a0 for the call
 *   Retail's pattern for THIS call: load D_004804C8[3] into a0 (not v0),
 *   add s2(i) into a0, mask into a1 EARLY (mid-block, well before the
 *   float chain finishes), hold v0 live with the 0.5f bit pattern the WHOLE
 *   time, and only move w into a0 in the jal's own delay slot (i.e. a0 is
 *   reused/repurposed three times: id-scratch, then w, in that order).
 *   Ours instead does the `mtc1 v0,$f12` immediately after the `lui`, reuses
 *   v0 (not a0) as the id scratch, moves w into a0 up front, and only masks
 *   id into a1 in the jal's delay slot.
 *   The SECOND func_290F50 call two lines later (`D_004804C8[2] + i`, same
 *   idiom, no ox/oy subtraction) is BYTE IDENTICAL retail vs ours using
 *   exactly the pattern we produce for call 1 (early mtc1, early a0=w,
 *   v0 as id scratch, late andi in the delay slot). So retail itself uses
 *   TWO DIFFERENT scheduling patterns for what is structurally the same
 *   call idiom, and the only source-level difference between the two calls
 *   is that call 1's a2/a3 expressions each have one extra `- ox`/`- oy`
 *   subtraction (2 extra float instructions) that call 2 does not have.
 *   This strongly suggests an mwcc list-scheduler heuristic sensitive to the
 *   exact instruction distance/latency between the id computation and the
 *   call, not something under direct source control.
 *   TRIED and NULLED (all zero net effect, i.e. produced byte-identical
 *   output to baseline -- confirms mwcc normalizes these particular
 *   spellings away, do not retry):
 *     - Extracting `id = D_004804C8[3] + i;` into its own statement before
 *       the call (matching the style every OTHER call site in this function
 *       already uses for its id argument): no change at all.
 *     - Reversing the addition operand order to `i + D_004804C8[3]`: no
 *       change.
 *     - Respelling the 0.5f literal as `5.0e-1f`: no change (expected --
 *       confirms this is a value-level literal pool, not text-sensitive).
 *   TRIED and NULLED (active regression, do not retry):
 *     - Moving `q2 = &normal_D_005275A0[j].f02;`'s statement position earlier
 *       (before `r18`/`dx`/`dy`): changes function length (0x61c vs
 *       0x610), so q2's declaration position is already load-bearing for
 *       the surrounding block's size -- do not reposition it.
 *   Genuinely untried: nothing that touches the float-op GROUPING of the
 *   `(dx + f00) - ox` expression was attempted, because that grouping is
 *   ALREADY exactly what produces the correct add.s-then-sub.s instruction
 *   pair -- any associativity change risks breaking the parts that already
 *   match and was judged not worth the regression risk this session. A
 *   fresh angle worth trying next: whatever register-pressure signal
 *   distinguishes call 1 from call 2 for mwcc's scheduler is almost
 *   certainly set by something EARLIER in the loop body (this session did
 *   not have time to bisect by temporarily deleting/shrinking earlier
 *   statements one at a time to find what specifically flips the
 *   scheduler's choice between the two call sites).
 *
 * s38/n38d: confirmed the 24-bad/388-word baseline still holds unchanged.
 *   Tried the untried idea root cause A named (perturb p2's first-assignment
 *   register color while keeping it as its own variable, WITHOUT changing
 *   the block's size/schedule):
 *     - Swapping the `Spr *p2;`/`Box *b;` declaration order (two variants:
 *       simple adjacent swap, and hoisting `Spr *p2;` to the very first
 *       declaration in the function): both NULL, zero effect, still
 *       exactly 24 bad at 388 words. Declaration-order alone does not
 *       reach p2's register color here (consistent with the decl-order
 *       tie-break lever only firing over callee-saved regs -- p2 may not
 *       be one in this frame).
 *     - Swapping the STATEMENT order of the adjacent
 *       `b = func_290460(w, id)->f20;` / `p2 = &normal_D_005275A0[i];` pair (p2
 *       first, then b): ACTIVE REGRESSION, 39 bad (up from 24) at the same
 *       388-word length. This is a real, reachable lever on this pair's
 *       vreg creation order, but it moves the WRONG direction -- do not
 *       retry this swap or any reordering that changes which of b/p2 is
 *       created first at this site.
 *   Root cause A and root cause B are UNCHANGED by anything tried this
 *   session; no candidate for the "intervening dummy statement" half of the
 *   untried idea was found that didn't risk the same kind of
 *   schedule-shifting regression seen above, given the round-trip budget.
 *   Root cause B (scheduling divergence between the two func_290F50 calls)
 *   was not reached this session -- parking after root cause A's 3 tries.
 *   Still parked at 24 bad / 388 words, length correct.
 */

typedef struct Spr {
    s16 f00; s16 f02; s16 f04; s16 f06; s16 f08; s16 f0A;
    f32 f0C; f32 f10; f32 f14; f32 f18; f32 f1C; f32 f20; f32 f24;
} Spr;

typedef struct Box { u8 pad00[4]; s16 f04; s16 f06; } Box;
typedef struct Wid { u8 pad00[0x20]; Box *f20; } Wid;

extern Spr normal_D_005275A0[];
extern u16 D_004804C8[4];
extern u8  D_0048445C;

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
s32 normal_BtlChgMenuOpenBurstUpdate_4fb280(void *w)
{
    s32  x;
    s32  y;
    s16 *q4;
    s16 *q6;
    s16 *q8;
    s16 *qA;
    s16 *q2;
    f32 *rC;
    f32 *r10;
    f32 *r14;
    f32 *rC2;
    f32 *r18;
    f32 *r1C;
    f32 *r20;
    f32 *r24;
    Spr *p2;
    Box *b;
    f32  dx;
    f32  dy;
    f32  ox;
    f32  oy;
    u16  id;
    s32  j;
    s32  i;
    s32  k;
    s32  nz;
    s32  nh;

    nh = 0;
    nz = 0;
    j = 0;
    if (UiGetWidgetAlpha_290770(w, 0x45) >= D_0047D920) {
        UiFadeWidgetAlpha_290690(w, 0x45, 0.0f, D_0047DA44, -1.0f);
    }
    if (D_0048445C == 1) {
        return 1;
    }
    for (i = 0; i < 16; i++) {
        q8 = &normal_D_005275A0[j].f08;
        q4 = &normal_D_005275A0[j].f04;
        q6 = &normal_D_005275A0[j].f06;
        normal_D_005275A0[j].f08 = normal_D_005275A0[j].f04;
        normal_D_005275A0[j].f0A = normal_D_005275A0[j].f06;
        r10 = &normal_D_005275A0[j].f10;
        r14 = &normal_D_005275A0[j].f14;
        qA = &normal_D_005275A0[j].f0A;
        rC = &normal_D_005275A0[j].f0C;
        normal_D_005275A0[j].f14 = normal_D_005275A0[j].f10;
        normal_D_005275A0[j].f10 = normal_D_005275A0[j].f0C;
        normal_D_005275A0[j].f0C = normal_D_005275A0[j].f0C + D_0047D354;
        if (normal_D_005275A0[j].f0C > 32.0f) {
            *rC = 32.0f;
        }
        if (*r10 > 20.0f) {
            *r10 = 20.0f;
        }
        if (*r14 > 10.0f) {
            *r14 = 10.0f;
        }
        id = i + 0x25;
        UiGetWidgetPos_2910a0(w, id, &x, &y);
        b = ((Wid *)UiFindWidget_290460(w, id))->f20;
        p2 = &normal_D_005275A0[(s32)j];
        b->f04 = (s16)p2->f14;
        b->f06 = (s16)p2->f14;
        b = ((Wid *)UiFindWidget_290460(w, i + 0x15))->f20;
        b->f04 = (s16)p2->f10;
        b->f06 = (s16)p2->f10;
        b = ((Wid *)UiFindWidget_290460(w, i + 5))->f20;
        b->f04 = (s16)p2->f0C;
        b->f06 = (s16)p2->f0C;
        rC2 = &p2->f0C;
        b = ((Wid *)UiFindWidget_290460(w, i + 0x35))->f20;
        b->f04 = (s16)(1.5f * *rC2);
        b->f06 = (s16)(1.5f * *rC2);
        ox = dptofp(dpmul(0.25, litodp(b->f04)));
        oy = dptofp(dpmul(0.25, litodp(b->f06)));
        *q4 = x;
        *q6 = y;
        r24 = &p2->f24;
        p2->f18 = p2->f18 - D_0047D5D0;
        p2->f24 = p2->f24 * p2->f24;
        if (p2->f24 > 14.0f) {
            *r24 = 14.0f;
        }
        r1C = &normal_D_005275A0[j].f1C;
        r20 = &normal_D_005275A0[j].f20;
        normal_D_005275A0[j].f1C = normal_D_005275A0[j].f1C - normal_D_005275A0[j].f24;
        normal_D_005275A0[j].f20 = normal_D_005275A0[j].f20 - normal_D_005275A0[j].f24;
        if (normal_D_005275A0[j].f1C < 0.0f) {
            *r1C = 0.0f;
        }
        if (*r20 < 0.0f) {
            *r20 = 0.0f;
        }
        if (*r1C == 0.0f && *r20 == 0.0f) {
            nz++;
        }
        r18 = &normal_D_005275A0[j].f18;
        dx = *r1C * Cosf_128d30(*r18);
        dy = *r20 * Sinf_128fd0(*r18);
        id = D_004804C8[3] + i;
        q2 = &normal_D_005275A0[j].f02;
        UiMoveWidgetUniform_290f50(w, id, (s32)((dx + (f32)normal_D_005275A0[j].f00) - ox), (s32)((dy + (f32)*q2) - oy), 0.5f, 0);
        UiMoveWidgetUniform_290f50(w, D_004804C8[2] + i, (s32)(dx + (f32)normal_D_005275A0[j].f00), (s32)(dy + (f32)*q2), 0.5f, 0);
        UiSetWidgetPos_290f60(w, D_004804C8[1] + i, *q4, *q6);
        UiSetWidgetPos_290f60(w, D_004804C8[0] + i, *q8, *qA);
        j++;
    }
    if (nz == 16) {
        for (k = 0; k < 4; k++) {
            for (i = 0; i < 16; i++) {
                id = i + D_004804C8[k];
                UiFadeWidgetAlpha_290690(w, id, 0.0f, 1.0f, -1.0f);
                if (UiGetWidgetAlpha_290770(w, id) <= 0.0f) {
                    nh++;
                }
            }
        }
        if (nh == 64) {
            UiFadeWidgetAlpha_290690(w, 0x45, D_0047D920, D_0047D94C, -1.0f);
            D_0048445C = 1;
            return 1;
        }
    }
    return 0;
}
