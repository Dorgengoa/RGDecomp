/* === SESSION 53 (2026-09-08, SOLO): CLOSED.  34 bad / 115 words -> MATCH,
 * object 2839f135.  FOUR edits, ALL read off the MERGED, byte-identical,
 * ADJACENT sibling `normal_TransWarpListScrollState_51bdb0` (clone.py: 140w, 0.829 opcode
 * overlap).  The two units are near line-for-line; nobody had diffed them.
 *
 * (1) `q = func_1DCB50(n);` -- the twin KEEPS that call's result in q, where
 *     we discarded it and wrote `q = pl;`.  34 -> 32, census 19 -> 15.
 * (2) `func_3242B0(void *p, f32 *x, f32 *y, s32 n)` -- the twin declares the
 *     last parameter s32, we had u8.  THE TELL IS opscan: `andi 2 -> 0`, and
 *     retail carries `andi $7,$4,0xFF` TWICE at 0x0051BCDC/CE8.  A u8 argument
 *     against an s32 parameter is masked BY THE CALLER; declared u8 the callee
 *     narrows and the caller emits nothing ([[merged-callee-signature-oracle]],
 *     [[mwcc-daddiu-unsigned-narrow]]).  ALONE THIS IS +1 WORD.
 * (3) the twin's FALLBACK SHAPE -- the `fallback:` label written INSIDE the
 *     `if (id < 0) { }` block with `cid = id;` after it, no `join:` label --
 *     plus its statement order (`hval = 1;` FIRST, then dx, then `h8 = h + 8;`
 *     BETWEEN dx and dy).  ALONE THIS IS -1 WORD.
 *     ⚠ the shape WITHOUT the statement reorder is -2, so the reorder is
 *     worth exactly one word and both halves of (3) bind.
 *     (2) x (3) is the cross: exact length, 1 bad.
 * (4) `u8 hval` + `normal_TransMenuBobIconShow_5183c0(u8 a)` -- the twin's `vis`.  1 -> MATCH.
 *     ⚠ MEASURED WORSE ALONE at both earlier coats (35 each, and 34 as a
 *     pair), which is why five sessions never kept it: it is only live once
 *     (2)+(3) are in ([[two-edit-cross-beats-count-ranking]]).
 *
 * MEASURED INERT: declaring `h8` FIRST of all locals, as the twin does
 * (byte-identical at every coat tried -- decl order does not reach this unit).
 */
/* SESSION 44 (n44y, SOLO): 34 bad / 115 words, UNMOVED, 36 arms.
 * The immediate screen written this session (offscan.py --imm) states the
 * whole narrow-type defect in one line:
 *     daddiu 0x1: retail 2 -> ours 1     addiu 0x1: retail 3 -> ours 4
 *     andi 0xff:  retail 2 -> ours 0
 * s43 found the FIRST of those (flagByte).  The screen names a SECOND that s43
 * never looked for: retail also spells `hval = 1` as `daddiu $16,$0,1`
 * (0x0051BD38), so hval is a narrow unsigned local too
 * ([[levers.d/mwcc-daddiu-unsigned-narrow]]).
 * MEASURED, the full 3 x 3 x 4 cross of {flagByte u8/u16/s32} x
 * {hval s32/u8/u16} x {h8 = h + 8 hoisted before the call / after dx / after
 * dy / before the call}: 27 of 36 cells are LENGTH-WRONG, 3 reproduce the
 * baseline object and 6 read 35.  `u8 hval` and `u16 hval` are one object each
 * and both are +1 bad at correct length; every non-u8 flagByte is length-wrong
 * in every h8 position.  So hval's width IS a live axis and it still needs the
 * same -1 partner flagByte's does.  The residue also shows retail computing
 * `h8` TWELVE WORDS earlier, interleaved into the dx/dy float block, which no
 * h8 position tried reaches. */
