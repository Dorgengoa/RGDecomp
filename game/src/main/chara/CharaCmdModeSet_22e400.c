/* rgp:protos */
#define RGP_SELF_CharaCmdModeSet_22e400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

s32 CharaCmdModeSet_22e400(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 r0;
    s32 o;

    if (argc != 1) {
        return 0;
    }
    r0 = ((s32)GetActionMgr_1fdb50());
    o = ((s32)ActionMgrFindById_233b50(r0, p0->m00));
    if (o == 0) {
        return 1;
    }
    CharaSetBaseActionMode_213820(o, ScriptArgGetInt_302d70(p1));
    return 1;
}
