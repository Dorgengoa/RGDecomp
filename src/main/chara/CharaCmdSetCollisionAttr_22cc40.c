/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0xF4 vs retail 0x110. */
#include "types.h"

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern s32 CharaGetActionTable_214cd0(s32);
extern void *ActCfgTableFindColPrmByName_222b40(s32, s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 ScriptArgGetInt_302d70(s32);
extern s32 ScriptArgGetTag_302df0(s32);
extern s16 *TableFindByNameHashed_3f8180(s32, s32);

s32 CharaCmdSetCollisionAttr_22cc40(s32 *arg0, s32 arg1, s32 arg2)
{
    s16 *temp_2_4;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_2;
    void *temp_16;
    void *temp_2_3;
    void *t;

    if (arg2 != 2) {
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
    temp_2_3 = ActCfgTableFindColPrmByName_222b40(temp_2_2, ScriptArgGetStr_302cb0(arg1));
    if (temp_2_3 == NULL) {
        return 1;
    }
    if (ScriptArgGetTag_302df0(arg1 + 5) == 2) {
        temp_16 = GetGameData_1fede0();
        temp_2_4 = TableFindByNameHashed_3f8180(S32(PTR(PTR(temp_16, 8), 0x50), 0xC), ScriptArgGetStr_302cb0(arg1 + 5));
        if (temp_2_4 == NULL) {
            return 1;
        }
        S32(temp_2_3, 4) = *temp_2_4;
    } else {
        S32(temp_2_3, 4) = ScriptArgGetInt_302d70(arg1 + 5);
    }
    return 1;
}
