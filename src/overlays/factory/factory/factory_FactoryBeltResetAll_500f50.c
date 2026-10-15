#include "types.h"

/* factory.bin overlay, 0x00500F50 -- clear every cell's high flag, then walk
 * the pending-move list: for each entry that resolves, mark its cell, take the
 * step delta and hand the result to the per-entry record.
 * 512 bytes, 128 instructions, 6 conditional branches, 6 calls (br/ins 0.047).
 *
 * * NEAR-TWIN of `factory_FactoryFloorClearAll_501150` at ratio 0.858 -- that one is this
 * function with a second cell grid (`f2A0`/`f2A4`/`f2A6`) cleared first.
 *
 * * `factory_FactoryBeltTileRemoveAt_500f20` reads only `$4`, but the caller marshals `$5` and
 * `$6` with two `daddu`s that would otherwise be dead, so it takes THREE
 * parameters and ignores two -- the same shape as `factory_FactoryBlueprintCancel_4fb5a0`'s
 * unused FIRST parameter, read from the other end.
 *
 * * `off = n * 6` is a NAMED LOCAL: retail computes the row's byte offset once
 * and adds `j * 6` separately (`addu $3,$3,$7` then `addu $3,$3,$2`), which a
 * single `&base[n + j]` would fold into one multiply.
 *
 * * `x0 = p.x` before the subtraction: `factory_FactoryBeltStart_504cc0`'s FIFTH argument
 * is the OLD x, still live in `$8` from the `lh` that feeds the `subu`.
 *
 * * `p.f & ~3` materialises `addiu $3, $0, -0x4`, so the mask is the promoted
 * `int` complement, not a 16-bit `andi`.
 *
 * * `p` is declared FIRST because mwcc allocates stack locals in REVERSE
 * declaration order: `p` is at 0x58($29) and `d` at 0x50($29).
 */

typedef struct Cell {
    u8  pad00[0x4];
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Item {
    s16 f00;
    s16 f02;
    u16 f04;
} Item;                                         /* 6 */

typedef struct Pos {
    s16 x;
    s16 y;
    u16 f;
} Pos;                                          /* 6 */

typedef struct List {
    u8    pad00[0x10];
    Item *f10;
    s32   f14;
} List;

typedef struct Rec {
    u8 pad00[0xC];
} Rec;                                          /* 0xC */

typedef struct Obj {
    u8    pad000[0x234];
    List *f234;
    u8    pad238[0x5C];
    Cell *f294;
    s16   f298;
    s16   f29A;
    u8    pad29C[0x10];
    Rec  *f2AC;
} Obj;

extern void factory_FactoryBeltRebuildTiles_500b00(Obj *o);
extern void factory_FactoryBeltTileRemoveAt_500f20(Obj *o, s32 j, s32 i);
extern void factory_FactoryBeltTilePlaceAt_501ad0(Obj *o, s32 k, s32 x, s32 y, s32 f);
extern s32  factory_FactoryPortToFineCell_5029b0(Obj *o, Pos *p, s32 x, s32 y, s32 f);
extern void factory_FactoryGridDirToStep_502a70(Obj *o, Pos *d, s32 f);
extern void factory_FactoryBeltStart_504cc0(Rec *r, s32 x, s32 y, s32 f, s32 x0);

void factory_FactoryBeltResetAll_500f50(Obj *o)
{
    Pos   p;
    Pos   d;
    List *l;
    Item *it;
    Cell *c;
    s32   off;
    s32   n;
    s32   cnt;
    s32   i;
    s32   j;
    s32   k;
    s16   x0;

    if (o->f294 != 0) {
        for (i = 0; i < o->f29A; i++) {
            for (j = 0; j < o->f298; j++) {
                off = i * o->f298 * 6;
                c = &((Cell *)((u8 *)o->f294 + off))[j];
                c->f04 = c->f04 & 0x7FFF;
                factory_FactoryBeltTileRemoveAt_500f20(o, j, i);
            }
        }
    }
    l = o->f234;
    if (l != 0) {
        it = l->f10;
        cnt = l->f14;
        for (k = 0; k < cnt; k++, it++) {
            if (factory_FactoryPortToFineCell_5029b0(o, &p, it->f00, it->f02, it->f04 & 3) != 0) {
                factory_FactoryBeltTilePlaceAt_501ad0(o, 0x17, p.x, p.y, p.f & 3);
                n = p.y * o->f298;
                c = &((Cell *)((u8 *)o->f294 + n * 6))[p.x];
                c->f04 = c->f04 & 0x7FFF;
                c->f04 = c->f04 | 0x8000;
                factory_FactoryGridDirToStep_502a70(o, &d, p.f & 3);
                x0 = p.x;
                p.x = x0 - d.x;
                p.y = p.y - d.y;
                p.f = (u16)(((p.f & ~3) | ((p.f & 3) + 2)) & 3);
                factory_FactoryBeltStart_504cc0(&o->f2AC[k], p.x, p.y, p.f & 3, x0);
            }
        }
    }
    factory_FactoryBeltRebuildTiles_500b00(o);
}
