/* rgp:protos */
#define RGP_SELF_RandomLayoutLoad_1fef50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 RandomLayoutLoad_1fef50(s32 *out0, s32 *out1) {
    s32 temp_3;
    s32 var_5;
    s8 *var_6;
    s32 var_5_2;
    u8 *temp_4;
    s32 *temp_4_2;
    temp_4 = (u8 *)*(void **)((u8 *)GetGameData_1fede0() + 0x18) + 0x1C0;
    if (temp_4 == NULL) {
        return 0;
    }
    if (*(s16 *)temp_4 != 0x6A4) {
        return 0;
    }
    var_6 = (s8 *)(temp_4 + 2);
    var_5 = 0;
    do {
        if (!((var_5 % 10) != 0)) {
            *out0 = -1;
        } else {
            *out0 = *var_6;
        }
        var_5 += 1;
        out0 += 1;
        var_6 += 1;
    } while (var_5 <= 0x64);
    var_5_2 = 0;
    do {
        temp_4_2 = (s32 *)((u8 *)out1 + (var_5_2 * 4));
        var_5_2 += 2;
        temp_4_2[0] = *var_6 & 0xF;
        temp_3 = *var_6 >> 4;
        var_6 += 1;
        temp_4_2[1] = temp_3 & 0xF;
    } while (var_5_2 < 0x64);
    return 1;
}
