/* rgp:protos */
#define RGP_SELF_normal_LeaderHudGaugeBarSet_506630 1
#include "port/game_protos.h"
#line 1
/* === SESSION 80 (2026-09-21, SOLO): 2 bad -> MATCH, exact 133 words, on the
 * SAME ONE-WORD LEVER that closed normal_FieldHudTacticsModeIconRefresh_4f7be0 this session: `const`
 * on the seven read-only s16 tables.  The residue was retail emitting
 * `sh $2,0x6($16)` BEFORE `cvt.w.s $f0,$f0` and us emitting the store last;
 * a non-const extern global ALIASES every store in the function, so the list
 * scheduler could not move the table load across it.  s69/s72/s76's
 * exhaustive statement-order and pragma sweeps on this unit could never have
 * reached it -- it is a TYPE QUALIFIER, not an order.
 * NOT A NEW MECHANISM: [[levers.d/mwcc-const-sdata-load-hoist]] at a BODY store
 * on lui-addressed tables -- `const` alone, no `.sdata` (these are not small-data
 * symbols).  build/wf-normal/s80/d1.py.
 * [[levers.d/mwcc-const-global-unpins-load]] */
/* === SESSION 72 (2026-09-21, SOLO): 13 -> 2 BAD, exact 133 words.  NOT merged.
 * The whole move is the s72 lever: `#pragma opt_dead_assignments off` plus
 * NAMING each loaded value, which is what makes the source statement order the
 * vreg CREATION order.  Under the pragma alone the unit is byte-identical to
 * the old park (aadcaa2a) -- the names are the other half of the cross.
 *  1. `c58`/`c60` for normal_D_00526458[k]/normal_D_00526460[k], BOTH LOADED FIRST, then the
 *     three stores.  13 -> 9.  (c60 before c58 is 13; the loaded ORDER is the
 *     discriminator, not the store order.)
 *  2. `dt = func_13AF68(t);` THEN `one = (s64)0x3FF00000 << 0x20;` -- in that
 *     order; the reverse, and naming only `one`, are both inert.  -> 6.
 *  3. `c48`/`c50` for normal_D_00526448[k]/normal_D_00526450[k] the same way.  -> 2.
 *     ⚠ `(u32)k` on THOSE two is one word SHORT -- they take bare `k`.
 * RESIDUE, 2 words at 0x005067C4/C8: retail emits `sh $2,0x6($16)` (g->f06)
 * and THEN `cvt.w.s`; we emit the conversion one slot earlier.  MEASURED NULL
 * (build/wf-normal/s72/w4..w8.py):
 *   - all 6 store orders of f0C/f0E/f06 (2/3/3/4/4/4, four objects);
 *   - 8 spellings of `v = (s32)((f32)len * t)` incl. a named `f32 fl` product,
 *     a named `(f32)len`, `(s16)` in place of `(s32)`, the operand swap
 *     (3 bad) -- every other one is ONE object;
 *   - a 9-statement POSITION LATTICE for the multiply and the conversion
 *     (`fl` at the block head / before each store / before the loads, `v`
 *     after the stores): ONE object -- mwcc re-fuses mul and cvt whatever the
 *     source does;
 *   - re-reading normal_D_00526460[k] at the f06 store, a second name for it, and a
 *     named `s16 vv = (s16)v`: all ONE object;
 *   - ★ THE WHOLE 68-NAME `opt_*` TABLE `off` CROSSED WITH dassign_off at this
 *     coat: 3 live cells, all length-wrong (opt_common_subs +4, opt_scalarize
 *     and opt_scalarizeliveranges -1).  ARMED: bogus name == coat,
 *     `opt_unroll_count` / `opt_full_unroll_limit` / `opt_unroll_instr_count`
 *     fail to build.
 * NEXT: this is the store-vs-conversion tie-break, the same shape as
 * normal_SpaceMenuUpdate_512070's `sw`; see [[levers.d/insect-session64-levers]] s1.
 * KEEP OUT OF config/ocunits/normal.txt.
 */
