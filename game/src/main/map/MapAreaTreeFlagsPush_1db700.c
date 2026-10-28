/* rgp:protos */
#define RGP_SELF_MapAreaTreeFlagsPush_1db700 1
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

void MapAreaTreeFlagsPush_1db700(void *p0)
{
    u8 *e;
    s32 n;
    s32 i;

    if (((unsigned char)MapDataIsLoaded_1e79d0((int)p0)) == 0) {
        return;
    }
    MapDataHiddenStackPush_1e7280(p0);
    e = ((u8 *)MapAreaGetBlocks_1dce30(p0));
    if (e != 0) {
        n = MapAreaGetBlockCount_1dce20(p0);
        for (i = 0; i < n; i++, e += 0xCC) {
            MapDataFlagsPush_1e7240(e);
        }
    }
    e = ((u8 *)MapAreaGetShares_1dce60(p0));
    if (e != 0) {
        n = MapAreaGetShareCount_1dce50(p0);
        for (i = 0; i < n; i++, e += 0x58) {
            MapDataFlagsPush_1e7240(e);
        }
    }
}
