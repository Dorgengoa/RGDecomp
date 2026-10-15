#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

extern s32 SaveMgrGetResult_375a00(void);
extern void SaveResultClear_3761b0(s32 handle);

void SaveMgrClearResult_3759d0(void)
{
    s32 handle;

    handle = SaveMgrGetResult_375a00();
    if (handle != 0) {
        SaveResultClear_3761b0(handle);
    }
}
