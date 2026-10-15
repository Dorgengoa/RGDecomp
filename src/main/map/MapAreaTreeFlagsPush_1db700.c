#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(void);
extern void MapDataHiddenStackPush_1e7280(void *p);
extern u8 *MapAreaGetBlocks_1dce30(void *p);
extern s32 MapAreaGetBlockCount_1dce20(void *p);
extern u8 *MapAreaGetShares_1dce60(void *p);
extern s32 MapAreaGetShareCount_1dce50(void *p);
extern void MapDataFlagsPush_1e7240(void *p);

void MapAreaTreeFlagsPush_1db700(void *p0)
{
    u8 *e;
    s32 n;
    s32 i;

    if (MapDataIsLoaded_1e79d0() == 0) {
        return;
    }
    MapDataHiddenStackPush_1e7280(p0);
    e = MapAreaGetBlocks_1dce30(p0);
    if (e != 0) {
        n = MapAreaGetBlockCount_1dce20(p0);
        for (i = 0; i < n; i++, e += 0xCC) {
            MapDataFlagsPush_1e7240(e);
        }
    }
    e = MapAreaGetShares_1dce60(p0);
    if (e != 0) {
        n = MapAreaGetShareCount_1dce50(p0);
        for (i = 0; i < n; i++, e += 0x58) {
            MapDataFlagsPush_1e7240(e);
        }
    }
}
