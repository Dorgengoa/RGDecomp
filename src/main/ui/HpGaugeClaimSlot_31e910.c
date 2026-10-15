#include "types.h"

extern void HpGaugeRefreshSlot_31e7e0(s32 arg0, s32 arg1, s32 arg2);
extern s32 FindS16Index16_31e870(s32 arg0, s32 arg1);

void HpGaugeClaimSlot_31e910(s32 arg0, s32 arg1, f32 fparg0) {
    s16 *temp_4;
    s32 temp_2;
    s32 var_7;
    s32 off8;
    s32 off4;

    temp_2 = FindS16Index16_31e870(arg0, arg1);
    if (temp_2 != -1) {
        HpGaugeRefreshSlot_31e7e0(arg0, arg1, temp_2);
        return;
    }
    var_7 = 0;
    while (var_7 < 0x10) {
        temp_4 = (s16 *)((u8 *)arg0 + (var_7 * 2));
        if (*temp_4 == -1) {
            *temp_4 = (s16)arg1;
            off8 = var_7 * 8;
            off4 = var_7 * 4;
            *(s64 *)(u8 *)(off8 + arg0 + 0x20) = 0x4E;
            *(f32 *)(u8 *)(off4 + arg0 + 0x1D0) = fparg0;
            *(u8 *)(u8 *)(var_7 + arg0 + 0x1C0) = 1;
            return;
        }
        var_7 += 1;
    }
}
