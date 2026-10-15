#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

extern s32 GetFactoryObj_367f30(void);
extern void func_5069E0(s32 handle);

void TaskStepFactory_367960(void)
{
    s32 handle;

    handle = GetFactoryObj_367f30();
    if (handle != 0) {
        func_5069E0(handle);
    }
}
