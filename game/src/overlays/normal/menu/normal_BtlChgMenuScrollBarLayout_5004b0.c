/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuScrollBarLayout_5004b0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 51 (2026-09-08, SOLO): 4 BAD -> BYTE-IDENTICAL, MERGED, after
 * 66+ arms across five sessions and a written verdict of "SCHEDULER-level
 * result, not a spelling".  It was a spelling.
 * `h[]` becomes `union HU { s16 v[3]; S3 s; }` assigned as
 * `hu.s = *(S3 *)&D_00480560;`, every `h[i]` becomes `hu.v[i]`, and the copy
 * group is written `w, h, fl`.  s46's "⚠ `*(S3 *)h` is FOUR WORDS LONG --
 * h[] must stay elementwise" is RETIRED: the pointer cast pins `&h[0]` so
 * every later `h[i]` costs an extra `addiu`; the union member assignment gets
 * the identical L,L,S,L,S,S block move with the frame offset still folded.
 * [[mwcc-union-aggregate-fill]].  ⚠ `u_wac`/`u_wca` MATCH; `u_cwa` is 4,
 * `u_awc`/`u_acw` 12, `u_caw` 12.
 * ALSO MEASURED AND NEGATIVE this session: a 2-aligned or 4-aligned WRAPPER
 * struct over D_00480560 (the lever that moved normal_BtlChgPageWeaponListBuild_504b50's f32
 * `.sdata` table, [[mwcc-sdata-alignment-wrapper]]) makes mwcc emit a
 * byte-copy loop -- +7 words.  It is an f32/8-byte lever only.
 * Everything below predates this and its numbers are history. */
/* === SESSION 50 (2026-09-08, SOLO): STILL 4 BAD, and the residue is now
 * priced to the WORD.  It is TWO ADJACENT-PAIR SWAPS with one sign -- retail
 * issues BOTH of h[0]'s ops one slot EARLIER:
 *     0x00500524/52C  retail [lh $8,h0][sh $6,w2]   ours [sh w2][lh h0]
 *     0x0050053C/540  retail [sh $8,h0][lh $6,h2]   ours [lh h2][sh h0]
 * (the twin normal_HelpMenuScrollBarLayout_522b90 is the identical shape at 0x00522C00/C08 and
 * 0x00522C18/C1C).
 * ⚠⚠ IT IS NOT REACHABLE FROM THE FILL LIST.  Eight more arms, and
 * `h[0]` moved ABOVE the fl copy, `h[0]+h[1]` above it, a named `s16 hh` temp
 * for the h[0] load, and a `const s16 *hp` cursor are ALL THE BYTE-IDENTICAL
 * BASE OBJECT (c8da7e41) -- mwcc canonicalises the whole fill list, which is
 * what s46's 45 arms already said.  h[0] above the w copy is 13, the h0/h2
 * swap is 7, fl-first is 8, fl-h0-w is 9.
 * The 95-column pragma screen is also a null here: `opt_lifetimes off` 97,
 * `nofpregforblkmv on` 17, everything else length-wrong or == base.
 * => The next arm must change the SCHEDULER's input, not the statement list. */
/* === SESSION 46 (2026-09-07, SOLO): 11 -> 4 BAD, exact 177 words, ONE arm:
 * `*(S3 *)w = *(S3 *)&D_00480558;` AND `*(V3 *)fl = *(V3 *)&D_00480568;`
 * (both aggregate; each alone is 8-11).  Same lever as the twins
 * normal_TransHunterScrollBarLayout_51ed00 / 0050b2a0 / 00522b90.
 * ⚠ `*(S3 *)h` is FOUR WORDS LONG -- h[] must stay elementwise.
 * RESIDUE, 4 words, TWO TRANSPOSITIONS: retail is lh h0, lh h1, sh h0,
 * lh h2, sh h1, sh h2 (L,L,S,L,S,S) and ours is L,L,L,S,S,S, so retail's
 * `lh h0` beats our `sh w2` and its `sh h0` beats our `lh h2`.
 * ⚠⚠ MEASURED FLOOR: ~45 arms this session (a_004b0*.py) -- 12 statement
 * orders of {w,fl,h0,h1,h2}, all 6 h-element orders, the S2+scalar splits,
 * `s16 h[4]`, and a 19-cell DECLARATION sweep (n through all 9 positions,
 * {ws,wd} and {hs,hd} as blocks).  ALL are 4 or worse and most collapse onto
 * ONE object.  ⚠ ANY fill moved inside the `f32 pos[3] = {0}` block is
 * exactly -1 WORD, always: the fill sinks into the clear loop's `nop`.
 * That -1 is NOT a useful cross half -- the word it deletes is retail's nop. */
