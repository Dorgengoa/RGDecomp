#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(void);
extern void MapDataHiddenStackPop_1e7270(void *p);
extern u8 *MapAreaGetBlocks_1dce30(void *p);
extern s32 MapAreaGetBlockCount_1dce20(void *p);
extern u8 *MapAreaGetShares_1dce60(void *p);
extern s32 MapAreaGetShareCount_1dce50(void *p);
extern void MapDataFlagsPop_1e7210(void *p);

void MapAreaTreeFlagsPop_1db620(void *p0)
{
    u8 *e;
    s32 n;
    s32 i;

    if (MapDataIsLoaded_1e79d0() == 0) {
        return;
    }
    MapDataHiddenStackPop_1e7270(p0);
    e = MapAreaGetBlocks_1dce30(p0);
    if (e != 0) {
        n = MapAreaGetBlockCount_1dce20(p0);
        for (i = 0; i < n; i++, e += 0xCC) {
            MapDataFlagsPop_1e7210(e);
        }
    }
    e = MapAreaGetShares_1dce60(p0);
    if (e != 0) {
        n = MapAreaGetShareCount_1dce50(p0);
        for (i = 0; i < n; i++, e += 0x58) {
            MapDataFlagsPop_1e7210(e);
        }
    }
}
