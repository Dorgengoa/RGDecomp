#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    u128 a;
    u128 b;
} Q2_338af0;

extern s32 TreasureBoxCollectCollPolys_3393f0(s32 arg0, void *arg1, s32 arg2, Q2_338af0 *arg3);

s32 TreasureBoxPoolCollectCollPolys_338af0(void *arg0, u8 *arg1, s32 arg2, Q2_338af0 *arg3)
{
    Q2_338af0 sp60;
    u8 *var_20;
    s32 var_4;
    s32 var_18;
    s32 var_17;
    s32 var_16;

    sp60 = *arg3;
    var_17 = *(s32 *)((u8 *)arg0 + 0);
    if (var_17 == 0) {
        return 0;
    }
    if (!(*(u8 *)((u8 *)arg0 + 0xA) & 1)) {
        return 0;
    }
    var_18 = 0;
    var_16 = 0;
    do {
        var_18 += TreasureBoxCollectCollPolys_3393f0(var_17, arg1 + (var_18 * 0x60), arg2 - var_18, &sp60);
        var_16 += 1;
        var_17 += 0x80;
    } while (var_16 < 0x20);
    var_4 = 0;
    var_20 = arg1;
    while (var_4 < var_18) {
        var_4 += 1;
        *(s16 *)((u8 *)var_20 + 0x46) = (*(s16 *)((u8 *)var_20 + 0x46) | 0x800);
        *(s32 *)((u8 *)var_20 + 0x54) = -2;
        var_20 = (u8 *)var_20 + 0x60;
    }
    return var_18;
}
