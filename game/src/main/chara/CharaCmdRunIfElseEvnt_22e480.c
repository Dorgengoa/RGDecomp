/* rgp:protos */
#define RGP_SELF_CharaCmdRunIfElseEvnt_22e480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdRunIfElseEvnt_22e480(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 o;
    s32 h;
    s32 t;

    r0 = ((s32)GetActionMgr_1fdb50());
    o = ((s32)ActionMgrFindById_233b50(r0, p0));
    if (o == 0) {
        return 1;
    }
    h = CharaGetActionTable_214cd0(o);
    if (h == 0) {
        return 1;
    }
    if (p1 != 0) {
        if (p3 > 0) {
            t = ScriptArgGetStr_302cb0(p2);
            ActCfgTableRunEvntByName_21f680(h, p0, t);
        }
    } else {
        if (p3 > 1) {
            t = ScriptArgGetStr_302cb0(p2 + 5);
            ActCfgTableRunEvntByName_21f680(h, p0, t);
        }
    }
    return 1;
}
