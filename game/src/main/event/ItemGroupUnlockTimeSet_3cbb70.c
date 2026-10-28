/* rgp:protos */
#define RGP_SELF_ItemGroupUnlockTimeSet_3cbb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair, storing a doubleword into a 0x40-entry table at
   +0x880.  Same TU and same shape as ItemGroupUnlockProgressSet_3cbbf0/c50/cb0. */

typedef struct QwTable {
    u8 pad000[0x880];
    s64 slot[1];       /* +0x880 */
} QwTable;

s32 ItemGroupUnlockTimeSet_3cbb70(QwTable *t, s32 index, s64 value)
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
