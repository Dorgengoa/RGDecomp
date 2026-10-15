#pragma divbyzerocheck on
#include "types.h"


s32 PlanetAreaMatrixCountInGroup_415040(void *arg0, s64 arg1) {
    s16 temp_6;
    s32 *var_9;
    s32 var_2;
    s32 var_8;
    s32 temp_7;

    temp_7 = (s16)arg1;
    if (temp_7 < 0) {
        return 0;
    }
    temp_6 = *(s16 *)((u8 *)arg0 + 0x7C);
    if (temp_6 <= 0) {
        return 0;
    }
    var_9 = *(s32 **)((u8 *)arg0 + 0x8C);
    if (var_9 == NULL) {
        return 0;
    }
    var_2 = 0;
    var_8 = 0;
    while (var_8 < temp_6) {
        if (temp_7 == (s32)((*var_9 / 10000000) % 100)) {
            var_2 += 1;
        }
        var_8 += 1;
        var_9 += 2;
    }
    return var_2;
}
