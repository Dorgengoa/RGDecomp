/* rgp:protos */
#define RGP_SELF_ItemGroupUnlockProgressSet_3cbbf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The asymmetric guard pair, STORING rather than loading: a byte table of 0x40
   entries at +0x840. The two guards return 0, the compute returns 1. */

typedef struct ByteTable_FUN_003cbbf0 {
    u8 pad000[0x840];
    u8 slot[1];        /* +0x840 */
} ByteTable_FUN_003cbbf0;

s32 ItemGroupUnlockProgressSet_3cbbf0(ByteTable_FUN_003cbbf0 *t, s32 index, u8 value)
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
