#include "types.h"

typedef struct { u8 pad[0x20]; f32 f20; s32 f24; f32 f28; f32 f2C; } T_001d1fa0;

extern void SoundSlotSetVolumeNow_1d2020(T_001d1fa0 *);

void SoundSlotFadeTo_1d1fa0(T_001d1fa0 *p, s32 n, f32 v)
{
    if (n <= 0) {
        SoundSlotSetVolumeNow_1d2020(p);
        return;
    }
    if (v < 0.0f) v = 0.0f;
    if (v > 1.0f) v = 1.0f;
    p->f2C = v;
    p->f28 = (v - p->f20) / (f32)n;
}
