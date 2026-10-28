/* rgp:protos */
#define RGP_SELF_ShopStockSet_3cbc50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The asymmetric guard pair, STORING rather than loading: a byte table of 0x400
   entries at +0x440. The two guards return 0, the compute returns 1. */

typedef struct ByteTable_FUN_003cbc50 {
    u8 pad000[0x440];
    u8 slot[1];        /* +0x440 */
} ByteTable_FUN_003cbc50;

s32 ShopStockSet_3cbc50(ByteTable_FUN_003cbc50 *t, s32 index, u8 value)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x400;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    t->slot[index] = value;
    return 1;
}
