/* rgp:protos */
#define RGP_SELF_EvTargetSetRefreshEnabled_336630 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvTargetSetRefreshEnabled_336630(void *arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_2;
    s8 var_3;
    void *u;

    TargetRefResolve_2e5ed0((void *)arg0, 0);
    if (TargetRefResolve_2e5ed0((u8 *)arg0 + 0x30, 0) != 0) {
        TargetRefApplyToEventObj_2e6810((s32)((u8 *)arg0 + 0x30), (s32)((u8 *)arg0 + 0xC0));
    }
    temp_16 = ((s32)GetMapMgr_201a90());
    if (arg1 != 0) {
        *(s8 *)((u8 *)arg0 + 0x116) = MapSlotsFindActiveBlockByKeyMaybe_1e4690(temp_16, ((short)EvTargetSetGetId_336970(arg0)), 0) != 0;
    } else {
        *(s8 *)((u8 *)arg0 + 0x116) = 0;
        temp_2 = MapSlotsFindBlockById_1e49b0(temp_16, ((short)EvTargetSetGetId_336970(arg0)), 0);
        var_3 = temp_2 != 0;
        if (var_3 != 0) {
            var_3 = ((unsigned char)MapDataIsEnabled_1e7c20(temp_2)) != 0;
        }
        *(s8 *)((u8 *)arg0 + 0x116) = var_3;
    }
    TargetRefResolve_2e5ed0((u8 *)arg0 + 0x60, 0);
    TargetRefResolve_2e5ed0((u8 *)arg0 + 0x90, 0);
    return 1;
}
