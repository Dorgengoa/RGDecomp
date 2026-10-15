#include "types.h"

/* factory.bin overlay, 0x004F2D50 -- lay out the recipe list widgets.
 *
 * 284 instructions, 15 conditional branches, 31 calls: the branch-light band.
 *
 * ★ THE INNER `switch`'s CASE ORDER IS REVERSED IN THE COMPARE CHAIN.  Retail
 * tests 0x44C, 0x450, 0x44E, 0x44D, 0x44F in that order, so the source runs
 * 0x44F, 0x44D, 0x44E, 0x450, 0x44C -- which is also the ascending ADDRESS
 * order of the five bodies.  Writing them in the chain's order is the right
 * length and the wrong bytes.
 * ★ The chain's fall-through `b .L004F3068` carries `lw $2, 0x0($21)`, the
 * instruction at .L004F3064 -- the ordinary likely/plain-branch duplication of
 * the merge's first instruction, NOT a default arm.  There is no `default:`.
 * ★ `beql $2, $0, .L004F3148` on `func_28FE10`'s result, and both `bne`s after
 * it, are one three-term `&&`: all three land on the same increment block.
 * ★ `daddu $7, $6, $0` at the second func_291110 is mwcc noticing both
 * arguments are 1; the source says `1, 1`.
 *
 * ★★★★ THE RESIDUE WAS A 3-CYCLE IN THE CALLEE-SAVED ASSIGNMENT AND IT TOOK
 * TWO LEVERS IN SEQUENCE, NEITHER OF WHICH WORKS ALONE.
 *  1. THE FIRST TWO LOOPS' COUNTER IS A DIFFERENT SOURCE VARIABLE FROM THE
 *     THIRD LOOP'S.  Written with one `i` throughout, i/j/e come out
 *     $18/$19/$20 against retail's $20/$18/$19 -- 24 bad words.  Giving the
 *     two 4-iteration loops their own `n` takes it to 18 and turns the cycle
 *     into a PAIR.  (normal's "each loop's counter and cursor are distinct
 *     source variables", confirmed here.)
 *  2. A PAIR HAS EXACTLY ONE SWAP, so declaration order settles it: every
 *     order declaring `i` BEFORE `e` is byte-identical and every order
 *     declaring `e` first is 18 or 24 bad.  Six orders measured on the fixed
 *     base, two exact.
 * ⚠ Declaration order alone is a MEASURED NO-OP on the 3-cycle: ten orders
 * over the one-counter version give exactly two outcomes, 24 and 33, and
 * neither is 0.  The counter split has to come first.
 *
 * ★ `k = s->f00->f2C;` and `r = func_28FE10(...)` are separate statements
 * ahead of `func_288E50(r, k, ...)`.  Written with the call inside the
 * argument list -- the recorded "a call inside an argument list evaluates the
 * other arguments first" spelling -- mwcc SINKS the `lh` past the call and the
 * unit is one word short.  Eight spellings measured; only the fully split one
 * is the right length.
 */

typedef struct Item {
    s16   f00;
    u8    pad02[0x2];
    s16   f04;
    u8    pad06[0x26];
    s16   f2C;
} Item;

typedef struct Slot {
    Item *f00;
    s16   f04;
    u8    pad06[0x2];
    u8    f08;
    u8    pad09[0x7];
} Slot;                                         /* 0x10 */

typedef struct List {
    u8    pad00[0x8];
    s16   f08;
    u8    pad0A[0x2];
    Slot *f0C;
} List;

typedef struct Ctx {
    u8    pad00[0x70];
    List *f70;
} Ctx;

typedef struct Ent {
    u8  pad00[0x40];
} Ent;                                          /* 0x40 */

typedef struct Group {
    u8   pad00[0xC];
    s16  f0C;
    Ent *f10;
} Group;

typedef struct Hit {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
} Hit;

typedef struct Screen {
    u8    pad00[0x40];
    void *f40;
} Screen;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

