/* rgp:protos */
#define RGP_SELF_EvCmdCharaSetHoldDir_25a6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaSetHoldDir_25a6b0(s64 *arg0) {
    f32 v[3];
    s32 t;

    t = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), ScriptGetInt_26a2a0((s32)arg0++)));
    if (t != 0) {
        v[0] = TaggedGetFloat_26a280((s32)arg0++);
        v[1] = TaggedGetFloat_26a280((s32)arg0++);
        v[2] = TaggedGetFloat_26a280((s32)arg0);
        CharaSetHoldDir_214390(t, v);
    }
    return 1;
}
