#include "types.h"

/* factory.bin overlay, 0x00500D80 -- 79 words, EXACT LENGTH, 7 bad (was 9).
 * Session 23, lane fz23a.
 *
 * WHAT MOVED (9 -> 7): splitting the float product into
 *     lim = o->f2A8;
 *     lim = 2.0f * lim;
 * fixed 0x00500D8C (`mtc1 $2,$f0`, was $f1) and 0x00500DD4 (`lwc1 $f1,0x2A8`,
 * was $f0).  mwcc numbers the two fp temps by BIRTH, and the separate load
 * statement makes the LOAD born first ($f1) and the literal second ($f0),
 * which is retail's colouring.  mwcc does NOT fold that pair back.
 *
 * RESIDUE 1 -- 0x00500DE4: ours 46000802 `mul.s $f0,$f1,$f0`, retail 46010002
 * `mul.s $f0,$f0,$f1`.  Registers are now CORRECT ($f0 = 2.0f, $f1 = f2A8);
 * only fs/ft are swapped.  Our compiler emits dst == ft here: with one operand
 * a REGISTER-RESIDENT LOCAL it puts that local in fs, so the literal lands in
 * ft.  Retail has dst == fs with the literal in fs.
 *   MEASURED INERT / WORSE on this word:
 *     `lim = 2.0f * o->f2A8;`            (baseline, and it also loses the two
 *                                        register words above)
 *     `lim = 2.0f; lim = lim * o->f2A8;` CONSTANT-PROPAGATED -- byte-identical
 *                                        to the baseline object (both reg
 *                                        words lost again).
 *   NOT YET TRIED: a literal used TWICE, e.g. `(2.0f*x)*(2.0f*x)`.
 *
 * RESIDUE 2 -- 0x00500DF4..0x00500E04 + 0x00500E78, a 6-word REGISTER
 * PERMUTATION in the address arithmetic, no instruction differs:
 *     ours   f06=$5  base=$2  acc=$3   result reuses BASE's reg
 *     retail f06=$3  base=$5  acc=$2   result reuses ACC's reg
 *   The shift/add chain (f06*2, +f06, *2, +base) and the folded -0x6/-0x4 lh
 *   displacements are already correct.
 *   MEASURED INERT: `s32 n = e->f06; e->f00[n-1].x` (a named local for f06 --
 *   byte-identical, still folds the -1 into the displacement);
 *   `p = (V*)(e->f06*6 + (s32)e->f00); p[-1].x` -- ALSO byte-identical to the
 *   plain `e->f00[e->f06-1].x` array form, so index-first arithmetic is a
 *   MEASURED NULL here (it is NOT the 00500450 lever).
 *   WORSE / LENGTH-BREAKING: `p = (V*)((e->f06 - 1) * 6 + (s32)e->f00)` costs
 *   +1 word -- the explicit `- 1` materialises `addiu $5,$3,-1` and the -0x6
 *   displacement fold is LOST.  (It did put f06 in $3, but only because the
 *   new temp took $5.)
 */

/* ** SESSION 23 (lane fz23l): 7 -> 6 bad, 79 words.  RESIDUE 1, the `mul.s`
 * fs/ft swap at 0x00500DE4, is CLOSED.  ONE TOKEN -- give the PRODUCT its own
 * destination instead of writing back into the load's local:
 *     lim = o->f2A8;   pr = 2.0f * lim;   lim = pr * pr;
 * MECHANISM: `lim = 2.0f * lim;` is a SELF-ASSIGNMENT and mwcc rewrites it as
 * an accumulate, which forces the reused local into `fs` and the literal into
 * `ft`.  A distinct destination leaves the SOURCE operand order intact, so the
 * literal keeps `fs` and retail's `mul.s $f0,$f0,$f1` comes out.  The load must
 * still be born into `lim` FIRST -- that is what holds $f1/$f0.
 *   ⚠ THE COMPLEMENTARY ARM IS REGRESSIVE, measured: moving the LOAD to a new
 *   local instead (`tw = o->f2A8; lim = 2.0f * tw;`) goes 7 -> 9 -- it flips the
 *   $f0/$f1 birth colouring back to the baseline AND leaves the operand order
 *   wrong.  It is the PRODUCT that needs the fresh name, not the load.
 *
 * ! RESIDUE, 6 words -- the address-arithmetic register permutation only:
 *   0x00500DF4/F8/FC/E00/E04 + 0x00500E78.  No instruction differs.
 *     ours   n=$5  base=$2  acc=$3   result reuses BASE's register
 *     retail n=$3  base=$5  acc=$2   result reuses ACC's register
 *   MEASURED INERT THIS SESSION: naming the base pointer
 *   (`V *vp; vp = e->f00; a = vp[n-1].x;`) -- byte-identical, so naming the
 *   BASE joins naming the INDEX and the whole index-first pointer form in the
 *   null column.  Every spelling of this address is one object.
 */

