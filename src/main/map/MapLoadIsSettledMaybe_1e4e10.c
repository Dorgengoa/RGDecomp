#include "types.h"

extern s32 MapSlotsFindBlockById_1e49b0(void *, s16, s32);
extern s32 MapSlotsFindShareById_1e4a50(void *, s16, s32);
extern void *MapGetAreaSlot2_1e5740(void *);
extern void *MapGetFirstAreaSlot_1e5760(void);
extern void MapIdListRemove_1e5910(void *, s16);
extern s32 MapIdListCount_1e5a40(void *);
extern s16 *MapIdListGetEntry_1e5a50(void *, s32);
extern s16 *MapIdListGetEntries_1e5a70(void *);
extern s32 MapDataIsStreamActive_1e7920(s32);
extern s32 MapDataIsLoadedOrUnloading_1e7980(s32);
extern s32 MapDataIsLoaded_1e79d0(void *);
extern s32 MapDataGetState_1e7a00(s32);
extern s32 MapDataIsEnabled_1e7c20(s32);

u8 MapLoadIsSettledMaybe_1e4e10(void *arg0, s32 arg1)
{
    void *temp_2_2;
    void *temp_2;
    u8 var_19;
    s32 var_18_3;
    s32 var_18_2;
    s16 *var_18;
    s32 temp_2_7;
    s32 temp_2_5;
    s32 var_17;
    s32 temp_22;
    s32 temp_2_3;
    s16 *temp_2_6;
    s16 *temp_2_4;
    u8 *base;

    base = (u8 *)arg0;
    temp_2 = MapGetFirstAreaSlot_1e5760();
    if (MapDataIsLoaded_1e79d0(temp_2) == 0) {
        return 0;
    }
    if (*(s16 *)(base + 0x20AC) >= 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)temp_2 + 0x2C) & 0x400) {
        return 1;
    }
    temp_2_2 = MapGetAreaSlot2_1e5740(arg0);
    if ((temp_2_2 != NULL) && (MapDataIsLoaded_1e79d0(temp_2_2) != 0)) {
        return 1;
    }
    var_19 = 1;
    if (MapIdListCount_1e5a40(base + 0x21F8) > 0) {
        var_19 = 0;
        var_18 = MapIdListGetEntries_1e5a70(base + 0x21F8);
        temp_22 = MapIdListCount_1e5a40(base + 0x21F8);
        var_17 = 0;
        while (var_17 < temp_22) {
            temp_2_3 = MapSlotsFindBlockById_1e49b0(arg0, *var_18, 0);
            if (temp_2_3 != 0) {
                if (MapDataIsEnabled_1e7c20(temp_2_3) == 0 || MapDataIsLoadedOrUnloading_1e7980(temp_2_3) != 0) {
                    var_19 = 1;
                } else if (MapDataGetState_1e7a00(temp_2_3) == 1) {
                    return 0;
                }
            }
block_27:
            var_17 += 1;
            var_18 += 0x4;
        }
    }
    if (arg1 && var_19) {
        var_18_2 = 0;
        while (var_18_2 < MapIdListCount_1e5a40(base + 0x21F8)) {
            temp_2_4 = MapIdListGetEntry_1e5a50(base + 0x21F8, var_18_2);
            temp_2_5 = MapSlotsFindBlockById_1e49b0(arg0, *temp_2_4, 0);
            if ((temp_2_5 == 0) || (MapDataIsEnabled_1e7c20(temp_2_5) == 0) || (MapDataIsStreamActive_1e7920(temp_2_5) == 0)) {
                MapIdListRemove_1e5910(base + 0x21F8, *temp_2_4);
                var_18_2 -= 1;
            }
            var_18_2 += 1;
        }
        var_18_3 = 0;
        while (var_18_3 < MapIdListCount_1e5a40(base + 0x2154)) {
            temp_2_6 = MapIdListGetEntry_1e5a50(base + 0x2154, var_18_3);
            temp_2_7 = MapSlotsFindShareById_1e4a50(arg0, *temp_2_6, 0);
            if ((temp_2_7 == 0) || (MapDataIsEnabled_1e7c20(temp_2_7) == 0) || (MapDataIsStreamActive_1e7920(temp_2_7) == 0)) {
                MapIdListRemove_1e5910(base + 0x2154, *temp_2_6);
                var_18_3 -= 1;
            }
            var_18_3 += 1;
        }
    }
    return var_19;
}
