#include "types.h"

typedef struct Entry70b {
    u8 pad70[0x70];
} Entry70b;

s32 MapBlockGetLinkIdCount_1dfed0(s32);
s16 *MapBlockGetLinkIds_1dfee0(s32);
void MapBlockIdListClear_1e32e0(s32);
void MapBlockIdListAdd_1e3320(s32, s16);
extern s32 MapFindBlockAtPos_1e3a00(s32, s32, f32);
s32 MapCollectBlocksAtPoint_1e3cb0(s32, void *, s32, s32, f32 );
s32 MapSlotsFindActiveById_1e4870(s32, s32, s32);
s32 MapSlotsFindBlockById_1e49b0(s32, s16, s32);
s32 MapDataGetLinkKeyMaybe_1e7b50(s32);
s16 MapDataGetId_1e7bd0(s32);
s32 MapDataIsEnabled_1e7c20(s32);
s32 GetMapMgr_201a90(void);

void MapBlockIdListRebuildAtPos_1ff570(s32 arg0) {
    s32 sp70[0x14];
    s16 *var_17;
    s32 temp_16;
    s32 temp_20;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_16;
    s32 temp_2_3;
    s32 var_17_2;
    u8 *temp_2_4;

    temp_2 = GetMapMgr_201a90();
    MapBlockIdListClear_1e32e0(temp_2);
    temp_2_2 = MapFindBlockAtPos_1e3a00(temp_2, arg0, 0);
    if (temp_2_2 != 0) {
        MapBlockIdListAdd_1e3320(temp_2, MapDataGetId_1e7bd0(temp_2_2));
        var_17 = MapBlockGetLinkIds_1dfee0(temp_2_2);
        if (var_17 != NULL) {
            temp_20 = MapBlockGetLinkIdCount_1dfed0(temp_2_2);
            var_16 = 0;
            while (var_16 < temp_20) {
                temp_2_3 = MapSlotsFindBlockById_1e49b0(temp_2, *var_17, 0);
                if ((temp_2_3 != 0) && (MapDataIsEnabled_1e7c20(temp_2_3) != 0) && (MapSlotsFindActiveById_1e4870(temp_2, MapDataGetLinkKeyMaybe_1e7b50(temp_2_3), 0) == 0)) {
                    MapBlockIdListAdd_1e3320(temp_2, *var_17);
                }
                var_16 += 1;
                var_17 += 0x1;
            }
        }
    }
    temp_16 = MapCollectBlocksAtPoint_1e3cb0(temp_2, sp70, 0x14, arg0, 0.0f);
    var_17_2 = 0;
    while (var_17_2 < temp_16) {
        if ((MapDataIsEnabled_1e7c20(sp70[var_17_2]) != 0) && (MapSlotsFindActiveById_1e4870(temp_2, MapDataGetLinkKeyMaybe_1e7b50(sp70[var_17_2]), 0) == 0)) {
            MapBlockIdListAdd_1e3320(temp_2, MapDataGetId_1e7bd0(sp70[var_17_2]));
        }
        var_17_2 += 1;
    }
}
