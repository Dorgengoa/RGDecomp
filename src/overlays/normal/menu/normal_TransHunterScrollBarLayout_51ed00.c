/* === SESSION 51 (2026-09-08, SOLO): 6 BAD -> BYTE-IDENTICAL, MERGED.
 * TWO EDITS, and s46's own "MEASURED FLOOR ON SOURCE ORDER ... mwcc
 * CANONICALISES the fill list" is RETIRED -- it was true of the ELEMENTWISE
 * a[] fill and false the moment a[] became an aggregate.
 *  1. ★ `a[]` IS A UNION, NOT A POINTER CAST.  `typedef union AU { s16 v[3];
 *     S3 s; } AU; AU au; au.s = *(S3 *)&D_00480770;` and every `a[i]` becomes
 *     `au.v[i]`.  s46 recorded `*(S3 *)a` as "ONE WORD LONG"; THAT WORD IS THE
 *     ADDRESS PIN, not the copy -- taking `&a[0]` through a pointer cast stops
 *     mwcc folding 0xA0 into the later `lh K($3)` and it materialises the base
 *     instead.  The union member assignment gives the same L,L,S,L,S,S block
 *     move with no pin.  6 -> 2.  [[mwcc-union-aggregate-fill]].
 *  2. THE COPY-GROUP ORDER IS `b, a, c` -- the un-indexed s16[3] first, the
 *     union second, the f32[3] LAST.  2 -> MATCH.  `bca` is 2, `abc` 12,
 *     `acb`/`cab` 13, `cba` 2, and `hf = (f32)h` moved to the end is 33.
 * Everything below predates this and its numbers are history. */
/* === SESSION 46 (2026-09-07, SOLO): 18 -> 6 BAD, exact 183 words, TWO edits,
 * both of them RECORDED NULLS RE-SWEPT IN THE NEW COAT.
 *  1. `*(S3 *)b = *(S3 *)&D_00480768;`  (18 -> 8).  s22's header records
 *     "`b` and `a` as S3 struct copies ... 39-40 bad" -- TRUE AT THE OLD
 *     BASELINE and FALSE NOW.  A 3-element s16 global->local fill IS an
 *     AGGREGATE STRUCT COPY: retail emits lh,lh,lh,sh,sh,sh (batched) and
 *     elementwise C emits a scheduler-chosen interleave.
 *     ⚠ ONLY `b`.  `*(S3 *)a` is ONE WORD LONG -- retail's a[] is
 *     lh,lh,sh,lh,sh,sh, a DIFFERENT pattern in the SAME function.
 *  2. the `*(V3 *)c` copy written BEFORE the a[] fill (8 -> 6).
 * RESIDUE, 6 words, THREE TRANSPOSITIONS, all one bias: retail issues the
 * a[]-related op one slot EARLIER at each
 *   (lh a0 <-> sh b2 ; sh a0 <-> lh a2 ; sh a1 <-> swc1 c1).
 * ⚠⚠ MEASURED FLOOR ON SOURCE ORDER: 33 orderings of {h, b, c, a0, a1, a2, d}
 * this session (build/wf-normal/s46/a_1ed00*.py).  mwcc CANONICALISES the
 * fill list -- B0C12, B01C2, BC012, CB012 and the installed order are ONE
 * OBJECT.  `hf = (f32)h;` is INERT at every position.  Every `d`-block
 * position except last is 20-46.  Do not re-sweep statement order. */
/* === SESSION 42 (2026-09-07, SOLO): 36 -> 18 BAD, exact 183 words -- the
 * biggest single-edit move on this twin family.  The `p`/`n` byte loop over
 * d[] is mwcc's own ARRAY-INITIALISER clear; written as a BLOCK-SCOPED
 * `f32 d[3] = {0};` opening right after the V3 copy the cursor/counter become
 * compiler temps and land on retail's registers
 * ([[levers.d/mwcc-array-initialiser-clear-loop]], FACTORY s63).
 * MEASURED after it: all five other orders of the b[]/a[]/c[] copy groups are
 * 19-20, and spelling the V3 copy as three scalars is 2 words short.
 * The 18 that remain are the b[]/a[]/c[] store SCHEDULE, not the clear.
 * See [[levers.d/normal-session42-levers]]. */
