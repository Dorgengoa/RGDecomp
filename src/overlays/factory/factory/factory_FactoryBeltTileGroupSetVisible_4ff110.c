#include "types.h"

/* factory.bin overlay, 0x004FF110 -- walk the panel's item array and run one
 * per-item update.  112 bytes, 28 instructions, 2 conditional branches.
 *
 * ★ TWIN of `factory_FactoryPartGroupStep_4fea10` -- IDENTICAL mnemonic sequence (ratio
 * 1.000).  The only differences are the element STRIDE (0x34 vs 0x40) and the
 * per-item callee, so the second source is a `sed` of this one.  Found by the
 * OPEN-vs-OPEN similarity sweep, not by `f_sim.py`.
 *
 * ★ `i++, it++` in the FOR-INCREMENT, not `it++` as the last body statement:
 * retail bumps the counter FIRST, and a body-tail `it++` reverses the pair.
 * Same rule as `factory_FactoryPartGroupBuildObjs_4fead0`, which shares these structures.
 */

typedef struct Item {
    u8 pad00[0x34];
} Item;                                         /* 0x34 */

typedef struct Panel {
    u8    pad00[0xA];
    s16   f0A;
    u8    pad0C[0x4];
    Item *f10;
} Panel;

extern void factory_FactoryBeltTileObjSetVisible_4fefe0(Item *it, s32 a);

void factory_FactoryBeltTileGroupSetVisible_4ff110(Panel *o, s32 a)
{
    Item *it;
    s32   i;

    it = o->f10;
    if (it != 0) {
        for (i = 0; i < o->f0A; i++, it++) {
            factory_FactoryBeltTileObjSetVisible_4fefe0(it, a);
        }
    }
}
