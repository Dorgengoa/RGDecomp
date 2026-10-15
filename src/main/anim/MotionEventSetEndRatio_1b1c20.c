#include "types.h"

extern f32 D_0047D24C;
extern f32 D_0047D3E8;

void MotionEventSetEndRatio_1b1c20(void *arg0, f32 fparg0)
{
    f32 var_f12;
    f32 var_f3;
    f32 var_f1;
    void *temp_14;
    f32 f_a;
    f32 f_b;

    var_f12 = fparg0;
    if (!(var_f12 < 1.0f)) {
        var_f12 = 1.0f;
    }
    temp_14 = *(void **)((u8 *)arg0 + 0x14);
    if (temp_14 == NULL) {
        var_f3 = 0.0f;
    } else {
        f_a = *(f32 *)((u8 *)temp_14 + 0x24);
        f_b = *(f32 *)((u8 *)temp_14 + 0x28);
        var_f3 = f_a + var_f12 * (f_b - f_a);
        var_f1 = var_f3 - (f32)(s32)var_f3;
        var_f1 = (var_f1 < 0.0f) ? -var_f1 : var_f1;
        if (!(var_f1 <= D_0047D3E8)) {
            var_f3 = (f32)(s32)(D_0047D24C + var_f3);
        }
    }
    *(f32 *)((u8 *)arg0 + 0xC) = var_f3;
    *(f32 *)((u8 *)arg0 + 0x20) = var_f12;
}
