/* SESSION 67 (2026-09-20): **MATCH**, 154 -> 0 on a FIVE-EDIT CROSS.
 * The screen was [[mwcc-identity-cast-splits-cse]]'s: NINE callee-saved `sq`s
 * against retail's EIGHT, frame 0xA0 vs 0x90.  The ninth register held
 * `a + i`, CSE'd between the record index and the bounds index across six
 * calls, where retail rematerialises it at 0x0051D994.
 *   1. `k = a + (s32)i;`  -- an IDENTITY cast on the ADDEND (not the index)
 *      is what splits an INTEGER-add web; every index-cast spelling
 *      ((u32)/(s32)/plain, both sites, all 8 combinations) is ONE OBJECT.
 *      This alone is sq 9 -> 8, frame 0x90, and 1 word SHORT.
 *   2. `ok = 0; if (k < 0 || k >= s->f07C) {} else { ok = 1; }` -- the
 *      EMPTY-THEN `||` guard.  if/else, pre-assign+`&&`, the nested form and
 *      the `ok = (expr)` form all emit `bnel` where retail has `beqz`+`nop`;
 *      this form is the +1 word that pays for edit 1.  (thread.py @0x0051D9B0)
 *   3. `v = e->f010;` moved BELOW func_291250 -- retail loads it at
 *      0x0051D91C into $2.  Above the calls it is +2 bad on the old coat and
 *      the difference between 55 and 5 on the new one.
 *   4. `(s32)e->f00C` at the func_1343B8 call -- a REDUNDANT NARROWING at an
 *      `s16` parameter; it puts `addiu $5,$5,%lo(D_00526848)` in the jal's
 *      delay slot instead of `daddu $4,$21,$0`.
 *   5. `(u32)e->f004` at the func_291250 call -- it orders the `lw $7,0x4($18)`
 *      BEFORE the `lw $4,-0xA60($28)`.  (long)/(s32)(u32) and an `u32`/`long`
 *      4th parameter are the same object; a plain `(s32)` is not.
 * Edits 4 and 5 are independently -2 each and compose exactly.
 * Sweeps in build/wf-normal/s67/ (gen1d820*.py). */
