/* rgp:protos */
#define RGP_SELF_CharaCmdFlagSet_22b3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdFlagSet_22b3d0(s32 *p0, void *p1, s32 kind)
{
    s32 obj;

    if (kind != 1) {
        return 1;
    }
    obj = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *p0));
    if (obj == 0) {
        return 1;
    }
    CharaFlagWordSet_214830(obj, ScriptArgGetInt_302d70(p1));
    return 1;
}
