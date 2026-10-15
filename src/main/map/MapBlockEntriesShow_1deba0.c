#include "types.h"

extern void MapEntryShow_1e0c70(s32);
extern s32 MapDataIsLoadedOrUnloading_1e7980(void);

void MapBlockEntriesShow_1deba0(void *arg0)
{
    s32 var_17;
    s32 var_16;

    if (MapDataIsLoadedOrUnloading_1e7980() == 0) {
        return;
    }
    var_17 = *(s32 *)((u8 *)arg0 + 0xC0);
    if (var_17 == 0) {
        return;
    }
    var_16 = 0;
    while (var_16 < *(s16 *)((u8 *)arg0 + 0xC8)) {
        MapEntryShow_1e0c70(var_17);
        var_16 += 1;
        var_17 += 0x7A0;
    }
}
