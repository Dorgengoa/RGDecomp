#include "types.h"

/* factory.bin overlay, 0x004F97A0 -- refresh the two blueprint sub-panels.
 *
 * ★ `f_ds.py` classifies all five branches: the three `beql`s each DUPLICATE
 * the merge's first instruction, so every one of them is a plain forward branch
 * and there is no `switch` anywhere in here.  Two plain `beqz`s with `nop` slots
 * are the `&&` of the second guard.
 *
 * ★ `lbu 0x14 / andi 1` is bit 0 and `lbu / dsll32 30 / dsrl32 31` is bit 1 of
 * the same byte -- a two-bit `u8` bitfield, not a mask to write out.
 *
 * ★ `sub` is `&rec->sub`, the named record ELEMENT: the first size computation
 * reads the same halfwords through the RECORD (`0x14($2)`) while the panel
 * stores read them through `sub` (`0x10($16)`).  Those are two source
 * expressions for one address and writing either as the other misplaces $16.
 */

typedef struct Sub {
    s16 f00;                    /* rec + 0x04 */
    s16 f02;                    /* rec + 0x06 */
    u8  pad04[0xC];
    s16 f10;                    /* rec + 0x14 */
    s16 f12;                    /* rec + 0x16 */
    u8  pad14[0x2];
    s16 f16;                    /* rec + 0x1A */
} Sub;

typedef struct Rec {
    u8  pad00[0x4];
    Sub sub;
} Rec;

typedef struct Ent {
    u8 pad00[0x14];
    u8 b0 : 1;
    u8 b1 : 1;
} Ent;

typedef struct Row {
    s16 f00;
    u8  pad02[0x16];
    s16 f18;
} Row;

typedef struct Page {
    u8    pad00[0x60];
    s16   f60;
    u8    pad62[0x16];
    s16   f78;
    s16   f7A;
    u8    f7C;
    u8    pad7D[0x3];
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

extern void *D_004807EC;                        /* _gp - 0x4984 */

extern World *func_1FEDE0(void);
extern void   func_370170(Iter *it, s32 key);
extern Rec   *func_28EA40(void *ctx, s32 id);
extern void   func_36FFF0(Iter *it, s32 n);
extern Ent   *func_36FF80(Iter *it);
extern void   func_290010(void *w, s32 id, s32 a, s32 b);
extern void   func_291110(void *w, s32 id, s32 a, s32 b);
extern void   func_28EA90(void *ctx, s32 id, s32 a);
extern void   func_290F60(void *w, s32 id, s32 a, s32 b);
extern Row   *func_28FE10(void *w, s32 id, s32 a);
extern void   func_28FCD0(void *w, s32 id, s32 a, s32 b);
extern void   factory_FactoryBlueprintShowRecipe_4f9380(Page *o, Ent *e);
extern void   factory_FactoryBlueprintShowProduct_4f9130(Page *o, Ent *e);

void factory_FactoryBlueprintOpenDetail_4f97a0(Page *o)
{
    Iter it;
    Rec *rec;
    Sub *sub;
    Ent *e;
    Row *row;
    s32  key;

    key = ((Area *)((Zone *)func_1FEDE0()->f08)->fA4)->f0C;
    if (key != 0) {
        key = key + 0x88;
    }
    func_370170(&it, key);
    rec = func_28EA40(o->f84, 0x88CC);
    sub = &rec->sub;
    func_36FFF0(&it, rec->sub.f10 + (rec->sub.f12 + rec->sub.f16) * 6);
    e = func_36FF80(&it);
    if (e != 0) {
        if (e->b0 != 0) {
            o->f78 = sub->f10;
            o->f7A = sub->f12;
            o->f7C = 1;
            func_290010(o->f80, 0x27, 1, -1);
            func_290010(o->f80, 0x2A, 1, -1);
            func_290010(o->f80, 0x2B, 0, -1);
            func_290010(o->f80, 0x3A, 0, -1);
            func_291110(D_004807EC, 0x97, 1, 1);
            func_291110(o->f80, 0x40, 0, 1);
            func_291110(o->f80, 0x26, 0, 1);
            func_28EA90(o->f84, 0x88D6, 1);
            rec = func_28EA40(o->f84, 0x88D6);
            sub = &rec->sub;
            func_290F60(D_004807EC, 0x97, sub->f00 + 0x37, sub->f02 + 0x36);
            row = func_28FE10(o->f80, 0x3D, 3);
            func_28FCD0(o->f80, 0x3D, row->f00 + 2 + sub->f10 * row->f18, 6);
            o->f60 = 0;
            factory_FactoryBlueprintShowRecipe_4f9380(o, e);
            func_290010(o->f80, 0x20, 0, -1);
            func_290010(o->f80, 0x28, 0, -1);
        }
        if (e->b0 != 0 && e->b1 != 0) {
            o->f7C = 2;
            func_290010(o->f80, 0x27, 1, -1);
            func_290010(o->f80, 0x2A, 1, -1);
            func_290010(o->f80, 0x2B, 0, -1);
            func_290010(o->f80, 0x39, 0, -1);
            func_291110(D_004807EC, 0x97, 1, 1);
            func_291110(o->f80, 0x40, 0, 1);
            func_291110(o->f80, 0x26, 0, 1);
            func_28EA90(o->f84, 0x88E0, 1);
            rec = func_28EA40(o->f84, 0x88E0);
            func_290F60(D_004807EC, 0x97, rec->sub.f00 + 0x37, rec->sub.f02 + 0x36);
            factory_FactoryBlueprintShowProduct_4f9130(o, e);
            func_290010(o->f80, 0x20, 0, -1);
            func_290010(o->f80, 0x28, 0, -1);
        }
    }
}
