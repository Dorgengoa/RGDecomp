/* rgp:protos */
#define RGP_SELF_GetObjNodeByName_1ce3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 GetObjNodeByName_1ce3a0(s32 arg0, s32 arg1, s8 *arg2)
{
    s32 temp_2;

    temp_2 = GetLiveObjById_1ce420((int)arg0, (int)arg1);
    if (temp_2 == 0) {
        return 0;
    }
    if ((arg2 != NULL) && (*arg2 != 0)) {
        return ((s32)ModelGetFrame_1511f0(temp_2, ModelFindFrameIndexByName_151220(temp_2, arg2)));
    }
    return ModelGetRootFrame_1511a0(temp_2);
}
