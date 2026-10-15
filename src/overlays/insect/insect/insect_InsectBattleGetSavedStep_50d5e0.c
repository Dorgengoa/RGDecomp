#include "types.h"
/* insect 0x50D5E0 -- 8 B / 2 words.  `j insect_InsectBattleGetStep_50d6a0` with
 * `addiu $5, $5, 0x6` in the delay slot: `return f(o, k + 6);`.  The tail call
 * only forms because the callee returns s32 and so does this. */

typedef struct Ins { u8 raw[1]; } Ins;

extern s32 insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);

s32 insect_InsectBattleGetSavedStep_50d5e0(Ins *o, s32 k)
{
    return insect_InsectBattleGetStep_50d6a0(o, k + 6);
}
