#include "types.h"

typedef struct S1D0 {
    u8  pad000[0xB4AC];
    f32 fB4AC;
    f32 fB4B0;
    s32 fB4B4;
} S1D0;

void GameSceneSoundSetVolumeNow_1d0400(S1D0 *p, f32 v)
{
    p->fB4B4 = 0;
    if (v < 0.0f) {
        v = 0.0f;
    }
    if (v > 1.0f) {
        v = 1.0f;
    }
    p->fB4B0 = v;
    p->fB4AC = v;
}
