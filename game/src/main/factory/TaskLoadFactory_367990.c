/* rgp:protos */
#define RGP_SELF_TaskLoadFactory_367990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

/*rgp*/
/*rgp*/

void TaskLoadFactory_367990(void)
{
    s32 handle;

    handle = GetFactoryObj_367f30();
    if (handle != 0) {
        func_504600(handle);
    }
}
