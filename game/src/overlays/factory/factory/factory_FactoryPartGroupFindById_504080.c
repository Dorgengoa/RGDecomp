/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupFindById_504080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504080 -- 72 bytes / 18 words, 3 branches, 0 calls.
 * Linear search of the 0x68-stride table at `0xD4` (count `0xD8`, a full word)
 * for the entry whose `0x04` half matches the key; NULL if the table is NULL
 * or nothing matches.
 *
 * SEED of sub-family C of lane fy04 with `factory_FUN_005040D0` (0xCC/0xD0,
 * 0x14 stride) and `factory_FactoryFloorFindById_504120` (0xCC guard but 0xC4/0xC8 data,
 * 0x18 stride).
 *
 * * `bnel $5, $3` puts the KEY in `rs`: mwcc emits the compare's LEFT source
 * operand as `rs`, so this is `key == p->f04`, not `p->f04 == key`.  The
 * `00502AD0` cousin has the field on the left and its `bnel` has the field in
 * `rs` -- same rule, opposite spelling.
 * * The `lh` lives in the loop-test `bnel`'s likely slot, hoisted; it is a
 * plain field read at its use, NOT a named local.
 * * `daddu $2,$0,$0` sits in the loop-exit slot and the found `p` is already
 * in `$2`: the two returns tail-merge onto one `jr`, which is what makes the
 * unit 18 words instead of 20.
 */

typedef struct Item {
    u8   pad00[0x4];
    s16  f04;
    u8   pad06[0x62];
} Item;

typedef struct Ctx {
    u8    pad00[0xD4];
    Item *fD4;
    s32   fD8;
} Ctx;

Item *factory_FactoryPartGroupFindById_504080(Ctx *c, s32 key)
{
    Item *p;
    s32   n;
    s32   i;

    p = c->fD4;
    if (p == 0) {
        return 0;
    }
    n = c->fD8;
    for (i = 0; i < n; i++, p++) {
        if (key == p->f04) {
            return p;
        }
    }
    return 0;
}
