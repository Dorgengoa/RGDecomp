#include "types.h"
typedef unsigned __int128 u128;
#pragma optimization_level 3
#pragma opt_common_subs off

void AnimBlendBufInit_153370(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_5;
    s32 temp_5_2;
    s32 var_6;
    s32 var_6_2;
    u8 *temp_3;
    u8 *temp_3_2;

    *(s32 *)((u8 *)arg0 + 4) = arg1;
    *(s32 *)((u8 *)arg0 + 0) = arg2;
    *(s32 *)((u8 *)arg0 + 0xC) = arg3;
    var_6 = 0;
    *(s32 *)((u8 *)arg0 + 8) = arg4;
    while (var_6 < *(s32 *)((u8 *)arg0 + 0)) {
        temp_5 = var_6 * 0x60;
        var_6 += 1;
        temp_3 = *(u8 **)((u8 *)arg0 + 4) + temp_5;
        *(u128 *)(temp_3 + 0) = 0;
        *(u128 *)(temp_3 + 0x10) = 0;
    }
    var_6_2 = 0;
    while (var_6_2 < *(s32 *)((u8 *)arg0 + 8)) {
        temp_5_2 = var_6_2 * 0x30;
        var_6_2 += 1;
        temp_3_2 = *(u8 **)((u8 *)arg0 + 0xC) + temp_5_2;
        *(s32 *)(temp_3_2 + 4) = 0;
        *(s32 *)(temp_3_2 + 0) = 0;
    }
}
