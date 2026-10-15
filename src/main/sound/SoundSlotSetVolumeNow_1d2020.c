#include "types.h"

typedef struct S1D2 {
    u8  pad000[0x20];
    f32 f20;
    u8  pad024[4];
    s32 f28;
    f32 f2C;
} S1D2;

void SoundSlotSetVolumeNow_1d2020(S1D2 *p, f32 v)
{
    p->f28 = 0;
    p->f2C = v;
    if (v < 0.0f) {
        p->f2C = 0.0f;
    }
    if (p->f2C > 1.0f) {
        p->f2C = 1.0f;
    }
    p->f20 = p->f2C;
}
