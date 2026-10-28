/* rgp:protos */
#define RGP_SELF_MapMgrSlotsUpdateEntriesMaybe_1e16b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void MapMgrSlotsUpdateEntriesMaybe_1e16b0(u8 *p, void *a)
{
    u8 *q;
    s32 i;

    q = p + 0x1928;
    for (i = 0; i < 4; i++) {
        MapAreaActiveBlocksUpdateEntriesMaybe_1d9280(q, a);
        q += 0x1CC;
    }
}
