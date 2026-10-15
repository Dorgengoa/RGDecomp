#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
extern s32 MapSlotsFindActiveBlockByKeyMaybe_1e4690(s32, s32, s32);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern s32 MapDataIsEnabled_1e7c20(s32);
extern s32 GetMapMgr_201a90(void);
extern s32 TargetRefResolve_2e5ed0(void *, s32);
extern void TargetRefApplyToEventObj_2e6810(s32, s32);
extern s32 EvTargetSetGetId_336970(void *);

s32 EvTargetSetRefreshEnabled_336630(void *arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_2;
    s8 var_3;
    void *u;

    TargetRefResolve_2e5ed0(u, 0);
    if (TargetRefResolve_2e5ed0((u8 *)arg0 + 0x30, 0) != 0) {
        TargetRefApplyToEventObj_2e6810((s32)((u8 *)arg0 + 0x30), (s32)((u8 *)arg0 + 0xC0));
    }
    temp_16 = GetMapMgr_201a90();
    if (arg1 != 0) {
        *(s8 *)((u8 *)arg0 + 0x116) = MapSlotsFindActiveBlockByKeyMaybe_1e4690(temp_16, EvTargetSetGetId_336970(arg0), 0) != 0;
    } else {
        *(s8 *)((u8 *)arg0 + 0x116) = 0;
        temp_2 = MapSlotsFindBlockById_1e49b0(temp_16, EvTargetSetGetId_336970(arg0), 0);
        var_3 = temp_2 != 0;
        if (var_3 != 0) {
            var_3 = MapDataIsEnabled_1e7c20(temp_2) != 0;
        }
        *(s8 *)((u8 *)arg0 + 0x116) = var_3;
    }
    TargetRefResolve_2e5ed0((u8 *)arg0 + 0x60, 0);
    TargetRefResolve_2e5ed0((u8 *)arg0 + 0x90, 0);
    return 1;
}
