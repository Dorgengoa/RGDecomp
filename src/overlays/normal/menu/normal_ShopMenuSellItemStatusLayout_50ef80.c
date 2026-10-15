#pragma optimization_level 3
/* ******* CLOSED s28 (2026-09-03) -- BYTE-IDENTICAL, 1,732 B, on ONE WORD:
 * the func_3D4630 arm's `return 1;` became `goto done;` with `done: return 1;`
 * at the function's end.  The last two words were the id == -1 arm ending
 * `b <epilogue> / li $2,1` where retail has `b <join> / nop`: with an EXPLICIT
 * `return 1` at the EARLIER exit, mwcc gives that exit its own return block and
 * the shared `return 1` block's FIRST predecessor becomes the id == -1 arm,
 * which is the one predecessor mwcc threads (the join's `addiu $2,$0,1` moved
 * into its delay slot, target bumped past the join).  With every early exit a
 * `goto` to the ONE shared return, the first predecessor is the func_3D4630 arm
 * -- exactly where retail has `b <epilogue> / li $2,1` -- and every later exit
 * gets `b <join> / nop`.  [[mwcc-branch-likely-duplication]] FIX 3 ("mwcc
 * threads only the FIRST predecessor of a shared `return K` block") read from
 * the other side: AN EXPLICIT `return K` AT AN EARLY SITE STEALS THE THREADED
 * SLOT FROM THE SITE RETAIL THREADS.
 * Found by a 486-arm PER-SITE EXIT LATTICE (3 spellings x 5 exit sites x arms
 * swapped, build/wf-normal/s28/mk28_ef80x.py + bulkarm28.py, exit_ef80.log):
 * 16 arms MATCH and every one has `goto done` at the func_3D4630 site; the
 * other four sites are FREE between fall-through and `goto` (one object), and
 * `return 1` at any of them is worse.  s27's six exit shapes were six points
 * of that lattice and none was this cell ([[mwcc-mixed-exit-statements]]).
 * MEASURED NULLS AT LEVEL 3 THIS SESSION (bulkarm28, do not re-run):
 *  * the WHOLE pragma surface, 6,592 arms (every lowercase identifier in
 *    mwccps2.exe x 2 polarities + the numeric family): 6,547 arms are the
 *    identity object, 12 are LIVE and all 12 length-wrong (levels 0/1/2/4,
 *    cplusplus, far_call, floatsp32 off, fp_library off, interrupt,
 *    no_branch_likely, optimize_for_size off, padloop off), 23 NOBUILD (the
 *    recorded crash/grammar bucket).  0 better.  prag_ef80.log.
 *  * declaration order, whole-list: 110 single moves + 55 pairwise swaps +
 *    the full reversal of the 11 locals = 167 arms, floor 2, best other 8.
 *    decl_ef80.log.  A knob that moved the starting point invalidated s27's
 *    sweep record, so this was re-measured at level 3, not inherited. */
/* ★★★★★★★ CLOSED / MOVED, s27, BY `#pragma optimization_level 3`.
 * mwcc's DEFAULT here is -O4.  Level 3 is a DISTINCT AXIS from the `opt_*`
 * pragma namespace [[mwcc-pragma-namespace]] enumerates: 14 `opt_*` arms were a
 * clean null on normal_FieldHudLeaderChangedNop_4f50e0 and 23 were a clean null on this unit's
 * residue, while the LEVEL knob moved both.  Screened over all 68 open drafted
 * normal units in build/wf-normal/s27/olevel.log (levels 1/2/3): levels 1 and 2
 * are catastrophic on every unit, level 3 CLOSED normal_FieldHudPartyPanelsStep_4f57f0 and
 * normal_MenuBattleEndMemberRowsFadeIn_4eb5f0 outright and took normal_ShopMenuSellItemStatusLayout_50ef80 and
 * normal_BtlChgMenuWeaponGridDrawCb_503930 from LENGTH-WRONG to the RIGHT LENGTH. */
