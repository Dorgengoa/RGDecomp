/* rgp:protos */
#define RGP_SELF_TaskStepMenuInsectResult_319580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

/*rgp*/
/*rgp*/

void TaskStepMenuInsectResult_319580(void)
{
    s32 handle;

    handle = InsectBattleGet_31a8d0();
    if (handle != 0) {
        func_4F0F60(handle);
    }
}