extern s32 factory_FactoryPartObjGetGridX_4fe120(Ent *e);
extern s32 factory_FactoryPartObjGetGridY_4fe0c0(Ent *e);
extern Hit *factory_FactorySlotFindAt_502ad0(s32 h, s32 a, s32 b);
extern Group *factory_FactoryPartGroupFindById_504080(s32 h, s32 k);
extern void func_288E50(void *p, s16 k, s32 a, s32 b);
extern void func_28EFC0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F970(void *w, u16 id, s32 a, s32 b, s32 c);
extern void func_28FAC0(void *w, u16 id, s32 a, s32 b);
extern void *func_28FE10(void *w, u16 id, s32 k);
extern void func_291110(void *w, u16 id, s32 a, s32 b);
extern void func_291250(void *w, u16 id, s32 a, s64 v);
extern s32 func_367F30(void);

void factory_FactoryMaterialReqListLayout_4f2d50(Screen *o)
{
    List *p;
    Slot *s;
    Group *g;
    Hit *h;
    s32 hnd;
    s32 i;
    Ent *e;
    s32 j;
    s32 n;
    s16 k;
    void *r;

    func_291110(o->f40, 0x66, 0, 1);
    p = D_00484A48->f70;
    if (p == NULL) {
        return;
    }
    func_291110(o->f40, 0x66, 1, 1);
    for (n = 0; n < 4; n++) {
        func_28F670(o->f40, 0x70, 0x1A, 0x2A, 0x1A, 0x2A, n);
        func_28F670(o->f40, 0x6C, 0x34, 0x14, 0x34, 0x14, n);
        func_28F670(o->f40, 0x74, 0, 0, 0, 0, n);
        func_28F670(o->f40, 0x71, 0, 0, 0, 0, n);
        func_28EFC0(o->f40, 0x7B, 0xC, 0x10, 0xA, 0x10, n);
        func_28EFC0(o->f40, 0x7A, 0xC, 0x10, 0xA, 0x10, n);
    }
    for (n = p->f08; n < 4; n++) {
        func_28F670(o->f40, 0x70, 0, 0, 0, 0, n);
        func_28F670(o->f40, 0x6C, 0, 0, 0, 0, n);
        func_28EFC0(o->f40, 0x7B, 0, 0, 0, 0, n);
        func_28EFC0(o->f40, 0x7A, 0, 0, 0, 0, n);
    }
    func_28FAC0(o->f40, 0x6B, p->f08, 0);
    func_28FAC0(o->f40, 0x6F, p->f08, 0);
    func_28FAC0(o->f40, 0x7A, p->f08, 0);
    hnd = func_367F30();
    s = p->f0C;
    for (i = 0; i < p->f08; i++, s++) {
        func_291250(o->f40, 0x7B, i, s->f04);
        if (s->f08 & 1) {
            switch (s->f00->f04) {
            case 0x44F:
                func_28F970(o->f40, 0x6C, 0, 0xD6, i);
                break;
            case 0x44D:
                func_28F970(o->f40, 0x6C, 0x34, 0xD6, i);
                break;
            case 0x44E:
                func_28F970(o->f40, 0x6C, 0x68, 0xD6, i);
                break;
            case 0x450:
                func_28F970(o->f40, 0x6C, 0x9C, 0xD6, i);
                break;
            case 0x44C:
                func_28F970(o->f40, 0x6C, 0xD0, 0xD6, i);
                break;
            }
            k = s->f00->f2C;
            r = func_28FE10(o->f40, 0x71, i);
            func_288E50(r, k, 0x28, 0x2D);
            func_28F670(o->f40, 0x70, 0, 0, 0, 0, i);
            g = factory_FactoryPartGroupFindById_504080(hnd, 0xD);
            if (g != NULL) {
                e = g->f10;
                for (j = 0; j < g->f0C; j++, e++) {
                    h = factory_FactorySlotFindAt_502ad0(hnd, factory_FactoryPartObjGetGridX_4fe120(e),
                                             factory_FactoryPartObjGetGridY_4fe0c0(e));
                    if (h != NULL && h->f04 == s->f00->f00 && h->f06 == s->f04) {
                        func_28F670(o->f40, 0x74, 0x2A, 0x1C, 0x2A, 0x1C, i);
                    }
                }
            }
        } else {
            func_28F970(o->f40, 0x6C, 0x102, 0xD6, i);
        }
    }
}
