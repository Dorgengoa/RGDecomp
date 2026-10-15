#include "types.h"

extern void ModelObjTexAnimResetAll_1ac450(s32 arg0);
extern void ModelObjTexAnimResetByName_1ac510(s32 arg0, s32 arg1);
extern void ModelObjTexAnimStartByName_1ac590(s32 arg0, s32 arg1);
extern s32 ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern s32 ScriptGetCodeAddr_26a200(s32 arg0);
extern s32 ScriptGetInt_26a2a0(s32 arg0);
extern s32 D_00481F78;

s32 EvCmdObjTexAnimSet_267040(s64 *arg0, s32 arg1)
{
    s32 temp_20;
    s32 temp_18;
    s32 temp_2;
    s32 temp_16;
    s32 var_17;

    temp_18 = ScriptGetInt_26a2a0((s32)arg0++);
    temp_16 = ScriptGetInt_26a2a0((s32)arg0++);
    var_17 = 0;
    if (arg1 > 2) {
        var_17 = ScriptGetCodeAddr_26a200((s32)arg0);
    }
    temp_2 = ObjRecGetLiveObject_1c4a90(D_00481F78, temp_18);
    if (temp_2 == 0) {
        return 0;
    }
    if (temp_16 != 0) {
        ModelObjTexAnimStartByName_1ac590(temp_2, var_17);
    } else if (var_17 != 0) {
        ModelObjTexAnimResetByName_1ac510(temp_2, var_17);
    } else {
        ModelObjTexAnimResetAll_1ac450(temp_2);
    }
    return 1;
}
