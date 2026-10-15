#include "types.h"

extern void TreasureBoxReset_33b4c0(void *);

s32 TreasureBoxPoolResetByGroupId_3389c0(void **arg0, s32 arg1) {
    u8 *var_17;
    s32 var_16;

    var_17 = (u8 *)*arg0;
    var_16 = 0;
    do {
        if (arg1 == *(s16 *)(var_17 + 0x20) || arg1 < 0) {
            TreasureBoxReset_33b4c0(var_17);
        }
        var_16 += 1;
        var_17 += 0x80;
    } while (var_16 < 0x20);
    return 1;
}
