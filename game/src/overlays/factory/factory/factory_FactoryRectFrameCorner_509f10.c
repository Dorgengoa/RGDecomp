/* rgp:protos */
#define RGP_SELF_factory_FactoryRectFrameCorner_509f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00509F10 -- project one spinning billboard quad and
 * stroke it.  624 bytes, 156 instructions, 5 conditional branches, 25 calls
 * (br/ins 0.032): the branch-light band.
 *
 * ⚠⚠ PARKED, session 8 -- RIGHT LENGTH (156 words), 12 bad, and NOT in
 * config/ocunits/factory.txt.  The residue is a pure ROTATION: retail
 * interleaves the four gp float loads, the `row * 24` computation and the
 * copy-loop setup with the three `swc1 $f22/$f21/$f20` translation stores in
 * one order and mwcc picks another.  Every value, register and slot agrees;
 * only the emission order differs, plus one commutative `addu` operand pair.
 * THIRTY-TWO statement orderings over four probe builds; the floor is 12 and
 * eleven distinct orderings reach it.  This is the recorded gp-float SCHEDULE
 * class ([[overlay-c-pipeline]], "retail hoists a gp float load, we do not"),
 * which session 3f closed as a bounded negative on the title image.
 * ⇒ Its 820-byte sibling factory_FUN_0050A180 is the same shape and was not
 * opened for the same reason.
 *
 * ★ The first parameter is never read here, but factory_FactoryRectFrameDraw_50a4c0
 * marshals it (`daddu $4, $20, $0`) at all four call sites, so it IS a
 * parameter ([[factory-unused-first-parameter]]).  The four float arguments
 * are moved into $f20..$f23 before the first call, so the callee's own
 * `$f12..$f15` are this function's floats left in place.
 *
 * ★★ FOUR `lwc1`/`swc1` PAIRS ARE FOUR GLOBALS, NOT A BLOCK COPY.  A 16-byte
 * `extern` struct is over mwcc's small-data threshold and compiles to
 * `lui`/`%lo` plus `lw`/`sw`; the reference is gp-relative and goes through
 * the FPU, so the source reads four separate 4-byte f32 externs into a local
 * whose integer view is what the stroke coordinates use.
 *
 * ★ factory_D_0050C970 is OVERLAY data at 0x50xxxx, far outside the gp window
 * (_gp 0x00485170 +/- 0x8000), so it is an INCOMPLETE array and takes %hi/%lo.
 * D_00480E70 (_gp - 0x4300) is inside the window and stays plain.
 */

/* ** SESSION 23 (lane fz23l): still 156 words / 11 bad.  TWO MORE ORDERINGS
 * MEASURED, both dead, on top of the file's earlier 32:
 *   - `extern f32 D_00480E7x` -> `extern const f32 D_00480E7x` (all four):
 *     LENGTH BREAKS, 0x280 vs retail's 0x270 -- +1 word EACH.  `const` takes
 *     these four out of the gp small-data window and each reference grows an
 *     address pair.  The round-3 `const` lever that paid on factory_FactoryPartPlace_5013f0
 *     is therefore NOT portable to a gp float that is READ INTO A LOCAL here;
 *     it pays only where the load must RISE past an aliasing store.
 *   - the full INTERLEAVED source order mirroring retail's emission
 *     (w, sp, q0, y0, q1, dp, q2, n, q3, qp, x, y, z): 11 -> 12 bad.
 *   - sinking ONLY `m.r3.x/y/z` to sit immediately before the copy loop, with
 *     `m.r3.w` left early: byte-identical, which RE-CONFIRMS the recorded
 *     "moving m.r3.x/y/z after the q assignments is inert" cell.
 * The residue is unchanged and is a pure SCHEDULE rotation: retail software-
 * pipelines L0,L1,S0,L2,S1,L3,S2,S3 (2 loads in flight) and holds the three
 * `swc1 $f22/$f21/$f20` translation stores to the very end; ours holds 3 loads
 * in flight and emits the translation stores in the middle.  Every register,
 * every stack slot and every value already agree.  Statement order is now
 * 35 cells deep with a floor of 11 -- treat this axis as CLOSED and look for a
 * non-ordering handle, or park the unit.
 */
typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;
typedef struct Pos { s32 x; s32 y; s32 z; s32 w; } Pos;
typedef struct Mtx { Vec r0; Vec r1; Vec r2; Vec r3; } Mtx;

