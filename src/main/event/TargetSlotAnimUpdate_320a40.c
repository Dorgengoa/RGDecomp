#include "types.h"

extern f32 D_0047D5D0;
extern f32 D_0047DADC;

void TargetSlotAnimUpdate_320a40(void *arg0) {
    u8 *p;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;

    p = (u8 *)arg0;
    if (*(s32 *)(p + 0x34) == 3) {
        temp_f1 = *(f32 *)(p + 0x40) + D_0047DADC;
        *(f32 *)(p + 0x40) = temp_f1;
        if (!(temp_f1 <= 1.0f)) {
            *(f32 *)(p + 0x40) = 0.0f;
        }
    }
    if (*(s32 *)(p + 0x34) == 2) {
        temp_f1_2 = *(f32 *)(p + 0x38);
        if (!(temp_f1_2 <= -1.0f)) {
            *(f32 *)(p + 0x38) = temp_f1_2 - D_0047D5D0;
        } else {
            *(s32 *)(p + 0x34) = 3;
            *(f32 *)(p + 0x38) = 0.0f;
        }
    }
    if (*(s32 *)(p + 0x34) == 1) {
        temp_f1_3 = *(f32 *)(p + 0x38);
        if (temp_f1_3 < 0.5f) {
            *(f32 *)(p + 0x38) = temp_f1_3 + D_0047D5D0;
        } else {
            *(s32 *)(p + 0x34) = 0;
        }
    }
}
