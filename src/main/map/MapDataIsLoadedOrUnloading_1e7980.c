#include "types.h"

extern s32 MapDataGetState_1e7a00(s32);

u8 MapDataIsLoadedOrUnloading_1e7980(s32 p0)
{
    u8 a;

    a = (MapDataGetState_1e7a00(p0) == 2);
    if (a == 0) {
        a = (MapDataGetState_1e7a00(p0) == 3);
    }
    return a;
}
