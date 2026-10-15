/* === SESSION 95 (2026-09-23): 3 -> MATCH (object text exact; the scorer's
 * 3 are .lit4 notes, BYTE-IDENTICAL at the link).  ONE EDIT: the three
 * D_0047D5D0 / D_0047D248 loads spelled as the float LITERALS 0.2f / 0.7f.
 * WHY (build/wf-normal/s95/sch.py trace + Alias.c FUN_00490090 decompiled):
 * a load of a named global carries an alias object, so the pre-RA scheduler
 * gave the `sw 1.0f -> arg0->f40` a MEMORY edge from the alpha lwc1 (latency 3,
 * earliest cycle 4) and the a0/a1 setup went first.  A .lit4 literal load has
 * no alias object, no edge, and the store issues at cycle 2 as in retail.
 * s87's "no C shape, no statement order and no optimiser pass reaches it" was
 * right about ORDER -- the lever was a DEPENDENCE EDGE.  Deck s95/b1.py:
 * both loads literal is needed (either alone is worse). */
/* === SESSION 93 (2026-09-22): STILL 3 BAD.  ONE WIDE ARMED NULL on an axis
 * this file had never touched -- the s93 PROMOTION lever
 * ([[levers.d/mwcc-propagated-temp-colouring]], and this session's normal
 * board).  Deck build/wf-normal/s93/g7.py, 5 arms, and EVERY ONE IS
 * BYTE-IDENTICAL to base (eeef6a87):
 *     `Obj *q = arg0; q = (Obj *)(s32)q;` with the f40/f44 stores and the
 *     call through `q`; with the stores only; with the call only; the same
 *     alias WITHOUT the round trip; and `f32 one = 1.0f;` for the stored
 *     constant.
 * ==> the store's base operand cannot be given a web of its own here -- the
 * alias coalesces onto the parameter whatever the spelling, so the scheduler
 * sees the identical node set and the 3-word tie-break is untouched.  The
 * round trip that closed 004fa3c0 and 00502250 this session DOES NOT REACH a
 * value that is already a parameter.
 * Everything below predates this session. */
/* === SESSION 88 (2026-09-22): STILL 3 BAD.  The DECLARATION-ORDER axis is
 * re-priced at this coat (s88/dsweep.py, 18 arms over the eight locals): TWO
 * objects, 3 and 14, base best.  Armed.  Nothing else touched this unit. */
/* === SESSION 87 (2026-09-22): STILL 3 BAD.  THE STATEMENT-ORDER AXIS IS NOW
 * EXHAUSTIVE and the ARGUMENT-EVALUATION axis is refuted on this board too.
 *  - s87/a1.py: ALL 12 legal permutations of the four statements
 *    {initial load, alpha load, f40 store, f44 store} (the 12th is the park).
 *    Nine distinct objects, 4/5/6/7 bad; BASE IS THE BEST.  s69 tried 8
 *    hand-picked orders; the set is now closed.
 *  - s87/g1.py: the f40 store written INSIDE the call's own argument list --
 *    8 comma placements (arg 1, 2, 3, both stores in arg 3, split across two)
 *    x {base, `opt_treetransformation off`}.  EVERY placement of the f40
 *    store collapses onto the `i_a_s44_s40` object (6 bad, 8 with the
 *    pragma); every placement of the f44 store is byte-identical to base.
 *    This is levers.d/insect-session64-levers section 1 measured on NORMAL:
 *    the front end normalises argument side effects to "before the call", so
 *    C CANNOT express a store evaluated with the argument setup.
 *  - s87/e2.py: the whole 68-name `opt_*` table (s69 swept 20).  ONE new
 *    object: `opt_treetransformation off` == `opt_addtogetherconstantparts...
 *    off` = 374b0a0b at 5 bad -- a cross half, nothing better.
 * ==> the three words are ONE list-scheduler tie-break and no C shape, no
 * statement order and no optimiser pass reaches it.
 * Everything below predates this session. */
/* === SESSION 86 (2026-09-22): STILL 3 BAD.  Two new axes, both armed nulls.
 * (1) VOLATILE on the f40 store (lvalue cast, member, both members, s32 pun):
 *     all BYTE-IDENTICAL -- volatility adds no sw->jal edge the scheduler sees.
 * (2) INLINE HELPERS (build/wf-normal/s86/c1.py, c2.py, c3.py = 216 generated
 *     arms: each of {initial, alpha, f40, f44, call} plain / wrapped in a
 *     static inline / named / inlined, both store orders): ONLY SIX OBJECTS,
 *     4..7 bad, none under 3.  `h2(arg0,1.0f,D_0047D5D0)` (4) puts the `sw`
 *     in retail's slot but drops alpha's lwc1 below it -- the same trade as
 *     s69's `G_one_named`.  Do not re-sweep inline wrapping. */
