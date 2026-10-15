/* === SESSION 72 (2026-09-21, SOLO): **MATCH**, merged, NORMAL.BIN relinked
 * BYTE-IDENTICAL with an armed 1-byte control at 0x0050A240.
 * 13 -> 4 -> link-clean.  The four words n_obytecheck still calls bad are
 * MAIN .lit4 pool relocations ("defined in this object's .lit4"); n_olink
 * retargets them -- ALWAYS relink before believing a residue of lwc1 gp words
 * ([[overlay-normal]] s71 #9).
 * THREE EDITS, and all three only work under ONE pragma:
 *   0. `#pragma opt_dead_assignments off`.  Every earlier session's naming arm
 *      ("a named s32 m = i*38", "s32 id9 = i+9", "m = i*19; m = m*2" as two
 *      visible steps, 37 arms over s38/s39/s44/s51) was BYTE-IDENTICAL because
 *      this pass folds the name back onto the temp.  With it off, source
 *      statement order IS the vreg creation order and all of them become live.
 *   1. the i*38 strength-reduction chain written as FOUR separate assignments
 *      `m = i * 9; m = m * 2; m = m + i; m = m * 2;` -- one expression
 *      `((m*2)+i)*2` leaves `addu $2,$16,$2` where retail has `addu $2,$2,$16`
 *      (the commutative operand order is NOT spellable, the STEP COUNT is).
 *   2. `id = i + 9;` FIRST, above the float block.  That is the whole
 *      argument-setup order: retail materialises args 3 and 5 (`-0x4A`, `0`)
 *      before arg 4 (`38i + 0x32`), and naming either constant is inert --
 *      moving `id` is what re-times it.  `id` between the chain steps (s51's
 *      reading of retail, "i+9 created SECOND, in $3") is 7 bad.
 *   3. `fi = (f32)i;` named, so both gp float constants load before the mul.
 * LADDER (build/wf-normal/s72/v*.py): 13 -> 9 (chain steps) -> 8 (fi) ->
 * 7 (4 steps) -> 4 (id first).  ARMED: bogus pragma name == base,
 * `opt_unroll_count off` fails to build, `m_a/m_b/m_c` operand-order arms are
 * one object, and every /base cell of the ladder is the old 13.
 * Same lever as normal_TransMenuTopState_514e10 and normal_ThinkMenuPromptScrollStep_521660 this session.
 */
/* === SESSION 54 (2026-09-12, SOLO): STILL 9 BAD / 73 words.  The s38 header's
 * one untried lead -- "hoisting `i*38` into a named local computed in two
 * visible steps" -- is now MEASURED and it is a CLEAN NULL.
 * a_50a1c0.py, 8 arms: `m = i * 38;` before the calls, at the top of the body
 * (13, worse), as `h = i*19; m = h*2;`, as `m = i*19; m = m + m;`, as
 * `(i*19) << 1`, with `id = i + 9` named before or after it, and with only the
 * FIRST call using `m`.  Every cell is 9 -- four distinct objects
 * (a58b30c8 baseline, 6993a5fb, 8a24d2b0, 4b4ce951), so the arms are LIVE and
 * merely inert on the count; they are cross halves, not progress.
 * The residue is exactly two things and both are allocator, not shape:
 *   0x0050A1E8-FC  retail keeps the strength-reduction chain in ONE register
 *     ($2: 9i, 18i, 19i) and puts `i + 9` in $3 BETWEEN the 18i and 19i steps;
 *     we run the chain through $2/$3 alternately and put `i + 9` in $2 after
 *     it.  A two-web swap, and naming either side does not move it.
 *   0x0050A204-0C  retail materialises call args 3 and 5 (`-0x4A`, `0`) BEFORE
 *     arg 4 (`38i + 0x32`); ours does arg 4 first.  Same three instructions.
 */
