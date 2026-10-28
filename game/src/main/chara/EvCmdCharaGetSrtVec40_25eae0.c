/* rgp:protos */
#define RGP_SELF_EvCmdCharaGetSrtVec40_25eae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S8_0025eae0 {
    s32 a;
    s32 b;
} S8_0025eae0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaGetSrtVec40_25eae0(S8_0025eae0 *a0)
{
    S8_0025eae0 *p;
    s32 id;
    void *r;
    f32 v[4] __attribute__((aligned(16)));

    p = a0;
    id = ScriptGetInt_26a2a0(p++);
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (r == 0) {
        return 0;
    }
    CharaGetSrtVec40_238880(r, v);
    ScriptSetRefFloat_26a1c0(p++, v[0]);
    ScriptSetRefFloat_26a1c0(p++, v[1]);
    ScriptSetRefFloat_26a1c0(p, v[2]);
    return 1;
}
