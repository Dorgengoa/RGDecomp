#include "types.h"
#pragma opt_propagation off
#pragma opt_repositioncode on

typedef struct Item00229cf0 {
    s16 unk0;
    u8 pad2[0x12];
    s32 unk14;
} Item00229cf0;

typedef struct Ent00229cf0 {
    u8 pad0[0x18];
    Item00229cf0 *unk18;
} Ent00229cf0;

extern s32 StrEqualNonNull_1ca6c0(s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern s32 CharaGetActionTable_214cd0(s32);
extern s32 CharaCmdRunIfElseEvnt_22e480(s32, s32, s32, s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 ScriptArgGetInt_302d70(s32);
extern s32 ScriptArgGetTag_302df0(s32, s32);

s32 CharaCmdFixEncount_229cf0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 arg_h0;
    s32 arg_h3;
    s32 temp_2;
    s32 var_5;
    Ent00229cf0 *temp_2_2;
    Item00229cf0 *var_19;

    if (arg2 < 0) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 != 0) {
        if (CharaGetActionTable_214cd0(temp_2) == 0) {
            return 1;
        }
        temp_2_2 = *(Ent00229cf0 **)(*(u8 **)((u8 *)GetGameData_1fede0() + 0x20) + 0x238);
        if (temp_2_2 != NULL) {
            var_19 = temp_2_2->unk18;
        } else {
            var_19 = NULL;
        }
        var_5 = 0;
        if (var_19 != NULL) {
            if (!(ScriptArgGetTag_302df0(arg1, 0) != 2)) {
                var_5 = StrEqualNonNull_1ca6c0(var_19->unk14, ScriptArgGetStr_302cb0(arg1)) & 0xFF;
            } else {
                var_5 = var_19->unk0 == ScriptArgGetInt_302d70(arg1);
            }
        }
        arg_h3 = arg2 - 1;
        return CharaCmdRunIfElseEvnt_22e480(*arg0, var_5, arg1 + 5, arg_h3);
    }
    return 1;
}
