/* rgp:protos */
#define RGP_SELF_MapRestoreState_1e41c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

/*rgp*/
/*rgp*/

void MapRestoreState_1e41c0(void *arg0) {
    u8 *var_7;
    u8 *var_6;
    u8 *var_17;
    s8 temp_2;
    s8 t3;
    s32 var_5;
    s32 var_16;

    var_5 = 0x10;
    var_7 = (u8 *)arg0 + 0x3C;
    var_6 = (u8 *)arg0 + 0xC;
    *(s16 *)((u8 *)arg0 + 0) = *(s16 *)((u8 *)arg0 + 0x30);
    *(s16 *)((u8 *)arg0 + 2) = *(s16 *)((u8 *)arg0 + 0x32);
    *(s16 *)((u8 *)arg0 + 4) = *(s16 *)((u8 *)arg0 + 0x34);
    *(s16 *)((u8 *)arg0 + 6) = *(s16 *)((u8 *)arg0 + 0x36);
    *(s16 *)((u8 *)arg0 + 8) = *(s16 *)((u8 *)arg0 + 0x38);
    *(s8 *)((u8 *)arg0 + 0xA) = *(s8 *)((u8 *)arg0 + 0x3A);
    *(s8 *)((u8 *)arg0 + 0xB) = *(s8 *)((u8 *)arg0 + 0x3B);
    do {
        var_5 -= 1;
        temp_2 = *(s8 *)(var_7 + 0);
        t3 = *(s8 *)(var_7 + 1);
        var_7 += 2;
        *(s8 *)(var_6 + 0) = temp_2;
        *(s8 *)(var_6 + 1) = t3;
        var_6 += 2;
    } while (var_5 > 0);
    var_17 = (u8 *)arg0 + 0x1928;
    var_16 = 0;
    *(s16 *)((u8 *)arg0 + 0x2C) = *(s16 *)((u8 *)arg0 + 0x5C);
    *(s16 *)((u8 *)arg0 + 0x2E) = *(s16 *)((u8 *)arg0 + 0x5E);
    *(s32 *)((u8 *)arg0 + 0xCC) = *(s32 *)((u8 *)arg0 + 0xD0);
    do {
        MapAreaTreeFlagsPop_1db620(var_17);
        var_16 += 1;
        var_17 += 0x1CC;
    } while (var_16 < 4);
    MapApplyAreaEnv_1e2bc0(arg0, *(s32 *)((u8 *)arg0 + 0xCC), 1);
}
