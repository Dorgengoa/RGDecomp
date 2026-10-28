/* rgp:protos */
#define RGP_SELF_MapResolveAreaLightRef_1e5510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapResolveAreaLightRef_1e5510(s32 arg0, s32 arg1)
{
    s32 t;
    s32 r;

    if (arg1 == 0) {
        return 0;
    }
    r = 0;
    switch (((short)MapDataGetLightRef_1e7b70(arg1))) {
    case -4:
        r = MapGetActiveArea_1e56e0(arg0);
        break;
    case -3:
        r = ((s32)MapFindAreaSlotById_1e4cb0(arg0, ((short)MapDataGetParentId_1e7bb0(arg1))));
        break;
    case -2:
        if (((signed char)MapDataGetType_1e7c00(arg1)) == 4) {
            r = MapSlotsFindActiveShareById_1e47d0(arg0, ((short)MapBlockGetShareId_1e0080(arg1)), 0);
        }
        break;
    default:
        t = ((short)MapDataGetId_1e7bd0(arg1));
        if (t == ((short)MapDataGetLightRef_1e7b70(arg1))) {
            return arg1;
        }
        return MapResolveAreaLightRefById_1e5680(arg0, ((short)MapDataGetLightRef_1e7b70(arg1)));
    case -1:
        return arg1;
    }
    return r;
}
