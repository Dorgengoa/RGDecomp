/* rgp:protos */
#define RGP_SELF_factory_FactoryGridDirToStep_502a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00502A70 -- point one grid cell at a piece: stamp the
 * piece id into the cell's low flag bits and cache its two footprint extents.
 * 96 bytes, 24 instructions, 1 conditional branch, 2 calls.
 *
 * * The FIRST parameter is never read ([[factory-unused-first-parameter]]);
 * the cell arrives in `$5` and the piece id in `$6`.
 *
 * ** `and` with -4 in a REGISTER, then `or`, then `andi 3`, is the plain
 * `u16` expression `((c->f04 & ~3) | v) & 3` and NOT a bitfield: mwcc's own
 * bitfield insert masks the VALUE before the `or` and reads a 2-bit field
 * through `lbu`/`sb`, which is three words longer and the wrong access width.
 * The `~3` stays in a register because the `| v` keeps the intermediate
 * INT-wide -- narrow it back to `u16` first and mwcc folds the mask to
 * `andi 0xFFFC`.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

/*rgp*/
/*rgp*/

void factory_FactoryGridDirToStep_502a70(s32 unused, Cell *c, s32 v)
{
    if (c != 0) {
        c->f04 = ((c->f04 & ~3) | v) & 3;
        c->f00 = factory_FactoryGridDirDx_4ff9f0(v);
        c->f02 = factory_FactoryGridDirDy_4ff9b0(v);
    }
}
