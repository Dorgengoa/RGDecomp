/* rgp:protos */
#define RGP_SELF_MapAreaFindBlockNoByNavGraphId_1dcba0 1
#include "port/game_protos.h"
#line 1
/* PARK (round 1): length 0x148 vs retail 0x13C. */
#include "types.h"
#pragma opt_common_subs off

#define S8F(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/

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
        if ((((short)MapDataGetId_1e7bd0(*var_17)) >= 0x4E20) && (((short)MapDataGetId_1e7bd0(*var_17)) < 0x4E85) &&
            (arg1 == MapBlockGetNavGraphId_1e0050(*var_17))) {
            return ((short)MapDataGetId_1e7bd0(*var_17)) - 0x4E20;
        }
        var_16 += 1;
        var_17 += 1;
    }
    var_17_2 = S32(arg0, 0x98);
    var_16_2 = 0;
    while (var_16_2 < S16(arg0, 0x8E)) {
        if ((((short)MapDataGetId_1e7bd0(var_17_2)) >= 0x4E20) && (((short)MapDataGetId_1e7bd0(var_17_2)) < 0x4E85) &&
            (arg1 == MapBlockGetNavGraphId_1e0050(var_17_2))) {
            return ((short)MapDataGetId_1e7bd0(var_17_2)) - 0x4E20;
        }
        var_16_2 += 1;
        var_17_2 += 0xCC;
    }
    return -1;
}
