#include "types.h"

s32 PadSetRepeat_183d50(u8 *, s32, s32, s32);              /* extern */

void PadApplyRepeatConfig_183800(u8 *arg0, u8 *arg1) {
    s32 temp_16;
    s32 temp_5;
    s32 var_8;
    s32 var_18;
    s32 var_7;
    s32 var_17;
    s32 *temp_3;
    s32 *temp_6;

    var_7 = 1;
    var_8 = 0;
    temp_6 = (s32 *)(arg0 + 0xC0);
    do {
        if (var_7 != 0) {
            temp_5 = ~var_7;
            temp_6[0] &= temp_5;
            temp_6[1] &= temp_5;
            temp_3 = temp_6 + var_8;
            temp_3[2] = 0;
            temp_3[0x22] = 0;
            temp_3[0x42] = 0;
        }
        var_8 += 1;
        var_7 *= 2;
    } while (var_8 < 0x20);
    temp_16 = *(s32 *)arg1;
    var_17 = 1;
    var_18 = 0;
    do {
        if (temp_16 & var_17) {
            PadSetRepeat_183d50(arg0, var_17, ((s32 *)arg1)[var_18 + 1], ((s32 *)arg1)[var_18 + 0x21]);
        }
        var_18 += 1;
        var_17 *= 2;
    } while (var_18 < 0x20);
    if (arg1[0x104] > 0) {
        *(s32 *)(arg0 + 0x248) = arg1[0x105];
    } else {
        *(s32 *)(arg0 + 0x248) = 0;
    }
}