#include "types.h"
/* === SESSION 43 (2026-09-07): still 115 w / 34 bad, but the FIRST cluster is
 * now read off exactly, from build/wf-normal/s43/opscan.py's `andi:2->0`.
 * Retail keeps flagByte in $4 across the whole if/else-if and NARROWS INTO the
 * argument register -- `daddiu $4,$0,1` ... `daddu $4,$0,$0` ... `andi
 * $7,$4,0xFF` -- and the SECOND `andi` at 0x0051BCDC is just the first one
 * duplicated into a branch-LIKELY delay slot, so the source carries ONE
 * conversion.  We materialise flagByte straight into $7 and emit no narrowing
 * at all, and fill that delay slot with the next statement's `$4 = q`.
 * ⇒ retail's local is UNSIGNED NARROW (the `daddiu`) but WIDER THAN THE u8
 * PARAMETER -- i.e. `u16` ([[levers.d/mwcc-local-width-at-assignment]]:
 * a wide local narrows AT THE CALL, a matching-width local at the assignment).
 * ⚠ MEASURED: `u16 flagByte` DOES buy the narrowing and is +1 word (0x1d0);
 * u32/s32/s16 are one object with each other and also +1 (they lose the
 * `daddiu` as well).  So the close needs a -1 partner and I did not find it:
 *  - deleting the `h8 = h + 8;` hoist this file's header calls a length fix is
 *    ALSO +1 (0x1d0), not -1 -- that claim is STALE in the current coat;
 *  - `h8` moved to three other positions: +1 each;
 *  - merging `pl` into `q` (two spellings) : +1 each, and crossed with u16 +2.
 * NEXT: the -1 has to come from somewhere else in the unit.  Cluster 1
 * (retail puts `q = pl` in func_201A70's own DELAY SLOT, we put it after the
 * guard) is still the untouched 2 words and is the obvious place to look.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* WARNING PARKED, session gr2-park (re-open pass): tried the digest's u8/daddiu
 * lever (#10) + hoisting h8=h+8 on top of gr12's 2-words-over park.  NET
 * RESULT: `u8 flagByte` (kept below) DOES fix the length -- 0x1d4 -> 0x1d0
 * with u8 alone (still 1 word over), and adding `h8 = h + 8;` right after
 * func_3242B0 (also kept) closes the LAST word: len now EXACTLY 0x1cc = 115
 * words, matching retail.  But the combination now reads 34 BAD WORDS at
 * that correct length -- worse on the "bad words" axis even though the
 * length axis is finally right.  Do not revert these two changes without
 * re-deriving the length fix; the next lane should fix content, not length.
 *
 * `q = pl = func_201A70();` (residue item 1 below, gr12's untried arm) was
 * tried and is a MEASURED NULL -- rebuilds byte-IDENTICAL to the two-statement
 * `pl = func_201A70(); q = pl;` form already in this file. Do not re-try it.
 *
 * normal 0x0051BBE0 -- resolves the active follower's screen position and
 * hands it (or a fixed off-screen fallback) to normal_TransMenuBobIconMoveTo_518420 /
 * normal_TransMenuBobIconShow_5183c0.  Mirrors normal_TransMenuDraw_5163a0's
 * func_15DE80/func_1451E0/func_1451D0/func_1E49B0/func_1DCB50/func_201A70
 * chain, but resolves the target through func_324270 twice against
 * D_00484768 instead of reading e->f18->fXX directly.
 *
 * Solved arms (keep these, all measured byte-exact against retail up to the
 * points below):
 *   - a bare `func_1FEDE0();` call with the result discarded sits right
 *     after normal_TransWarpCursorBob_51c720(...) -- easy to miss reading the .s cold.
 *   - EVERY early "return 1" must be a NESTED `if (cond != 0) { ... }` all
 *     the way down to one shared `return 1;` at the very end, not a flat
 *     chain of `if (cond == 0) return 1;` guards -- the flat form compiles
 *     retail's single long `beql ...,to-epilogue` into a short local skip
 *     instead, costing 2 words per guard.  Same lever closed 00503450.
 *   - the flagByte passed to func_3242B0 is a genuine `u8` parameter (not
 *     s32) -- declaring it u8 in the extern reproduces retail's per-arm
 *     `andi $a3,$a0,0xFF` tail-merge; declare `flagByte = 1;` BEFORE
 *     `id = -1;` (source order, not just "both before the if").
 *
 * RAW DIFF at this writing (gr2-park build, right length, 34 bad; addresses
 * are the FIRST divergence in each cluster, read with dv_osbuild --verbose):
 *   1. 0x51BC80/BC88: retail places `daddu $s4,$v0,$zero` (q = pl) in the
 *      jal's own delay slot (right after `jal func_201A70`); ours STILL
 *      places it one instruction later (after the `beqz $v0,...` guard's own
 *      delay slot) even with the two-statement form -- this local 2-word
 *      swap is UNCHANGED by anything tried so far and is the first
 *      divergence.  Not yet closed by any arm.
 *   2. 0x51BCC4: `daddiu $a0,0,1` for flagByte's literal 1 now matches
 *      register-wise as $4 in retail vs OURS NOW USING $7 -- the `u8`
 *      change fixed the opcode (daddiu, lever 10) but shifted flagByte to a
 *      different argument-staging register, and everything from 0x51BCC4
 *      through 0x51BD60 (the whole float/guard tail) now shows a
 *      register-renumbering cascade, not just isolated opcode diffs.
 *      Suspect: `u8 flagByte` needs a companion change (declare it in a
 *      different position among the locals, or keep the wide-then-narrow
 *      pattern from lever 11) to land in $4 instead of $7 -- UNTRIED.
 *   3. The `h8 = h + 8;` hoist's own placement (right after func_3242B0) was
 *      NOT individually verified against retail's exact instruction address
 *      for `addiu $v1,$s0,8` in this new register-shifted layout -- worth
 *      rechecking once (2) is fixed, since the register cascade may have
 *      moved it too.
 *   4. 0x51BD60's `bgezl` vs `bltz` polarity (previously item 4) is now
 *      buried inside the cascade from (2) and cannot be judged in isolation
 *      until (2) is fixed.
 * Do not re-try: swapping the if/else polarity on the b==-1-style guards
 * (not applicable here, this unit has no such guard); the goto-based
 * `skip:`/`after:` restructuring for the return-1 guards (measured WORSE
 * than the nested-if form, reverted); `q = pl = func_201A70();` (measured
 * NULL, see above). */

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

