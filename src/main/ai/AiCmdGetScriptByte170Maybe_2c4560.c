#include "types.h"

extern u8 *D_004DB930[3];
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);

s32 AiCmdGetScriptByte170Maybe_2c4560(s32 a0)
{
    ScriptSlotStoreIntRef_2cc900(a0, D_004DB930[0][0x170]);
    return 1;
}