/* SESSION 45: 177/177 w, 11 bad, no change.  Two axes retired at this base:
 *  - the s45 PAIR-TEMP lever (name a copy's loads in locals that are dead
 *    there, which took normal_FieldHudAllySuggestOpen_4efc50 from 16 to 10 on the SAME shape):
 *    five arms, `w0/w1` and `h0/h1` via `n`/`i`, all fold back to the baseline
 *    object.  Only `i/n` in the other order moves it, to 23.
 *  - the ARRAY-INITIALISER SPELLING, which s42 never swept even though the
 *    clear's cursor/counter are the two webs in question: `{0.0f,0.0f,0.0f}`,
 *    `{0.0f,0.0f}`, `{0.0f}`, no-size and a `f32 pos[4]` are all the baseline
 *    object (pos[4] is 12); `s32 pos[3]` and a second dummy array (either
 *    order) are LENGTH-WRONG by 4 and 10 words.
 * So the remaining 11 words really are the interference between w[0]/w[1] and
 * the clear temps, and neither the copy statements nor the initialiser text
 * reaches it. */
/* === SESSION 42 (2026-09-07, SOLO): 21 -> 11 BAD, exact 177 words, and the
 * "SCHEDULER-level result, not a spelling" verdict above is RETIRED.
 * TWO edits, and the second only became reachable because of the first:
 *  1. THE CLEAR IS NOT A HAND LOOP.  `u8 *cp; u32 cn; if (cp != 0) do {...}`
 *     is mwcc's own ARRAY-INITIALISER clear ([[levers.d/mwcc-array-initialiser-clear-loop]],
 *     FACTORY s63 / INSECT ix32, never tried on this image).  Written as a
 *     BLOCK-SCOPED `f32 pos[3] = {0};` the cursor/counter become COMPILER
 *     TEMPS created at the initialiser, so they colour to retail's LOW pair
 *     $3/$2 instead of our $8/$7.  21 -> 13.
 *     ARMING: the same initialiser at FUNCTION scope reads 47.
 *     ⚠ The block must open AFTER every copy statement: all 24 cells of
 *     (6 group orders x 4 block positions) except position-last are exactly
 *     ONE WORD SHORT (0x2c0 vs 0x2c4) -- s31's own observation, generalised.
 *  2. THE COPY-GROUP ORDER IS LIVE AGAIN IN THE NEW COAT.  s31/s36 spent ~66
 *     arms on wfh/hwf/interleaves with the hand loop in place and found
 *     nothing; with the initialiser in, `fwh` (fl, w, h) is 13 -> 11 and
 *     hwf/hfw are 15.  Those nulls were about that coat, not about the axis
 *     ([[levers.d/two-edit-cross-beats-count-ranking]]).
 * WHAT IS LEFT (11 words, all at 0x004EFxxx..0x00500540): retail keeps w[0]
 * and w[1] in $3/$2 and REUSES those same two registers for the initialiser's
 * cursor and counter; we colour cp/cn $3/$2 and push w0/w1 up to $8/$7.
 * Everything else is already retail's -- the lh/lwc1 issue order, w2=$6,
 * h0/h1/h2 = $8/$7/$6, and the stack layout (w 0x88, h 0x80, fl 0x70,
 * pos 0x60).  ALSO SPENT THIS SESSION: all six within-triple permutations of
 * w[], h[] and fl[] (11-16, six distinct objects) and a 21-arm whole-file
 * pragma sweep with an `opt_bogus_control_name off` arming arm -- eight
 * byte-identical inert, seven length-wrong, opt_lifetimes off 104.
 * Its TWIN normal_HelpMenuScrollBarLayout_522b90 took the identical pair of edits, 21 -> 11.
 * See [[levers.d/normal-session42-levers]]. */
