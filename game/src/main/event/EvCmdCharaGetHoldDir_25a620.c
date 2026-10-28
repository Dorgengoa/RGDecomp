/* rgp:protos */
#define RGP_SELF_EvCmdCharaGetHoldDir_25a620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } E_0025a620;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaGetHoldDir_25a620(E_0025a620 *p)
{
    f32 v[4] __attribute__((aligned(16)));
    void *r;
    void *s;
    void *t;

    r = GetActionMgr_1fdb50();
    s = ScriptGetInt_26a2a0(p++);
    t = ActionMgrFindById_233b50(r, s);
    if (t != 0) {
        CharaGetHoldDir_2143b0(t, v);
        ScriptSetRefFloat_26a1c0(p++, v[0]);
        ScriptSetRefFloat_26a1c0(p++, v[1]);
        ScriptSetRefFloat_26a1c0(p, v[2]);
    }
    return 1;
}
