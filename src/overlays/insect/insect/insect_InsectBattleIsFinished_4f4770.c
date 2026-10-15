#include "types.h"
/* insect 0x004F4770 -- 36 bytes, 9 instructions, 1 call.
 *
 * `xori 0x28` / `sltiu 1` is the canonical mwcc `== K` boolean; $4 is never
 * written, so the first argument is passed straight through.
 */

typedef struct Ins Ins;

extern s32 insect_InsectBattleGetState_50d6f0(Ins *o, s32 k);

s32 insect_InsectBattleIsFinished_4f4770(Ins *o)
{
    return insect_InsectBattleGetState_50d6f0(o, 0) == 0x28;
}
