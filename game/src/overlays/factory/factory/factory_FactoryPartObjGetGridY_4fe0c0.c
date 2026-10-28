/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjGetGridY_4fe0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FE0C0 -- pick one of the item's two extents by its
 * orientation byte, through a four-entry stack table.
 * 92 bytes, 23 instructions, 2 conditional branches, 0 calls.
 *
 * * TWIN of `factory_FactoryPartObjGetGridX_4fe120` at ratio 1.000 -- the same function over
 * `f30`/`f34` instead of `f32`/`f36`.
 *
 * * The 0x10-byte clear is the BYTE loop with a redundant null test on the
 * pointer and an unfilled latch that `factory_FactoryPartObjStateOn_4fd5c0` and
 * `factory_FactoryPartGroupBuildObjs_4fead0` also carry; the counter must be UNSIGNED, or an `s32`
 * gives `bgtz` where retail has `bnez`.
 */

typedef struct Item {
    u8  pad00[0x26];
    s8  f26;
    u8  pad27[0x9];
    s16 f30;
    s16 f32;
    s16 f34;
    s16 f36;
    u8  pad38[0x8];
} Item;                                         /* 0x40 */

s32 factory_FactoryPartObjGetGridY_4fe0c0(Item *o)
{
    s32  v[4] __attribute__((aligned(16)));
    s8  *p;
    u32  n;

    p = (s8 *)v;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v[0] = o->f32;
    v[1] = o->f32;
    v[2] = o->f36;
    v[3] = o->f36;
    return v[o->f26];
}
