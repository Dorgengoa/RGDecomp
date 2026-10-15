/* PARK (round 1): length 0x148 vs retail 0x13C. */
#include "types.h"
#pragma opt_common_subs off

#define S8F(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 MapBlockGetNavGraphId_1e0050(s32);
extern s32 MapDataGetId_1e7bd0(s32);

s32 MapAreaFindBlockNoByNavGraphId_1dcba0(void *arg0, s32 arg1)
{
    s32 *var_17;
    s32 var_16;
    s32 var_17_2;
    s32 var_16_2;

    if (!(S32(arg0, 0x2C) & 1)) {
        return -1;
    }
    if (S32(arg0, 0x98) == 0) {
        return -1;
    }
    var_17 = (s32 *)((u8 *)arg0 + 0x178);
    var_16 = 0;
    while (var_16 < S16(arg0, 0x1CA)) {
        if ((MapDataGetId_1e7bd0(*var_17) >= 0x4E20) && (MapDataGetId_1e7bd0(*var_17) < 0x4E85) &&
            (arg1 == MapBlockGetNavGraphId_1e0050(*var_17))) {
            return MapDataGetId_1e7bd0(*var_17) - 0x4E20;
        }
        var_16 += 1;
        var_17 += 1;
    }
    var_17_2 = S32(arg0, 0x98);
    var_16_2 = 0;
    while (var_16_2 < S16(arg0, 0x8E)) {
        if ((MapDataGetId_1e7bd0(var_17_2) >= 0x4E20) && (MapDataGetId_1e7bd0(var_17_2) < 0x4E85) &&
            (arg1 == MapBlockGetNavGraphId_1e0050(var_17_2))) {
            return MapDataGetId_1e7bd0(var_17_2) - 0x4E20;
        }
        var_16_2 += 1;
        var_17_2 += 0xCC;
    }
    return -1;
}
