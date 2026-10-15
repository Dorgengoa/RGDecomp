#include "types.h"

extern s32 EventCollectCollPolys_1ff3b0(void);
extern void *GetMapMgr_201a90(void);
extern s32 MapSlotsCollectCollTrisMaybe_1e35b0(void *, u8 *, s32, s32);

s32 MapEvCollectCollPolysMaybe_1ff270(u8 *a0, s32 a1, s32 a2)
{
    s32 x;
    void *y;

    if (a0 == 0 || a1 <= 0) {
        return 0;
    }
    x = EventCollectCollPolys_1ff3b0();
    y = GetMapMgr_201a90();
    return x + MapSlotsCollectCollTrisMaybe_1e35b0(y, a0 + x * 96, a1 - x, a2);
}
