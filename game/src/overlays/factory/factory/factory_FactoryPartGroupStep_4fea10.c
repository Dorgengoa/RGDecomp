/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupStep_4fea10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FEA10 -- walk the panel's item array and run one
 * per-item update.  112 bytes, 28 instructions, 2 conditional branches.
 *
 * ★ TWIN of `factory_FactoryBeltTileGroupSetVisible_4ff110` -- IDENTICAL mnemonic sequence (ratio
 * 1.000).  The only differences are the element STRIDE (0x40 vs 0x34) and the
 * per-item callee, so the second source is a `sed` of this one.  Found by the
 * OPEN-vs-OPEN similarity sweep, not by `f_sim.py`.
 *
 * ★ `i++, it++` in the FOR-INCREMENT, not `it++` as the last body statement:
 * retail bumps the counter FIRST, and a body-tail `it++` reverses the pair.
 * Same rule as `factory_FactoryPartGroupBuildObjs_4fead0`, which shares these structures.
 */

typedef struct Item {
    u8 pad00[0x40];
} Item;                                         /* 0x40 */

typedef struct Panel {
    u8    pad00[0xA];
    s16   f0A;
    u8    pad0C[0x4];
    Item *f10;
} Panel;

/*rgp*/

void factory_FactoryPartGroupStep_4fea10(Panel *o, s32 a)
{
    Item *it;
    s32   i;

    it = o->f10;
    if (it != 0) {
        for (i = 0; i < o->f0A; i++, it++) {
            factory_FactoryPartObjStep_4fe000(it, a);
        }
    }
}
