/* rgp:protos */
#line 1
/* === SESSION 78 (2026-09-21, SOLO): ** MATCH ** -- 91/91 words, 0 bad, from
 * 9 bad held since session 32.  THE s72 CROSS, and s32/s44/s54 each had one
 * half of it.  Three edits, all forced:
 *  1. `#pragma opt_dead_assignments off`.  s54's "the named-constant arms are
 *     BYTE-IDENTICAL to the baseline (mwcc propagates them back)" and s44's
 *     "the declaration position of `one` is INERT" are the classic CROSS-HALF
 *     verdict of levers.d/mwcc-named-local-dead-assignment: with this pass ON
 *     nothing is named, so both halves read as armed nulls.
 *     The whole 68-name opt_* table, BOTH ways, armed (bogus == base, three
 *     value-taking names fail to build) is in build/wf-normal/s78/f1.log:
 *     **`opt_dead_assignments` is the ONLY name that keeps a name alive here.**
 *  2. `one = 1.0f;` assigned BETWEEN the v-clamp and the SECOND lim load, and
 *     used only at `x = one + v`.  That starts the second 1.0f's web before
 *     the 0.5f web dies, which is the whole 9-bad residue:
 *       retail lui $3,0x3F80 | mtc1 $2,$f0 | nop | add.s $f14,$f0,$f2 |
 *              mtc1 $3,$f1   | nop | add.s $f12,$f1,$f2
 *     One slot LATER (just before `z`) the block collapses the other way;
 *     one slot EARLIER it is inert.  s32's "the two 1.0f must be ONE vreg" is
 *     WRONG -- retail materialises 1.0f twice, at words 45 and 59.
 *  3. the divide split `t = (f32)(3 - (s16)n); t = t / 10.0f;`.  The pragma is
 *     whole-function and costs ONE WORD in the FIRST half: it hoists the
 *     subtraction's 1.0f into its own FPR ($f3) across the divide and eats the
 *     mtc1/sub.s hazard nop at 0x005088E8.  Splitting the divide into its own
 *     statement puts the mtc1 back next to the sub.s.  Which split matters:
 *       t = .../10.0f; v = (1.0f-t)*s;   91w 11 bad (wrong register map)
 *       t = (f32)(...); v = (1.0f-t/10.0f)*s;  91w 11 bad, RETAIL'S SCHEDULE,
 *                                       both nops, only the registers wrong
 *       t = (f32)(...); t = t/10.0f;     ** MATCH **
 *     The 4-bad step in between was a pure GPR transposition on the integer
 *     subtraction (retail creates the `(s16)n` web first, $2, and the constant
 *     3 second, $3); `three = 3;` as its own statement also reaches MATCH.
 * !! `opt_dead_assignments` is PER-PROCEDURE: a scoped `off` in the middle of
 * the body gives the SAME object as the file-level one, and a matching `on`
 * or `#pragma pop` ANYWHERE inside the body cancels it back to base (f2.log).
 * Decks: build/wf-normal/s78/e1..e9, f1..f7.
 */
/* === SESSION 54 (2026-09-12, SOLO): STILL 9 BAD / 91 words.  ONE class, and
 * it is the two float CONSTANTS:
 *   retail  lui $2,0x3F00 / lui $3,0x3F80 / mtc1 $2,$f0 / nop /
 *           add.s $f14,$f0,$f2 / mtc1 $3,$f1 / nop / add.s $f12,$f1,$f2 /
 *           lwc1 $f0,-0x7E14($28)
 *           -- BOTH `lui`s hoisted together, 0.5f in $f0 and 1.0f in $f1, so
 *           `lim` gets $f0 and the following c.lt.s / mov.s read $f0.
 *   ours    lui $2,0x3F00 / mtc1 $2,$f0 / nop / add.s $f14,$f0,$f2 /
 *           lui $2,0x3F80 / mtc1 $2,$f0 / nop / add.s $f12,$f0,$f2 /
 *           lwc1 $f1,-0x7E14($28)
 *           -- we REUSE $2 and $f0 for the second constant, which pushes `lim`
 *           to $f1 and renames the c.lt.s and the mov.s.  9 bad, 6 of them a
 *           pure $f0/$f1 transposition.
 * âš  14 arms over two decks, all negative:
 *  a_508820.py  (8) every order of the `z = 0.5f + v; x = 1.0f + v; y = x;`
 *      group, `v` on the left, `y` computed from its own `1.0f + v`, `y` first,
 *      and both constants hoisted into named `f32 k0/k1` locals in either
 *      order -- the named-constant arms are BYTE-IDENTICAL to the baseline
 *      (mwcc propagates them back), the reorders are 10-13.
 *  a_508820b.py (6) moving the `lim` load for the x-clamp to AFTER the three
 *      assignments (retail's `lwc1` for it IS after both adds), after `z`,
 *      after `x`, and inlining it at both uses: 10-11, and all of them trade
 *      the $f0/$f1 pair for a WORSE $f2/$f1 one.
 * â‡’ the axis is mwcc reusing one GPR/FPR pair for two short-lived constants
 * where retail keeps both live.  No source spelling tried reaches it.
 */