/* ** SESSION 50 (2026-09-03), tag fg50: 11 bad -> BYTE-IDENTICAL, 156 words,
 * object md5 75625047a250, armed in the same run (005069e0 = MATCH /
 * 1a0e9c68216b; 00500450 = bad 2 / 409c28db0188, promoted as the second
 * arming control because THIS unit was the one under test) with the
 * cmp-verified identity (977182cbe9b7 / 11) and the recorded-live delivery
 * cell (`n = 8` -> `n = 7` = 3dbae0e55ee0 / 12) reproduced in every batch.
 *
 * THE CLOSE, two edits, BOTH necessary:
 *   1. the four gp floats are copied as a 2+2 SPLIT of aggregate assignments
 *          *(Vec2 *)&q      = *(Vec2 *)&D_00480E70;
 *          *(Vec2 *)&q.f[2] = *(Vec2 *)&D_00480E78;
 *      (whole 4-copy 13 / 3+1 12, both recorded s44; 2+2 alone here = 4);
 *   2. `y0 = row * 24;` is written RIGHT AFTER the copy and BEFORE the
 *      copy-loop setup (sp/dp/n).  With the setup between the copy and y0 the
 *      last op of the product (`sll s0,v0,3`) issues six slots late = 4 bad;
 *      with y0 first of all = 6; y0 between the pairs = 4.
 * Attribution in one run: same order with 3+1 = 14, with elementwise = 14;
 * 2+2 with the setup before y0 = 4.  `volatile` on q (the merged sibling
 * factory_FactoryRectFrameEdge_50a180's spelling) is INERT on the 2+2 (S2 = C1 = C2 = C3 =
 * ec686373f0db) -- the pair cast strips the qualifier -- and only LIVE on the
 * elementwise form (11 -> 9).
 *
 * HOW IT WAS FOUND (build/fg50/s50/winscreen.py, denominator 2284 units
 * scanned): retail's two-in-flight interleave `L0 L1 S0 L2 S1 L3 S2 S3` with
 * foreign instructions inside occurs in exactly THREE windows in the whole
 * five-overlay corpus -- this unit, 0050a710's sp100 site, and the MERGED
 * factory_FactoryRectFrameEdge_50a180, whose source puts the row product (`ty = row * 0x18`)
 * NEXT TO the copy.  Every other window (37) is the loads-first
 * `L0 L1 L2 S0 L3 S1 S2 S3` that a plain elementwise copy already produces.
 * The mechanism, read off the object: mwcc issues the integer product chain
 * one op per slot BETWEEN the copy's memory ops only when the product
 * statement immediately FOLLOWS the copy in source; the 2+2 split is what
 * makes the copy's own eight ops take retail's `S_k` two slots after `L_k`.
 * See [[factory-session50-levers]].
 */
typedef struct Vec3 { f32 x; f32 y; f32 z; } Vec3;
typedef struct Vec2 { f32 x; f32 y; } Vec2;
typedef union  Box { f32 f[4]; s32 i[4]; } Box;

extern f32 D_00480E70;                          /* _gp - 0x4300 */
extern f32 D_00480E74;
extern f32 D_00480E78;
extern f32 D_00480E7C;
extern s32 factory_D_0050C970[];

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

void factory_FactoryRectFrameCorner_509f10(s32 unused, void *g, void *tex, s32 phase, s32 row,
                          void *col, f32 scale, f32 tx, f32 ty, f32 tz)
{
    Mtx  m __attribute__((aligned(16)));
    Box  q __attribute__((aligned(16)));
    Box *qp;
    Vec  base[4] __attribute__((aligned(16)));
    Vec  v[4] __attribute__((aligned(16)));
    Pos  r[4] __attribute__((aligned(16)));
    s32 *sp;
    s32 *dp;
    s32  n;
    s32  y0;
    s32  y1;
    s32  x1;

    MatRotY_1cb200(&m, factory_FactoryGridDirToAngle_4ff990(phase));
    VecScale_1cbca0(&m.r0, &m.r0, scale);
    VecScale_1cbca0(&m.r1, &m.r1, scale);
    VecScale_1cbca0(&m.r2, &m.r2, scale);
    m.r3.x = tx;
    m.r3.y = ty;
    m.r3.z = tz;
    m.r3.w = 1.0f;
    *(Vec2 *)&q = *(Vec2 *)&D_00480E70;
    *(Vec2 *)&q.f[2] = *(Vec2 *)&D_00480E78;
    y0 = row * 24;
    qp = &q;
    sp = factory_D_0050C970;
    dp = (s32 *)base;
    n = 8;
    do {
        dp[0] = sp[0];
        dp[1] = sp[1];
        sp += 2;
        dp += 2;
        n--;
    } while (n > 0);
    MatMulPoint_1cb8e0(&v[0], &m, &base[0]);
    MatMulPoint_1cb8e0(&v[1], &m, &base[1]);
    MatMulPoint_1cb8e0(&v[2], &m, &base[2]);
    MatMulPoint_1cb8e0(&v[3], &m, &base[3]);
    if (ProjectToScreen_15d340(&r[0], &v[0]) == 0) {
        return;
    }
    if (ProjectToScreen_15d340(&r[1], &v[1]) == 0) {
        return;
    }
    if (ProjectToScreen_15d340(&r[2], &v[2]) == 0) {
        return;
    }
    if (ProjectToScreen_15d340(&r[3], &v[3]) == 0) {
        return;
    }
    GsPktOpenPrim_13f730(g, 4);
    GsPktSetRGBAQVec_13edd0(g, col);
    GsPktSetTexture_13ec00(g, tex);
    GsPktSetUV_13ed60(g, qp->i[0], y0);
    GsPktSetXYZVecI_13eeb0(g, &r[0]);
    y1 = y0 + qp->i[3] - 1;
    GsPktSetUV_13ed60(g, qp->i[0], y1);
    GsPktSetXYZVecI_13eeb0(g, &r[1]);
    x1 = qp->i[2];
    x1 = qp->i[0] + x1 - 1;
    GsPktSetUV_13ed60(g, x1, y0);
    GsPktSetXYZVecI_13eeb0(g, &r[2]);
    GsPktSetUV_13ed60(g, x1, y1);
    GsPktSetXYZVecI_13eeb0(g, &r[3]);
    GsPktClose_13f5b0(g);
}