/* === SESSION 51 (2026-09-08): no move (9 bad, 73 words).  The residue is
 * NAMED: retail keeps the WHOLE `i * 38` chain in ONE register --
 * `sll $2,$16,3 | addu $2,$2,$16 | sll $2,$2,1 | addu $2,$2,$16 |
 *  sll $17,$2,1` -- and creates `i + 9` SECOND, in $3, at 0x0050A1EC.
 * We alternate v0/v1 through the chain because our `i + 9` is created FOURTH
 * and steals v0 in the middle of it; the rest is the `lui $4` and the
 * `addiu $7,$17,0x32` argument-setup order sliding by two slots.
 * SEVEN ARMS, ALL 9 BAD WITH THE IDENTICAL CENSUS (v0>v1:4 v1>v0:1
 * zero>s1:1 a2>a3:1) -- a named `u16 id` before or after the float pair, a
 * named `s32 n = i * 38`, both, either order, `((i*9*2)+i)*2` written to
 * match retail's shift chain, and a `(u16)` cast at all three id sites.
 * Four of them are different OBJECT md5s but that is only the local symbol
 * names; the CODE is one object.  Deck: build/wf-normal/s51/a_50a1c0.py.
 * => the creation order of the two webs is not reachable from the argument
 *    expressions; the next arm has to be an allocator-level one. */
/* SESSION 44 (n44t, SOLO): 9 bad / 73 words, UNMOVED, 17 more arms.
 * s39's header named the one untried direction -- "changing what is LIVE
 * across the chain (e.g. the float temps' shape)".  It is now measured and it
 * is dead.  SIX DISTINCT OBJECTS, every one 9 bad with the IDENTICAL residue
 * census (v0>v1:4 v1>v0:1 zero>s1:1 a2>a3:1):
 *  - the float shape: `t = 0.18f + 0.02f*(f32)i;` as one statement,
 *    `t = s + 0.18f;`, a named `f32 fi = (f32)i;`, `s = (f32)i * 0.02f`
 *    (`t = 0.18f; t += s;` REGRESSES to 15);
 *  - all five remaining declaration permutations of (s, t, i) -- ONE object;
 *  - a `s32 m = i * 38;` DOMINATING DEFINITION
 *    ([[levers.d/mwcc-dominating-def-colouring]]), m declared first or last --
 *    a new object, still 9;
 *  - a named `id9 = i + 9;` web, declared first or last -- still 9;
 *  - `(s32)((u32)i * 38)` ([[levers.d/mwcc-index-cast-defeats-cse]]) -- 9;
 *  - the loop rewritten `i = 0; do { ... } while (i < 2);` -- 9.
 * All board screens (opscan/spscan/brscan and the new offset and immediate
 * screens) are SILENT on this unit.  ~37 arms over three sessions now agree
 * the $2/$3 transposition of the i*38 chain against `i+9` is not reachable
 * from C.  PARK IT. */
/* SESSION 39 (n39d, SOLO): NO MOVEMENT, still 73/73 words, 9 bad.
 * 15 more arms, all scored, all 9 bad except one regression.  The residue is
 * a v0/v1 TRANSPOSITION ([[residue-transposition-class]]) inside the i*38
 * strength-reduction chain: retail keeps the whole chain in $2
 * (8i,9i,18i,19i) and puts `i+9` in $3; ours runs 8i,9i in $2, then switches
 * the chain to $3 for 18i,19i and puts `i+9` in the freed $2.  Both then
 * land 38i in $17.  The other three bad words are the same instructions in a
 * different SCHEDULE order (retail sets the constant arguments $6,$8 before
 * the computed $7 = $17+0x32; ours sets $7 first).
 * CONFIRMED NULLS added this session -- do not re-try any of these:
 *   - naming the intermediates: `s32 m = i*38;` alone, `s32 id = i+9;` alone
 *     (re-confirming s38's null), BOTH with m declared first, BOTH with id
 *     declared first, and `m = i*19; m = m*2;` as two visible steps (the
 *     untried idea s38's own header named) -- ALL 9 bad, mwcc canonicalises
 *     the chain identically no matter how it is spelled.
 *   - hoisting `m = i*38;` ABOVE the two float statements: REGRESSION to 13.
 *   - the full COMMUTATIVE OPERAND-ORDER lattice, all 8 combinations of
 *     `i+9`/`9+i` x `i*38`/`38*i` x `m+0x32`/`0x32+m`
 *     ([[mwcc-commutative-add-operand-order]]) -- all 9 bad, every one inert.
 * Nothing in the source's integer shape reaches this.  Two sessions and
 * ~20 arms now agree it is list-scheduler/colouring only.  If it is picked
 * up again, the only untried direction is changing what is LIVE across the
 * chain (e.g. the float temps' shape), not the chain itself. */