/* SESSION 44 (n44u/n44v/n44w, SOLO): 9 bad / 91 words, UNMOVED, 37 arms --
 * but THIS FILE'S s32 HEADER IS STALE ON THE ONE POINT THAT MATTERS.
 * It says naming the shared 1.0f web "buys it a callee-saved $f20 and a 92nd
 * word", and calls that the open door.  MEASURED: every `f32 one` arm this
 * session is still 91 WORDS -- there is no 92nd word and no $f20.  What
 * actually happens is:
 *  - `one = 1.0f;` assigned before `v = (one - ...) * s;`, or right after or
 *    before the func_128FD0 call, with both 1.0f sites using it: 10 bad, ONE
 *    object (5b2a68bd), and the declaration position of `one` is INERT.
 *  - `one = 1.0f;` assigned immediately before `z = 0.5f + v;` or before
 *    `x = one + v;`: ONE WORD SHORT (0x168 vs 0x16c) -- mwcc folds the web
 *    away entirely.  Those are CROSS HALVES.
 *  - using the web at only ONE site: at the subtraction 10 bad, at the add
 *    byte-identical to the baseline.
 * The +1 partner was hunted and NOT found (22 further arms): every z/x/y
 * statement order (xzy and xyz are 13 bad), a fifth `lim` volatile read before
 * or after the block (LENGTH +1 but 89 bad -- it restructures every clamp),
 * `y = one + v;` instead of `y = x;` (11 bad, or 1 short with the folded web),
 * and `z = v + 0.5f;`.
 * => The door is still open, but it is a ONE-WORD CROSS, not a register
 * problem.  Look for a +1 that does NOT touch the clamp chain. */
/* SESSION 32 (lane nc32q): 10 -> 9 bad, 91/91 words -- PARKED, not merged.
 * The 9 remaining words are ONE basic block (0x0050890C..0x00508938) and they
 * are pure REGISTER COLOURING; every instruction from 0x00508928 on is already
 * retail's in the alternative arm below.
 * WHAT PAID: `y` is an explicit COPY of x, not a second CSE of the same
 * expression -- `x = 1.0f + v; y = x;`.  That makes x the primary web ($f12,
 * retail) instead of y ($f13) and puts `mov.s $f13,$f12` in the delay slot.
 * THE MAPPED AXIS (about 190 arms this session, 7 bulk32 decks; the whole
 * statement-order/lim-placement surface reaches exactly TWO objects):
 *   installed here   lim read BEFORE the adds:  v=$f2, 0.5=v0 (both retail),
 *                    but the 1.0 `lui` is not hoisted and REUSES v0/$f0.
 *   arm a3_b_zxy_cK_post (move `lim = *(volatile f32 *)&D_0047D35C;` to
 *                    AFTER `y = x;`): retail's exact instruction ORDER, both
 *                    `lui`s at the block head, 0x00508928..end byte-identical,
 *                    but v=$f1 and the two constant registers are SWAPPED
 *                    (0.5=v1/$f0, 1.0=v0/$f0) -- 10 bad.
 * Retail's colours (0.5=v0/$f0, 1.0=v1/$f1, v=$f2) need the vreg CREATION
 * order v, 1.0, 0.5 with the EMISSION order 0.5, 1.0 -- i.e. the `1.0f` of
 * `(1.0f - ...)` and the `1.0f` of `x = 1.0f + v` must be ONE vreg.  Naming it
 * (`f32 one = 1.0f;`, plain or const) does create it early but buys it a
 * callee-saved $f20 and a 92nd word.  That is the open door.
 * MEASURED INERT here: commutative operand order on either add, the mul
 * operand swap, splitting the (1.0f - ...) temp, inlining func_128FD0,
 * declaration order (all 6 permutations -> ONE object: C++ normalises it),
 * `x = (x >= lim) ? lim : x` (branchless, 90 w), `!(x < lim)`, `lim <= x`
 * (worse), a named -1.0f local, extra early volatile lim webs, and
 * `#pragma optimization_level 3/4` -- the last one UNARMED, a bogus pragma
 * name gave the same object.
 * KEEP OUT OF config/ocunits/normal.txt.  Deck logs and the residue dumper:
 * build/wf-normal/s32/var/nc32q/ , report build/wf-normal/s32/reports/nc32q.md
 */
