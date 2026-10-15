#include "types.h"
#pragma opt_propagation off

extern f32 D_0047E040[3] __attribute__((section(".sdata")));
extern f32 D_0047E050[3] __attribute__((section(".sdata")));


void FarClipRecGetPresetFadeRates_186e70(s32 mode, f32 *out1, f32 *out2)
{
    s32 idx;
    f32 a;
    f32 c;

    idx = mode & 0xFF;
    if (idx < 0 || idx >= 3) {
        *out2 = 1.0f;
        *out1 = 1.0f;
    } else {
        a = D_0047E040[idx];
        c = D_0047E050[idx];
        *out1 = a;
        *out2 = c;
    }
}
