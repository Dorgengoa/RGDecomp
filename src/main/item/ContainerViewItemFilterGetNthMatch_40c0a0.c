#include "types.h"

extern s32 ContainerViewItemFilterMatch_40c280(u8 *, s32);

s32 ContainerViewItemFilterGetNthMatch_40c0a0(u8 *arg0, s32 arg1)
{
    s32 temp_16;
    s16 temp_2_2;
    s16 temp_2_3;
    s16 temp_3;
    s32 var_19;
    s32 var_18;
    s32 temp_3_2;
    s32 var_17;
    u8 *temp_2;
    u8 *temp_4;

    temp_2 = *(u8 **)(arg0 + 0x4);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_4 = *(u8 **)(*(u8 **)(*(u8 **)(temp_2 + 0x8) + 0x40) + 0x8);
    if (temp_4 == NULL) {
        return 0;
    }
    temp_3 = *(s16 *)(arg0 + 0x10);
    var_19 = 0;
    temp_16 = *(s16 *)(temp_4 + 0x7C);
    var_18 = 0;
    if (temp_3 >= 0) {
        temp_2_2 = *(s16 *)(arg0 + 0xE);
        if (temp_2_2 >= 0) {
            if (temp_2_2 + 1 == arg1) {
                var_19 = temp_2_2 + 1;
                var_18 = temp_3 + 1;
            }
        }
    }
    temp_3_2 = *(s32 *)(temp_4 + 0x8C);
    if (temp_3_2 == 0) {
        return 0;
    }
    {
        var_17 = temp_3_2 + (var_18 * 0x34);
        while (var_18 < temp_16) {
            if (ContainerViewItemFilterMatch_40c280(arg0, var_17) != 0) {
                if (var_19 == arg1) {
                    *(s16 *)(arg0 + 0xE) = var_19;
                    *(s16 *)(arg0 + 0x10) = var_18;
                    return var_17;
                } else {
                    var_19 += 1;
                }
            }
            var_18 += 1;
            var_17 += 0x34;
        }
        return 0;
    }
    return 0;
    return 0;
}
