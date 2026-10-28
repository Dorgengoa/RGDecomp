/* rgp:protos */
#define RGP_SELF_factory_FactoryPartLift_501ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00501FF0 -- remove the placement `idx' from the list:
 * validate its rectangle is still clear, run the per-cell release, unstamp both
 * grids (fixing up every later index), compact the slot array down and re-seat
 * the transform of the slot that moved into the hole.  1188 bytes.
 *
 * ** SESSION 23 (lane fz23c): the 4 residue words at 0x005023F0-0x005023FC are
 * a PURE SCHEDULER TIE-BREAK on two independent 2-instruction chains, and the
 * REGISTER ASSIGNMENT ALREADY MATCHES ($2 = tmp.f26, $4 = last->f26, $3 = -4),
 * so mwcc's IR order is retail's -- only the final schedule swaps the two `lb`s.
 * Retail: lb tmp.f26 / lb last->f26 / andi / and.  Ours: lb last / lb tmp / and
 * / andi.  MEASURED INERT: naming the mask in its own local
 * (`mm = last->f26 & ~3; last->f26 = (s8)(mm | kk);`) -- BYTE-IDENTICAL object,
 * mwcc folds the local away entirely.  MEASURED WORSE (4 -> 5): swapping the OR
 * operands to `(s8)(kk | (last->f26 & ~3))` -- it flips the `or` encoding at
 * 0x00502400 and does NOT reorder the loads, which proves the load order is
 * independent of the source expression order.  Reverted.
 *
 * ** LANE fz23g, 2026-08-31: still 4 bad at exact length, same four words.
 * The 4-bad baseline was RE-CONFIRMED offline against build/obj-fz23c first.
 * TWO MORE CELLS MEASURED, both now closed:
 *   - MEASURED WORSE (4 -> 19): hoisting `kk = tmp.f26 & 3;` up to immediately
 *     after `factory_FactoryPartObjCopy_4fe180(last, &tmp);`.  This is the brief's
 *     `give the scheduler an independent instruction first` arm and it FAILS
 *     here for a reason worth recording: mwcc DOES move `lb $x,0xC6($29)`
 *     above the twelve stores through `last`, i.e. it does NOT treat the
 *     address-taken local `tmp` as aliasing stores through the `Slot *`.  The
 *     load lands at 0x005023B8 and the whole register assignment rotates
 *     ($4=kk, $2=-4, $3=last), destroying the one thing that was already right.
 *     ⇒ STATEMENT POSITION MOVES THE LOAD; it does not re-order the pair.
 *   - MEASURED INERT (byte-identical): naming BOTH halves and putting the
 *     `last` half FIRST -- `mm = last->f26 & ~3; kk = tmp.f26 & 3;
 *     last->f26 = (s8)(mm | kk);`.  This is NOT the cell the earlier note
 *     measured (that one left `kk` defined first); it is a distinct
 *     declaration/definition ORDER and it is also inert.
 * ⇒ Three independent axes -- expression operand order, named-local definition
 * order, and statement position -- are now all measured.  The emission order of
 * the two `lb`s is invariant under every one of them, so it is NOT reachable
 * through the source of this expression.  The remaining hypothesis is that the
 * scheduler prefers to continue with the base register the twelve preceding
 * stores already use ($16, `last`) before starting a $29-based load; testing
 * that needs a different unit, not another spelling here.
 *
 * ** LANE fz23k, 2026-08-31: **CLOSED, BYTE-IDENTICAL, 297 words.**  The four
 * words were bought by NAMING THE RAW LOAD -- not the masked value:
 *     t = tmp.f26;
 *     last->f26 = (s8)((last->f26 & ~3) | (t & 3));
 * Every earlier cell named the MASKED half (`kk = tmp.f26 & 3;`), which mwcc
 * folds away; naming the LOAD ITSELF pins it as its own statement and the two
 * `lb`s come out in retail's order (tmp first).  ⚠ THE TYPE OF THE NAMED LOCAL
 * IS LOAD-BEARING: `u32 kk = tmp.f26;` is BYTE-IDENTICAL TO THE BASELINE (the
 * s8->u32 conversion lets mwcc fold the load back into the expression), while
 * `s32 t = tmp.f26;` and `u32 kk = *(volatile s8 *)&tmp.f26;` are ONE OBJECT
 * and both MATCH.  So the lever is `name the raw load in a local WIDE AND
 * SIGNED enough that the load needs no conversion`.
 * Measured alongside, all still wrong: `kk = *(volatile s8 *)&tmp.f26 & 3;`
 * (the masked value, volatile) reaches retail's LOAD ORDER but rotates the
 * -1/-4 constant pair onto the wrong registers -> 12 bad; the same pin with
 * the `or` operands swapped, with a named `mm` for either half, with `~3` in
 * its own variable, with `kk` re-typed u8/u16/s32 and with `kk` declared first
 * are all 12.  `s8 kk` is a LENGTH change (+2).  Statement position for the
 * masked form (before f38/f3C, before the rect stores) is 14.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Rect {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} Rect;

