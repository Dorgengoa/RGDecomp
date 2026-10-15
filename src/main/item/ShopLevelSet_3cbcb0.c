#include "types.h"

/* The asymmetric guard pair, STORING rather than loading: a byte table of 0x40
   entries at +0x400. The two guards return 0, the compute returns 1. */

typedef struct ByteTable_FUN_003cbcb0 {
    u8 pad000[0x400];
    u8 slot[1];        /* +0x400 */
} ByteTable_FUN_003cbcb0;

s32 ShopLevelSet_3cbcb0(ByteTable_FUN_003cbcb0 *t, s32 index, u8 value)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x40;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    t->slot[index] = value;
    return 1;
}
