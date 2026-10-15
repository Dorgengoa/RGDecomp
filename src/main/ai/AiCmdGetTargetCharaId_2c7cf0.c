#include "types.h"

extern s32 AiGetTargetCharaId_2c0fd0(s32 arg0);
extern void ScriptSlotStoreIntRef_2cc900(s32 arg0, s32 arg1);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 CharaGetAiById_2cedd0(s32 arg0);
extern s32 D_004DB930[0x100];

s32 AiCmdGetTargetCharaId_2c7cf0(s64 *arg0, s32 arg1)
{
    s32 t;

    if (arg1 == 1) {
        if (D_004DB930[0] == 0) {
            return 0;
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, AiGetTargetCharaId_2c0fd0(D_004DB930[0]));
    } else if (arg1 == 2) {
        t = CharaGetAiById_2cedd0(ScriptSlotGetInt_2cc9c0((s32)arg0++));
        if (t == 0) {
            return 0;
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, AiGetTargetCharaId_2c0fd0(t));
    }
    return 1;
}
