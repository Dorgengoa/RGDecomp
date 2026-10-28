/* rgp:protos */
#define RGP_SELF_normal_HelpMenuScrollBarLayout_522b90 1
#include "port/game_protos.h"
#line 1
/* === SESSION 51 (2026-09-08, SOLO): 4 BAD -> BYTE-IDENTICAL, MERGED.
 * `h[]` becomes `union HU { s16 v[3]; S3 s; }` assigned as
 * `hu.s = *(S3 *)&D_004807D0;`, every `h[i]` becomes `hu.v[i]`, and the copy
 * group is written `w, h, fl`.  This header's own "`*(S3 *)h` is LONG here
 * too" was the ADDRESS PIN of the pointer cast, not the copy.
 * [[mwcc-union-aggregate-fill]].  ⚠ `u_wac` and `u_wca` MATCH; `u_cwa` is 4
 * (a different object), `u_awc`/`u_acw`/`u_caw` are 12.
 * Everything below predates this. */
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
/* === SESSION 46 (2026-09-07, SOLO): 11 -> 4 BAD, exact 168 words, the SAME
 * single arm as its twin normal_BtlChgMenuScrollBarLayout_5004b0:
 * `*(S3 *)w = *(S3 *)&D_004807C8;` + `*(V3 *)fl = *(V3 *)&D_004807D8;`.
 * `*(S3 *)h` is LONG here too.  Residue is the identical L,L,S,L,S,S vs
 * L,L,L,S,S,S h[]-fill schedule -- read 005004b0's header before touching it. */
/* SESSION 45: 168/168 w, 11 bad.  Six differing words, a pure SCHEDULE
 * PERMUTATION of one straight-line block (identical instruction multiset:
 * 1 lwc1, 3 swc1, 5 sh, 3 lh, 2 addiu).  WARN MEASURED: all six orders of the
 * three copy groups {fl[], w[], h[]} plus three interleavings -- the INSTALLED
 * order (fl, w, h) is the unique best at 11 and every other cell is 13-16.
 * See the TWIN normal_BtlChgMenuScrollBarLayout_5004b0, whose header carries the full analysis;
 * the two units' mdiff hunks are identical shapes. */
/* === SESSION 42 (2026-09-07, SOLO): 21 -> 11 BAD, exact 168 words.  The
 * IDENTICAL pair of edits that moved the seed normal_BtlChgMenuScrollBarLayout_5004b0 21 -> 11,
 * so the "blocked by the seed's measured negative" note above is retired:
 *  1. the `cp`/`cn` byte loop is mwcc's own ARRAY-INITIALISER clear, written
 *     as a BLOCK-SCOPED `f32 pos[3] = {0};` opening after the last copy
 *     statement ([[levers.d/mwcc-array-initialiser-clear-loop]]) -- 21 -> 13;
 *  2. the copy-group order `fwh` (fl, then w, then h), which is LIVE AGAIN
 *     only in the coat edit 1 creates -- 13 -> 11.
 * Residue is now the same 11 as the seed: retail reuses w[0]/w[1]'s $3/$2 for
 * the cursor and counter.  Read the seed's header before spending an arm. */
/* PARKED -- lane na08.  21 bad words / 168.  object sha1 a72bb445.
 * Length RIGHT, one `break 0,7` present.  SAME residue as the seed
 * normal_BtlChgMenuScrollBarLayout_5004b0 (0x00522BD8-0x00522C40): the w[]/h[]/fl[] copy plus the
 * pos[] clear, loads byte-identical, store schedule and cp/cn register
 * assignment wrong in exactly the same way.  Blocked by the seed's 31-arm
 * measured negative -- see normal_BtlChgMenuScrollBarLayout_5004b0.c in this directory for the
 * exhaustive spelling list.  Nothing after 0x00522C40 is wrong. 
 * === LANE nu07 (batch D1) RE-OPEN, 2026-08-30.  STILL 21 BAD, object a72bb445
 * (re-scored from disk, 168 words = declared 0x2A0, notes column empty).
 * Blocked by the seed normal_BtlChgMenuScrollBarLayout_5004b0, whose negative is now 53 arms with
 * 19 INERT cells (see that file's header and build/nu07_v4b0.py /
 * build/nu07_v4b0b.py).  The two NEW levers this re-open carried do not apply:
 * the unit has no `.lit4` pool float and no float contraction, and the
 * assignment-placement axis is a measured null on the seed in both directions.
 */
#pragma divbyzerocheck on
#include "types.h"
/* normal 0x00522B90 -- 3-slice vertical window layout, twin of 0x005004B0.
 * Differences: the owner handle is the ADDRESS of the overlay object
 * normal_D_00528180 (lui/%lo, still null-tested), and the scaled loop has no
 * "blank the frame" flag arm. */

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

typedef struct Obj { u8 pad00[0x40]; } Obj;

extern Obj   normal_D_00528180;
extern s16   D_004807C8[3];                /* gp - 0x49A8 */
extern s16   D_004807D0[3];                /* gp - 0x49A0 */
extern f32   D_004807D8;
extern f32   D_004807DC;
extern f32   D_004807E0;                /* gp - 0x4998 */

/*rgp*/

f32 normal_HelpMenuScrollBarLayout_522b90(s32 a, s32 b, s32 c, s32 d)
{
    s16 w[3];
    HU  hu __attribute__((aligned(16)));
    f32 fl[3];
    f32 fb;
    f32 p1;
    f32 p2;
    f32 v;
    f32 r;
    volatile f32 *m;
    void *p;
    Owner *o;
    Quad *q;
    s32 n;
    s32 i;

    fb = (f32)b;
    p = &normal_D_00528180;
    if (p == NULL) {
        return 0.0f;
    }
    *(S3 *)w = *(S3 *)&D_004807C8;
    hu.s = *(S3 *)&D_004807D0;
    *(V3 *)fl = *(V3 *)&D_004807D8;
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
        q->f0C = 8;
        q->f04 = 8;
        q->f0E = hu.v[i];
        q->f06 = hu.v[i];
        q->f08 = 0x5E;
        q->f0A = w[i];
        q->f10 = 0;
        q->f14 = fl[i];
        q++;
    }
    return r;
    }
}
