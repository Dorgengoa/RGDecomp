/* rgp:protos */
#define RGP_SELF_RandomLayoutSave_1ff030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 RandomLayoutSave_1ff030(s32 arg0, s32 arg1)
{
    s32 var_5;
    s8 *var_6;
    s32 var_5_2;
    u8 *temp_2;
    u8 *temp_3;
    u8 *temp_3_2;

    temp_2 = *(u8 **)((u8 *)GetGameData_1fede0() + 0x18);
    temp_3 = temp_2 + 0x1C0;
    if (temp_3 == NULL) {
        return 0;
    }
    var_6 = (s8 *)(temp_3 + 2);
    *(u16 *)temp_3 = 0x6A4;
    var_5 = 0;
    do {
        if (!((var_5 % 10) != 0)) {
            *var_6 = -1;
        } else {
            *var_6 = *(s32 *)((u8 *)(s32)arg0 + (var_5 * 4));
        }
        var_5 += 1;
        var_6 += 1;
    } while (var_5 <= 0x64);
    var_5_2 = 0;
    do {
        temp_3_2 = (u8 *)(s32)arg1 + (var_5_2 * 4);
        var_5_2 += 2;
        *var_6 = (*(s32*)(temp_3_2 + 0x0) & 0xF) | ((*(s32 *)(temp_3_2 + 0x4) & 0xF) * 0x10);
        var_6 += 1;
    } while (var_5_2 < 0x64);
    return 1;
    return 0;
}
