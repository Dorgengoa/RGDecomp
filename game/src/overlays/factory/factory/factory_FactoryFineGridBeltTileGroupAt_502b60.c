/* rgp:protos */
#define RGP_SELF_factory_FactoryFineGridBeltTileGroupAt_502b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00502B60 -- resolve a grid coordinate to its cell and
 * hand the cell's id to the group lookup.
 * 64 bytes, 16 instructions, 1 conditional branch, 2 calls.
 *
 * * TWIN of `factory_FactoryGridPartGroupAt_502b20` -- the other grid's pair of helpers -- and
 * the same shape as `factory_FactoryPartLiftAt_501f30` minus the flag test.
 *
 * * `factory_FactoryFineGridCellAt_503880` takes three parameters and the call marshals none:
 * `x` and `y` pass straight through in `$5`/`$6`.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Grid {
    u8 pad000[0x2A0];
} Grid;

/*rgp*/
/*rgp*/

s32 factory_FactoryFineGridBeltTileGroupAt_502b60(Grid *o, s32 x, s32 y)
{
    Cell *c;

    c = ((Cell *)factory_FactoryFineGridCellAt_503880(o, x, y));
    if (c != 0) {
        return ((s32)factory_FactoryBeltTileGroupFindById_5040d0(o, c->f00));
    }
    return 0;
}
