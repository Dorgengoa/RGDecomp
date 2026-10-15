#include "types.h"
typedef struct { s32 a, b; } E8_32ea80;
extern s32 GetActionMgr_1fdb50(void);
extern s32 ScriptSlotGetInt_3348b0(E8_32ea80 *);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetAi_214a10(s32);
extern s32 AiGetTargetCharaId_2c0fd0(s32);
extern void ScriptSlotStoreIntRef_3347f0(E8_32ea80 *, s32);

s32 ScriptCmdCharaGetTargetId_32ea80(E8_32ea80 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = GetActionMgr_1fdb50();
    r1 = ScriptSlotGetInt_3348b0(p0++);
    r2 = ActionMgrFindById_233b50(r0, r1);
    if (r2 == 0) {
        return 0;
    }
    r3 = CharaGetAi_214a10(r2);
    r4 = AiGetTargetCharaId_2c0fd0(r3);
    ScriptSlotStoreIntRef_3347f0(p0, r4);
    return 1;
}
