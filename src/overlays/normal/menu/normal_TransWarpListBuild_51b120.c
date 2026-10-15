#include "types.h"
/* normal 0x0051B120 -- DRAFTED s27 by ORACLE TRANSFER from MERGED
 * normal_FUN_0051AEF0 / normal_FUN_0051AD60: the same shop-slot rebuild of
 * D_00484870, the same `Ent` (0x30) / `Itm` / `Q` / `It` types, the same
 * `func_131B60` clear + `func_425440` / `func_370170` / `func_370040` iterator,
 * and the same `while (e = func_370040(&it), e != 0)` comma-operator loop test
 * that selects retail's `bnel` with the body's first `lw` duplicated into the
 * ANNULLED slot ([[mwcc-branch-likely-duplication]]).
 * This one has NO source list to walk: it builds every row from the iterator,
 * emitting a HEADER row whenever the id CHANGES (`prev != k`) and a DETAIL row
 * for the selected id.  `k = func_426560(e)` is a NAMED local for the same
 * reason 0051AEF0 records: retail stores the CALL RESULT, not the parameter.
 *
 * FIRST BUILD: RIGHT LENGTH, 47 bad -- a whole-function REGISTER MAP problem
 * plus one schedule.  CLOSED in THREE arms, every one read through the MAP and
 * not the byte score (build/wf-normal/s27/rm_b120.py + msweep.py):
 * 1. 47 -> 28: `prev` declared FIRST.  Retail coalesces {w, d} onto $18 and
 *    leaves `prev` alone on $19; ours was coalescing {h, prev} onto $16 and
 *    giving `d` its own $19.  ⚠⚠ ALL SEVEN positions of `d`, of `w` and of `h`
 *    are wrong -- only `prev` at position 0 or 1 gives retail's map, and a
 *    BYTE-COUNT sweep of the same permutations reads 31/33/36/47/52/55 with no
 *    signal at all.  This is why the readout has to be the register.
 * 2. 28 -> 4: `k` declared BEFORE `e` (positions k@3 / e@5 / e@6 are one
 *    object).  Ours had e=$17 k=$16, retail e=$16 k=$17.
 * 3. 4 -> BYTE-IDENTICAL: `prev = -1;` moved BEFORE `func_370170(&it, &q)`.
 *    mwcc only sinks the instruction IMMEDIATELY BEFORE a call into its delay
 *    slot; with the assignment after the call the slot took the call's second
 *    argument instead, and `d = D_00484870` lost the following `b`'s slot.
 *    ⚠ Hoisting BOTH assignments above the call is one word LONG. */

typedef struct Ent {
    s16 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s8  f18;
    u8  pad19[7];
    f32 f20;
    f32 f24;
    f32 f28;
    s32 f2C;
} Ent;                                          /* 0x30 */

typedef struct Itm {
    s16 f00;
    u8  pad02[0x8 - 0x2];
    s32 f08;
    u8  pad0C[0x14 - 0xC];
    s16 f14;
    u8  pad16[0x18 - 0x16];
    s16 f18;
    u8  f1A;
    u8  pad1B[0x20 - 0x1B];
    f32 f20;
    f32 f24;
    f32 f28;
    u8  pad2C[0x40 - 0x2C];
    u32 f40;
} Itm;

typedef struct Sub { u8 pad00[4]; s16 f04; } Sub;
typedef struct Ev  { u8 pad00[0x18]; Sub *f18; } Ev;
typedef struct Q   { s32 x[4]; } Q;
typedef struct It  { s32 x[2]; } It;

extern Ent *D_00484870;      /* gp - 0x900 */
extern s32  D_00484850;      /* gp - 0x920 */

extern void  func_131B60(void *p, s32 v, s32 n);
extern Ev   *func_1FEDE0(void);
extern s32   func_207F30(void);
extern void  func_425440(Q *q, Ev *e, s16 w, s32 f);
extern void  func_370170(It *it, Q *q);
extern Itm  *func_370040(It *it);
extern s32   func_426540(Itm *e);
extern s32   func_426560(Itm *e);

s32 normal_TransWarpListBuild_51b120(s32 a)
{
    Q    q;
    It   it;
    s32  prev;
    Ev  *w;
    Ent *d;
    s32  k;
    Itm *e;
    s32  f;
    s16  h;

    D_00484850 = 0;
    func_131B60(D_00484870, 0, 0xC00);
    w = func_1FEDE0();
    h = w->f18->f04;
    f = 1;
    if (func_207F30() != 0) {
        f = 0;
    }
    func_425440(&q, w, h, f);
    prev = -1;
    func_370170(&it, &q);
    d = D_00484870;
    while (e = func_370040(&it), e != 0) {
        if ((e->f40 & 1) != 0) {
            k = func_426560(e);
            if (prev != k) {
                if (a == k) {
                    d->f00 = 2;
                } else {
                    d->f00 = 1;
                }
                d->f04 = func_426540(e);
                d->f0C = k;
                d->f10 = e->f14;
                d->f14 = e->f18;
                d->f18 = e->f1A & 1;
                D_00484850++;
                d++;
            }
            if (a == k) {
                d->f00 = 3;
                d->f04 = e->f08;
                d->f0C = k;
                d->f08 = e->f00;
                d->f10 = e->f14;
                d->f14 = e->f18;
                d->f18 = e->f1A & 1;
                d->f20 = e->f20;
                d->f24 = e->f24;
                d->f28 = e->f28;
                if (d->f20 == 0.0f && d->f24 == 0.0f && d->f28 == 0.0f) {
                    d->f10 = -1;
                }
                D_00484850++;
                d++;
            }
            prev = k;
        }
    }
    d->f00 = -1;
    return 1;
}
