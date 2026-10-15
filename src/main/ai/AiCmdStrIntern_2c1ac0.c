#include "types.h"
#pragma opt_propagation off

extern void ScriptSlotStoreIntRef_2cc900(s32 arg0, s32 arg1);
extern s32 ScriptSlotGetCodeAddr_2cc980(void);
extern s32 ScriptStrTableIntern_2cce20(s32 arg0);
extern u32 strlen(const char *s);
extern s32 D_004825DC;

s32 AiCmdStrIntern_2c1ac0(s32 arg0, s32 arg1)
{
    s32 s;

    if (D_004825DC == 0) {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
        return 0;
    }
    if (arg1 != 2) {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
        return 1;
    }
    arg0 += 8;
    s = ScriptSlotGetCodeAddr_2cc980();
    if (strlen((const char *)s) >= 0x50) {
        ScriptSlotStoreIntRef_2cc900(arg0, -1);
        return 0;
    }
    ScriptSlotStoreIntRef_2cc900(arg0, ScriptStrTableIntern_2cce20(s));
    return 1;
}
