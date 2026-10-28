/* rgp:protos */
#define RGP_SELF_MapAreaRefreshBlocksEnabled_1da5a0 1
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

void MapAreaRefreshBlocksEnabled_1da5a0(s32 arg0)
{
    u8 *var_19;
    s32 temp_18;
    s32 temp_21;
    s32 var_17;
    s32 temp_16;

    var_19 = (u8 *)MapAreaGetBlocks_1dce30((void *)arg0);
    if (var_19 != NULL) {
        temp_18 = ((s32)GetGameData_1fede0());
        temp_16 = MapAreaGetBlockCount_1dce20(arg0);
        var_17 = 0;
        while (var_17 < temp_16) {
            if ((*(s32 *)(var_19 + 0x2C) & 1)) {
                MapDataSetEnabled_1e7440(var_19, 0);
            } else {
                temp_21 = ((short)MapDataGetId_1e7bd0(arg0));
                MapDataSetEnabled_1e7440(var_19, WorldSavedFlagTestMaybe_3ed400(temp_18, temp_21, 0, MapDataGetName_1e7bf0(var_19)));
            }
            var_17 += 1;
            var_19 += 0xCC;
            continue;
        }
    }
}
