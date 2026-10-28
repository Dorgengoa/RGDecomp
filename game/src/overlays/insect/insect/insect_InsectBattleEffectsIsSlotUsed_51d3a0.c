/* rgp:protos */
#define RGP_SELF_insect_InsectBattleEffectsIsSlotUsed_51d3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051D3A0 -- 20 bytes, 5 instructions, leaf.  `sltu $2,$0,$2` in the
 * `jr` delay slot is the `!= 0` predicate on the word two slots past the
 * indexed entry. */

s32 insect_InsectBattleEffectsIsSlotUsed_51d3a0(s32 *a, s32 i)
{
    return a[i + 2] != 0;
}
