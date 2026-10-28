/* rgp:protos */
#define RGP_SELF_CharaCmdLaunch_22a040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdLaunch_22a040(s32 *self, u8 *p1, s32 kind)
{
    s32 obj;
    s32 b;
    f32 x;

    if (kind != 3) {
        return 0;
    }
    obj = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *self));
    if (obj == 0) {
        return 1;
    }
    b = ScriptArgGetInt_302d70(p1);
    x = ScriptArgGetFloat_302cf0(p1 + 5);
    CharaLaunchTowardTarget_2114e0(obj, b, x, ScriptArgGetFloat_302cf0(p1 + 0xA));
    return 1;
}
