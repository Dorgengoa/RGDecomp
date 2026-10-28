/* rgp:protos */
#define RGP_SELF_StateVarSetQuiet_3cca20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair, storing a halfword into a 0x80-entry table at
   +0x128. */

typedef struct HwTable {
    u8 pad000[0x128];
    s16 slot[1];       /* +0x128 */
} HwTable;

s32 StateVarSetQuiet_3cca20(HwTable *t, s32 index, s16 value)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x80;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    t->slot[index] = value;
    return 1;
}
