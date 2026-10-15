#include "types.h"
#pragma opt_propagation off

extern f32 VecDistance_13d3d0(void *arg0, void *arg1);
extern void *ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern s32 SceneObjGetPosById_2ce720(s32 arg0, s32 arg1, void *arg2);
extern f32 D_0047D5D0;

s32 BattleFindNearestTarget_2ce520(s32 arg0, s32 arg1, s32 *arg2, s32 arg3)
{
    u8 spB0[0x10];
    u8 spA0[0x10];
    f32 temp_f0;
    f32 var_f20;
    f32 fa;
    f32 fb;
    f32 fk;
    void *objA;
    void *objB;
    s32 var_19;
    s32 temp_18;
    s32 var_17;

    var_19 = -1;
    var_f20 = (f32)0xFFFF;
    objA = ObjRecGetLiveObject_1c4a90(arg0, arg1);
    if (objA == NULL) {
        return var_19;
    }
    SceneObjGetPosById_2ce720(arg0, arg1, spB0);
    for (var_17 = 0; var_17 < arg3; var_17++) {
        temp_18 = arg2[var_17];
        if (temp_18 >= 0) {
            objB = ObjRecGetLiveObject_1c4a90(arg0, temp_18);
            if (objB == NULL) {
                return -1;
            }
            if (SceneObjGetPosById_2ce720(arg0, temp_18, spA0) != 0) {
                temp_f0 = VecDistance_13d3d0(spB0, spA0);
                fa = *(f32 *)((u8 *)objA + 0x4C8);
                fk = D_0047D5D0;
                fb = *(f32 *)((u8 *)objB + 0x4C8);
                temp_f0 = temp_f0 - (fk * fa + fk * fb);
                if (!(var_f20 <= temp_f0)) {
                    var_f20 = temp_f0;
                    var_19 = temp_18;
                }
            }
        }
    }
    return var_19;
}