/* SESSION 67 (2026-09-20): 120 bad -> 13, EXACT LENGTH (133 w), on a
 * FOUR-EDIT CROSS found from the [[mwcc-identity-cast-splits-cse]] sq screen
 * (build/wf-normal/s67/sqscan.py): FIVE callee-saved `sq`s against retail's
 * FOUR, frame 0x70 vs 0x60.
 *   1. THE SIGNATURE IS WRONG.  Retail is `daddu $19,$4 / daddu $18,$6 /
 *      daddu $17,$7` -- FOUR integer parameters, ours had three, so every
 *      register was off by one slot.  `(N *p, s32 d1, s32 k, s32 len, ...)`
 *      with an UNUSED d1 at $5 reproduces retail's prologue BYTE-IDENTICALLY.
 *   2. `len` IS s32, NOT s16, AND `n` DOES NOT EXIST.  `n = len;` with an s16
 *      `n` cost a `dsll32/dsra32` sign-extend pair AND the fifth callee-saved
 *      register; using the parameter directly removes both.
 *   3. EARLY RETURN, not a wrapping `if (g != NULL)`.  Retail has TWO
 *      `daddu $2,$0,$0`s -- one in a `b` delay slot at the guard, one at
 *      .L00506818 -- i.e. two separate `return 0;` statements (+2 w).
 *   4. `(u32)k` at THREE of the four table-access groups (+1 w each, and ANY
 *      three of the four give the SAME OBJECT).  One cast is +1 and two are
 *      +1; it is the COUNT of DISTINCT cast sites >= 3 that buys both words.
 *      !! `(s16)k`/`(long)k` are +3 (they re-introduce dsll32/dsra32), and
 *      `(k)` / `k + 0` are inert.
 * !! THE SESSION-31 TERNARY NOTE IS SUPERSEDED: on the correct signature the
 * `(k != 1) ? A : B` ternary is 2 words SHORT of the `if/else`, and the
 * if/else is what retail has -- it DUPLICATES the `sh $2,0x0($16)` store into
 * both arms ([[mwcc-branch-likely-duplication]]).
 * THE 13 LEFT ARE TWO PURE SCHEDULER FACTS, both measured inert to source
 * order (deck M, 12 arms):
 *   (a) 3 w at 0x005066C4 -- retail materialises `lui $3,0x3FF0` BEFORE
 *       `daddu $4,$2,$0`, so its `dsll32 $5,$3,0` reads $3 and ours reads $2.
 *       Hoisting the s64 into a local, a named `one`, a comma expression and
 *       a 64-bit literal are ALL ONE OBJECT.
 *   (b) 10 w at 0x005067A4/B8/C4 and 0x005067FC/0C -- five SWAPS of one `sh`
 *       against one `lh`/`lui`.  Retail computes BOTH table addresses, then
 *       BOTH loads, then ALL the stores; ours interleaves.  Two temps (s16 or
 *       s32) and reordering the stores are all one object (m3 is WORSE, 16).
 * Sweeps in build/wf-normal/s67/gen6630*.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
#pragma opt_dead_assignments off
/* normal 0x00506630 -- fills one gauge record from the seven parallel s16
 * tables at normal_D_00526440..normal_D_00526470, scaling its length by cur/max clamped to
 * 1.0.  `func_100260(func_13AF68(x), 0x3FF00000 << 32)` is the double compare
 * against 1.0. */
typedef struct G {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
} G;

typedef struct N {
    u8  pad000[0xAC];
    s16 fAC;
} N;

extern s16 normal_D_00526440[];
extern s16 normal_D_00526448[];
extern s16 normal_D_00526450[];
extern s16 normal_D_00526458[];
extern s16 normal_D_00526460[];
extern s16 normal_D_00526468[];
extern s16 normal_D_00526470[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudGaugeBarSet_506630(N *p, s32 d1, s32 k, s32 len, f32 max, f32 cur)
{
    G  *g;
    f32 t;
    s32 v;
    s16 c58;
    s16 c60;
    s16 c48;
    s16 c50;
    s64 one;
    s64 dt;

    g = ((G *)UiPageGetWidgetSprites_289ad0((int)p, (int)d1));
    if (g == NULL) {
        return 0;
    }
    t = 0.0f;
    if (max > 0.0f) {
        t = cur / max;
    }
    if (cur <= 0.0f) {
        t = 0.0f;
    }
    dt = ((s64)__builtin_bit_cast(long long, fptodp(t)));
    one = (s64)0x3FF00000 << 0x20;
    if (((unsigned char)DoubleGreater_100260(__builtin_bit_cast(double, (long long)(dt)), __builtin_bit_cast(double, (long long)(one)))) != 0) {
        t = 1.0f;
    }
    if (len == -1) {
        len = normal_D_00526440[k];
    }
    if (k == 1) {
        g->f00 = normal_D_00526468[(u32)k] + p->fAC * 9;
    } else {
        g->f00 = normal_D_00526468[(u32)k];
    }
    g->f02 = normal_D_00526470[(u32)k];
    g->f06 = 0;
    g->f04 = 0;
    g->f0E = 0;
    g->f0C = 0;
    g->f0A = 0;
    g->f08 = 0;
    if (t > 0.0f) {
        c58 = normal_D_00526458[(u32)k];
        c60 = normal_D_00526460[(u32)k];
        g->f0C = c58;
        g->f0E = c60;
        g->f06 = c60;
        v = (s32)((f32)len * t);
        g->f04 = v;
        if ((s16)v <= 0) {
            g->f0C = 0;
        }
        c48 = normal_D_00526448[k];
        c50 = normal_D_00526450[k];
        g->f08 = c48;
        g->f0A = c50;
    }
    return 0;
}
