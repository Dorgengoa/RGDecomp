#include "types.h"

extern s32 MapBlockGetShareId_1e0080(s32);
extern s32 MapSlotsFindActiveShareById_1e47d0(s32, s32, s32);
extern s32 MapFindAreaSlotById_1e4cb0(s32, s32);
extern s32 MapResolveAreaLightRefById_1e5680(s32, s32);
extern s32 MapGetActiveArea_1e56e0(s32);
extern s32 MapDataGetLightRef_1e7b70(s32);
extern s32 MapDataGetParentId_1e7bb0(s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern s32 MapDataGetType_1e7c00(s32);

s32 MapResolveAreaLightRef_1e5510(s32 arg0, s32 arg1)
{
    s32 t;
    s32 r;

    if (arg1 == 0) {
        return 0;
    }
    r = 0;
    switch (MapDataGetLightRef_1e7b70(arg1)) {
    case -4:
        r = MapGetActiveArea_1e56e0(arg0);
        break;
    case -3:
        r = MapFindAreaSlotById_1e4cb0(arg0, MapDataGetParentId_1e7bb0(arg1));
        break;
    case -2:
        if (MapDataGetType_1e7c00(arg1) == 4) {
            r = MapSlotsFindActiveShareById_1e47d0(arg0, MapBlockGetShareId_1e0080(arg1), 0);
        }
        break;
    default:
        t = MapDataGetId_1e7bd0(arg1);
        if (t == MapDataGetLightRef_1e7b70(arg1)) {
            return arg1;
        }
        return MapResolveAreaLightRefById_1e5680(arg0, MapDataGetLightRef_1e7b70(arg1));
    case -1:
        return arg1;
    }
    return r;
}
