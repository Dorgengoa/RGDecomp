#include "types.h"

s32 TextEntryGetString_435640(void *arg0, s8 *arg1) {
    u8 *var_11;
    u8 *var_10;
    s32 var_9;
    s8 *var_5;
    s8 temp_2;
    s8 temp_8;

    var_5 = arg1;
    var_11 = (u8 *)arg0 + 0x30;
    var_10 = (u8 *)arg0 + 0x197;
    var_9 = 0;
    do {
        if (*(s16 *)((u8 *)arg0 + 0xE0) == 0) {
            temp_8 = *(s8 *)var_11;
            if (temp_8 != 0xA) {
                if (*(s8 *)var_10 == 0x31) {
                    *var_5 = temp_8;
                    var_5 += 1;
                }
                var_10 += 1;
            }
        } else {
            temp_2 = *(s8 *)var_11;
            if ((temp_2 != 0x2A) && (temp_2 != 0xA)) {
                *var_5 = temp_2;
                var_5 += 1;
            }
        }
        var_9 += 1;
        var_11 += 1;
    } while (var_9 < 0xAE);
    *var_5 = 0;
    return 0;
}
