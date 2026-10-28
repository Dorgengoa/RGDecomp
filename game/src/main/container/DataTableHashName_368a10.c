/* rgp:protos */
#define RGP_SELF_DataTableHashName_368a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on
#pragma opt_propagation off

extern s32 strlen(u8 *);

s32 DataTableHashName_368a10(void *arg0, u8 *arg1)
{
    s32 temp_2;
    u32 var_7;
    s32 var_6;
    u32 temp_5;
    u8 *var_16;

    var_16 = arg1;
    temp_2 = strlen(var_16);
    var_7 = 0;
    var_6 = 0;
    temp_5 = *(s16 *)((u8 *)arg0 + 0x7C) - 1;
    while (var_6 < temp_2) {
        var_7 = (u32)((var_6 + ((u32)((*var_16 - 0x20) * temp_5) / 224U)) + var_7) % temp_5;
        var_6 += 1;
        var_16 += 1;
        continue;
    }
    return var_7 & 0xFFFF;
}
