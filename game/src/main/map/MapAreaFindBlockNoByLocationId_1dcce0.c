/* rgp:protos */
#define RGP_SELF_MapAreaFindBlockNoByLocationId_1dcce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MapAreaFindBlockNoByLocationId_1dcce0(void *arg0, s32 arg1)
{
    s32 var_17;
    s32 var_16;

    if (!(*(s32 *)((u8 *)arg0 + 0x2C) & 1)) {
        return -1;
    }
    var_17 = *(s32 *)((u8 *)arg0 + 0x98);
    if (var_17 == 0) {
        return -1;
    }
    var_16 = 0;
    while (var_16 < *(s16 *)((u8 *)arg0 + 0x8E)) {
        if ((((short)MapDataGetId_1e7bd0(var_17)) >= 0x4E20) && (((short)MapDataGetId_1e7bd0(var_17)) < 0x4E85) &&
            (arg1 == ((short)MapBlockGetLocationId_1e0070(var_17)))) {
            return ((short)MapDataGetId_1e7bd0(var_17)) - 0x4E20;
        }
        var_16 += 1;
        var_17 += 0xCC;
    }
    return -1;
}
