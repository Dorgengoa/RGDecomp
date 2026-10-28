/* rgp:protos */
#define RGP_SELF_LoaderQueueSeparatorGlobal_28afd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of CameraModeInsectBattleUpdate_307ac0 (byte-identical, in cunits):
   fetch a handle, and if there is one hand it to the second callee. */

/*rgp*/
/*rgp*/

void LoaderQueueSeparatorGlobal_28afd0(void)
{
    s32 handle;

    handle = ((s32)GetLoaderMgr_1f59d0());
    if (handle != 0) {
        LoaderQueueAppendSeparator_1cd670(handle);
    }
}
