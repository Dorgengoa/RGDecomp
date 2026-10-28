/* rgp:protos */
#define RGP_SELF_MeshPktUnpackV4Indexed_165550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_lifetimes off

s32 MeshPktUnpackV4Indexed_165550(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, u16 *arg5) {
    u8 *var_3;
    u8 *temp_5;
    u8 *var_8;
    u16 *var_9;
    s32 var_6;
    s32 temp_2;
    s32 var_2;
    s32 temp_3;

    var_6 = arg2;
    var_9 = arg5;
    var_3 = (u8 *)arg0;
    switch (arg4) {
    case 32:
    case 16:
        break;
    case 8:
        arg4 = arg1 | 0xC000;
        temp_5 = var_3 + 4;
        *(s32 *)arg0 = arg4 | (var_6 << 0x10) | 0x6E000000;
        var_8 = temp_5;
        while (var_6 > 0) {
            var_6 -= 1;
            temp_2 = *var_9 * 4;
            var_9 += 1;
            *(s32 *)var_8 = *(s32 *)((u8 *)arg3 + temp_2);
            var_8 += 4;
        }
        temp_3 = var_8 - temp_5;
        var_2 = temp_3 >> 2;
        if (temp_3 < 0) {
            var_2 = (temp_3 + 3) >> 2;
        }
        var_3 = temp_5 + (var_2 * 4);
        break;
    }
    temp_3 = var_3 - (u8 *)arg0;
    var_2 = temp_3 >> 2;
    if (temp_3 < 0) {
        var_2 = (temp_3 + 3) >> 2;
    }
    return var_2;
}
