#include "types.h"

extern s32 MapFindBlockAtPos_1e3a00(s32, s32, f32);
extern s32 MapResolveAreaLightRef_1e5510(s32, s32);

s32 MapResolveAreaLightRefAtPos_1e5640(s32 p0, s32 p1)
{
    s32 r;

    r = MapFindBlockAtPos_1e3a00(p0, p1, 0.0f);
    if (r != 0) {
        return MapResolveAreaLightRef_1e5510(p0, r);
    }
    return 0;
}
