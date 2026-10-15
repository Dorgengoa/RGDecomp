#include "types.h"

extern s32 ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetMapMgr_201a90(void);
extern void CharaPreUpdate_20f3a0(s32 arg0);
extern s32 CharaGetActScopeId_214a70(s32 arg0);
extern s32 CharaGetId_214a80(s32 arg0);
extern s32 CharaGetActionTable_214cd0(s32 arg0);
extern s32 ActCfgTableGetScopeId_223d00(s32 arg0);
extern void ActionMgrLoadActionInfo_2336b0(s32 arg0, s32 arg1);
extern void CharaSetModelObj_238700(s32 arg0, s32 arg1);
extern s32 IntCompare_42ca30(s32 arg0, s32 arg1);
extern s32 DListGetHead_42ea60(s32 arg0);
extern s32 DListGetCountPow2_42ea70(s32 arg0);
extern s32 DListNodeAdvance_42eb00(s32 arg0, s32 arg1);
extern s32 DListGetNext_42eb30(s32 arg0);

void ActionMgrPreUpdateAll_232c00(s32 arg0)
{
    s32 var_2;
    s32 temp_2;
    s32 var_19;
    s32 var_18;
    s32 temp_17;
    s32 temp_30;
    s32 temp_2_4;
    s32 temp_2_3;
    s32 temp_2_2;
    s32 var_23;
    s32 var_16;

    temp_2 = GetCurrentScene_1f5be0();
    if (temp_2 != 0) {
        GetMapMgr_201a90();
        var_2 = DListGetHead_42ea60(arg0 + 0x20);
        while (var_2 != 0) {
            temp_17 = var_2 + 0x10;
            temp_30 = CharaGetActScopeId_214a70(temp_17);
            temp_2_2 = DListGetHead_42ea60(arg0 + 0x10);
            var_23 = temp_2_2;
            if (temp_2_2 == 0) {
                var_19 = 0;
            } else {
                var_19 = 0;
                var_18 = DListGetCountPow2_42ea70(arg0 + 0x10);
                while (var_18 > 0) {
                    var_18 = var_18 >> 1;
                    temp_2_3 = DListNodeAdvance_42eb00(var_23, var_18);
                    if (temp_2_3 != 0) {
                        temp_2_4 = IntCompare_42ca30(temp_30, ActCfgTableGetScopeId_223d00(temp_2_3 + 0x10));
                        if (temp_2_4 == 0) {
                            var_19 = temp_2_3;
                            break;
                        } else {
                            if (temp_2_4 > 0) {
                                var_23 = temp_2_3;
                            }
                            continue;
                        }
                    } else {
                        continue;
                    }
                }
            }
            if (var_19 == 0) {
                var_16 = 0;
            } else {
                var_16 = var_19 + 0x10;
            }
            if (var_16 != CharaGetActionTable_214cd0(temp_17)) {
                ActionMgrLoadActionInfo_2336b0(arg0, CharaGetId_214a80(temp_17));
            }
            CharaSetModelObj_238700(temp_17, ObjRecGetLiveObject_1c4a90(temp_2, CharaGetId_214a80(temp_17)));
            CharaPreUpdate_20f3a0(temp_17);
            var_2 = DListGetNext_42eb30(var_2);
        }
    }
}
