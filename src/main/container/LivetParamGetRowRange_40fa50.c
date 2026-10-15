/* main s27m: CLOSED -- TWO unused leading params (retail reads $t0..$t2) and
   `(var_5 * 0x54) - (-arg0)` so the product stays in rs (commutative-add lever). */
#include "types.h"

extern s32 MainCharaIdToNumber_4016b0(s32);

s32 LivetParamGetRowRange_40fa50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, s32 *arg5, s32 *arg6) {
    s32 var_5;
    s32 var_3;
    u8 *temp_3;

    *arg5 = -1;
    *arg6 = -1;
    if (arg1 < 0) {
        return -1;
    }
    var_5 = MainCharaIdToNumber_4016b0(arg1) - 1;
    var_3 = *arg4;
    if ((var_5 < 0) || (var_5 >= 9)) {
        var_5 = 9;
    }
    if ((s32) var_3 >= 0x14) {
        var_3 = 0x14;
    }
    temp_3 = (u8 *)((var_3 * 4) + ((var_5 * 0x54) - (-arg0)));
    *arg5 = *(s16 *)(temp_3 + 0x98);
    *arg6 = *(s16 *)(temp_3 + 0x9A);
    return *arg5;
}
