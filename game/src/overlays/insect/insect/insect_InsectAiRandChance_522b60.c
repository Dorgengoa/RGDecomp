/* rgp:protos */
#define RGP_SELF_insect_InsectAiRandChance_522b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522B60 -- 52 bytes, 13 instructions. */

/*rgp*/

s32 insect_InsectAiRandChance_522b60(s32 a, s32 pct)
{
    return Rand_133710() % 100 < pct;
}
