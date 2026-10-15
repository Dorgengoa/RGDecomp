#include "types.h"

extern s32 MapGetAreaSlot2_1e5740(s32);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapGetFirstAreaSlot_1e5760(s32);

s32 MapGetActiveArea_1e56e0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = MapGetAreaSlot2_1e5740(p0);
    if (r0 != 0) {
        r1 = MapDataIsLoaded_1e79d0(r0);
        if (r1 != 0) {
            return r0;
        }
    }
    return MapGetFirstAreaSlot_1e5760(p0);
}
