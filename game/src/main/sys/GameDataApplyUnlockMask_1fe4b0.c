/* rgp:protos */
#define RGP_SELF_GameDataApplyUnlockMask_1fe4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/

void GameDataApplyUnlockMask_1fe4b0(void)
{
    s64 v;
    s32 o;

    o = ((s32)GetGameData_1fede0());
    McSaveGetMergedFlags_373050(&v);
    UnlockMaskGrantItems_3e3ef0(o, v);
}
