#include "types.h"

extern f32 RandFloat_1980f0(s32);
extern f32 RandGaussian_197d70(s32);
extern void EffParamApplyAlpha_1a85d0(s32, void *, f32 *);
extern f32 D_0047D420;

void EffectParamRandomizeApplyAlpha_198df0(void *arg0, s32 arg1, s32 arg2) {
    f32 sp4C;
    f32 var_f0;
    s32 temp_3;

    temp_3 = *(s32 *)((u8 *)arg0 + 0x10);
    if (temp_3 <= 0) {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20);
    } else if (temp_3 == 1) {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20) +
                 *(f32 *)((u8 *)arg0 + 0x30) * (2.0f * (RandFloat_1980f0(arg1 + 4) - 0.5f));
    } else if (temp_3 == 2) {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20) +
                 *(f32 *)((u8 *)arg0 + 0x30) * (D_0047D420 * RandGaussian_197d70(arg1 + 4));
    } else {
        var_f0 = *(f32 *)((u8 *)arg0 + 0x20);
    }
    sp4C = var_f0;
    EffParamApplyAlpha_1a85d0(arg2, (u8 *)arg1 + 0x4C, &sp4C);
}
