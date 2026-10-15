#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

extern s32 GetFactoryObj_367f30(void);
extern void func_504600(s32 handle);

void TaskLoadFactory_367990(void)
{
    s32 handle;

    handle = GetFactoryObj_367f30();
    if (handle != 0) {
        func_504600(handle);
    }
}
