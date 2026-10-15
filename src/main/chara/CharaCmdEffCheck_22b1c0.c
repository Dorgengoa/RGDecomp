#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern s32 EffectIsLoadedByName_2dff60(s32,s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaGetAbltName_213810(s32 arg0);
extern s32 CharaCmdRunIfElseEvnt_22e480(s32 arg0, s32 arg1, void *arg2, s32 arg3);
extern s32 ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern s32 ScriptArgGetStr_302cb0(s32 arg0);

s32 CharaCmdEffCheck_22b1c0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;
    s32 temp_2;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    temp_16=GetEffectMgr_2d9040();
    return CharaCmdRunIfElseEvnt_22e480(*arg0,EffectIsLoadedByName_2dff60(temp_16,ScriptArgGetStr_302cb0(arg1)),(u8 *)arg1+5,arg2-1);
}