#pragma divbyzerocheck on
#include "types.h"
/* !! PARKED at RIGHT LENGTH, 40 BAD -- one residue class, the clear loop's register pair.
 * NOT merged.  Drafted from nothing this session (s22); the shape was read off
 * MERGED normal_LeaderHudWeaponFrameLayout_506850, which carries the 12-byte `sb` clear verbatim,
 * and off MERGED normal_BtlChgPageListFrameLayout_505af0, which gives the 0x20-byte Row struct and
 * proves row stores follow SOURCE ORDER one-for-one.
 *
 * WHAT IS SOLVED (both loops and the whole body are BYTE-IDENTICAL):
 *  * `f32 c[3]` MUST be filled by ONE AGGREGATE ASSIGNMENT through a cast --
 *    `*(V3 *)c = *(V3 *)&D_x;`.  Elementwise, mwcc DEAD-STORE-ELIMINATES
 *    `c[1] = ...` because the `t != 0` arm overwrites it before the only read,
 *    and the unit reads as TWO WORDS SHORT, not as a wrong store.  Measured:
 *    elementwise and `c[1]` written twice give the SAME OBJECT (so it is DSE,
 *    not scheduling); a `f32 *` alias for the fill is also that object; a
 *    `volatile` pin on the one element reaches the right length but 41 bad.
 *    This EXTENDS [[mwcc-float-table-struct-copy]] from a 4-float schedule
 *    lever to a 3-float DEAD-STORE lever.
 *  * `hf = (f32)h` must be a NAMED LOCAL assigned before the call, or mwcc
 *    never allocates $f20 and the unit is one word short.
 *  * The two float arrays are SEPARATE locals.  Merging them into `f32 v[8]`
 *    also defeats the DSE, but then mwcc materialises ONE base `&v[i]` and
 *    offsets it by 0x10, where retail recomputes `$29 + i*4` at both sites --
 *    right length, 66 bad.  A four-array struct is 4 words LONG.
 *
 * THE RESIDUE, and it is the SAME CLASS on both family members:
 *   the byte-clear's pointer and counter take the caller-saved LOCAL band
 *   ($7/$6 here, $6/$5 on 0x0050B2A0) where retail takes $3/$2, so retail's
 *   fill temps are pushed UP and every temp in the prologue is renamed.  The
 *   corpus says retail's choice is the normal one: build/wf-normal/s22/
 *   clearscan.py finds 36 MERGED units carrying this clear and 33 of them use
 *   $3/$2 (the other 3 use $4/$3) -- INCLUDING units with 30-184 instructions
 *   ahead of the clear, so "the clear is early" is NOT the reason.
 *
 * !! MEASURED NULLS, 70+ cells, do not re-run (logs in build/wf-normal/s22/):
 *   - statement position of `p`/`n`: every gap in the 7-statement fill list,
 *     split and together, 16 cells -> ONE object (mwcc sinks them regardless).
 *   - declaration order: `p` and `n` each through ALL 12 positions of the full
 *     local list ([[mwcc-wholelist-decl-sweep]] discipline), 22 cells -> TWO
 *     objects, both the same bad count.
 *   - clear-loop spelling: `while` top-tested, `*p++`/`--n`, block scope, s32
 *     counter, guard on the array, no guard -- 6 cells, base object or worse.
 *   - MOVING THE WHOLE CLEAR BLOCK ahead of the fills (3 cells): 45/47 bad.
 *     mwcc does NOT hoist the fills back above the loop, so retail's fills
 *     really are ahead of the clear in the source.
 *   - counter shared with `i`/`q`/`t` ([[mwcc-loop-counter-priority]] in
 *     reverse): one distinct object, no movement.
 *   - fill spelling/order: `b` and `a` as S3 struct copies, all 6 orderings of
 *     the three fill groups -- 8 cells, 6 objects, 39-40 bad.
 *   - 15 allocation/scheduling pragmas (opt_lifetimes, opt_propagation,
 *     opt_repositioncode, register_coloring, schedule, opt_common_subs, ...):
 *     every live arm is WORSE or the wrong length.
 * => The axis is mwcc's allocation PRIORITY between a loop-resident pointer
 * pair and short-lived fill temps, and no source spelling tried reaches it.
 * A merged unit with gp INTEGER fills batched ahead of a clear in the SAME
 * basic block would settle it; the corpus scan above found none.
 */
