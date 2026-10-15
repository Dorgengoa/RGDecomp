#include "types.h"

extern s32 StrEqualNonNull_1ca6c0(s32, void *);
extern s32 GetActionMgr_1fdb50(void);
extern void CharaInvokeInitBt2_212a70(s32);
extern void CharaInvokeInitBt1_212ad0(s32);
extern void CharaInvokeInitNrm_212b30(s32);
extern s32 CharaGetActScopeId_214a70(s32);
extern void ActCfgTableRunEvntByName_21f680(s32, s32, s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ActionMgrFindTableByScopeId_233c20(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern u8 D_0045D608[0x10];
extern u8 D_0045D618[0x10];
extern u8 D_0045D628[0x10];

s32 CharaCmdEvent_22a4e0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_16;

    if (arg2 != 1) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = GetActionMgr_1fdb50();
    temp_2_2 = ActionMgrFindTableByScopeId_233c20(temp_16, CharaGetActScopeId_214a70(temp_2));
    if (temp_2_2 == 0) {
        return 1;
    }
    if (StrEqualNonNull_1ca6c0(ScriptArgGetStr_302cb0(arg1), D_0045D608) != 0) {
        CharaInvokeInitNrm_212b30(temp_2);
        return 1;
    }
    if (StrEqualNonNull_1ca6c0(ScriptArgGetStr_302cb0(arg1), D_0045D618) != 0) {
        CharaInvokeInitBt1_212ad0(temp_2);
        return 1;
    }
    if (StrEqualNonNull_1ca6c0(ScriptArgGetStr_302cb0(arg1), D_0045D628) != 0) {
        CharaInvokeInitBt2_212a70(temp_2);
        return 1;
    }
    ActCfgTableRunEvntByName_21f680(temp_2_2, *arg0, ScriptArgGetStr_302cb0(arg1));
    return 1;
}