#include "types.h"
#pragma opt_dead_assignments off
/* SESSION 30: 12 -> 10 bad on the pool-wide DEFINING-STATEMENT MOVE deck
 * (build/wf-normal/s30/mkmove30.py) -- CREATION order, not declaration
 * order.  Still open.  KEEP OUT OF config/ocunits/normal.txt. */
/* normal 0x00508820 -- the pulsing tint on widget 0x13.  Advances the gp phase
 * by 0.1 * (count / 1.5) and wraps it at pi, then scales sinf(phase) by how far
 * the slot-303 count still is from 3 and clamps each channel at D_0047D35C.
 *
 * C++ virtual: `lw $25,0x4C4($25)` -> slot (0x4C4-8)/4 = 303.
 * `adda.s $f1,$f2 / madd.s $f2,$f3,$f4` is plain C `x + y*z`
 * (levers.d/ps2-float-accumulator).
 * `dsll32/dsra32 ..,16` twice off one value is an s32 local with an explicit
 * `(s16)` cast written at EACH use. */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s303() { return VCM0(s32, 0x4C4); }
};

typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern f32   D_00484574;          /* gp - 0xBFC */
extern f32   D_0047D1FC;          /* gp - 0x7F74 */
extern f32   D_0047D35C;          /* gp - 0x7E14 */
extern f32   D_0047D520;          /* gp - 0x7C50 */

extern Ctx *GetGameData_1fede0(void);
extern Ent *PartyGetLeaderChara_3c2820(s32 w);
extern f32  Sinf_128fd0(f32 t);
extern void UiSetWidgetColor_2905b0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
}

extern "C" s32 normal_LeaderHudGaugeLevelPulse_508820(void)
{
    Ctx *c;
    Ent *e;
    s32  n;
    f32  s;
    f32  lim;
    f32  t;
    f32  one;
    f32  v;
    f32  x;
    f32  y;
    f32  z;

    c = GetGameData_1fede0();
    if (c == 0) {
        return 0;
    }
    e = PartyGetLeaderChara_3c2820(c->f18);
    if (e == 0) {
        return 0;
    }
    n = (s16)e->s303();
    D_00484574 = D_00484574 + D_0047D520 * ((f32)n / 1.5f);
    if (D_00484574 >= D_0047D1FC) {
        D_00484574 = 0.0f;
    }
    s = Sinf_128fd0(D_00484574);
    t = (f32)(3 - (s16)n);
    t = t / 10.0f;
    v = (1.0f - t) * s;
    lim = *(volatile f32 *)&D_0047D35C;
    if (v >= lim) {
        v = lim;
    }
    one = 1.0f;
    lim = *(volatile f32 *)&D_0047D35C;
    z = 0.5f + v;
    x = one + v;
    y = x;
    if (x >= lim) {
        x = lim;
    }
    lim = *(volatile f32 *)&D_0047D35C;
    if (y >= lim) {
        y = lim;
    }
    lim = *(volatile f32 *)&D_0047D35C;
    if (z >= lim) {
        z = lim;
    }
    UiSetWidgetColor_2905b0(D_00484564, 0x13, x, y, z, -1.0f);
    return 0;
}
