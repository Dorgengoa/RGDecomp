/* rgp:protos */
#define RGP_SELF_MapBlockIdListRebuildAtPos_1ff570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Entry70b {
    u8 pad70[0x70];
} Entry70b;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

int MapBlockIdListRebuildAtPos_1ff570(s32 arg0) { int rgp_v0 = 0;
    s32 sp70[0x14] __attribute__((aligned(16)));
    s16 *var_17;
    s32 temp_16;
    s32 temp_20;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_16;
    s32 temp_2_3;
    s32 var_17_2;
    u8 *temp_2_4;

    temp_2 = ((s32)GetMapMgr_201a90());
    MapBlockIdListClear_1e32e0(temp_2);
    temp_2_2 = MapFindBlockAtPos_1e3a00(temp_2, arg0, 0);
    if (temp_2_2 != 0) {
        MapBlockIdListAdd_1e3320(temp_2, MapDataGetId_1e7bd0(temp_2_2));
        var_17 = ((s16 *)MapBlockGetLinkIds_1dfee0(temp_2_2));
        if (var_17 != NULL) {
            temp_20 = MapBlockGetLinkIdCount_1dfed0(temp_2_2);
            var_16 = 0;
            while (var_16 < temp_20) {
                temp_2_3 = MapSlotsFindBlockById_1e49b0(temp_2, *var_17, 0);
                if ((temp_2_3 != 0) && (((unsigned char)MapDataIsEnabled_1e7c20(temp_2_3)) != 0) && (MapSlotsFindActiveById_1e4870(temp_2, ((short)MapDataGetLinkKeyMaybe_1e7b50(temp_2_3)), 0) == 0)) {
                    MapBlockIdListAdd_1e3320(temp_2, *var_17);
                }
                var_16 += 1;
                var_17 += 0x1;
            }
        }
    }
    temp_16 = (rgp_v0 = MapCollectBlocksAtPoint_1e3cb0(temp_2, sp70, 0x14, arg0, 0.0f));
    var_17_2 = 0;
    while (var_17_2 < temp_16) {
        if (((rgp_v0 = ((unsigned char)MapDataIsEnabled_1e7c20(sp70[var_17_2]))) != 0) && ((rgp_v0 = MapSlotsFindActiveById_1e4870(temp_2, ((short)MapDataGetLinkKeyMaybe_1e7b50(sp70[var_17_2])), 0)) == 0)) {
            (rgp_v0 = MapBlockIdListAdd_1e3320(temp_2, MapDataGetId_1e7bd0(sp70[var_17_2])));
        }
        var_17_2 += 1;
    }
return rgp_v0; }
