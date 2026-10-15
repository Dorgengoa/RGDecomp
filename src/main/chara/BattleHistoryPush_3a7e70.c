#include "types.h"

extern void BattleHistoryCalcAverages_3a7bd0(s16 *);
extern void memcpy(void *, void *, s32);

s32 BattleHistoryPush_3a7e70(s16 *arg0, void *arg1)
{
    s16 temp_2;
    s32 var_16;
    u8 *temp_5;

    if (arg1 == NULL) {
        return 0;
    }
    temp_2 = *arg0 + 1;
    *arg0 = temp_2;
    if (temp_2 > 5) {
        *arg0 = 5;
    }
    var_16 = *arg0 - 2;
    while (var_16 >= 0) {
        temp_5 = (u8 *)arg0 + (var_16 * 0x60) + 0x30;
        memcpy(temp_5 + 0x60, temp_5, 0x60);
        var_16 -= 1;
        continue;
    }
    memcpy((u8 *)arg0 + 0x30, arg1, 0x60);
    BattleHistoryCalcAverages_3a7bd0(arg0);
    return 1;
}
