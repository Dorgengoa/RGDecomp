/* rgp:protos */
#define RGP_SELF_AreaBoxGetBounds_1e97b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma no_branch_likely on

void AreaBoxGetBounds_1e97b0(void *arg0, void *arg1, void *arg2)
{
    f32 var_f1_2;
    f32 var_f3;
    f32 var_f1;
    f32 var_f4;
    f32 temp_f1;
    f32 temp_f4;
    f32 temp_f3;
    f32 temp_f2;

    temp_f3 = *(f32 *)((u8 *)arg0 + 0x1C);
    var_f4 = temp_f3 * *(f32 *)((u8 *)arg0 + 0x34);
    if (var_f4 < 0.0f) {
        var_f4 = -var_f4;
    }
    temp_f2 = *(f32 *)((u8 *)arg0 + 0x24);
    var_f1 = temp_f2 * *(f32 *)((u8 *)arg0 + 0x3C);
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    temp_f4 = var_f4 + var_f1;
    var_f3 = temp_f3 * *(f32 *)((u8 *)arg0 + 0x38);
    if (var_f3 < 0.0f) {
        var_f3 = -var_f3;
    }
    var_f1_2 = temp_f2 * *(f32 *)((u8 *)arg0 + 0x40);
    if (var_f1_2 < 0.0f) {
        var_f1_2 = -var_f1_2;
    }
    temp_f1 = var_f3 + var_f1_2;
    *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg0 + 0x28) + temp_f4;
    *(f32 *)((u8 *)arg1 + 4) = *(f32 *)((u8 *)arg0 + 0x44);
    *(f32 *)((u8 *)arg1 + 8) = *(f32 *)((u8 *)arg0 + 0x30) + temp_f1;
    *(u32 *)((u8 *)arg1 + 0xC) = 0x3F800000;
    *(f32 *)((u8 *)arg2 + 0) = *(f32 *)((u8 *)arg0 + 0x28) - temp_f4;
    *(f32 *)((u8 *)arg2 + 4) = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg2 + 8) = *(f32 *)((u8 *)arg0 + 0x30) - temp_f1;
    *(u32 *)((u8 *)arg2 + 0xC) = 0x3F800000;
}
