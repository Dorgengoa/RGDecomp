#include "types.h"

s16 PartyGetNonLeaderId_3c2750(void *arg0, s32 arg1)
{
    s32 temp_6 = *(s16 *)((u8 *)arg0 + 0x18C);
    s16 temp_2;
    s32 var_8;
    s32 var_7;
    s32 bound;

    bound = temp_6 - 1;
    if (arg1 < 0 || arg1 >= bound) {
        return -1;
    }
    var_8 = 0;
    var_7 = 0;
    while (var_7 < temp_6) {
        temp_2 = *(s16 *)((u8 *)arg0 + 0x190 + (var_7 * 2));
        if (temp_2 != *(s16 *)((u8 *)arg0 + 0x18E)) {
            if (var_8 == arg1) {
                return temp_2;
            }
            var_8 += 1;
            var_7 += 1;
            continue;
        }
        var_7 += 1;
    }
    return -1;
}
