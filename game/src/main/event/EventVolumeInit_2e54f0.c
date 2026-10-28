/* rgp:protos */
#define RGP_SELF_EventVolumeInit_2e54f0 1
#include "port/game_protos.h"
#line 1
#pragma no_branch_likely on
/* PARK 1/3: length-wrong (77w vs retail 78w), close. Vector-copy struct (3x vec4 with unused w) may have a slot off by one. */
#include "types.h"

/*rgp*/
/*rgp*/

void EventVolumeInit_2e54f0(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4, u8 *arg5) {
    f32 sp60[16] __attribute__((aligned(16)));
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;

    MatFromRot_1cb180(sp60, arg4);
    *(f32 *)(arg0 + 4) = sp60[0];
    *(f32 *)(arg0 + 8) = sp60[1];
    *(f32 *)(arg0 + 0xC) = sp60[2];
    *(f32 *)(arg0 + 0x10) = sp60[4];
    *(f32 *)(arg0 + 0x14) = sp60[5];
    *(f32 *)(arg0 + 0x18) = sp60[6];
    *(f32 *)(arg0 + 0x1C) = sp60[8];
    *(f32 *)(arg0 + 0x20) = sp60[9];
    *(f32 *)(arg0 + 0x24) = sp60[10];
    *(f32 *)(arg0 + 0x28) = *(f32 *)(arg3 + 0);
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(arg3 + 4);
    *(f32 *)(arg0 + 0x30) = *(f32 *)(arg3 + 8);
    var_f1 = *(f32 *)(arg5 + 0);
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    *(f32 *)(arg0 + 0x34) = var_f1;
    var_f1_2 = *(f32 *)(arg5 + 4);
    if (var_f1_2 < 0.0f) {
        var_f1_2 = -var_f1_2;
    }
    *(f32 *)(arg0 + 0x38) = var_f1_2;
    var_f1_3 = *(f32 *)(arg5 + 8);
    if (var_f1_3 < 0.0f) {
        var_f1_3 = -var_f1_3;
    }
    *(f32 *)(arg0 + 0x3C) = var_f1_3;
    EventVolumeSetFlags_2e5620(arg0, arg1 | arg2);
}
