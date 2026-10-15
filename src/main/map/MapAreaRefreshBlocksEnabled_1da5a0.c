#include "types.h"

extern s32 MapAreaGetBlockCount_1dce20(s32);
extern void *MapAreaGetBlocks_1dce30(void);
extern void MapDataSetEnabled_1e7440(void *, s32);
extern s32 MapDataGetId_1e7bd0(s32);
extern s32 MapDataGetName_1e7bf0(void *);
extern s32 GetGameData_1fede0(void);
extern s32 WorldSavedFlagTestMaybe_3ed400(s32, s32, s32, s32);

void MapAreaRefreshBlocksEnabled_1da5a0(s32 arg0)
{
    u8 *var_19;
    s32 temp_18;
    s32 temp_21;
    s32 var_17;
    s32 temp_16;

    var_19 = (u8 *)MapAreaGetBlocks_1dce30();
    if (var_19 != NULL) {
        temp_18 = GetGameData_1fede0();
        temp_16 = MapAreaGetBlockCount_1dce20(arg0);
        var_17 = 0;
        while (var_17 < temp_16) {
            if ((*(s32 *)(var_19 + 0x2C) & 1)) {
                MapDataSetEnabled_1e7440(var_19, 0);
            } else {
                temp_21 = MapDataGetId_1e7bd0(arg0);
                MapDataSetEnabled_1e7440(var_19, WorldSavedFlagTestMaybe_3ed400(temp_18, temp_21, 0, MapDataGetName_1e7bf0(var_19)));
            }
            var_17 += 1;
            var_19 += 0xCC;
            continue;
        }
    }
}
