/* rgp:protos */
#define RGP_SELF_TaskDrawMenuInsectResult_319550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

/*rgp*/
/*rgp*/

void TaskDrawMenuInsectResult_319550(void)
{
    s32 handle;

    handle = InsectBattleGet_31a8d0();
    if (handle != 0) {
        func_4F14E0(handle);
    }
}