/* === LANE b1, NORMAL session 31.  PARKED WITHOUT SPENDING AN ARM, by the
 * session brief's own instruction.  This unit is the named SEED of the
 * "divide float-twin family" recorded exhaustive negative (with
 * normal_HelpMenuScrollBarLayout_522b90 and normal_TransWarpScrollBarLayout_51b700): 53 arms and 19 inert cells
 * already spent across earlier sessions, and the brief states it needs a
 * SCHEDULER-level result, not a spelling.  Instruction: draft it, score it
 * ONCE to record the residue, park it, do not sweep spellings.
 *
 * RESIDUE RE-MEASURED FROM DISK THIS SESSION (nscore.py --tag b1, 1 round
 * trip): 177 words, LENGTH RIGHT, TWENTY-ONE bad words, lit4 no/0.
 * That reproduces the figure the orchestrator measured, so the draft on disk
 * is intact.  0 arms spent by this lane. */
/* PARKED -- lane na08 (WF40 pass 4, div-float-twins).  21 bad words / 177.
 * object sha1 2e3d9591.  Length is RIGHT (scorer printed a count, not '?'),
 * so the divide trap is fully handled: the object carries exactly one
 * `break 0,7` (0x000001CD), same as retail.
 * RESIDUE: 0x005004FC-0x00500564, the w[]/h[]/fl[] copy + the pos[] clear.
 * The six gp LOADS are byte-identical to retail; only the STORE schedule and
 * the register assignment differ.  retail stores W0,FL0,W1,FL1,<lh H0>,
 * <addiu cp>,W2,<li 12>,<lh H1>,FL2,H0,<lh H2>,H1,beqz,H2 and allocates
 * W0=$3 W1=$2 W2=$6 H0=$8 H1=$7 H2=$6 cp=$3 cn=$2; we emit W0,<addiu cp>,W1,
 * <li 12>,W2,FL0,... and allocate cp=$8 cn=$7 (i.e. retail reuses the W
 * registers for the clear pointer/counter and we take fresh ones).
 * MEASURED NEGATIVES: 31 arms over two x_vsweep round trips, floor flat at 21.
 *  - sweep A (build/na08_v4b0.py, 16 arms): every statement ORDER of the nine
 *    copies -- wfh fwh hwf fhw hfw, inter_wf inter_wfh inter_whf inter_fw --
 *    all 21 bad; wfh and inter_wf are INERT (object 0395eb6d = baseline).
 *    Every arm that moves the clear earlier (whf_cb0 wfh_cb0 whf_cb3 whf_cb6
 *    wfh_cb6 wfh_cb3 inter_wf_cb0) comes back ONE WORD SHORT, len 0x2c0 vs
 *    0x2c4, so it is not scorable.
 *  - sweep B (build/na08_v4b0b.py, 15 arms): cn_first, pp_first, predec,
 *    s8ptr, cp_decl_first, cp_decl_mid, goto_clr, addr_elem, tmp_reads are all
 *    INERT (object 2e3d9591 = baseline); cn_s32, w_arr4, fl_arr2, wfh_cnfirst
 *    are live and still 21; local array INITIALISERS blow the length up
 *    (init_decl len 0x350, wfh_init len 0x318) -- mwcc emits a real copy.
 * The clear itself is already the settled spelling taken from the confirmed
 * insect_InsectBattleCamTargetToCell_4f2ff0 / factory_FactoryPartObjStateOn_4fd5c0 sources (named u8* + u32 locals,
 * not a static inline helper); that rewrite is what took 0051b700 from 40 to
 * 33 and is kept here even though it is worth 0 on this unit. 
 * === LANE nu07 (batch D1) RE-OPEN, 2026-08-30.  STILL 21 BAD, object 2e3d9591.
 * Two new one-round-trip sweeps, 22 more arms, floor flat.  The NEW lever the
 * re-open was for -- round 2's "what moves register ranking is where the
 * ASSIGNMENT sits relative to a guard" -- is a MEASURED NULL here, in both
 * directions:
 *  - build/nu07_v4b0.py (9 arms): hoisting `cp = (u8 *)pos;` and/or `cn = 12;`
 *    ABOVE the `if (p == NULL)` guard is strictly WORSE -- cpcn_top 34
 *    (118ea9ef), cp_top 32 (3c34210a), cn_top 33 (467814b2), and the same 34
 *    for after-fb / before-guard / reversed / `&pos[0]` / `12U`.  A
 *    declaration initialiser `u8 *cp = (u8 *)pos;` is 32, the same object as
 *    cp_top (3c34210a).
 *  - build/nu07_v4b0b.py (13 arms): sliding the assignment PAIR to every
 *    position INSIDE the nine-statement copy block is INERT -- whf_asg1,
 *    whf_asg2, whf_asg3, whf_asg6, wfh_asg3, wfh_asg6, wfh_asg9, whf_asg3_rev,
 *    whf_asg6_rev are all object 2e3d9591 = baseline (NINE inert cells).  Only
 *    the arms that also interleave w/fl move the object (interwf_asg6 21 /
 *    0c0db2d2; interwf_asg2, interwf_asg4, wfh_asg4 22 / 5fd3072f).
 * Total measured negative on this construct is now 53 arms over four sweeps,
 * with 19 confirmed INERT cells (0395eb6d, 2e3d9591).  The residue is retail
 * REUSING the w[0]/w[1] registers $3/$2 for the clear pointer/counter while
 * mwcc takes fresh $8/$7, and no source spelling of the copy block or of the
 * clear reaches it.
 * === LANE n36f, NORMAL session 36, 2026-09-06.  STILL 21 BAD / 177, object
 * 2e3d9591 (confirmed byte-identical to the parked baseline before and after
 * this lane's edits).  13 more round trips, all negative, none displacing the
 * source:
 *  - Whole-block reorder relative to the EARLIER `p == NULL` guard: hoisting
 *    the entire w[]/h[]/fl[]/pos[] block above that guard is UNSCORABLE, len
 *    0x2c8 vs 0x2c4 (1 word too long) -- a new axis beyond the cp/cn-only
 *    hoist nu07 already measured worse.
 *  - A full 9-statement interleave matching retail's documented STORE order
 *    (w0,fl0,w1,fl1,cp,w2,cn,fl2,h0,h1,h2) is WORSE: 23 bad (new object).
 *    Retail's literal store sequence is not a legal/reachable C statement
 *    order here -- unsurprising since `inter_wf` (pure w/fl interleave) was
 *    already proven BYTE-IDENTICAL to the un-interleaved `whf` baseline
 *    (object 0395eb6d for both), meaning mwcc's own list scheduler already
 *    normalises this block's instruction order independent of source order.
 *    That is strong direct evidence the residue is not statement-order
 *    reachable at all, confirming the "SCHEDULER-level, not a spelling"
 *    verdict from first principles rather than by exhaustion alone.
 *  - Moving `fb = (f32)b;` from before to after the `p == NULL` guard (still
 *    legal, same path) is WORSE: 36 bad, right length.
 *  - Reusing the already-declared loop counter `i` in place of `cn` for the
 *    pos[] clear: as a `do/while` (same shape, `i` substituted for `cn`) is a
 *    TIED alternate spelling, 21 bad, but a DIFFERENT object (526a4327) --
 *    not an improvement, reverted. As a `for` loop it is WORSE, 22 bad.
 *  - `#pragma optimization_level 3/2/1` (the register-colouring/scheduler
 *    knob that closed several sister-family and cross-image units on this
 *    exact residue class): ALL THREE are catastrophically length-wrong here
 *    (0x2d0, 0x338, 0x3a0 vs 0x2c4) -- the pragma demonstrably reaches the
 *    compiler (arming proven by the length changes themselves) but this unit
 *    is a level-4-default unit, not a level-3 one.
 *  - `#pragma scheduling off`: INERT, byte-identical to baseline (2e3d9591).
 *  - `#pragma opt_common_subs off`, `opt_propagation off`,
 *    `opt_dead_assignments off`: all length-wrong (too long).
 *  - `#pragma opt_lifetimes off`: right length but much worse, 114 bad.
 * Total now 66 arms over five sweeps/sessions. The optimization_level and
 * opt_* knob axis (the project's other lead for register-colouring residues)
 * is now measured NULL on this specific unit too, alongside the exhausted
 * statement-reorder space. UNEXPLORED: per-statement `#pragma` scoping
 * (opt_* pragmas can be toggled mid-function, not just file-wide, in mwcc);
 * a targeted on/off bracket around just the copy block was not tried. Also
 * untried: expressing cp/cn via a small struct or union overlay with w[] to
 * see if that changes the allocator's view of interference; and the
 * unroll_count / opt_full_unroll_limit knobs (untested numeric opt_* pragmas)
 * on this residue specifically. Do not conclude this is unreachable --
 * record it as parked with a wider negative footprint and specific untried
 * levers for the next lane.
 */
