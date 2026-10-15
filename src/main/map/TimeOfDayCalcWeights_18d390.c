#include "types.h"
#pragma divbyzerocheck on

void TimeOfDayPhaseWeights_18d630(void);
s32 TimeOfDaySlot_18d7d0(void *);
f32 TimeOfDayGetHour_18d920(void);
extern f32 D_0047E06C;

s32 TimeOfDayCalcWeights_18d390(u8 *arg0, f32 *arg1)
{
    s32 n;
    f32 t;
    s32 i;
    f32 w;
    s32 k;
    s32 m;
    f32 a;
    f32 b;
    f32 d;

    n = *(s32 *)(arg0 + 0x1F8);
    if (n == 4) {
        TimeOfDayPhaseWeights_18d630();
        return n;
    }
    t = TimeOfDayGetHour_18d920();
    for (i = 0; i < n; i++) {
        arg1[i] = 0.0f;
    }
    if (n < 2) {
        arg1[0] = 1.0f;
        return n;
    }
    w = 1.0f;
    k = TimeOfDaySlot_18d7d0(arg0);
    m = (k + 1) % n;
    a = 9.0f + (f32)k * (24.0f / (f32)n);
    if (!(a < 24.0f)) {
        a -= 24.0f;
    }
    b = a + (24.0f / (f32)n);
    if (!(b <= 24.0f) && (t < 1.0f)) {
        b -= 24.0f;
    }
    d = b - t;
    if (d < D_0047E06C) {
        w = d / D_0047E06C;
    }
    arg1[k] = w;
    arg1[m] = 1.0f - w;
    return n;
}
