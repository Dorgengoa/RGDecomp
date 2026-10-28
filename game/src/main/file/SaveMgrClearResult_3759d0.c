/* rgp:protos */
#define RGP_SELF_SaveMgrClearResult_3759d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

/*rgp*/
/*rgp*/

void SaveMgrClearResult_3759d0(void *rgp_a0)
{
    s32 handle;

    handle = ((s32)SaveMgrGetResult_375a00((void *)rgp_a0));
    if (handle != 0) {
        SaveResultClear_3761b0(handle);
    }
}
