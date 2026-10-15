#include "types.h"

/* factory.bin overlay, 0x005040D0 -- 72 bytes / 18 words, 3 branches, 0 calls.
 * Linear search of the 0x14-stride table at `0xCC` (count `0xD0`) for the entry
 * whose `0x04` half matches the key.
 *
 * TWIN of `factory_FactoryPartGroupFindById_504080` at ratio 1.000 -- only the two field offsets
 * and the element size differ, so the residue reasoning there applies verbatim
 * (`key` on the LEFT of the compare, field read at its use, tail-merged
 * returns).
 */

typedef struct Item {
    u8   pad00[0x4];
    s16  f04;
    u8   pad06[0xE];
} Item;

typedef struct Ctx {
    u8    pad00[0xCC];
    Item *fCC;
    s32   fD0;
} Ctx;

Item *factory_FactoryBeltTileGroupFindById_5040d0(Ctx *c, s32 key)
{
    Item *p;
    s32   n;
    s32   i;

    p = c->fCC;
    if (p == 0) {
        return 0;
    }
    n = c->fD0;
    for (i = 0; i < n; i++, p++) {
        if (key == p->f04) {
            return p;
        }
    }
    return 0;
}