/* ⚠⚠ THE s19 STOP VERDICT BELOW IS WITHDRAWN, s27.  It says "no SOURCE
 * spelling reaches it" about the 3-word frame-address residue, and that stays
 * true -- but the residue was never a SOURCE problem: `#pragma
 * optimization_level 3` closed the length on the first build.  The unit is now
 * RIGHT LENGTH at **2 bad**, and the last two words are the exit shape the s19
 * header already named ("our id==-1 arm ends `b <epilogue> / li $2,1` where
 * retail has `b <join> / nop`").
 * TWO FURTHER FIXES, both DECLARATION ORDER read through the byte score
 * (build/wf-normal/s27/bsweep.py):
 *  * 17 -> 10 bad: declare the copy loop's SOURCE `s` BEFORE the DEST `d`.
 *    Retail keeps dest in $4 and source in $5; ours had them swapped and the
 *    two `addiu ..,2` bumps swapped with them.  5 orders swept, spread 10-20.
 *    [[mwcc-caller-saved-decl-order]].
 *  * 10 -> 2 bad: declare `id` BEFORE `nd`.  Retail has nd=$18 / id=$19.
 *    ⚠ `id` at positions 0-2 of the group is 46 bad -- the WHOLE permutation
 *    matters, not the pairwise swap ([[mwcc-decl-statement-order]]).
 * MEASURED NULLS on the last 2 words (do not re-run):
 *  * 6 exit shapes -- arms swapped, `return 1` in one arm, in both, a `goto`
 *    to a shared label, two sequential `if`s, and the arm dropped (control).
 *    Only `goto_done` ties base; every other arm is worse or length-wrong.
 *    v_ef80_exit.py.
 *  * 23 pragma knobs stacked under the level line -- v_ef80_knob.py.  FIVE of
 *    them change the LENGTH (so the deck is armed) and NOT ONE moves the two
 *    words.
 *
 * ===== LANE nd, session 19 -- STILL 3 words SHORT.  STOP GRINDING THIS ONE.
 * MEASURED NULL (1 arm, added to the 18 recorded below): the access-site
 * volatile pin `*(volatile s16 *)&sp[i].x` does NOT force a second
 * frame-address computation -- same length, and one word worse in shape.
 * REVERTED.
 * ⇒ DIAGNOSIS: the value retail rematerialises is `sp + i*6`, a FRAME ADDRESS.
 * That is precisely the shape [[insect-cse-two-spellings]] was NARROWED to
 * REFUTE in insect session 23 -- "mwcc canonicalises every spelling of &local
 * to one $sp+K value BEFORE CSE runs" -- refuted there four independent times
 * over 14 spelling PAIRS.  This is the cross-image confirmation on NORMAL, and
 * normal_BtlChgMenuWeaponGridDrawCb_503930 (16 spellings + 488 pragmas, same frame-address shape) is
 * a third instance.  No SOURCE spelling reaches it. */
#include "types.h"
/* WARNING OPEN at THREE WORDS SHORT (430 of 433) -- NOT in config/ocunits/normal.txt.
 * Everything else is exact: all 46 calls in order, every gap right, the two
 * length levers below both landed.  The residue is ONE allocator preference in
 * the marker-lookup loop: retail keeps the loop counter in $16 and RECOMPUTES
 * `sp + i*6` after the func_291110 call (sll/addu/sll/addu, 4 words); mwcc
 * computes it once in the test block, parks it in a callee-saved register and
 * reuses it (1 word).  Both use exactly one callee-saved register and three
 * more are free in BOTH, so it is not register pressure.
 * Measured and byte-for-byte identical (18 spellings, 6 builds): plain
 * subscript / `id ==` reversed / flat `((s16*)sp)[i*3]` on either side or both
 * / a UNION with a Slot and an s16 view / `while` instead of `for` /
 * `continue` instead of the positive test / `i = 0xA` instead of `break` /
 * a block-scoped `Slot *q = &sp[i]` before or after the call (the pointer
 * hoists ABOVE the test and costs 2 words elsewhere) / x and y into locals /
 * a local for the id load / a second index variable / `volatile Slot sp[11]`
 * / and all twelve declaration positions of `i` and `ctx`.
 * Also open, 0 net words: our id==-1 arm ends `b <epilogue> / li $2,1` where
 * retail has `b <join> / nop` and materialises the 1 once at the join.
 *
 * normal 0x0050EF80 -- the party-member detail panel refresh: widgets 0x5A-0x62
 * and 0x7E-0x80 for one entry, then the map-marker lookup for its home slot.
 *
 * The 0x21-halfword block copied out of D_00525AA0 into the frame is read back
 * as ELEVEN 6-byte records ({id, x, y}), so it is one table under two views:
 * the copy walks it as s16 and the lookup indexes it as Slot (`sll 1 / addu /
 * sll 1` is the *6).
 * `dsll32 $7,$2,0 / dsra32 $7,$7,0` on a call result is s32 -> s64 widening
 * into func_291250's fourth parameter.
 * func_2905B0 takes FOUR floats: m2c renders $f15 as a leftover 0x3F800000
 * integer argument because it does not track the mov.s chain. */