typedef struct V3 { f32 x; f32 y; f32 z; } V3;
typedef struct S3 { s16 x; s16 y; s16 z; } S3;
typedef union  AU { s16 v[3]; S3 s; } AU;

typedef struct Row { s16 ax; s16 ay; s16 aw; s16 ah;
                     s16 bx; s16 by; s16 bw; s16 bh;
                     f32 f10; f32 f14; u8 pad18[8]; } Row;   /* 0x20 */

extern Row  *func_28FE10(void *w, s32 id, s32 k);
extern void *D_00484710;          /* gp - 0xA60  */
extern s16   D_00480768[3];       /* gp - 0x4A08 */
extern s16   D_00480770[3];       /* gp - 0x4A00 */
extern f32   D_00480778;          /* gp - 0x49F8 */
extern f32   D_0048077C;
extern f32   D_00480780;

f32 normal_TransHunterScrollBarLayout_51ed00(s32 id, s32 x, s32 y, s32 h, s32 lo, s32 hi, s32 flat)
{
    s16  b[3];
    AU   au;
    f32  c[3];
    s32  m;
    Row *r;
    s32  i;
    s32  t;
    s32  q;
    f32  ret;
    f32  hf;

    hf = (f32)h;
    *(S3 *)b = *(S3 *)&D_00480768;
    au.s = *(S3 *)&D_00480770;
    *(V3 *)c = *(V3 *)&D_00480778;
    {
    f32  d[3] = {0};

    r = func_28FE10(D_00484710, id, 0);
    if (r == 0) {
        return 0.0f;
    }

    t = hi - lo;
    if (t < 0) {
        t = 0;
    }

    if (t == 0) {
        for (i = 0; i < 3; i++) {
            r[i].ax = x + 2;
            r[i].bw = 8;
            r[i].aw = 8;
            r[i].bh = au.v[i];
            r[i].ah = au.v[i];
            r[i].f14 = 0.0f;
            r[i].f10 = 0.0f;
        }
        r[1].ah = h - (au.v[0] + au.v[2]);
        r[0].ay = y;
        r[1].ay = y + au.v[0];
        r[2].ay = r[1].ay + r[1].ah;
        ret = 0.0f;
    } else {
        q = (h - (au.v[0] + au.v[2])) / au.v[1] - (t + 2);
        c[1] = (f32)q;
        if (c[1] < 1.0f) {
            c[1] = 1.0f;
        }
        d[0] = 0.0f;
        d[1] = d[0] + (f32)au.v[0];
        d[2] = d[1] + (f32)au.v[1] * c[1];
        ret = (hf - (d[2] + (f32)au.v[2])) / (f32)t;
        for (i = 0; i < 3; i++) {
            r->ax = x + 2;
            r->ay = (s32)((f32)y + d[i]);
            if (flat != 0) {
                r->bw = 0;
                r->aw = 0;
                r->bh = 0;
                r->ah = 0;
            } else {
                r->bw = 8;
                r->aw = 8;
                r->bh = au.v[i];
                r->ah = au.v[i];
            }
            r->bx = 0x5E;
            r->by = b[i];
            r->f10 = 0.0f;
            r->f14 = c[i];
            r++;
        }
    }
    return ret;
    }
}
