#include "types.h"

/* factory.bin overlay, 0x004FA8C0 -- build the whole crafting-result panel.
 *
 * 364 instructions, 12 conditional branches, 52 calls: the branch-light band.
 *
 * ★ `o->f80` is spelled out at every one of its ~40 call sites -- retail
 * reloads `lw $4, 0x80($19)` each time, and mwcc's per-basic-block CSE
 * reproduces that for free because a call separates every use.  `t` is the
 * opposite: `lw $16, 0x70($19)` happens ONCE and lives in a callee-saved
 * register for the rest of the function, so it is a named local.
 * ★ The tail dispatch is a `switch`, not an if/else-if chain: retail compares
 * 4, 3, 2, 1, 0 in that order and a compiled compare chain runs in REVERSE
 * source-case order.
 * ★ The 12/15 dispatch is NOT a switch -- the outer test is a `||` (source
 * order, because it short-circuits) and the inner one an if/else-if.  m2c
 * renders both as nested `switch`es.
 * ★ `beql $2, $0, .L004FACF4` on `e->f08 & 1` makes the SET case the
 * fall-through, so that is the `if` arm and the clear case is the `else`.
 * ★ `andi $5, $2, 0xFFFF` at every computed id says the id parameter is u16;
 * the constant ids need no mask, which is why only the loops carry one.
 */

typedef struct Sub {
    u8   pad00[0x4];
    s16  f04;
    u8   pad06[0x6];
    void *f0C;
} Sub;

typedef struct Elem {
    Sub  *f00;
    s16   f04;
    u8    pad06[0x2];
    u8    f08;
    u8    pad09[0x3];
    void *f0C;
} Elem;                                         /* 0x10 */

typedef struct Part {
    u8    pad00[0x10];
    void *f10;
    u8    pad14[0x18];
    s16   f2C;
} Part;

typedef struct Table {
    u8     pad00[0x2];
    s16    f02;
    Part  *f04;
    s16    f08;
    u8     pad0A[0x2];
    Elem  *f0C;
} Table;

typedef struct Panel {
    u8     pad00[0x70];
    Table *f70;
    u8     pad74[0xC];
    void  *f80;
    void  *f84;
} Panel;

extern void *D_004807EC;                        /* _gp - 0x4984 */
extern u8 D_0050CCC8[];

extern void factory_FactoryBlueprintListInit_4fbab0(void);
extern void factory_FactoryBlueprintSetCategoryIcon_4f8e90(Panel *o, s16 a, s32 i);
extern void func_288E50(void *p, s16 k, s32 a, s32 b);
extern void func_28EA90(void *w, s32 id, s32 a);
extern void func_28F510(void *w, u16 id, void *p, s32 k);
extern void func_28F670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_28F9D0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_28FC30(void *w, u16 id, s32 a, s32 b, s32 c);
extern void *func_28FE10(void *w, u16 id, s32 k);
extern void func_290010(void *w, u16 id, s32 a, s32 b);
extern void func_290BD0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern void func_291110(void *w, u16 id, s32 a, s32 b);
extern void func_291250(void *w, u16 id, s32 a, s64 v);

void factory_FactoryBlueprintViewInit_4fa8c0(Panel *o)
{
    Table *t;
    Elem *e;
    s32 i;
    s16 k;

    factory_FactoryBlueprintListInit_4fbab0();
    func_290010(o->f80, 0x27, 1, -1);
    func_290010(o->f80, 0x2A, 0, -1);
    func_290010(o->f80, 0x2B, 1, -1);
    func_290010(o->f80, 0x3A, 0, -1);
    func_291110(D_004807EC, 0x97, 0, 1);
    func_28EA90(o->f84, 0x894E, 1);
    func_28F670(o->f80, 0x3C, 0, 0, 0, 0, 0xC);
    func_28F670(o->f80, 0x3C, 0, 0, 0, 0, 0xD);
    func_28F670(o->f80, 0x3C, 0, 0, 0, 0, 0xE);
    func_290010(o->f80, 0x28, 0, -1);
    func_291110(o->f80, 0x29, 0, 1);
    func_291110(o->f80, 0x23, 0, 1);
    func_291110(o->f80, 0x40, 0, 1);
    func_291110(o->f80, 0x26, 0, 1);
    func_290010(o->f80, 0x3D, 0, -1);
    func_28F510(o->f80, 0x39, D_0050CCC8, 2);
    func_28F510(o->f80, 0x39, D_0050CCC8, 3);
    func_28F510(o->f80, 0x39, D_0050CCC8, 5);
    t = o->f70;
    func_28F510(o->f80, 0x39, t->f04->f10, 4);
    func_290010(o->f80, 0x3E, 0, -1);
    func_290010(o->f80, 0x3F, 0, -1);
    func_290BD0(o->f80, 0x3E, 0x200, 0, 0, 0);
    func_290BD0(o->f80, 0x3F, 0x200, 0, 0, 0);

    k = t->f04->f2C;
    if (k == 0xC || k == 0xF) {
        if (k == 0xC) {
            func_28FC30(o->f80, 0x3F, 0x28, 0x2D, 0);
            func_28F9D0(o->f80, 0x3F, 0x140, 0x20, 0x20, 0x20, 0);
        } else if (k == 0xF) {
            func_28FC30(o->f80, 0x3F, 0x28, 0x2D, 0);
            func_28F9D0(o->f80, 0x3F, 0x140, 0, 0x20, 0x20, 0);
        }
        func_290010(o->f80, 0x3F, 1, -1);
    } else {
        func_288E50(func_28FE10(o->f80, 0x3E, 0), k, 0x28, 0x2D);
        func_290010(o->f80, 0x3E, 1, -1);
    }

    for (i = t->f08; i < 4; i++) {
        func_290010(o->f80, i + 0x31, 0, -1);
        func_28F670(o->f80, 0x3B, 0, 0, 0, 0, i);
    }

    e = t->f0C;
    for (i = 0; i < t->f08; i++, e++) {
        func_291250(o->f80, i + 0x35, 0, i + 1);
        func_291250(o->f80, i + 0x35, 1, e->f04);
        func_290010(o->f80, i + 0x31, 1, -1);
        func_28FC30(o->f80, 0x3B, 0x16, 0x16, i);
        if (e->f08 & 1) {
            func_28F510(o->f80, i + 0x31, e->f00->f0C, 0);
            factory_FactoryBlueprintSetCategoryIcon_4f8e90(o, e->f00->f04, i);
        } else {
            func_28F510(o->f80, i + 0x31, e->f0C, 0);
            func_28F9D0(o->f80, 0x3B, 0xA6, 0x2E, 0x16, 0x16, i);
        }
    }

    func_290010(o->f80, 0x2C, 0, -1);
    func_290010(o->f80, 0x2D, 0, -1);
    func_290010(o->f80, 0x2E, 0, -1);
    func_290010(o->f80, 0x2F, 0, -1);
    func_290010(o->f80, 0x30, 0, -1);
    switch (t->f02) {
    case 0:
        func_290010(o->f80, 0x2C, 1, -1);
        break;
    case 1:
        func_290010(o->f80, 0x2D, 1, -1);
        break;
    case 2:
        func_290010(o->f80, 0x2E, 1, -1);
        break;
    case 3:
        func_290010(o->f80, 0x2F, 1, -1);
        break;
    case 4:
        func_290010(o->f80, 0x30, 1, -1);
        break;
    }
}