#pragma divbyzerocheck on
#include "types.h"
/* normal 0x005004B0 -- the 3-slice vertical window layout, the five-way twin
 * family (0051B700 / 00522B90 / 005004B0 / 0050B2A0 / 0051ED00).
 *
 * Three 0x20-byte quads: top / middle / bottom.  `n == 0` is the unscaled
 * path; otherwise the middle slice's scale comes from an integer divide by
 * the middle height, which is why this file needs `divbyzerocheck on` -- at
 * -O4 mwcc folds the bnez/break pair away without it and the object comes
 * back exactly two words short.
 *
 * `f20` is the (f32) of the second parameter, computed BEFORE the early
 * return: it is live across the call, so it must be a named local assigned
 * at the top, not the return expression.
 */

typedef struct S3 { s16 x; s16 y; s16 z; } S3;
typedef union  HU { s16 v[3]; S3 s; } HU;
typedef struct V3 { f32 x; f32 y; f32 z; } V3;
typedef struct Quad {
    s16 f00; s16 f02; s16 f04; s16 f06;
    s16 f08; s16 f0A; s16 f0C; s16 f0E;
    s32 f10; f32 f14; s32 f18; s32 f1C;
} Quad;                                   /* 0x20 */

typedef struct Owner {
    u8    pad00[0x20];
    Quad *f20;
} Owner;

