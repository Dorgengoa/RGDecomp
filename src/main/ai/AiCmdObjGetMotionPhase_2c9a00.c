#include "types.h"

extern f32 ModelObjGetMotionPhase_1add70(s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 CharaGetId_214a80(s32);
extern void ScriptSlotStoreFloatRef_2cc8e0(s32, f32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 D_004DB920[];
extern s32 D_004DB92C[];

s32 AiCmdObjGetMotionPhase_2c9a00(s32 arg0, s32 arg1)
{
    s32 temp_16;
    s32 temp_2;
    s32 temp_4;
    s32 var_18;
    s32 var_2;

    var_18 = arg0;
    temp_16 = D_004DB920[0];
    if (D_004DB92C[0] == 0) {
        return 0;
    }
    var_2 = CharaGetId_214a80(D_004DB92C[0]);
    if (arg1 == 2) {
        temp_4 = var_18;
        var_18 += 8;
        var_2 = ScriptSlotGetInt_2cc9c0(temp_4);
    }
    temp_2 = ObjRecGetLiveObject_1c4a90(temp_16, var_2);
    if (temp_2 == 0) {
        return 0;
    }
    ScriptSlotStoreFloatRef_2cc8e0(var_18, ModelObjGetMotionPhase_1add70(temp_2));
    return 1;
}
