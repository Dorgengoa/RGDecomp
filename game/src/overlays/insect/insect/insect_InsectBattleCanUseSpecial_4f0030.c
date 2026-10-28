/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCanUseSpecial_4f0030 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0030 -- 44 bytes.  The first parameter is UNUSED.  Retail lays
 * the `return 1` block out AFTER the call block, so the guard is the positive
 * one and the constant return is the TRAILING statement. */

/*rgp*/

s32 insect_InsectBattleCanUseSpecial_4f0030(s32 a, void *p)
{
    if (p != 0) {
        return insect_InsectPieceSpecialUsable_514860(p);
    }
    return 1;
}
