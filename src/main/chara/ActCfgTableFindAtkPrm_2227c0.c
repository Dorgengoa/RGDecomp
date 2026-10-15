#include "types.h"

/* Linear search of the 8-byte-stride table at +0x50 (count s16 at +0x74)
   on two accessor keys.  `bne $18,$2` branches PAST the `return p`, so the
   fall-through is the if body. */

extern s32 ActInfoAtkPrmGetSlot_22ea80(s32);
extern s32 ActInfoAtkPrmGetId_22ea70(s32);

s32 ActCfgTableFindAtkPrm_2227c0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 p;
    s32 i;

    p = *(s32 *)(arg0 + 0x50);
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)(arg0 + 0x74); i++, p += 8) {
        if (arg1 == ActInfoAtkPrmGetSlot_22ea80(p)) {
            if (arg2 == ActInfoAtkPrmGetId_22ea70(p)) {
                return p;
            }
        }
    }
    return 0;
}
