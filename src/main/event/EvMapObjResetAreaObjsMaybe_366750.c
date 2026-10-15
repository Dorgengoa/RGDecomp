#include "types.h"

s32 MapSlotsFindById_1e4b90(s32, s32, s32);                      /* extern */
s32 MapDataFindObjsByName_1e6d40(s32, s32, u8 *, s32);                 /* extern */
s32 MapDataIsLoaded_1e79d0(s32);                              /* extern */
s32 GetMapMgr_201a90();                                 /* extern */
s32 TargetRefGetId_2e7120(u8 *);                           /* extern */
s32 EvMapObjGetName_366b90(u8 *);                           /* extern */

s32 EvMapObjResetAreaObjsMaybe_366750(u8 *arg0) {
    s32 sp30[317];
    s32 temp_17;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_5;
    u8 *temp_3;
    u8 *temp_4;

    if (!((*(s32 *)((u8 *)arg0 + 0xD0)) & 0x02000000)) {
        return 0;
    }
    temp_17 = GetMapMgr_201a90();
    temp_2 = MapSlotsFindById_1e4b90(temp_17, TargetRefGetId_2e7120(arg0 + 0xA0), 0);
    if ((temp_2 != 0) && (MapDataIsLoaded_1e79d0(temp_2) != 0)) {
        temp_2_2 = MapDataFindObjsByName_1e6d40(temp_2, EvMapObjGetName_366b90(arg0), (u8 *)sp30, 0x140);
        for (var_5 = 0; var_5 < temp_2_2; var_5++) {
            *(s32 *)(sp30[var_5] + 0x64) = 0;
            *(u16 *)(sp30[var_5] + 0x32) = 0;
            *(s32 *)(sp30[var_5] + 0x3C) |= 1;
        }
    }
    (*(u8 *)((u8 *)arg0 + 0x334)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x314)) = 0;
    return 1;
}
