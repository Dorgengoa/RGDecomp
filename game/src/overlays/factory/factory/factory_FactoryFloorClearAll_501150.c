/* rgp:protos */
#define RGP_SELF_factory_FactoryFloorClearAll_501150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00501150 -- reset the module, rebuild the slot
 * table, then clear the high flag over BOTH cell grids and walk the pending-
 * move list exactly as `factory_FactoryBeltResetAll_500f50` does.
 * 660 bytes, 165 instructions, 9 conditional branches, 9 calls (br/ins 0.054).
 *
 * * NEAR-TWIN of `factory_FactoryBeltResetAll_500f50` at ratio 0.858 -- this is that function
 * with the two opening calls and the `f2A0`/`f2A4`/`f2A6` grid pass in front.
 * `factory_FactoryMarkerClearAll_4ea120` takes NO argument: the `daddu $16, $4, $0` in its
 * delay slot is `o` being parked in a callee-saved register, not a marshal.
 *
 * * Each guard's `beql` delay slot carries the NEXT guard's `lw`, which is the
 * merge block's first instruction, so all three really are flat `if`s.
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
    u8    pad29C[0x4];
    Cell *f2A0;
    s16   f2A4;
    s16   f2A6;
    u8    pad2A8[0x4];
    Rec  *f2AC;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryFloorClearAll_501150(Obj *o)
{
    Pos   p __attribute__((aligned(16)));
    Pos   d __attribute__((aligned(16)));
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

    factory_FactoryMarkerClearAll_4ea120();
    factory_FactorySlotClearAll_5003b0(o);
    if (o->f2A0 != 0) {
        for (i = 0; i < o->f2A6; i++) {
            for (j = 0; j < o->f2A4; j++) {
                off = i * o->f2A4 * 6;
                c = &((Cell *)((u8 *)o->f2A0 + off))[j];
                c->f04 = c->f04 & 0x7FFF;
                factory_FactoryPartRemoveAt_500ef0(o, j, i);
            }
        }
    }
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
                factory_FactoryBeltStart_504cc0(&o->f2AC[k], p.x, p.y, p.f & 3);
            }
        }
    }
    factory_FactoryBeltRebuildTiles_500b00(o);
}
