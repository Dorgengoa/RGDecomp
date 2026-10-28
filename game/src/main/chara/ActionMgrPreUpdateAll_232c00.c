/* rgp:protos */
#define RGP_SELF_ActionMgrPreUpdateAll_232c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

int ActionMgrPreUpdateAll_232c00(s32 arg0)
{ int rgp_v0 = 0;
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

    temp_2 = (rgp_v0 = GetCurrentScene_1f5be0());
    if (temp_2 != 0) {
        GetMapMgr_201a90();
        var_2 = (rgp_v0 = DListGetHead_42ea60(arg0 + 0x20));
        while (var_2 != 0) {
            temp_17 = var_2 + 0x10;
            temp_30 = ((short)CharaGetActScopeId_214a70(temp_17));
            temp_2_2 = DListGetHead_42ea60(arg0 + 0x10);
            var_23 = temp_2_2;
            if (temp_2_2 == 0) {
                var_19 = 0;
            } else {
                var_19 = 0;
                var_18 = ((unsigned short)DListGetCountPow2_42ea70(arg0 + 0x10));
                while (var_18 > 0) {
                    var_18 = var_18 >> 1;
                    temp_2_3 = ((s32)DListNodeAdvance_42eb00(var_23, var_18));
                    if (temp_2_3 != 0) {
                        temp_2_4 = IntCompare_42ca30(temp_30, ((short)ActCfgTableGetScopeId_223d00(temp_2_3 + 0x10)));
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
                ActionMgrLoadActionInfo_2336b0(arg0, ((short)CharaGetId_214a80(temp_17)));
            }
            CharaSetModelObj_238700(temp_17, ((s32)ObjRecGetLiveObject_1c4a90(temp_2, ((short)CharaGetId_214a80(temp_17)))));
            CharaPreUpdate_20f3a0(temp_17);
            var_2 = (rgp_v0 = DListGetNext_42eb30(var_2));
        }
    }
return rgp_v0; }