extern void *D_0048449C;                  /* gp - 0xCD4  */
extern s16   D_00480558[3];                /* gp - 0x4C18 */
extern s16   D_00480560[3];                /* gp - 0x4C10 */
extern f32   D_00480568;
extern f32   D_0048056C;
extern f32   D_00480570;                /* gp - 0x4C08 */

/*rgp*/

f32 normal_BtlChgMenuScrollBarLayout_5004b0(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    s16 w[3];
    HU  hu __attribute__((aligned(16)));
    f32 fl[3];
    f32 fb;
    f32 p1;
    f32 p2;
    f32 v;
    f32 r;
    f32 *m;
    void *p;
    Owner *o;
    Quad *q;
    s32 n;
    s32 i;

    fb = (f32)b;
    p = D_0048449C;
    if (p == NULL) {
        return 0.0f;
    }
    *(S3 *)w = *(S3 *)&D_00480558;
    hu.s = *(S3 *)&D_00480560;
    *(V3 *)fl = *(V3 *)&D_00480568;
    {
    f32 pos[3] = {0};

    o = ((Owner *)UiFindWidget_290460(p, a));
    if (o == NULL) {
        return 0.0f;
    }
    q = o->f20;
    if (q == NULL) {
        return 0.0f;
    }

    n = d - c;
    if (n < 0) {
        n = 0;
    }
    if (n == 0) {
        for (i = 0; i < 3; i++) {
            q[i].f00 = 0;
            q[i].f0C = 8;
            q[i].f04 = 8;
            q[i].f0E = hu.v[i];
            q[i].f06 = hu.v[i];
            q[i].f14 = 0.0f;
            q[i].f10 = 0;
        }
        q[1].f06 = b - (hu.v[0] + hu.v[2]);
        q[0].f02 = 0;
        q[1].f02 = hu.v[0];
        q[2].f02 = hu.v[0] + q[1].f06;
        return 0.0f;
    }

    m = &fl[1];
    v = (f32)((b - (hu.v[0] + hu.v[2])) / hu.v[1] - (n + 2));
    *m = v;
    if (v < 1.0f) {
        *m = 1.0f;
    }
    pos[0] = 0.0f;
    p1 = pos[0] + (f32)hu.v[0];
    pos[1] = p1;
    p2 = p1 + (f32)hu.v[1] * *m;
    pos[2] = p2;

    r = (fb - (p2 + (f32)hu.v[2])) / (f32)n;
    for (i = 0; i < 3; i++) {
        q->f00 = 0;
        q->f02 = (s16)pos[i];
        if (e != 0) {
            q->f0C = 0;
            q->f04 = 0;
            q->f0E = 0;
            q->f06 = 0;
        } else {
            q->f0C = 8;
            q->f04 = 8;
            q->f0E = hu.v[i];
            q->f06 = hu.v[i];
        }
        q->f08 = 0x5E;
        q->f0A = w[i];
        q->f10 = 0;
        q->f14 = fl[i];
        q++;
    }
    return r;
    }
}
