#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaGetActScopeId_214a70(s32 arg0);
extern void *ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern void ScriptSlotStoreIntRef_2cc900(s32 arg0, s32 arg1);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern u8 D_004DB92C[0x400];

s32 AiCmdCharaGetActScopeId_2c8010(s64 *arg0, s32 arg1)
{
    s32 temp_16;
    s32 temp_2;

    if (arg1 == 1) {
        if ((*(s32 *)D_004DB92C) != 0) {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, CharaGetActScopeId_214a70((*(s32 *)D_004DB92C)));
        }
    } else if (arg1 == 2) {
        temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        temp_2 = (s32)ActionMgrFindById_233b50(GetActionMgr_1fdb50(), temp_16);
        if (temp_2 != 0) {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, CharaGetActScopeId_214a70(temp_2));
        } else {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, -1);
        }
    }
    return 1;
}