typedef struct Slot {
    s8    f00;
    u8    pad01[0x1F];
    Node *f20;
    s8    f24;
    s8    f25;
    s8    f26;
    s8    f27;
    s16   f28;
    s16   f2A;
    u8    pad2C[0x4];
    Rect  f30;
    s32   f38;
    s32   f3C;
} Slot;

typedef struct List {
    u8    pad00[0x4];
    s16   f04;
    u8    pad06[0x6];
    s16   f0C;
    u8    pad0E[0x2];
    Slot *f10;
} List;

typedef struct Ctx {
    u8    pad000[0x294];
    Cell *f294;
    s16   f298;
    s16   f29A;
    u8    pad29C[0x4];
    Cell *f2A0;
    s16   f2A4;
    s16   f2A6;
    u8    pad2A8[0x3C];
    s16   f2E4;
    u8    pad2E6[0x2];
    s16   f2E8;
    u8    pad2EA[0x10];
    s16   f2FA;
    s16   f2FC;
    s16   f2FE;
} Ctx;

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
/*rgp*/

List *factory_FactoryPartLift_501ff0(Ctx *c, s32 tag, s32 idx)
{
    Rect  r __attribute__((aligned(16)));
    Slot  tmp __attribute__((aligned(16)));
    f32   vc[4] __attribute__((aligned(16)));
    f32   vb[4] __attribute__((aligned(16)));
    f32   va[4] __attribute__((aligned(16)));
    List *l;
    Slot *h;
    Slot *s;
    Slot *last;

    Cell *p;
    s32   row;
    s32   col;
    s32   i;
    s32   n;
    s32   t;
    u32   mm;
    s32   x0;
    s32   y0;
    s32   x1;
    s32   y1;
    Rect *rp;
    Slot *base;
    Slot *s2;
    Node **pn;
    u32   kk;
    s32   off;

    l = ((List *)factory_FactoryPartGroupFindById_504080((void *)c, (int)tag));
    if (l == NULL) {
        return NULL;
    }
    if (l->f0C <= idx) {
        return NULL;
    }
    h = ((Slot *)factory_FactoryPartGroupGetObj_4fea80(l, idx));
    if (h == NULL) {
        return NULL;
    }
    x0 = h->f30.x0;
    y0 = h->f30.y0;
    x1 = h->f30.x1;
    y1 = h->f30.y1;
    r.x0 = (s16)x0;
    r.y0 = (s16)y0;
    r.x1 = (s16)x1;
    r.y1 = (s16)y1;
    if (x0 < 0) {
        return NULL;
    }
    if (r.y0 < 0) {
        return NULL;
    }
    if (r.x1 >= c->f2A4) {
        return NULL;
    }
    if (r.y1 >= c->f2A6) {
        return NULL;
    }
    for (row = r.y0; row <= r.y1; row++) {
        for (col = x0; col <= r.x1; col++) {
            p = c->f2A0 + row * c->f2A4 + col;
            t = !(p->f04 & 0x8000);
            if (t == 0) {
                return NULL;
            }
        }
    }
    rp = &r;
    for (row = r.y0; row <= rp->y1; row++) {
        for (col = rp->x0; col <= rp->x1; col++) {
            factory_FactorySlotPickUp_5000f0(c, col, row);
        }
    }
    for (row = 0; row < c->f2A6; row++) {
        for (col = 0; col < c->f2A4; col++) {
            p = c->f2A0 + row * c->f2A4 + col;
            if (p->f00 == tag) {
                if (p->f02 == idx) {
                    p->f00 = -1;
                    p->f02 = -1;
                    mm = p->f04 & ~3;
                    p->f04 = (u16)(mm & 3);
                } else if (idx < p->f02) {
                    p->f02 = p->f02 - 1;
                }
            }
        }
    }
    for (row = 0; row < c->f29A; row++) {
        for (col = 0; col < c->f298; col++) {
            p = c->f294 + row * c->f298 + col;
            t = !(p->f04 & 0x8000);
            if (t != 0) {
                if (p->f00 == tag) {
                    if (p->f02 == idx) {
                        p->f00 = -1;
                        p->f02 = -1;
                        mm = p->f04 & ~3;
                        p->f04 = (u16)(mm & 3);
                    } else if (idx < p->f02) {
                        p->f02 = p->f02 - 1;
                    }
                }
            }
        }
    }
    base = l->f10;
    off = idx * 0x40;
    tmp.f30.x0 = -1;
    tmp.f30.y0 = -1;
    tmp.f30.x1 = -1;
    tmp.f30.y1 = -1;
    tmp.f24 = -1;
    tmp.f38 = 0;
    tmp.f3C = 0;
    tmp.f00 = 0;
    tmp.f20 = NULL;
    tmp.f25 = 0;
    tmp.f26 = 0;
    tmp.f27 = 0;
    tmp.f28 = 0;
    tmp.f2A = 0;
    s = &base[idx];
    factory_FactoryPartObjCopy_4fe180(&tmp, s);
    s2 = (Slot *)(off + (s32)base);
    pn = (Node **)((s32)s2 + 0x20);
    NodeGetTranslation_186650(s2->f20, vc);
    NodeGetRotation_1865e0(*pn, vb);
    NodeGetScale_186560(*pn, va);
    for (i = idx + 1; i < l->f0C; i++) {
        factory_FactoryPartObjCopy_4fe180(&base[i - 1], &base[i]);
    }
    n = l->f0C - 1;
    l->f0C = n;
    last = &base[(s16)n];
    factory_FactoryPartObjCopy_4fe180(last, &tmp);
    last->f24 = -1;
    last->f25 = 0;
    last->f26 = 0;
    last->f27 = 0;
    last->f28 = 0;
    last->f2A = 0;
    last->f30.x0 = -1;
    last->f30.y0 = -1;
    last->f30.x1 = -1;
    last->f30.y1 = -1;
    last->f38 = 0;
    last->f3C = 0;
    t = tmp.f26;
    last->f26 = (s8)((last->f26 & ~3) | (t & 3));
    NodeSetTranslation_1866b0(last->f20, vc);
    NodeSetRotation_186620(last->f20, vb);
    NodeSetScale_1865b0(last->f20, va);
    last->f20->f32 = 0;
    c->f2E4 = last->f26 & 3;
    c->f2E8 = l->f04;
    c->f2FA = factory_FactoryPartObjGetGridX_4fe120(&tmp);
    c->f2FC = factory_FactoryPartObjGetGridY_4fe0c0(&tmp);
    c->f2FE = tmp.f26 & 3;
    return l;
}
