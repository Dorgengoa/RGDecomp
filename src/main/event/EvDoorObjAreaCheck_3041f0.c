#include "types.h"

extern s32 TargetRefIsActive_2e6f00(void *);
extern s32 XformPointInBoxSide_2e77e0(void *, s32, f32, f32, f32, f32);
extern s32 XformPointInScaleBoxMaybe_2e7960(void *, s32, f32, f32);
extern f32 D_0045B080[];

s32 EvDoorObjAreaCheck_3041f0(void *arg0, s32 arg1) {
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f15;

    if (TargetRefIsActive_2e6f00((u8 *)arg0 + 0xA0) == 0) {
        return 0;
    }
    temp_f15 = *(f32 *)((u8 *)arg0 + 0x174);
    temp_f13 = *(f32 *)((u8 *)arg0 + 0x170);
    temp_f12 = *(f32 *)((u8 *)arg0 + 0x178);
    if (!((temp_f12 * (temp_f13 * temp_f15)) <= 0.0f)) {
        return XformPointInBoxSide_2e77e0((u8 *)arg0 + 0x10, arg1, temp_f12, temp_f13, -D_0045B080[0], temp_f15);
    }
    return XformPointInScaleBoxMaybe_2e7960((u8 *)arg0 + 0x10, arg1, temp_f12, temp_f13);
}
