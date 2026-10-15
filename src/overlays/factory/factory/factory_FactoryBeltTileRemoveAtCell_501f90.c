#include "types.h"

/* factory.bin overlay, 0x00501F90 -- resolve a grid coordinate to its cell and,
 * if the cell is not marked, run the placement test on it.
 * 88 bytes, 22 instructions, 3 conditional branches, 2 calls.
 *
 * * TWIN of `factory_FactoryPartLiftAt_501f30` at ratio 1.000 -- the same function through
 * the OTHER grid's pair of helpers.
 *
 * * `factory_FactoryFineGridCellAt_503880` takes THREE parameters and the call marshals none
 * of them: `x` and `y` are passed straight through in `$5`/`$6`, which costs
 * zero instructions, and the `daddu $16, $4, $0` in the delay slot is `o`
 * being parked for the second call, not an argument.
 *
 * * `lhu` + `andi 0x8000` makes `f04` a `u16` here; the same field is `s16` in
 * `factory_FactoryFineGridCellAt_503880`, which only ever compares it.
 *
 * * `sltu $2, $0, $2` in the tail call's delay slot is `!= 0` on the result.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Grid {
    u8 pad000[0x2A0];
} Grid;

extern Cell *factory_FactoryFineGridCellAt_503880(Grid *o, s32 x, s32 y);
extern s32   factory_FactoryBeltTileRemove_5024a0(Grid *o, s32 x, s32 y);

s32 factory_FactoryBeltTileRemoveAtCell_501f90(Grid *o, s32 x, s32 y)
{
    Cell *c;

    c = factory_FactoryFineGridCellAt_503880(o, x, y);
    if (c == 0) {
        return 0;
    }
    if ((c->f04 & 0x8000) != 0) {
        return 0;
    }
    return factory_FactoryBeltTileRemove_5024a0(o, c->f00, c->f02) != 0;
}
