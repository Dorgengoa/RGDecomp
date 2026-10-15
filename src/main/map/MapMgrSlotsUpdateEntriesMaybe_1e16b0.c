#include "types.h"

extern void MapAreaActiveBlocksUpdateEntriesMaybe_1d9280(u8 *q, void *a);

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
