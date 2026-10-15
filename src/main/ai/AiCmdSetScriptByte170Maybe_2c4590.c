#include "types.h"

extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s8 *D_004DB930[3];

s32 AiCmdSetScriptByte170Maybe_2c4590(s32 a0)
{
    D_004DB930[0][0x170] = ScriptSlotGetInt_2cc9c0(a0);
    return 1;
}
