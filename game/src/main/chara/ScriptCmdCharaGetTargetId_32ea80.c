/* rgp:protos */
#define RGP_SELF_ScriptCmdCharaGetTargetId_32ea80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_32ea80;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdCharaGetTargetId_32ea80(E8_32ea80 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ((s32)GetActionMgr_1fdb50());
    r1 = ScriptSlotGetInt_3348b0(p0++);
    r2 = ((s32)ActionMgrFindById_233b50(r0, r1));
    if (r2 == 0) {
        return 0;
    }
    r3 = ((s32)CharaGetAi_214a10(r2));
    r4 = AiGetTargetCharaId_2c0fd0(r3);
    ScriptSlotStoreIntRef_3347f0(p0, r4);
    return 1;
}
