#include "types.h"

extern s32 MemStackAllocQw_14d950(s32, s32);
extern s32 MemStackNew_14e230(s32, s32);
extern s32 SlotGetInt_15f720(s32);
extern s32 VariantGetInt_15f780(s32);
extern s32 MapAreaModelFindModelCfgEntry_1896e0(s32, s32, s32);
extern s32 ObjRefListAddUnique_189770(s32, s32, s32);
extern s32 ObjRefListAddUnique_189890(s32, s32, s32);
extern s32 NodeSetEnabled_18bbc0(s32, s32);
extern s32 NodeObjBasicSetName_18c270(s32, s32);
extern s32 ListNodeNext_18c4f0(s32);
extern s32 ListNodeGetData_18c500(s32);
extern s32 ListNodeGetData_18c510(s32);
extern s32 MotionListIsNonEmpty_18c520(s32);
extern s32 ModelObjGetMotionList_18c530(s32);
extern s32 ModelCfgEntryGetModelObjMaybe_18c540(s32);
extern s32 MapAreaModelGetSceneCfg_18c550(s32);
extern s32 ListNodeSetData_18c560(s32, s32);
extern s32 NodeObjBasicCtor_18c570(s32);
extern s32 ListNodeCtor_18c5d0(s32);
extern s32 MapSceneCfgGetPcpName_193720(s32, s32);
extern s32 NodeObjBasicApplyModelCfgEntry_196fa0(s32, s32);
extern s32 strcpy(s32, s32);
extern u32 strlen(s32);
extern s32 D_00481250;
extern s32 D_00481254;
extern s32 D_00481258;
extern s32 D_0048125C;

s32 MapCfgPiece_18c280(s64 *arg0, s32 arg1) {
    s32 temp_2_3;
    s32 temp_2;
    s32 var_2_3;
    s32 var_5;
    s32 var_2;
    s32 temp_2_2;
    s32 temp_3;
    s32 temp_2_5;
    s32 var_16;
    s32 var_2_2;
    s32 var_19;
    s32 var_18;
    s32 temp_2_4;

    if (D_00481254 == 0) {
        return 0;
    }
    temp_2 = SlotGetInt_15f720((s32)arg0++);
    if (temp_2 == 0) {
        return 0;
    }
    var_2 = MemStackNew_14e230(0x18, D_0048125C);
    if (var_2 != 0) {
        var_2 = ListNodeCtor_18c5d0(var_2);
    }
    D_00481258 = var_2;
    var_16 = MemStackNew_14e230(0x90, D_0048125C);
    if (var_16 != 0) {
        var_16 = NodeObjBasicCtor_18c570(var_16);
    }
    ListNodeSetData_18c560(D_00481258, var_16);
    temp_3 = strlen(temp_2) + 1;
    if ((temp_3 % 16) != 0) {
        var_5 = temp_3 / 16 + 1;
    } else {
        var_5 = temp_3 / 16;
    }
    temp_2_2 = MemStackAllocQw_14d950(D_0048125C, var_5);
    strcpy(temp_2_2, temp_2);
    NodeObjBasicSetName_18c270(var_16, temp_2_2);
    if (arg1 > 1) {
        NodeSetEnabled_18bbc0(var_16, VariantGetInt_15f780((s32)arg0));
    }
    var_19 = 0;
    if (strlen(temp_2_2) > 2) {
        var_18 = 0;
loop_22:
        temp_2_3 = MapSceneCfgGetPcpName_193720(MapAreaModelGetSceneCfg_18c550(D_00481250), var_18);
        if (temp_2_3 != 0) {
            var_19 = MapAreaModelFindModelCfgEntry_1896e0(D_00481250, temp_2_2, temp_2_3);
            if (var_19 == 0) {
                var_18 += 1;
                goto loop_22;
            }
        }
        if (var_19 == 0) {
            var_19 = MapAreaModelFindModelCfgEntry_1896e0(D_00481250, temp_2_2, 0);
        }
    }
    if (var_19 != 0) {
        NodeObjBasicApplyModelCfgEntry_196fa0(var_16, var_19);
        temp_2_4 = ModelCfgEntryGetModelObjMaybe_18c540(var_19);
        if ((temp_2_4 != 0) && (MotionListIsNonEmpty_18c520(ModelObjGetMotionList_18c530(temp_2_4)) != 0)) {
            ObjRefListAddUnique_189890(D_00481250, temp_2_4, D_0048125C);
        }
        for (var_2_3 = ListNodeGetData_18c510(var_19); var_2_3 != 0; var_2_3 = ListNodeNext_18c4f0(var_2_3)) {
            temp_2_5 = ListNodeGetData_18c500(var_2_3);
            if (temp_2_5 != 0) {
                ObjRefListAddUnique_189770(D_00481250, temp_2_5, D_0048125C);
            }
        }
    }
    return 1;
}
