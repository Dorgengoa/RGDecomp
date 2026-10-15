#include "types.h"
/* insect 0x004F1950 -- 48 bytes, 12 instructions.  Two separate calls, not one
 * call with a normalised flag: the `bnez $5` fall-through is the ZERO arm, so
 * the source tests `== 0` first. */

extern void insect_InsectBattleTestFlag_50da40(void *o, s32 k);

void insect_InsectBattleIsSideAi_4f1950(void *o, s32 f)
{
    if (f == 0) {
        insect_InsectBattleTestFlag_50da40(o, 0);
    } else {
        insect_InsectBattleTestFlag_50da40(o, 1);
    }
}
