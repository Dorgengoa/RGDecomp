#include "types.h"

/* factory.bin overlay, 0x005024A0 -- remove the coarse-grid placement `idx':
 * validate the cell, unstamp the grid (fixing up every later index), compact
 * the slot array down and re-seat the transform that moved.  704 bytes.
 *
 * BYTE-IDENTICAL, session 23 (lane fz23c).  Four edits, every one of them a
 * shape its twin factory_FUN_00501FF0 already uses:
 *  1. NAME THE HANDLE: `base = l->f10;` hoisted above the `tmp` stores.  mwcc
 *     will not move a load past stores it cannot disambiguate, so leaving
 *     `l->f10` inline re-loaded it twice ([[insect-load-across-store]]).
 *  2. TWO SPELLINGS for the slot address: `s = &base[idx]` for the copy call and
 *     `s2 = (Slot *)(off + (s32)base)` for the transform reads, with
 *     `off = idx * 0x34`.  That is retail's two `addu`s (`addu $5,$16,$19` at
 *     0x00502640 and `addu $2,$19,$16` at 0x00502664) off one shared idx*52
 *     chain ([[insect-cse-two-spellings]]).
 *  3. `pn = (Node **)((s32)s2 + 0x20)` and `*pn` for the 2nd and 3rd transform
 *     calls: retail keeps &s->f20, not the slot pointer, in the callee-saved
 *     register across the calls (`addiu $19,$2,0x20` / `lw $4,0x0($19)`).
 *  4. The `tmp` init is written -1 GROUP FIRST (f30, f32, f24) then the zeros
 *     (f00, f20, f25, f26, f27, f28, f2A).  The store order IS the source order;
 *     the wrong order was the last 4 bad words (0x00502630-0x00502640).
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
    s16   f30;
    s16   f32;
} Slot;

typedef struct List {
    u8    pad00[0xC];
    s16   f0C;
    u8    pad0E[0x2];
    Slot *f10;
} List;

typedef struct Ctx {
    u8    pad000[0x294];
    Cell *f294;
    s16   f298;
    s16   f29A;
} Ctx;

extern List *factory_FactoryBeltTileGroupFindById_5040d0(void);
extern Slot *factory_FactoryBeltTileGroupGetObj_4ff180(List *l, s32 id);
extern void factory_FactoryBeltTileObjCopy_4ff030(Slot *dst, Slot *src);
extern void func_186650(Node *nd, f32 *v);
extern void func_1865E0(Node *nd, f32 *v);
extern void func_186560(Node *nd, f32 *v);
extern void func_1866B0(Node *nd, f32 *v);
extern void func_186620(Node *nd, f32 *v);
extern void func_1865B0(Node *nd, f32 *v);

List *factory_FactoryBeltTileRemove_5024a0(Ctx *c, s32 tag, s32 idx)
{
    Slot  tmp;
    f32   vc[4];
    f32   vb[4];
    f32   va[4];
    List *l;
    Slot *h;
    Slot *s;
    Slot *last;
    Slot *base;
    Slot *s2;
    Node **pn;
    Cell *p;
    s32   x;
    s32   y;
    s32   row;
    s32   col;
    s32   i;
    s32   n;
    s32   t;
    s32   off;

    l = factory_FactoryBeltTileGroupFindById_5040d0();
    if (l == NULL) {
        return NULL;
    }
    h = factory_FactoryBeltTileGroupGetObj_4ff180(l, idx);
    if (h == NULL) {
        return NULL;
    }
    x = h->f30;
    if (x < 0) {
        return NULL;
    }
    y = h->f32;
    if (y < 0) {
        return NULL;
    }
    if (x >= c->f298) {
        return NULL;
    }
    if (y >= c->f29A) {
        return NULL;
    }
    p = c->f294 + y * c->f298 + x;
    t = !(p->f04 & 0x8000);
    if (t == 0) {
        return NULL;
    }
    for (row = 0; row < c->f29A; row++) {
        for (col = 0; col < c->f298; col++) {
            p = c->f294 + row * c->f298 + col;
            if (p->f00 == tag) {
                if (p->f02 == idx) {
                    p->f00 = -1;
                    p->f02 = -1;
                    p->f04 = 0;
                } else if (idx < p->f02) {
                    p->f02 = p->f02 - 1;
                }
            }
        }
    }
    base = l->f10;
    tmp.f30 = -1;
    tmp.f32 = -1;
    tmp.f24 = -1;
    tmp.f00 = 0;
    tmp.f20 = NULL;
    tmp.f25 = 0;
    tmp.f26 = 0;
    tmp.f27 = 0;
    tmp.f28 = 0;
    tmp.f2A = 0;
    off = idx * 0x34;
    s = &base[idx];
    factory_FactoryBeltTileObjCopy_4ff030(&tmp, s);
    s2 = (Slot *)(off + (s32)base);
    pn = (Node **)((s32)s2 + 0x20);
    func_186650(s2->f20, vc);
    func_1865E0(*pn, vb);
    func_186560(*pn, va);
    for (i = idx + 1; i < l->f0C; i++) {
        factory_FactoryBeltTileObjCopy_4ff030(&base[i - 1], &base[i]);
    }
    n = l->f0C - 1;
    l->f0C = n;
    last = &base[(s16)n];
    factory_FactoryBeltTileObjCopy_4ff030(last, &tmp);
    func_1866B0(last->f20, vc);
    func_186620(last->f20, vb);
    func_1865B0(last->f20, va);
    last->f20->f32 = 0;
    return l;
}
