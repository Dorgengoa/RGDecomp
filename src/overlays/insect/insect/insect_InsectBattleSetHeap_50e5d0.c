#include "types.h"
/* insect 0x0050E5D0 -- pass-28 unnamed-listing conversion.  The 0x0050E110
 * setter over the same +0xD8 array.  ⚠ The INDEX is the THIRD argument ($6)
 * and the value is the second ($5), not the other way round -- read the
 * `sll $3, $6, 2` before the parameter list. */
typedef struct Tab {
    u8 pad00[0xD8];
    s32 mD8[1];        /* +0xD8 */
} Tab;

void insect_InsectBattleSetHeap_50e5d0(Tab *t, s32 v, s32 i)
{
    t->mD8[i] = v;
}
