/* rgp:protos */
#define RGP_SELF_TargetFindInFrontMaybe_2d0aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TargetFindInFrontMaybe_2d0aa0(s32 arg0, s32 arg1, f32 fparg0, f32 fparg1)
{
    s32 temp_2;

    if (arg0 == 0) {
        return -1;
    }
    TargetRefClear_2e71d0((void *)arg0);
    temp_2 = ActionMgrFindTargetInFrontMaybe_2330f0(((s32)GetActionMgr_1fdb50()), arg0, arg1, fparg0, fparg1);
    if (temp_2 != -1) {
        return temp_2;
    }
    if (EvMapObjFindTargetInFrontMaybe_2e9560(((s32)GetEventObjMgr_2d1960()), arg0, arg1, fparg0, fparg1) != 0) {
        return 1;
    }
    return -1;
}