typedef struct Slot { s16 id; s16 x; s16 y; } Slot;

typedef struct Ent  { u8 pad00[0x10]; s16 *f10; } Ent;
typedef struct Ctx  { u8 pad00[0x18]; void *f18; } Ctx;
typedef struct Node { u8 pad00[0xC]; s32 f0C; } Node;

extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845F8;          /* gp - 0xB78 */
extern f32   D_0047D288;          /* gp - 0x7EE8 */
extern s16   D_00525AA0[33];

extern void  func_28A800(s32 w, s32 a, s32 b, s32 c, s32 d);
extern s32   func_28AA30(void *p, s32 a);
extern void  func_28F970(void *p, s32 id, s32 x, s32 y, s32 c);
extern s32   func_28FE10(void *p, s32 id, s32 a);
extern void  func_2905B0(void *p, s32 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_290F60(void *p, s32 id, s32 c, s32 d);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern void  func_291250(void *p, s32 id, s32 c, s64 v);
extern Ctx  *func_1FEDE0(void);
extern s32   func_3C78D0(void *w, s32 id, s32 c, s32 d);
extern s32   func_3D4320(Ent *p);
extern s32   func_3D4360(Ent *p);
extern s32   func_3D4420(Ent *p);
extern s32   func_3D4630(Ent *p);
extern s32   func_3D46F0(Ent *p, Node *n);
extern s32   func_3D4860(Ent *p);
extern s32   func_3D4C20(Ent *p);
extern Node *func_3D4D80(Ent *p, s32 a);
extern s32   func_3E97C0(Ctx *c, s32 id, s32 a, s32 b, s32 c2, s32 d, s32 e);

s32 normal_ShopMenuSellItemStatusLayout_50ef80(Ent *p)
{
    Slot   sp[11];
    Ctx   *ctx;
    s32    t;
    s32    w;
    s32    id;
    Node  *nd;
    u8     flag;
    s32    i;
    s16   *s;
    s16   *d;
    s32    n;

    if (p == 0) {
        return 0;
    }
    {
        func_290F60(D_004845CC, 0x5C, 0x26, 6);
        func_2905B0(D_004845CC, 0x5C, 1.0f, 0.5f, 0.5f, 1.0f);
        if (func_3D4360(p) != 0 && func_3D4420(p) != 0) {
            func_291250(D_004845CC, 0x61, 0, func_3D4320(p));
            func_291110(D_004845CC, 0x5D, 1, 1);
            func_291110(D_004845CC, 0x5C, 0, 1);
        } else {
            func_291110(D_004845CC, 0x5C, 1, 1);
            func_291110(D_004845CC, 0x5D, 0, 1);
        }

        d = (s16 *)sp;
        s = D_00525AA0;
        n = 0x21;
        do {
            *d = *s;
            s++;
            d++;
            n--;
        } while (n > 0);

        ctx = func_1FEDE0();
        func_291250(D_004845CC, 0x62, 0,
                    func_3C78D0(ctx->f18, *p->f10, 0, 0));
        func_28FE10(D_004845CC, 0x58, 0);
        func_28FE10(D_004845CC, 0x7E, 0);
        w = func_28FE10(D_004845CC, 0x7F, 0);
        func_28FE10(D_004845CC, 0x80, 0);
        func_291110(D_004845CC, 0x5A, 1, 1);
        func_290F60(D_004845CC, 0x5A, 9, 0x1E);
        func_2905B0(D_004845CC, 0x5A, 1.0f, 1.0f, 1.0f, 1.0f);
        func_290F60(D_004845CC, 0x7E, 9, 6);
        func_290F60(D_004845CC, 0x7F, 9, 0x36);
        func_290F60(D_004845CC, 0x80, 9, 0x4F);
        func_2905B0(D_004845CC, 0x7F, 1.0f, 1.0f, 1.0f, 1.0f);
        func_2905B0(D_004845CC, 0x80, D_0047D288, D_0047D288, D_0047D288,
                    1.0f);

        if (func_3E97C0(ctx, *p->f10, -1, 0, 1, 1, 0) > 0) {
            t = func_28FE10(D_004845CC, 0x5A, 0);
            func_28A800(t, func_28AA30(D_004845F8, 0x16), 0, 0, -2);
        } else if (func_3E97C0(ctx, *p->f10, -1, 1, 0, 0, 1) > 0) {
            t = func_28FE10(D_004845CC, 0x5A, 0);
            func_2905B0(D_004845CC, 0x5A, D_0047D288, D_0047D288, D_0047D288,
                        1.0f);
            func_28A800(t, func_28AA30(D_004845F8, 0x17), 0, 0, -2);
        } else {
            t = func_28FE10(D_004845CC, 0x5A, 0);
            func_2905B0(D_004845CC, 0x5A, D_0047D288, D_0047D288, D_0047D288,
                        1.0f);
            func_28A800(t, func_28AA30(D_004845F8, 0x18), 0, 0, -2);
        }

        func_291110(D_004845CC, 0x7E, 1, 1);
        func_290F60(D_004845CC, 0x7E, 9, 6);
        func_291110(D_004845CC, 0x7F, 0, 1);
        func_291110(D_004845CC, 0x80, 0, 1);
        if (func_3D4860(p) != 0) {
            id = -1;
            nd = func_3D4D80(p, 1);
            if (nd != 0) {
                id = nd->f0C;
            }
            flag = 0;
            if (id == -1) {
                func_2905B0(D_004845CC, 0x7F, D_0047D288, D_0047D288,
                            D_0047D288, 1.0f);
                func_28A800(w, func_28AA30(D_004845F8, 0x12), 0, 0, -2);
            } else if ((u8)(func_3D4C20(p) != 0)) {
                func_28A800(w, func_28AA30(D_004845F8, 0x13), 0, 0, -2);
            } else if (func_3D46F0(p, nd) != 0) {
                func_28A800(w, func_28AA30(D_004845F8, 0x11), 0, 0, -2);
            } else {
                flag = 1;
            }
            if (flag) {
                func_28A800(w, func_28AA30(D_004845F8, 0x12), 0, 0, -2);
                func_291110(D_004845CC, 0x80, 1, 1);
                func_2905B0(D_004845CC, 0x7F, D_0047D288, D_0047D288,
                            D_0047D288, 1.0f);
                func_2905B0(D_004845CC, 0x5F, D_0047D288, D_0047D288,
                            D_0047D288, 1.0f);
            } else {
                func_2905B0(D_004845CC, 0x5F, 1.0f, 1.0f, 1.0f, 1.0f);
            }
            func_291110(D_004845CC, 0x7F, 1, 1);
            func_291110(D_004845CC, 0x5F, 1, 1);
            if (func_3D4630(p) != 0) {
                func_28F970(D_004845CC, 0x5F, 0x72, 0, 0);
                goto done;
            }
            if (id == -1) {
                func_291110(D_004845CC, 0x5F, 0, 1);
            } else {
                for (i = 0; i < 0xA; i++) {
                    if (sp[i].id == id) {
                        func_291110(D_004845CC, 0x5F, 1, 1);
                        func_28F970(D_004845CC, 0x5F, sp[i].x, sp[i].y, 0);
                        break;
                    }
                }
            }
        } else {
            func_291110(D_004845CC, 0x5F, 0, 1);
        }
    }
done:
    return 1;
}
