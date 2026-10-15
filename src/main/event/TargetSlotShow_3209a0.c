#include "types.h"
#pragma opt_common_subs off

extern s32 GetLoadedOverlayId_1c3200(void);
extern void TargetRefResolve_2e5ed0(void *arg0, s32 arg1);
extern void TargetRefSetAttachPoint_2e65f0(void);
extern f32 TargetRefGetRadius_2e7100(void *arg0);
extern u8 D_00527020[];
extern void func_4F12D0(s32 arg0, s32 arg1);

void TargetSlotShow_3209a0(void *arg0, s32 arg1) {
    TargetRefSetAttachPoint_2e65f0();
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