#include "types.h"
#pragma usefloatacc off
#pragma opt_dead_assignments off
/* normal 0x0050A1C0 -- two rows of three readouts, then a pair gated on the
 * gp s16 at 0x00484600 not being 3.  $f20 is the shared alpha, live across
 * every call.  The gp floats are MAIN's `.lit4` pool -- 0.02f, 0.18f, 0.1f. */
/* SESSION 38 (n38g): PARKED at 73/73 words (exact length), 9 bad.
 * `#pragma usefloatacc off` is REQUIRED and CONFIRMED -- without it, mwcc
 * folds `0.18f + 0.02f*i` into the adda.s/madd.s accumulator idiom (retail
 * uses plain lwc1/lwc1/mul.s/add.s here, no accumulator) and the object is
 * 1 word too long (a stray swc1 spill of the accumulator's intermediate to
 * the stack). With the pragma the length is exact.
 * Residue (9 bad, exact length): the `i*38` strength-reduction chain (used
 * by both `func_290F50` calls' 4th argument) and the `i+9` / `i+6` id
 * arguments interleave in a DIFFERENT register order than retail. Retail
 * keeps the running product in $2 across 8i->9i->18i->19i->(sll->$17=38i)
 * and computes `i+9` into a SEPARATE register ($3) in between the 9i and
 * 18i steps; ours computes the same values but the multiply chain and the
 * `+9` land in swapped registers (v0/v1) and in a different order. Tried:
 * hoisting `i+9` into its own named local (`s32 id9 = i+9;`) declared before
 * the multiply expression -- NULL, identical 9-bad object. Reads as a pure
 * list-scheduler register-assignment tie-break over independent short
 * integer chains, not a statement-shape defect; no lever closed it this
 * session. Untried: hoisting `i*38` itself into a named local computed in
 * two visible steps (`i*18`, then `+i`, matching retail's exact shift/add
 * sequence) to see whether naming each INTERMEDIATE forces the same
 * register choices. */
extern s16 D_00484600;            /* gp - 0xB70 */
extern u8  D_00527C40[];

extern void func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void func_291110(void *p, u16 id, s32 a, s32 b);

s32 normal_ShopMenuTopRowsSlideOut_50a1c0(void)
{
    f32 s;
    f32 t;
    s32 i;
    s32 m;
    s32 id;
    f32 fi;

    for (i = 0; i < 2; i++) {
        id = i + 9;
        fi = (f32)i;
        s = 0.02f * fi;
        t = 0.18f + s;
        m = i * 9;
        m = m * 2;
        m = m + i;
        m = m * 2;
        func_290F50(D_00527C40, id, -0x4A, m + 0x32, 0, t);
        func_290F50(D_00527C40, i + 6, -0x47, m + 0x35, 0, t);
        func_291110(D_00527C40, i + 0xB, 1, 1);
    }
    if (D_00484600 != 3) {
        func_290F50(D_00527C40, 0x11, 0x104, -0x14, 0, 0.1f);
        func_290F50(D_00527C40, 0x10, 0x107, -0x11, 0, 0.1f);
    }
    return 0;
}
