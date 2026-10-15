#include "types.h"

extern void *GetActionMgr_1fdb50(void);
extern void *ActionMgrFindById_233b50(void *a, s32 b);
extern void CharaJudgeObjRelease_213ca0(void *p);

s32 CharaCmdJoDelete_22b510(s32 *o, s32 a1, s32 a2)
{
    void *r;

    if (a2 == 0) {
        goto body;
    }
    return 0;
body:
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *o);
    if (r != 0) {
        goto call;
    }
    return 1;
call:
    CharaJudgeObjRelease_213ca0(r);
    return 1;
}
