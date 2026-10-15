#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetAi_214a10(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaGetAiById_2cedd0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetActionMgr_1fdb50();
    r1 = ActionMgrFindById_233b50(r0, p0);
    if (r1 != 0) {
        r2 = CharaGetAi_214a10(r1);
        return r2;
    }
    return 0;
}