/* ★★★★★★★ SESSION 36 (2026-09-02, lane fg36): 6 -> 0 BAD, BYTE-IDENTICAL,
 * MERGED into config/ocunits/factory.txt.  The named base pointer the line
 * above recorded as inert becomes the whole unit once its LOAD is pinned:
 *     vp = *(V *volatile *)&e->f00;
 *     a = vp[n - 1].x;
 *     b = vp[n - 1].y;
 * The volatile ACCESS-SITE pin ([[mwcc-volatile-access-site-pin]]) on the
 * BASE load is what decides the address-arithmetic colouring: pinned, the
 * base is loaded where the source says and the shift/add chain on `n` is
 * built after it, so `n` takes $3, the base $5, the accumulator $2 and the
 * result reuses the accumulator's register -- retail's map.  Same class as
 * factory_FactoryGridRotatePoint_4fe820's close this session (pin the LOAD that retail issues
 * first / in place), and the same tell: every NAMING of the value was inert
 * because mwcc forward-substitutes a single-use local; the pin is what makes
 * the load a statement of its own.
 * MEASURED THIS SESSION (md5 = object identity):
 *   INERT (baseline ed9cc02c6e89): `n` declared first / last; the named base
 *     `vp` declared first (unpinned); `vp` first + `n` last; the index-first
 *     `(V *)(n * 6 + (s32)e->f00)` through a named pointer; volatile pins on
 *     `e->f06`, `o->f2A8`, `o->f2B0`, `o->f2AC`.
 *   WORSE: `a`/`b` declared first: 32.  LENGTH-BREAKING (+5): a volatile pin on
 *     `e->f00[n - 1].x` or `.y` themselves -- it kills the -6/-4 displacement
 *     fold.  Pin the BASE, not the indexed element.
 */
typedef struct V {
    s16 x;
    s16 y;
    s16 z;
} V;

typedef struct E {
    V  *f00;
    u8  pad04[0x2];
    s16 f06;
    u8  pad08[0x4];
} E;

typedef struct A {
    u8  pad00[0x2A8];
    f32 f2A8;
    E  *f2AC;
    s16 f2B0;
} A;

extern f32 factory_FactoryFineGridCellCenterX_5037c0(A *o, s32 i);
extern f32 factory_FactoryFineGridCellCenterZ_503790(A *o, s32 i);

s32 factory_FactoryBeltFindEndNear_500d80(A *o, s16 *outA, s16 *outB, f32 px, f32 py)
{
    V  *vp;
    E  *e;
    s32 i;
    s32 best;
    s32 b;
    s32 a;
    s32 n;
    f32 lim;
    f32 pr;
    f32 ax;
    f32 ay;
    f32 d;

    e = o->f2AC;
    lim = o->f2A8;
    pr = 2.0f * lim;
    lim = pr * pr;
    best = -1;
    for (i = 0; i < o->f2B0; i++, e++) {
        n = e->f06;
        vp = *(V * volatile *)&e->f00;
        a = vp[n - 1].x;
        b = vp[n - 1].y;
        ax = factory_FactoryFineGridCellCenterX_5037c0(o, a);
        ay = factory_FactoryFineGridCellCenterZ_503790(o, b);
        d = (ax - px) * (ax - px) + (ay - py) * (ay - py);
        if (d < lim) {
            if (outA != 0) {
                *outA = a;
            }
            if (outB != 0) {
                *outB = b;
            }
            lim = d;
            best = i;
        }
    }
    return best;
}
