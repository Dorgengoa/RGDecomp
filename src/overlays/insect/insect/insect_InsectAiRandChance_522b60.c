#include "types.h"
/* insect 0x00522B60 -- 52 bytes, 13 instructions. */

extern s32 func_133710(void);

s32 insect_InsectAiRandChance_522b60(s32 a, s32 pct)
{
    return func_133710() % 100 < pct;
}
