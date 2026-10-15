#include "types.h"

extern s32 MapDataGetLightSet_1e77c0(s32 arg0, s32 arg1, s32 arg2);
extern s32 MapDataGetDefaultLightSet_1e7b60(s32 arg0);

s32 MapAreaGetLightSetOrDefault_1e5430(s32 unused0, s32 arg1, s32 arg2)
{
    s32 var_6;

    var_6 = arg2;
    if (arg1 == 0) {
        return 0;
    }
    if (var_6 < 0) {
        var_6 = MapDataGetDefaultLightSet_1e7b60(arg1);
    }
    if (var_6 < 0) {
        var_6 = 0;
    }
    return MapDataGetLightSet_1e77c0(arg1, var_6, var_6);
}
