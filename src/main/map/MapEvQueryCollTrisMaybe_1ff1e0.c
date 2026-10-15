#include "types.h"

extern s32 EventCollectCollTris_1ff300(void);
extern void *GetMapMgr_201a90(void);
extern s32 MapSlotsQueryCollTrisMaybe_1e34f0(void *, u8 *, s32, s32);

s32 MapEvQueryCollTrisMaybe_1ff1e0(u8 *a0, s32 a1, s32 a2)
{
    s32 x;
    void *y;

    if (a0 == 0 || a1 <= 0) {
        return 0;
    }
    x = EventCollectCollTris_1ff300();
    y = GetMapMgr_201a90();
    return x + MapSlotsQueryCollTrisMaybe_1e34f0(y, a0 + x * 96, a1 - x, a2);
}