/* === SESSION 69 (2026-09-20, SOLO): STILL 3 BAD / 222 words.  The residue is
 * now PRICED and three whole axes are measured nulls -- do not re-run them.
 * The three words are ONE intra-block list-scheduler tie-break at 0x00512160:
 *     retail  lwc1 $f0 | lui $2 | lwc1 $f12 | sw $2,0x40($17) | daddu $4 | addiu $5
 *     ours    lwc1 $f0 | lui $2 | lwc1 $f12 | daddu $4 | addiu $5 | sw v0,0x40
 * i.e. retail takes the SOURCE-ORDER rule (the store with no successors goes
 * FIRST) and we take the HEIGHT rule (the two call-argument set-ups, which feed
 * the `jal`, go first).  That is exactly the two-rules fact in
 * levers.d/insect-session64-levers.md section 1, seen from the losing side.
 *  * STATEMENT ORDER is LIVE and the park is the best of it: 15 arms over the
 *    six statements of the block (`initial`/`alpha` named or inlined in every
 *    combination, the f40/f44 stores in both orders, `alpha` after the stores),
 *    EIGHT distinct objects, 4/5/6/7 bad, never below 3.  `G_one_named`
 *    (`alpha` assigned after the two stores) DOES move the `sw` to retail's
 *    slot but then loses the `swc1` out of the `jal` delay slot: 4 bad.
 *  * The f40 STORE'S SPELLING is a clean null: `*(s32 *)&arg0->f40 =
 *    0x3F800000`, `(f32)1`, and a named `f32 one = 1.0f;` at two positions are
 *    ALL byte-identical to the park (object cd3143d7).
 *  * PRAGMAS, 20 names both ways + 5 optimization levels, ARMED (`peephole off`
 *    0x3cc, `opt_repositioncode on` 0x388, `opt_propagation off` 0x380,
 *    `opt_common_subs off` 0x388, `opt_dead_assignments off` 0x37c,
 *    `no_branch_likely on` 0x394, bogus-name control byte-identical): EVERY one
 *    that keeps the length is byte-identical at 3 bad.  !! `scheduling off` is
 *    INERT here, and `optimization_level 3` and `4` are both the default object
 *    (levels 0/1/2 are +166/+51/+42 words).
 * ==> The next arm on this unit is NOT a source-order or pragma one.  Sweeps in
 * build/wf-normal/s69/p_12070*.py.
 */
/* UNRESOLVED NORMAL 0x00512070, 888 bytes, three differing words.
 * Explicit input ID chain repairs unreachable ID 1/2 assignments in shared C.
 * State zero returns 0; bool flags, signed promoted comparisons, common tail.
 * D_0047D248 is corroborated from retail GP operands and main PT_LOAD bytes.
 * Three scheduling differences remain at 00512160/164/168. No config credit.
 * No pragmas. All external declarations and entry point retain C linkage.
 */
#include "types.h"

typedef struct Ent2 { u8 pad000[0x1A4]; u8 f1A4; } Ent2;
typedef struct Ent  { u8 pad00[0x18]; Ent2 *f18; } Ent;

typedef struct Obj {
    u8   pad00[0x14];
    u8   f14;
    u8   pad15[0x1C - 0x15];
    s32  f1C;
    s32  f20;
    s16  f24[3][4];
    s16  f3C;
    s16  f3E;
    f32  f40;
    f32  f44;
    s16  f48;
    u8   pad4A[0x64 - 0x4A];
    s32  f64;
    u8   pad68[0x6C - 0x68];
    u8   f6C;
} Obj;

extern "C" const u8 D_004B2570[];
extern "C" void  *D_004846B8;          /* gp - 0xAB8 */
extern "C" s16   D_004846A8;           /* gp - 0xAC8 */
extern "C" s32   D_00480678;           /* gp - 0x4AF8 */
extern "C" f32 D_0047D248;
extern "C" f32   D_0047D5D0;           /* gp - 0x7BA0 */

extern "C" s32   func_1839F0(const u8 *p, s32 mask);
extern "C" void  func_1B9520(s32 a, s32 b, s32 c, f32 x);
extern "C" void *func_2907A0(void *w, s32 id, f32 v);
extern "C" f32   func_290770(void *w, s32 id);
extern "C" void  func_2913A0(void *p);
extern "C" Ent  *func_1FEDE0(void);

