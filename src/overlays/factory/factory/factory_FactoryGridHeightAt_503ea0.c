#include "types.h"

/* factory.bin overlay, 0x00503EA0 -- the world height of whatever part owns
 * the cell at (x,y), or zero.
 * 84 bytes, 21 instructions, 2 conditional branches, 2 calls.
 *
 * * `factory_FUN_005037F0` takes three parameters and the call marshals NONE
 * (`factory_FUN_005002C0` reads the same prototype from the other end).
 *
 * * The `bnel`'s delay slot carries `lh $5, 0x0($2)`, which is the SECOND
 * call's argument and not the merge block's first instruction, so the null
 * check really is an early return.
 *
 * * The SECOND guard has the OPPOSITE polarity to the first: `if (g != 0)
 * return g->f1C; return 0.0f;` -- `factory_FUN_00502B60`'s shape.  Writing it
 * as an early `if (g == 0) return 0.0f;` gives a branch-LIKELY with the value
 * in the slot (`bnel / lwc1`) and five wrong words.
 *
 * * TWO `ld $31` copies: the first return has its own, the second guard and
 * the value share one -- the epilogue tail-merge shape of the 0x004EB-0x004EF
 * family read at this address.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Group {
    u8  pad00[0x1C];
    f32 f1C;
} Group;

typedef struct Obj {
    u8 pad000[0x2D0];
} Obj;

extern Cell  *factory_FactoryGridCellAt_5037f0(Obj *o, s32 x, s32 y);
extern Group *factory_FactoryPartGroupFindById_504080(Obj *o, s32 k);

f32 factory_FactoryGridHeightAt_503ea0(Obj *o, s32 x, s32 y)
{
    Cell  *c;
    Group *g;

    c = factory_FactoryGridCellAt_5037f0(o, x, y);
    if (c == 0) {
        return 0.0f;
    }
    g = factory_FactoryPartGroupFindById_504080(o, c->f00);
    if (g != 0) {
        return g->f1C;
    }
    return 0.0f;
}
