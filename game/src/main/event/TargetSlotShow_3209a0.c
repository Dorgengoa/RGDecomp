/* rgp:protos */
#define RGP_SELF_TargetSlotShow_3209a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00527020[];
/*rgp*/

void TargetSlotShow_3209a0(void *arg0, s32 arg1, int rgp_a2, int rgp_a3) {
    TargetRefSetAttachPoint_2e65f0((void *)arg0, (int)arg1, (int)rgp_a2, (int)rgp_a3);
    TargetRefResolve_2e5ed0(arg0, 0);
    *(s32 *)((u8 *)arg0 + 0x30) = arg1;
    *(s32 *)((u8 *)arg0 + 0x34) = 2;
    *(u32 *)((u8 *)arg0 + 0x38) = 0x3F800000;
    *(s32 *)((u8 *)arg0 + 0x40) = 0;
    *(f32 *)((u8 *)arg0 + 0x3C) = 2.0f * TargetRefGetRadius_2e7100(arg0);
    if (GetLoadedOverlayId_1c3200() == 3) {
        func_4F12D0((s32)D_00527020, *(s32 *)((u8 *)arg0 + 0x30));
    }
}