/* SESSION 65: `n >= 0x65` -> `n > 0x64`, the [[at-compare-class]] operator
 * spelling for retail's `slti $1,$2,0x65`.  atscan.py's `slti_at: 1->0` row is
 * gone; the two remaining rows are REGISTER-bound `slt $1,...` compares still
 * unfound in the source.  Still 154 bad / 167 words.
 */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `E_ifelse2_L145_els` from the seed/else deck (mkelse31.py)
 *   before: 167 words, 154 bad   after: 167 words, 154 bad   (retail 167 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * (STALE: MERGED session 67.) */
#include "types.h"
/* SESSION 30: 156 -> 154 bad on the pool-wide DEFINING-STATEMENT MOVE deck
 * (build/wf-normal/s30/mkmove30.py) -- CREATION order, not declaration
 * order.  Still open.  (STALE: MERGED session 67.) */
/* !! PARKED, lane `ne` (research), session 19.  RIGHT LENGTH (167 words),
 * 156 BAD.  NOT in config/ocunits/normal.txt.
 *
 * ROUND TRIPS: 3.  MOVEMENT: 3 words short -> right length, via
 *  * the small-data escape in the OTHER direction: `extern u8 D_00526848;`
 *    (1 byte) went to $gp (`addiu $a1,$gp,0x16D8`); declaring it
 *    `extern u8 D_00526848[16];` forces retail's `lui %hi / addiu %lo` pair.
 *  * two spellings for `a + i` (`(s32)(a + i)` at the record index, `i + a`
 *    at the bounds check), which stops mwcc CSE-ing them into one value.
 *
 * RESIDUE: ours allocates EIGHT callee-saved registers ($s0-$s7 + $fp,
 * frame 0xA0) against retail's seven (frame 0x90), and spilled the `a`
 * PARAMETER to 0xAC($sp) before the first call in the earlier arm.  The extra
 * register holds the scaled record index that retail recomputes.  Every
 * instruction OPCODE and every displacement matches; the whole 156 is the
 * register numbering that one extra live value forces.  Pure allocation. */

/* normal 0x0051D820 -- redraws the ten-row party list widget group 0x764x.
 *
 * The `v > 0 / v == 0 / v < 0` chain is written with all three tests present:
 * the third (`bgezl $2,.L0051D95C` at 0x0051D948) is provably dead by then, so
 * $16/$17 are genuinely uninitialised on the impossible path -- that is the
 * source shape, not a miss.  Each arm carries its own `addiu $16,$0,0x6A`.
 *
 * `daddiu $5,$0,0x1` for `ok` is a register-resident u8 and the consumer is a
 * BARE truth test, which is why there is no `andi` re-narrow
 * ([[mwcc-daddiu-unsigned-narrow]]). */

typedef struct Rec {
    u8  pad000[4];
    s32 f004;
    u8  pad008[4];
    s16 f00C;
    u8  pad00E[2];
    s16 f010;
} Rec;

typedef struct Rec2 {
    u8  pad000[4];
    s16 f004;
    u8  pad006[0x14 - 6];
} Rec2;

typedef struct Holder {
    u8   pad000[0x14];
    Rec *f014;
} Holder;

typedef struct Grp {
    u8    pad000[0x7C];
    s16   f07C;
    u8    pad07E[0x8C - 0x7E];
    Rec2 *f08C;
} Grp;

typedef struct Obj94 {
    u8      pad000[0x10];
    Grp    *f010;
    Holder *f014;
} Obj94;

typedef struct Node8 {
    u8      pad000[0x94];
    Obj94  *f094;
} Node8;

typedef struct Ctx {
    u8      pad000[8];
    Node8  *f008;
    u8      pad00C[4];
    void   *f010;
} Ctx;

extern s16   D_00480758;          /* gp - 0x4A18 */
extern void *D_00484710;          /* gp - 0xA60  */
extern u8    D_00526848[16];
extern u8    D_00527FA0[10][4];

extern Ctx  *func_1FEDE0(void);
extern void  func_290A40(void *p, s32 id, u32 c, s32 d);
extern void  func_1343B8(u8 *p, const u8 *fmt, s16 a);
extern void  func_28F510(void *p, s32 id, const void *q, s32 d);
extern void *func_3FDA80(Rec *e);
extern void  func_291250(void *w, s32 id, s32 a, s32 b);
extern void  func_28F970(void *p, s32 id, s32 c, s32 d, s32 e);
extern void  func_28F670(void *p, s32 id, s32 c, s32 d, s32 e, s32 f, s32 g);
extern s32   func_3CCAC0(void *a, s32 b);
extern void  func_28F930(void *p, s32 id, s32 c, s32 d);
extern s32   func_3FDAA0(Rec *e);

s32 normal_TransHunterRankListFill_51d820(s32 a)
{
    Ctx    *ctx;
    Holder *r;
    s32     i;
    Rec    *e;
    u8     *buf;
    void   *p;
    s32     v;
    s32     c;
    s32     d;
    Grp    *s;
    s32     k;
    u8      ok;
    Rec2   *q;
    s32     n;

    ctx = func_1FEDE0();
    r = ctx->f008->f094->f014;
    if (r == 0) {
        return 0;
    }
    i = 0;
    D_00480758 = -1;
    while (i < 10) {
        func_290A40(D_00484710, 0x7641, 0xFF303030, i);
        e = &r->f014[(s32)(a + i)];
        if (e == 0) {
            return 0;
        }
        buf = D_00527FA0[i];
        func_1343B8(buf, D_00526848, (s32)e->f00C);
        func_28F510(D_00484710, 0x7649, buf, i);
        p = func_3FDA80(e);
        func_28F510(D_00484710, 0x7641, p, i);
        func_291250(D_00484710, 0x7649, i, (u32)e->f004);
        v = e->f010;
        if (v > 0) {
            c = 0;
            d = 0x6A;
        } else if (v == 0) {
            c = 0x16;
            d = 0x6A;
        } else if (v < 0) {
            c = 0x2C;
            d = 0x6A;
        }
        func_28F970(D_00484710, 0x7647, c, d, i);
        func_28F670(D_00484710, 0x7648, 0, 0, 0, 0, i);
        s = ctx->f008->f094->f010;
        k = a + (s32)i;
        ok = 0;
        if (k < 0 || k >= s->f07C) {
        } else {
            ok = 1;
        }
        if (ok) {
            q = &s->f08C[k];
        } else {
            q = 0;
        }
        if (q->f004 > 0) {
            func_28F670(D_00484710, 0x7648, 0x14, 0x16, 0x14, 0x16, i);
            n = func_3CCAC0(ctx->f010, 0xF);
            if (n <= 0 || n > 0x64) {
                n = 0x64;
            }
            if (e->f00C < n) {
                func_28F930(D_00484710, 0x7648, 0x24, i);
            } else {
                func_28F930(D_00484710, 0x7648, 0x38, i);
            }
        }
        if (func_3FDAA0(e) == 0) {
            D_00480758 = i;
        }
        i++;
    }
    return 1;
}
