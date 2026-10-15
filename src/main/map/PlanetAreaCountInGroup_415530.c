#include "types.h"

#pragma divbyzerocheck on

s32 PlanetAreaCountInGroup_415530(void *arg0, s16 arg1)
{
    s16 temp_6;
    s32 *var_9;
    s32 var_2;
    s32 var_8;

    if (arg1 < 0) {
        return 0;
    }
    temp_6 = *(s16 *)((u8 *)arg0 + 0x7C);
    if (temp_6 > 0) goto L1;
    return 0;
L1:
    var_9 = *(s32 **)((u8 *)arg0 + 0x8C);
    if (var_9 != NULL) goto L2;
    return 0;
L2:
    var_2 = 0;
    var_8 = 0;
    while (var_8 < temp_6) {
        if (arg1 == (*var_9 / 10000000) % 100) {
            var_2 += 1;
        }
        var_8 += 1;
        var_9 += 0xb;
    }
    return var_2;
}
