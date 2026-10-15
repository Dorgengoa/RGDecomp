#include "types.h"

extern s32 MapBlockCollectAllCollTrisMaybe_1df9a0(void *, s32, s32, s32);
extern s32 MapBlockBoundsContainsXZ_1dfc20(void *, s32, f32);
extern s32 MapDataGetModel_1e7810(void);

s32 MapBlockCollectCollTrisNearMaybe_1df8c0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0)
{
    if ((arg1 == 0) || (arg2 <= 0)) {
        return 0;
    }
    if (MapDataGetModel_1e7810() == 0) {
        return 0;
    }
    if (!(*(u32 *)((u8 *)arg0 + 0x2C) & 0x10) && (MapBlockBoundsContainsXZ_1dfc20(arg0, arg4, fparg0) == 0)) {
        return 0;
    }
    return MapBlockCollectAllCollTrisMaybe_1df9a0(arg0, arg1, arg2, arg3);
}
