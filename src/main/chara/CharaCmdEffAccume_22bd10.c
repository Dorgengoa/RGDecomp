#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern void CharaSetEffectId_212230(s32, s32);
extern s32 CharaGetEffectId_212240(s32);
extern s32 CharaGetActionTable_214cd0(s32);
extern s32 CharaPlayEffectByName_21f800(s32, s32, s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetParamIntById_2e04a0(s32, s32, s32, s32);
extern void EffectKillById_2e0640(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);

s32 CharaCmdEffAccume_22bd10(s32 *arg0, s32 arg1, s32 arg2) {
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
    temp_2_2 = CharaGetActionTable_214cd0(temp_2);
    if (temp_2_2 == 0) {
        return 1;
    }
    temp_16 = GetEffectMgr_2d9040();
    if (CharaGetEffectId_212240(temp_2) >= 0) {
        EffectKillById_2e0640(temp_16, CharaGetEffectId_212240(temp_2));
        CharaSetEffectId_212230(temp_2, -1);
    }
    CharaSetEffectId_212230(temp_2, CharaPlayEffectByName_21f800(temp_2_2, *arg0, ScriptArgGetStr_302cb0(arg1)));
    EffectSetParamIntById_2e04a0(temp_16, CharaGetEffectId_212240(temp_2), 0, 0);
    return 1;
}
