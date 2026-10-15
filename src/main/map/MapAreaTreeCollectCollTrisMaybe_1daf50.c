#include "types.h"

extern s32 MapBlockCollectAllCollTrisMaybe_1df9a0(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 MapDataCollectCollTrisMaybe_1e6c80(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 MapDataIsLoaded_1e79d0();

s32 MapAreaTreeCollectCollTrisMaybe_1daf50(void *arg0, void *arg1, s32 arg2, s32 arg3)
{
    s32 var_17;
    void *var_4;
    s32 var_22_2;
    s32 var_3;
    void **var_16;
    void **var_16_2;
    s32 var_22;

    if ((arg1 == NULL) || (arg2 <= 0)) {
        return 0;
    }
    if (!(MapDataIsLoaded_1e79d0() != 0)) {
        return 0;
    }
    var_17 = MapDataCollectCollTrisMaybe_1e6c80(arg0, arg1, arg2, arg3);
    var_16 = (void **)((u8 *)arg0 + 0x128);
    var_22 = 0;
    while (var_22 < *(s16 *)((u8 *)arg0 + 0x1C8)) {
        if ((MapDataIsLoaded_1e79d0(*var_16) == 0) ||
            (var_17 += MapDataCollectCollTrisMaybe_1e6c80(*var_16, (u8 *)arg1 + (var_17 * 0x60), arg2 - var_17, arg3), (var_17 < arg2) != 0)) {
            var_22 += 1;
            var_16 += 1;
            continue;
        }
        break;
    }
    var_4 = arg1;
    var_3 = 0;
    while (var_3 < var_17) {
        var_3 += 1;
        *(s16 *)((u8 *)var_4 + 0x46) = *(s16 *)((u8 *)var_4 + 0x46) | 0x800;
        var_4 = (u8 *)var_4 + 0x60;
    }
    var_16_2 = (void **)((u8 *)arg0 + 0x178);
    var_22_2 = 0;
    while (var_22_2 < *(s16 *)((u8 *)arg0 + 0x1CA)) {
        if ((MapDataIsLoaded_1e79d0(*var_16_2) == 0) ||
            (var_17 += MapBlockCollectAllCollTrisMaybe_1df9a0(*var_16_2, (u8 *)arg1 + (var_17 * 0x60), arg2 - var_17, arg3), (var_17 < arg2) != 0)) {
            var_22_2 += 1;
            var_16_2 += 1;
            continue;
        }
        break;
    }
    return var_17;
    return 0;
}
