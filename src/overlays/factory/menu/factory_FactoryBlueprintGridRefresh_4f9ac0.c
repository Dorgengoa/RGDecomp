#include "types.h"

/* factory.bin overlay, 0x004F9AC0 -- 752 B / 188 words.  Walks the recipe
 * list and lays out up to 0x18 grid slots.
 *
 * DIVIDE-TRAP UNIT: one `%`/`/` pair by the literal 6 => two `div` and ONE
 * `bnez $3 / break 0,7`.  `#pragma divbyzerocheck on` restores it.
 *
 * SEED: src/overlays/factory/factory_FactoryBlueprintOpenDetail_4f97a0.c -- same iterator head
 * (`func_1FEDE0()->f08 -> fA4 -> f0C`, `+ 0x88` when non-zero), the same
 * `u8 b0:1 / b1:1` bitfield at +0x14 and the same `if (b0) ... if (b0 && b1)`
 * pair (beql then beqz/bne with a `nop` slot is the `&&` join).
 *
 * * The loop test is `i < 0x18 && e != 0` in that order: `slti $1` into $at
 *   (the STRICT compare) first, then `bnel $17,$0` into the body.
 * * `e->f04` is re-read at EVERY use -- four `lw 0x4($17)` -- so it must NOT
 *   be named in a local ([[normal-row-store-order]] second half).
 * * `o->f70` IS named once by mwcc's own CSE across `!= 0` and `->f00`, so
 *   the source spells it twice and lets the compiler share it.
 * * `dsll32/dsra32 ..,16` on the two div results is `factory_FactoryBlueprintMarkCell_4f7a40`'s
 *   declared `s16` parameters, not a cast -- the callee is already converted
 *   in src/overlays/factory/factory_FactoryBlueprintMarkCell_4f7a40.c with that prototype.
 */

#pragma divbyzerocheck on

typedef struct Sub {
    s16 f00;
    s16 f02;
    u8  pad04[0xC];
    s16 f10;
    s16 f12;
    u8  pad14[0x2];
    s16 f16;
} Sub;

typedef struct Rec {
    u8  pad00[0x4];
    Sub sub;
} Rec;

typedef struct Card {
    u8  pad00[0x2C];
    s16 f2C;
} Card;

typedef struct Ent {
    s16   f00;
    u8    pad02[0x2];
    Card *f04;
    u8    pad08[0xC];
    u8    b0 : 1;
    u8    b1 : 1;
} Ent;

typedef struct Page {
    u8    pad00[0x70];
    Ent  *f70;
    u8    pad74[0xC];
    void *f80;
    void *f84;
} Page;

typedef struct Iter { u8 pad[0x8]; } Iter;

typedef struct World {
    u8    pad00[0x8];
    void *f08;
} World;

typedef struct Zone {
    u8    pad00[0xA4];
    void *fA4;
} Zone;

typedef struct Area {
    u8  pad00[0xC];
    s32 f0C;
} Area;

extern World *func_1FEDE0(void);
extern void   func_370170(Iter *it, s32 key);
extern Rec   *func_28EA40(void *ctx, s32 id);
extern void   func_36FFF0(Iter *it, s32 n);
extern Ent   *func_36FF80(Iter *it);
extern Ent   *func_370040(Iter *it);
extern void   func_28F670(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void   func_291110(void *w, s32 id, s32 a, s32 b);
extern void   func_290BD0(void *w, s32 id, s32 a, s32 b, s32 c, s32 d);
extern void   factory_FactoryBlueprintGridSetIcon_4f8f90(Page *o, Card *c, s32 n);
extern void   factory_FactoryBlueprintMarkCell_4f7a40(Page *o, s16 a, s16 b);

void factory_FactoryBlueprintGridRefresh_4f9ac0(Page *o)
{
    Iter it;
    Ent *e;
    s32  i;
    s32  key;

    key = ((Area *)((Zone *)func_1FEDE0()->f08)->fA4)->f0C;
    if (key != 0) {
        key = key + 0x88;
    }
    func_370170(&it, key);
    func_36FFF0(&it, func_28EA40(o->f84, 0x88CC)->sub.f16 * 6);
    func_28F670(o->f80, 0x24, 0, 0, 0, 0, 0);
    func_28F670(o->f80, 0x24, 0, 0, 0, 0, 1);
    func_291110(o->f80, 0x23, 0, 1);
    e = func_36FF80(&it);
    for (i = 0; i < 0x18 && e != 0; i++) {
        func_28F670(o->f80, 0x22, 0x1A, 0x2A, 0x1A, 0x2A, i);
        func_28F670(o->f80, 0x25, 0, 0, 0, 0, i);
        if (e->b0 != 0) {
            func_290BD0(o->f80, 0x25, 0x200, 0, i, 0);
            if (e->f04->f2C == 12) {
                func_290BD0(o->f80, 0x24, 0x200, 0, 0, 0);
            }
            if (e->f04->f2C == 15) {
                func_290BD0(o->f80, 0x24, 0x200, 0, 1, 0);
            }
            factory_FactoryBlueprintGridSetIcon_4f8f90(o, e->f04, i);
            func_28F670(o->f80, 0x22, 0, 0, 0, 0, i);
        }
        if (e->b0 != 0 && e->b1 != 0) {
            func_290BD0(o->f80, 0x25, 8, 0, i, 0);
            if (e->f04->f2C == 12) {
                func_290BD0(o->f80, 0x24, 8, 0, 0, 0);
            }
            if (e->f04->f2C == 15) {
                func_290BD0(o->f80, 0x24, 8, 0, 1, 0);
            }
        }
        if (o->f70 != 0 && e->f00 == o->f70->f00) {
            factory_FactoryBlueprintMarkCell_4f7a40(o, (s16)(i % 6), (s16)(i / 6));
        }
        e = func_370040(&it);
    }
}
