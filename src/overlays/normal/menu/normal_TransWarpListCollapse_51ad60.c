#include "types.h"
/* normal 0x0051AD60 -- rebuilds the shop slot list D_00484870 in place.  The
 * old list is copied to a 0xC00 stack buffer, the global is zeroed, and the
 * entries are walked back one at a time; the entry whose f0C matches the
 * argument is re-tagged and every matching iterator hit skips one source row.
 * Frame -0xC70: save area 0x00-0x50, then q (0x10 at 0x50), buf (0xC00 at
 * 0x60) and it (8 B at 0xC68) in REVERSE declaration order -- `it` first
 * ([[factory-list-ranking]], normal_TransHunterBountyMarkReported_51e480's own note).
 * The prologue idiom is MERGED normal_TransWarpListRowsFill_51b4b0's verbatim.
 *
 * BYTE-IDENTICAL (s23).  Two levers after a right-length 43-bad first build:
 *
 * (1) `d` DECLARED BEFORE `p`.  First-declared takes the HIGHER callee-saved
 *     register: w=$19, d=$17, p=$16 ($18 is the parameter).  43 -> 15 bad, and
 *     every one of the 28 was a $16/$17 swap.
 *
 * (2) ****** THE COMMA OPERATOR IS WHAT SELECTS retail's BRANCH-LIKELY LOOP.
 *     `while ((e = f(&it)) != 0)` tests the ASSIGNMENT EXPRESSION's value --
 *     the call's return in $2 -- so the coalescing `daddu $4,$2,$0` is
 *     INDEPENDENT of the branch and mwcc SINKS IT into the delay slot and
 *     emits a plain `bnez $2`.  `while (e = f(&it), e != 0)` tests the NAMED
 *     `e`, so the copy must PRECEDE the branch, mwcc has nothing to sink, and
 *     it takes the likely-branch strategy retail has: `daddu $4,$2,$0` /
 *     `bnel $4,$0` with the body's first `lw $2,0x40($4)` DUPLICATED into the
 *     annulled slot and the target bumped past it.  15 bad -> MATCH.
 *     `, e`, `, !!e` and `(..., e) != 0` are the SAME OBJECT; `!= (Itm *)0`
 *     and a bare `while ((e = f(&it)))` are the BASE object.
 *     ⚠ Rewriting the loop as `for(;;) { e = f(&it); if (e == 0) break; ... }`
 *     -- the obvious way to name the test -- moves the CALL to the top of the
 *     loop and is TWO WORDS SHORT (4 spellings, one object).  The comma keeps
 *     the call in the latch block, which is what the rotation needs.
 *     => [[mwcc-branch-likely-duplication]] read in REVERSE: when RETAIL has
 *     the likely branch, the lever is to TAKE AWAY the sinkable instruction. */

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
    u8  pad00[0x40];
    u32 f40;
} Itm;

typedef struct Sub { u8 pad00[4]; s16 f04; } Sub;
typedef struct Ev  { u8 pad00[0x18]; Sub *f18; } Ev;
typedef struct Q   { s32 x[4]; } Q;
typedef struct It  { s32 x[2]; } It;

extern Ent *D_00484870;      /* gp - 0x900 */
extern s32  D_00484850;      /* gp - 0x920 */

extern void  func_1319A8(void *dst, void *src, s32 n);
extern void  func_131B60(void *p, s32 v, s32 n);
extern Ev   *func_1FEDE0(void);
extern s32   func_207F30(void);
extern void  func_425440(Q *q, Ev *e, s16 w, s32 f);
extern void  func_370170(It *it, Q *q);
extern Itm  *func_370040(It *it);
extern s32   func_426560(Itm *e);

s32 normal_TransWarpListCollapse_51ad60(s32 a)
{
    It   it;
    Ent  buf[0x40];
    Q    q;
    Ev  *w;
    Ent *d;
    Ent *p;
    Itm *e;
    s32  f;
    s16  h;

    func_1319A8(buf, D_00484870, 0xC00);
    D_00484850 = 0;
    func_131B60(D_00484870, 0, 0xC00);
    w = func_1FEDE0();
    h = w->f18->f04;
    f = 1;
    if (func_207F30() != 0) {
        f = 0;
    }
    func_425440(&q, w, h, f);
    func_370170(&it, &q);
    d = D_00484870;
    p = buf;
    while (p->f00 != -1) {
        if (D_00484850 > 0x40) {
            break;
        }
        if (p->f0C == a) {
            d->f00 = 1;
        } else {
            d->f00 = p->f00;
        }
        d->f04 = p->f04;
        d->f0C = p->f0C;
        d->f08 = p->f08;
        d->f10 = p->f10;
        d->f14 = p->f14;
        d->f18 = p->f18;
        d->f20 = p->f20;
        d->f24 = p->f24;
        d->f28 = p->f28;
        D_00484850++;
        d++;
        if (p->f0C == a) {
            while (e = func_370040(&it), e != 0) {
                if ((e->f40 & 1) != 0) {
                    if (a == func_426560(e)) {
                        p++;
                    }
                }
            }
        }
        p++;
    }
    d->f00 = -1;
    return 1;
}
