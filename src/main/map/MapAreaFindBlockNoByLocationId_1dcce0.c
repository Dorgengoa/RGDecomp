#include "types.h"

extern s32 MapBlockGetLocationId_1e0070(s32 arg0);
extern s32 MapDataGetId_1e7bd0(s32 arg0);

s32 MapAreaFindBlockNoByLocationId_1dcce0(void *arg0, s32 arg1)
{
    s32 var_17;
    s32 var_16;

    if (!(*(s32 *)((u8 *)arg0 + 0x2C) & 1)) {
        return -1;
    }
    var_17 = *(s32 *)((u8 *)arg0 + 0x98);
    if (var_17 == 0) {
        return -1;
    }
    var_16 = 0;
    while (var_16 < *(s16 *)((u8 *)arg0 + 0x8E)) {
        if ((MapDataGetId_1e7bd0(var_17) >= 0x4E20) && (MapDataGetId_1e7bd0(var_17) < 0x4E85) &&
            (arg1 == MapBlockGetLocationId_1e0070(var_17))) {
            return MapDataGetId_1e7bd0(var_17) - 0x4E20;
        }
        var_16 += 1;
        var_17 += 0xCC;
    }
    return -1;
}