extern "C" s32   normal_SpaceMenuCursorMove_5123f0(Obj *p, s32 a);
extern "C" void  normal_SpaceMenuSelectionRefresh_512a70(Obj *p);
extern "C" s32   normal_SpaceMenuAnimStep_513000(Obj *p);
extern "C" s32   normal_SpaceMenuGetPickedDest_5117d0(void *p);
extern "C" s32   normal_SpaceMenuGetCurrentDest_5117c0(void *p);
extern "C" s32   normal_SpaceMenuCancel_5117e0(Obj *p);
extern "C" void  normal_SpaceMenuConfirmStep_511940(Obj *p, s32 a);
extern "C" void  normal_SpaceMenuConfirmEndStep_511de0(Obj *p);
extern "C" s32   normal_SpaceMenuGetTransitToAreaId_5147c0(void);

extern "C" s32 normal_SpaceMenuUpdate_512070(Obj *arg0)
{
    f32 alpha;
    f32 initial;
    s32 id;
    bool ok;
    bool keep;
    s16 v;
    s32 res;
    s32 state;

    if (arg0->f14 >= 2) {
        id = 0;
        if (arg0->f14 == 2) {
            ok = 0;
            if (func_1839F0(D_004B2570, 0x8000) != 0) {
                ok = 1;
            } else if (func_1839F0(D_004B2570, 0x2000) != 0) {
                id = 1;
                ok = 1;
            } else if (func_1839F0(D_004B2570, 0x1000) != 0) {
                id = 2;
                ok = 1;
            } else if (func_1839F0(D_004B2570, 0x4000) != 0) {
                id = 3;
                ok = 1;
            }
            if (ok && normal_SpaceMenuCursorMove_5123f0(arg0, id) != 0) {
                func_1B9520(arg0->f64, 4, 0, 1.0f);
                initial = 0.2f;
                alpha = 0.7f;
                arg0->f40 = 1.0f;
                arg0->f44 = initial;
                func_2907A0(arg0, 7, alpha);
                func_2907A0(arg0, 0x1E, 0.7f);
                arg0->f20 = 0;
                normal_SpaceMenuSelectionRefresh_512a70(arg0);
            }
            if (func_1839F0(D_004B2570, 0x40) != 0) {
                v = arg0->f24[arg0->f3E][arg0->f3C];
                arg0->f1C = v;
                if ((s16)v > -1) {
                    func_1B9520(arg0->f64, 5, 0, 1.0f);
                    res = normal_SpaceMenuGetPickedDest_5117d0(D_004846B8);
                    if (res != normal_SpaceMenuGetCurrentDest_5117c0(D_004846B8)) {
                        keep = 1;
                        if (func_1FEDE0()->f18->f1A4 & 1) {
                            if (arg0->f1C == normal_SpaceMenuGetTransitToAreaId_5147c0()) {
                                keep = 0;
                            }
                        }
                        if (keep) {
                            arg0->f6C = 1;
                            arg0->f14 = 4;
                            D_004846A8 = 1;
                            D_00480678 = normal_SpaceMenuGetPickedDest_5117d0(D_004846B8);
                        }
                    } else {
                        normal_SpaceMenuCancel_5117e0(arg0);
                        D_004846A8 = 2;
                    }
                }
            }
            goto call_513000;
        } else {
            state = arg0->f14;
            if (state == 4) {
                arg0->f48 = arg0->f48 + 1;
                if ((s16)arg0->f48 > 10) {
                    if (func_1FEDE0() == 0) { return 1; }
                    arg0->f14 = 5;
                    normal_SpaceMenuConfirmStep_511940(arg0, 1);
                }
            } else if (state == 5) {
                normal_SpaceMenuConfirmStep_511940(arg0, 0);
            } else if (state == 6) {
                normal_SpaceMenuConfirmEndStep_511de0(arg0);
            }
        call_513000:
            normal_SpaceMenuAnimStep_513000(arg0);
        }
    }

    state = arg0->f14;
    if (state <= 0) {
        goto out;
    } else if (state == 1) {
        if (!(func_290770(arg0, 2) < 1.0f)) {
            arg0->f14 = 2;
        }
    } else if ((state == 8) || (state == 3)) {
        if ((func_290770(arg0, 1) <= 0.0f) || (func_290770(arg0, 2) <= 0.0f)) {
            if (arg0->f14 == 8) { arg0->f14 = 9; } else { arg0->f14 = 0xA; }
        }
    }
    func_2913A0(arg0);
out:
    return 0;
}
