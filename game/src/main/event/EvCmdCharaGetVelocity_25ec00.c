/* rgp:protos */
#define RGP_SELF_EvCmdCharaGetVelocity_25ec00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S8_0025ec00 {
    s32 a;
    s32 b;
} S8_0025ec00;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaGetVelocity_25ec00(S8_0025ec00 *a0)
{
    S8_0025ec00 *p;
    s32 id;
    void *r;
    f32 v[4] __attribute__((aligned(16)));

    p = a0;
    id = ScriptGetInt_26a2a0(p++);
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (r == 0) {
        return 0;
    }
    CharaGetVelocity_238890(r, v);
    ScriptSetRefFloat_26a1c0(p++, v[0]);
    ScriptSetRefFloat_26a1c0(p++, v[1]);
    ScriptSetRefFloat_26a1c0(p, v[2]);
    return 1;
}
