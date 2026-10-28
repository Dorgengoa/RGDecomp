/* rgp:protos */
#define RGP_SELF_EvCmdCharaHold_25a860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_0045EE70[];

s32 EvCmdCharaHold_25a860(void)
{
    s32 p;
    s32 q;

    TaskSetEnabled_27c2a0(1, D_0045EE70);
    p = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(((s32)GetActionMgr_1fdb50()))));
    while (p != 0) {
        q = p + 0x10;
        p = DListGetNext_42eb30(p);
        CharaSetHoldFlags_214270(q, (long long)(1));
    }
    return 1;
}
