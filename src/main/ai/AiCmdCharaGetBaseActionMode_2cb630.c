#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaGetBaseActionMode_213830(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern u8 D_004DB92C[0x400];

typedef struct { u8 b[8]; } E8_2cb630;

s32 AiCmdCharaGetBaseActionMode_2cb630(E8_2cb630 *arg0, s32 arg1)
{
    s32 temp_16;
    s32 temp_2;

    if (arg1 == 1) {
        ScriptSlotStoreIntRef_2cc900((s32) arg0, CharaGetBaseActionMode_213830((*(s32 *)D_004DB92C)));
    } else if (arg1 == 2) {
        temp_16 = ScriptSlotGetInt_2cc9c0((s32) arg0++);
        temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), temp_16);
        if (temp_2 != 0) {
            ScriptSlotStoreIntRef_2cc900((s32) arg0, CharaGetBaseActionMode_213830(temp_2));
        } else {
            ScriptSlotStoreIntRef_2cc900((s32) arg0, 0);
        }
    }
    return 1;
}
