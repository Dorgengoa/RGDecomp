/* rgp:protos */
#define RGP_SELF_AudioDecEndPut_1d24c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on
#pragma opt_common_subs off

void AudioDecEndPut_1d24c0(void *arg0, u32 arg1) {
    u32 var_5;
    u32 var_6;
    s32 temp_3;

    var_5 = arg1;
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        var_6 = 0x28 - *(u32 *)((u8 *)arg0 + 0x2C);
        var_6 = (var_6 < var_5) ? var_6 : var_5;
        temp_3 = *(s32 *)((u8 *)arg0 + 0x2C) + var_6;
        *(s32 *)((u8 *)arg0 + 0x2C) = temp_3;
        if ((u32)temp_3 >= 0x28U) {
            *(s32 *)((u8 *)arg0 + 0) = 1;
        }
        var_5 -= var_6;
    }
    *(s32 *)((u8 *)arg0 + 0x34) = (*(s32 *)((u8 *)arg0 + 0x34) + (s32)var_5) % *(s32 *)((u8 *)arg0 + 0x3C);
    *(s32 *)((u8 *)arg0 + 0x38) = *(s32 *)((u8 *)arg0 + 0x38) + var_5;
    *(s32 *)((u8 *)arg0 + 0x40) = *(s32 *)((u8 *)arg0 + 0x40) + var_5;
}
