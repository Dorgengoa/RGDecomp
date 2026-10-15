/* === SESSION 53 (2026-09-08, SOLO): CLOSED.  23 bad / 122 words -> MATCH,
 * object 1a3a6457, on ONE ADDED LINE:
 *
 *     id = (s16)id;          <- between func_13EE40 and the first func_13F110
 *
 * ★★★★★★★★ NEW LEVER: A REDUNDANT SELF-CAST NARROWING IS *KEPT*.
 * Retail narrows `id` TWICE -- `dsll32 $21,$3,16` at 0x004EA044 hoisted ABOVE
 * the func_13EE40 call with its `dsra32` riding the jal's delay slot, then a
 * SECOND full `dsll32/dsra32 $21` pair at 0x004EA064/6C -- and then passes
 * `addiu $6,$21,0x26` for the second call with NO third pair.  We emitted ONE
 * pair (after the call) and a spurious second one on `(s16)(id + 0x26)`.
 * `id = (s16)id;` on an ALREADY-s16 local supplies the missing pair AND
 * unpins the `+ 0x26` argument in one edit.
 * ⚠ this is the OPPOSITE of the recorded insect s60 fact that an integer
 * `x = x;` is DELETED ([[insect-session60-levers]]): a self-assignment with an
 * EXPLICIT NARROWING CAST survives.  ⚠⚠ this file carries
 * `#pragma opt_dead_assignments off` at the top; the arm was not measured
 * without it, so treat the pragma as part of the lever until someone does.
 *
 * MEASURED, all LENGTH-WRONG (0x1e0 vs 0x1e8, two words SHORT) and all ONE
 * OBJECT (ce1026d6) -- do not re-run them: dropping the `(s16)` from
 * `id + 0x26` alone, dropping it and adding `(s16)id` at the first use, and
 * declaring `id` as s32 with explicit casts at both uses.  Declaring
 * func_13F110's third parameter `s16` is +2 words with a 49-substitution
 * global renumbering, with or without the cast arms.
 */
#pragma opt_dead_assignments off
/* SESSION 29 (2026-09-04): 31 BAD -> 23 at exact length on ONE PRAGMA,
 * `#pragma opt_dead_assignments off`, from the s29 pool-wide LIVE-KNOB screen
 * (28 arms x 65 open drafted units; armed -- every unit's optimization_level
 * family changed the length and the bogus-name control was inert everywhere).
 * The mnemonic distance is unchanged at 2, so this is the same shape with
 * fewer wrong words, not a different one.
 * MEASURED NULL at the new base: the whole-list declaration deck, 137 arms /
 * 29 distinct objects, best = the identity (kdeck.log). */