extern s32 D_00484760;   /* gp - 0xA10 */
extern s32 D_00484764;   /* gp - 0xA0C */
extern s32 D_00484768;   /* gp - 0xA08 */
extern s32 D_00484878;   /* gp - 0x8F8 */

extern void *func_15DE80(void);
extern s32   func_1451E0(void *p);
extern s32   func_1451D0(void *p);
extern s32   normal_TransWarpCursorBob_51c720(void *p, s32 unused, s32 cx, s32 cy, s32 mode);
extern void *func_201A90(void);
extern void *func_1FEDE0(void);
extern void  func_1E49B0(void *p, s32 n, s32 *out);
extern void *func_1DCB50(s32 n);
extern Pl   *func_201A70(void);
extern s32   func_324270(void *a, s32 b);
extern void  func_3242B0(void *p, f32 *x, f32 *y, s32 n);
extern void  normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c);
extern void  normal_TransMenuBobIconShow_5183c0(u8 a);

s32 normal_TransWarpListCursorBobCb_51bbe0(void *a, s32 b)
{
    void *fb;
    s32   w;
    s32   h;
    void *p;
    s32   n;
    Pl   *pl;
    void *q;
    s32   res1;
    s32   res2;
    s32   id;
    u8    flagByte;
    f32   pos[2];
    s32   dx;
    s32   dy;
    s32   cid;
    u8    hval;
    s32   h8;

    fb = func_15DE80();
    w = func_1451E0(fb);
    h = func_1451D0(fb);
    normal_TransWarpCursorBob_51c720(a, b, 0, 0, 1);
    func_1FEDE0();
    p = func_201A90();
    if (p != 0) {
        n = 0;
        func_1E49B0(p, D_00484878, &n);
        if (n != 0) {
            q = func_1DCB50(n);
            pl = func_201A70();
            if (pl != 0) {
                q = pl->f514;
                if (q == 0) {
                    q = pl->f510;
                }
            }
            if (q != 0) {
                res1 = func_324270(q, 1);
                res2 = func_324270(q, 0);
                flagByte = 1;
                id = -1;
                if (D_00484768 == res1) {
                    id = res1;
                } else if (D_00484768 == res2) {
                    id = res2;
                    flagByte = 0;
                }
                func_3242B0(q, &pos[0], &pos[1], flagByte);
                hval = 1;
                dx = (s32)((f32)D_00484760 - pos[0]);
                h8 = h + 8;
                dy = (s32)((f32)D_00484764 - pos[1]);
                if (dx < -0x18) {
                    goto fallback;
                }
                if (dx >= w) {
                    goto fallback;
                }
                if (dy < -0x2A) {
                    goto fallback;
                }
                if (dy >= h8) {
                    goto fallback;
                }
                if (id < 0) {
                fallback:
                    dx = -0x64;
                    hval = 0;
                    dy = dx;
                }
                cid = id;
                normal_TransMenuBobIconMoveTo_518420(dx, dy, cid);
                normal_TransMenuBobIconShow_5183c0(hval);
            }
        }
    }
    return 1;
}
