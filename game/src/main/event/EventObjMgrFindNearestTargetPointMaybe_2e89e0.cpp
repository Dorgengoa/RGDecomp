#include "types.h"

extern "C" {
extern f32 VecDistSq_1cb3c0(f32 *, f32 *);
extern void MatMulPoint_1cb8e0(f32 *, f32 *, s32);
extern void VecCopy_1cbe30(f32 *, f32 *);
extern void XformGetMatrix_2e7750(s32, f32 *);
extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern s32 EvObjSubGetTargetCount_351fb0(s32);
extern s32 EvObjSubGetTargets_351fc0(s32);
extern s32 EvTargetGetPointCount_352950(s32);
extern s32 EvTargetGetPoints_352960(s32);
extern s32 EvTargetGetXform_352970(s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern f32 D_0047D1EC __attribute__((section(".sdata")));
}

extern "C" bool EventObjMgrFindNearestTargetPointMaybe_2e89e0(s32 arg0, f32 *arg1, f32 *arg2)
{
    bool var_21;
    s32 var_2;
    s32 var_19;
    s32 var_18;
    s32 var_17;
    s32 temp_23;
    s32 temp_22;
    s32 temp_17;
    f32 var_f21;
    f32 temp_f0;
    f32 spF0[4] __attribute__((aligned(16)));
    f32 spB0[0x10] __attribute__((aligned(16)));
    f32 spA0[4] __attribute__((aligned(16)));

    var_f21 = D_0047D1EC;
    var_21 = false;
    VecCopy_1cbe30(spF0, arg2);
    VecCopy_1cbe30(arg1, arg2);
    var_2 = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(arg0, 3));
    while (var_2 != 0) {
        temp_17 = var_2 + 0x10;
        var_19 = EvObjSubGetTargets_351fc0(temp_17);
        temp_22 = EvObjSubGetTargetCount_351fb0(temp_17);
        var_18 = 0;
        while (var_18 < temp_22) {
            XformGetMatrix_2e7750(EvTargetGetXform_352970(var_19), spB0);
            temp_23 = EvTargetGetPoints_352960(var_19);
            var_17 = 0;
            while (var_17 < EvTargetGetPointCount_352950(var_19)) {
                MatMulPoint_1cb8e0(spA0, spB0, temp_23 + (var_17 * 0x10));
                temp_f0 = VecDistSq_1cb3c0(spF0, spA0);
                if (temp_f0 < var_f21) {
                    VecCopy_1cbe30(arg1, spA0);
                    var_f21 = temp_f0;
                    var_21 = true;
                }
                var_17 += 1;
            }
            var_18 += 1;
            var_19 += 0x140;
        }
        var_2 = DListGetNext_42eb30(var_2);
    }
    return var_21;
}
