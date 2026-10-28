/* rgp:protos */
#define RGP_SELF_MapBlockEntriesShow_1deba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MapBlockEntriesShow_1deba0(void *arg0)
{
    s32 var_17;
    s32 var_16;

    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((int)arg0)) == 0) {
        return;
    }
    var_17 = *(s32 *)((u8 *)arg0 + 0xC0);
    if (var_17 == 0) {
        return;
    }
    var_16 = 0;
    while (var_16 < *(s16 *)((u8 *)arg0 + 0xC8)) {
        MapEntryShow_1e0c70(var_17, 0, 0, 0);
        var_16 += 1;
        var_17 += 0x7A0;
    }
}
