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
    virtual void s045();
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
    virtual void s242();
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual void s249();
    virtual void s250();
    virtual void s251();
    virtual void s252();
    virtual void s253();
    virtual void s254();
    virtual void s255();
    virtual void s256();
    virtual void s257();
    virtual void s258();
    virtual void s259();
    virtual void s260();
    virtual void s261();
    virtual void s262();
    virtual void s263();
    virtual void s264();
    virtual void s265();
    virtual void s266();
    virtual void s267();
    virtual void s268();
    virtual void s269();
    virtual void s270();
    virtual void s271();
    virtual void s272();
    virtual void s273();
    virtual void s274();
    virtual void s275();
    virtual void s276();
    virtual void s277();
    virtual void s278();
    virtual void s279();
    virtual void s280();
    virtual void s281();
    virtual void s282();
    virtual void s283();
    virtual void s284();
    virtual void s285();
    virtual void s286();
    virtual void s287();
    virtual void s288();
    virtual void s289();
    virtual void s290();
    virtual void s291();
    virtual void s292();
    virtual void s293();
    virtual void s294();
    virtual void s295();
    virtual void s296();
    virtual void s297();
    virtual void s298();
    virtual void s299();
    virtual void s300();
    virtual void s301();
    virtual void s302();
    virtual s32 s303();
};

typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern f32   D_00484574;          /* gp - 0xBFC */
extern f32   D_0047D1FC;          /* gp - 0x7F74 */
extern f32   D_0047D35C;          /* gp - 0x7E14 */
extern f32   D_0047D520;          /* gp - 0x7C50 */

extern Ctx *func_1FEDE0(void);
extern Ent *func_3C2820(s32 w);
extern f32  func_128FD0(f32 t);
extern void func_2905B0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
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

    c = func_1FEDE0();
    if (c == 0) {
        return 0;
    }
    e = func_3C2820(c->f18);
    if (e == 0) {
        return 0;
    }
    n = (s16)e->s303();
    D_00484574 = D_00484574 + D_0047D520 * ((f32)n / 1.5f);
    if (D_00484574 >= D_0047D1FC) {
        D_00484574 = 0.0f;
    }
    s = func_128FD0(D_00484574);
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
    func_2905B0(D_00484564, 0x13, x, y, z, -1.0f);
    return 0;
}
