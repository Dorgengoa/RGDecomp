/* rgp:protos */
#define RGP_SELF_factory_FactoryFloorFindById_504120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504120 -- 76 bytes / 19 words, 3 branches, 0 calls.
 * Linear search of the 0x18-stride table at `0xC4` (count `0xC8`) for the entry
 * whose leading half matches the key.
 *
 * TWIN of `factory_FactoryPartGroupFindById_504080` in shape, but the NULL guard tests a
 * DIFFERENT member: `lw $2, 0xCC` is checked and then thrown away, and the walk
 * starts from `0xC4`.  That is one extra word versus the twins and it is why
 * the unit is 0x4C rather than 0x48; writing the guard on `c->fC4` would
 * fold the two loads into one and come out a word short.
 * * `lw $2, 0xC4` rides in the guard's likely slot, so `p` is assigned first
 * and `n` second -- source order, hoisted by the scheduler.
 */

typedef struct Item {
    s16  f00;
    u8   pad02[0x16];
} Item;

typedef struct Ctx {
    u8    pad00[0xC4];
    Item *fC4;
    s32   fC8;
    void *fCC;
} Ctx;

Item *factory_FactoryFloorFindById_504120(Ctx *c, s32 key)
{
    Item *p;
    s32   n;
    s32   i;

    if (c->fCC == 0) {
        return 0;
    }
    p = c->fC4;
    n = c->fC8;
    for (i = 0; i < n; i++, p++) {
        if (key == p->f00) {
            return p;
        }
    }
    return 0;
}
