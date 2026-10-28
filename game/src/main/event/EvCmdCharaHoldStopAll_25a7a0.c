/* rgp:protos */
#define RGP_SELF_EvCmdCharaHoldStopAll_25a7a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0045EE70[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaHoldStopAll_25a7a0(void)
{
    void *n;
    void *o;

    TaskSetEnabled_27c2a0(1, D_0045EE70);
    n = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
    while (n != 0) {
        o = (void *)((u8 *)n + 0x10);
        n = DListGetNext_42eb30(n);
        CharaSetHoldFlags_214270(o, (long long)(4));
        CharaSetHoldDirXYZ_214380(o, 0.0f, 0.0f, 0.0f);
    }
    return 1;
}