#include "types.h"
/* normal 0x004E9F00 -- opens a print handle, sets nine text attributes on it,
 * then draws one coloured row per entry of the caller's list and hangs two
 * widget ids off each row.
 *
 * !! PARKED at the RIGHT LENGTH, 31 BAD (s24).  NOT merged.  Read the LENGTH
 * WARNING below before spending an arm.
 *
 * SOLVED (s23): the four gp f32 at _gp-0x4CE0 are ONE AGGREGATE ASSIGNMENT
 * through a cast ([[mwcc-float-table-struct-copy]]); `al = c[3]` must be a
 * NAMED f32 local or $f20 is never allocated; `b`, `g`, `r` DECLARED IN THAT
 * ORDER gives b=$16, g=$22, r=$23 as retail has.
 *
 * ====== s24 -- THE s23 PARK WAS TWO COMPENSATING ERRORS ======
 * s23 recorded `p = &a->e[i]` as the FIRST statement of the loop body as "the
 * only spelling that reaches the right length" and flagged it as provisional.
 * IT IS THE DEFECT, and the length agreement was a coincidence of +2/-2:
 *   +1  an explicit `addiu v0,v0,48` for `p` that retail does not have
 *   +1  a 4-word if/else ternary where retail spends 3
 *   -2  the missing re-narrowing pair around the call
 *
 * WHY `p` FIRST IS WRONG, and it is a TRANSFERABLE READING:
 * retail fills the LOOP LATCH`s delay slot with the NEXT iteration`s ternary
 * compare -- `bnel $2,$0,.L004EA004 / slti $1,$17,3` -- so the body opens with
 * `bnel $1,$0` and the ternary has NOTHING left to sink, which is exactly why
 * it takes the BRANCH-LIKELY form.  The latch slot is filled by the FIRST
 * INSTRUCTION OF THE BODY.  With `p` first, that slot gets `sll v0,s1,1` (the
 * address chain) instead, the compare stays in the body, and the ternary then
 * has something to sink and emits a PLAIN branch.
 * ==> PUT THE TERNARY FIRST.  `p` then DISAPPEARS ENTIRELY -- mwcc addresses
 *     the element as `lwc1 $f0,0x30($2)` off `a + i*12` with no `addiu`, and
 *     "ternary first WITH p", "no p inline ternary", "no p named k first" and
 *     "no p, id in two steps" are FOUR ARMS AND ONE OBJECT (a0924fa7).
 * ==> The LATCH now matches retail verbatim and so does the ternary`s shape.
 *
 * !! LENGTH WARNING -- DO NOT REPEAT s23`S MISTAKE.
 * With the ternary first the unit is 2 WORDS SHORT (0x1e0), which is the
 * HONEST state: the 2 words are retail`s re-narrowing pair around the call.
 * `(s16)(id + 0x26)` at the SECOND use buys exactly those 2 words back and
 * the unit scores 31 bad at 0x1e8 -- but it buys them in the WRONG PLACE
 * (a `dsll32/dsra32` on $6 at the use, where retail has `dsra32 $21` in the
 * CALL`S DELAY SLOT and `dsll32/dsra32 $21` after it).  THAT CAST IS A
 * COMPENSATING ERROR and is in the source only so the unit keeps scoring.
 * DELETE IT the moment the real defect below is fixed.
 *
 * THE ONE REAL DEFECT LEFT: mwcc SINKS the whole `id` chain PAST func_13EE40.
 * Retail computes `(s16)(k + 0x42 + i * 41)` BEFORE the call, interleaving it
 * with the float argument chain (lwc1 / mul.s / cvt.w.s / mfc1) so it fills
 * that chain`s stalls, ends with `dsra32 $21,$21,16` in the JAL`S DELAY SLOT,
 * and keeps the finished id in $21 across the call.  Ours keeps the RAW
 * ternary result k in $21 instead and computes the chain afterwards.  Exactly
 * ONE value crosses the call either way, so it is a pure scheduling
 * preference, not register pressure.
 *
 * !! MEASURED NULLS -- s24 re-measured the s23 decks ON THE NEW BASE, because
 * the axes are coupled and an old null does not bind a new base:
 *   - TERNARY POLARITY / SPELLING: `i >= 3 ? 6 : 0`, `i > 2 ? 6 : 0`,
 *     `i < 3 ? 0x42 : 0x48`, `i >= 3 ? 0x48 : 0x42`, and both named-k if/else
 *     forms are SIX DISTINCT OBJECTS, none of which changes the LENGTH.
 *     `i > 2 ? 6 : 0` is merely the best-scoring (31 vs 32); ours still emits
 *     `beql` where retail has `bnel` -- the arms are MIRRORED and no spelling
 *     tried swaps them.
 *   - FORCING THE SECOND NARROWING: `(s16)id` at one use, at both, `s32 id`
 *     with casts at the uses -- THREE arms, ALL the base object.  `u16 id` is
 *     1 short; `volatile s16 id` is 4 short and spills.
 *   - !! `id` COMPUTED AFTER THE CALL IS REFUTED, not merely null: 58 bad.
 *     The source order really is id-then-call; mwcc is not hoisting it.
 * ==> Next lane: the ONLY question is what makes mwcc schedule an independent
 *     integer chain INTO a float dependence chain`s stalls before a call
 *     rather than sinking it past.  Do not re-sweep the ternary, the
 *     narrowing casts, `p`, or declaration order (s23: 10 permutations,
 *     4 objects, no length change). */

typedef struct V4 { f32 x; f32 y; f32 z; f32 w; } V4;

typedef struct Item {
    f32 f00;
    u8  pad04[8];
} Item;                              /* 0xC */

typedef struct A {
    u8   pad00[8];
    s32  f08;
    u8   pad0C[0x30 - 0xC];
    Item e[3];
} A;

extern f32 D_00480490;               /* gp - 0x4CE0 */
extern f32 D_00480494;
extern f32 D_00480498;
extern f32 D_0048049C;

extern void *func_15DE80(void);
extern void *func_141B00(void *h);
extern void  func_141A20(void *h);
extern void  func_13E500(void *w, s32 a);
extern void  func_13E4F0(void *w, s32 a);
extern void  func_13E4D0(void *w, s32 a);
extern void  func_13E4C0(void *w, s32 a, s32 b);
extern void  func_13E460(void *w, s32 a);
extern void  func_13E430(void *w, s32 a);
extern void  func_13E3D0(void *w, s32 a);
extern void  func_13E400(void *w, s32 a);
extern void  func_13F730(void *w, s32 a);
extern void  func_13F5B0(void *w);
extern void  func_13EE40(void *w, s32 a, s32 b, s32 c, s32 d);
extern void  func_13F110(void *w, s32 x, s32 y, s32 z);

void normal_MenuBattleEndDrawLevelUpGlow_4e9f00(A *a)
{
    f32   c[4];
    void *h;
    void *d;
    s32   i;
    s32   b;
    s32   g;
    s32   r;
    s16   id;
    Item *p;
    f32   al;

    h = func_15DE80();
    *(V4 *)c = *(V4 *)&D_00480490;
    d = func_141B00(h);
    func_13E500(d, 1);
    func_13E4F0(d, 2);
    func_13E4D0(d, 1);
    func_13E4C0(d, 1, 0);
    func_13E460(d, 0);
    func_13E430(d, 1);
    func_13E3D0(d, 0);
    func_13E400(d, 0);
    func_13F730(d, 6);
    b = (s32)c[2];
    g = (s32)c[1];
    r = (s32)c[0];
    al = c[3];
    for (i = 0; i < a->f08; i++) {
        id = (s16)((i > 2 ? 6 : 0) + 0x42 + i * 41);
        func_13EE40(d, r, g, b, (s32)(al * a->e[i].f00));
        id = (s16)id;
        func_13F110(d, 0x12, id, 0);
        func_13F110(d, 0x102, id + 0x26, 0);
    }
    func_13F5B0(d);
    func_141A20(h);
}
