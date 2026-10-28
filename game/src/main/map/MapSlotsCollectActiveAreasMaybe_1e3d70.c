/* rgp:protos */
#define RGP_SELF_MapSlotsCollectActiveAreasMaybe_1e3d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapSlotsCollectActiveAreasMaybe_1e3d70(s32 arg0, s32 arg1, s32 arg2) {
    s32 n;
    s32 p;
    s32 i;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    n = 0;
    p = MapGetAreaSlot2_1e5740((int)arg0);
    if (p != 0 && ((unsigned char)MapDataIsEnabled_1e7c20(p)) != 0 && ((unsigned char)MapDataIsLoaded_1e79d0(p)) != 0) {
        n += MapAreaCollectVisibleTreeMaybe_1db930(p, arg1, arg2);
    } else {
    p = arg0 + 0x1928;
    for (i = 0; i < 4; i++, p += 0x1CC) {
        if (i == 2) {
            continue;
        }
        n += MapAreaCollectVisibleTreeMaybe_1db930(p, arg1 + n * 4, arg2 - n);
        if (n >= arg2) {
            break;
        }
    }
    }
    return n;
}
