/* rgp:protos */
#define RGP_SELF_normal_ShopMenuScrollBarLayout_50b2a0 1
#include "port/game_protos.h"
#line 1
/* === SESSION 51 (2026-09-08, SOLO): 8 BAD -> BYTE-IDENTICAL, MERGED.
 * The lever transferred verbatim from the twin normal_TransHunterScrollBarLayout_51ed00:
 * `a[]` becomes `union AU { s16 v[3]; S3 s; }` assigned as `au.s = *(S3 *)&
 * D_00480658;`, every `a[i]` becomes `au.v[i]`, and the copy group is written
 * `b, a, c`.  s22's "`*(S3 *)a` is ONE WORD LONG here too" was the ADDRESS
 * PIN, not the copy.  [[mwcc-union-aggregate-fill]].
 * ⚠ `u_bac`, `u_bca` and `u_cba` are ALL byte-identical (one object);
 * `u_abc`, `u_acb`, `u_cab` are 12.  Everything below predates this. */
/* === SESSION 46 (2026-09-07, SOLO): 22 -> 8 BAD, exact 178 words.
 * The [[levers.d/mwcc-index-cast-defeats-cse]]-adjacent AGGREGATE-COPY lever
 * transferred from its twin normal_TransHunterScrollBarLayout_51ed00: `*(S3 *)b = *(S3 *)&D_00480650;`
 * plus the `*(V3 *)c` copy moved BEFORE the a[] fill.  `bS` alone is 10.
 * ⚠ `*(S3 *)a` is ONE WORD LONG here too -- only b[] is the aggregate.
 * Residue is the same a[]-schedule class as 0051ed00 plus a live s1/s2 pair. */
/* === SESSION 42 (2026-09-07, SOLO): 26 -> 22 BAD, exact 178 words.  The
 * `p`/`n` byte loop over d[] is mwcc's own ARRAY-INITIALISER clear; written
 * as a BLOCK-SCOPED `f32 d[3] = {0};` opening right after the V3 copy
 * ([[levers.d/mwcc-array-initialiser-clear-loop]], FACTORY s63) it drops the
 * cursor/counter onto retail's registers.  MEASURED: opening the block BEFORE
 * the V3 copy is 33; all five other orders of the b[]/a[]/c[] groups are 22-23;
 * spelling the V3 copy as three scalars is 1 word short.
 * Residue (22) still carries `at>zero:2` and an s1/s2 TRANSPOSITION -- a
 * creation-order question, not a clear-loop one.
 * See [[levers.d/normal-session42-levers]]. */
#pragma divbyzerocheck on
/* SESSION 30: 31 -> 26 (a stage-1 move plus a stage-2 move) bad on the pool-wide DEFINING-STATEMENT MOVE deck
 * (build/wf-normal/s30/mkmove30.py) -- CREATION order, not declaration
 * order.  Still open.  KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* !! PARKED at RIGHT LENGTH, 31 BAD -- one residue class, the clear loop's register pair.
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
typedef struct V3  { f32 x; f32 y; f32 z; } V3;
typedef struct S3  { s16 x; s16 y; s16 z; } S3;
typedef union  AU  { s16 v[3]; S3 s; } AU;
typedef struct Row { s16 ax; s16 ay; s16 aw; s16 ah;
                     s16 bx; s16 by; s16 bw; s16 bh;
                     f32 f10; f32 f14; u8 pad18[8]; } Row;   /* 0x20 */

/*rgp*/
extern void *D_004845C8;          /* gp - 0xBA8  */
extern f32   D_00484634;          /* gp - 0xB3C  */
extern s16   D_00480650[3];       /* gp - 0x4B20 */
extern s16   D_00480658[3];       /* gp - 0x4B18 */
extern f32   D_00480660;          /* gp - 0x4B10 */

f32 normal_ShopMenuScrollBarLayout_50b2a0(s32 h, s32 lo, s32 hi, s32 flat)
{
    s16  b[3];
    AU   au __attribute__((aligned(16)));
    f32  c[3];
    Row *r;
    s32  i;
    s32  t;
    s32  q;
    f32  ret;
    f32  hf;

    hf = (f32)h;
    *(S3 *)b = *(S3 *)&D_00480650;
    au.s = *(S3 *)&D_00480658;
    *(V3 *)c = *(V3 *)&D_00480660;
    {
    f32  d[3] = {0};

    r = ((Row *)UiGetWidgetSprite_28fe10(D_004845C8, 0x25, 0));
    if (r == 0) {
        return 0.0f;
    }

    t = hi - lo;
    if (t < 0) {
        t = 0;
    }

    if (t == 0) {
        for (i = 0; i < 3; i++) {
            r[i].ax = 0x178;
            r[i].bw = 8;
            r[i].aw = 8;
            r[i].bh = au.v[i];
            r[i].ah = au.v[i];
            r[i].f14 = 0.0f;
            r[i].f10 = 0.0f;
        }
        r[1].ah = h - (au.v[0] + au.v[2]);
        ret = 0.0f;
        r[0].ay = 0x1F;
        r[1].ay = 0x1F + au.v[0];
        r[2].ay = r[1].ay + r[1].ah;
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
            r->ax = 0x178;
            r->ay = (s32)(31.0f + d[i]);
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
        D_00484634 = ret;
    }
    return ret;
    }
}
