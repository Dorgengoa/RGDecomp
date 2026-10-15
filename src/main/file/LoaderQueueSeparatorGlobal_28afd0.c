#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

extern s32 GetLoaderMgr_1f59d0(void);
extern void LoaderQueueAppendSeparator_1cd670(s32 handle);

void LoaderQueueSeparatorGlobal_28afd0(void)
{
    s32 handle;

    handle = GetLoaderMgr_1f59d0();
    if (handle != 0) {
        LoaderQueueAppendSeparator_1cd670(handle);
    }
}
