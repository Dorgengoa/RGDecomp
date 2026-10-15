#include "types.h"

/* factory.bin overlay, 0x00502D20 -- 108 bytes / 27 words, 4 branches, 1 call.
 * "Is the cell at (x,y) present, unflagged and back-facing?"  Every failing
 * guard returns 0 and the success path returns a comparison.
 *
 * * `factory_FactoryFineGridCellAt_503880` takes THREE parameters and the call marshals only
 *   TWO (`$5 = $6`, `$6 = $7`) -- `$4` passes straight through, so the second
 *   parameter of THIS function is the flag tested by the opening `bnez $5` and
 *   the grid coordinates are parameters three and four.
 * * Each guard is the inverted early return: a branch-likely INTO the
 *   continuation carrying the continuation's first load in its slot, falling
 *   through to a duplicated `b <epilogue>` / `daddu $2,$0,$0`.
 *
 * ** THE RESIDUE, and the transferable half: the 0x8000 test MATERIALISES its
 *    boolean (`sltu $3,$0,$3 / xori $3,$3,1`) instead of folding into the
 *    branch.  Written as `if ((c->f04 & 0x8000) != 0) return 0;` the unit is
 *    exactly TWO WORDS SHORT -- mwcc emits `andi` + `beql` and the sltu/xori
 *    pair never appears.  What recovers it is the `!` OPERATOR ASSIGNED TO AN
 *    s32 LOCAL:
 *        t = !(c->f04 & 0x8000);   if (t == 0) return 0;
 *    A twelve-spelling sweep in one round trip says the neighbouring forms are
 *    NOT the same object: `t = (c->f04 & 0x8000) == 0;`, `((...) == 0) == 0`,
 *    `!((...) == 0)`, `t = c->f04 & 0x8000; if ((t == 0) == 0)` and
 *    `if (!t)` on the `== 0` local are all byte-identical to the two-words-short
 *    baseline (sha1 44055959) -- mwcc folds `== 0` back into the branch but
 *    keeps `!`.  `u32 t` is live but two words WRONG, so the local is s32.
 *    `#pragma optimization_level 3` and `#pragma opt_propagation off` are both
 *    INERT here (same object as the baseline).
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

s32 factory_FactoryFineGridCellIsFree_502d20(Grid *o, s32 flag, s32 x, s32 y)
{
    Cell *c;
    s32   t;

    if (flag == 0) {
        return 0;
    }
    c = factory_FactoryFineGridCellAt_503880(o, x, y);
    if (c == 0) {
        return 0;
    }
    t = !(c->f04 & 0x8000);
    if (t == 0) {
        return 0;
    }
    if (c->f00 >= 0) {
        return 0;
    }
    return c->f02 < 0;
}
