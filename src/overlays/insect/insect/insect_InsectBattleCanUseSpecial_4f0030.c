#include "types.h"
/* insect 0x004F0030 -- 44 bytes.  The first parameter is UNUSED.  Retail lays
 * the `return 1` block out AFTER the call block, so the guard is the positive
 * one and the constant return is the TRAILING statement. */

extern s32 insect_InsectPieceSpecialUsable_514860(void *p);

s32 insect_InsectBattleCanUseSpecial_4f0030(s32 a, void *p)
{
    if (p != 0) {
        return insect_InsectPieceSpecialUsable_514860(p);
    }
    return 1;
}
