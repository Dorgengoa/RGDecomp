#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

extern s32 InsectBattleGet_31a8d0(void);
extern void func_50A5F0(s32 handle);

void TaskDrawInsect_319e40(void)
{
    s32 handle;

    handle = InsectBattleGet_31a8d0();
    if (handle != 0) {
        func_50A5F0(handle);
    }
}
