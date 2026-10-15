#include "types.h"

extern void sceVu0CopyVector(void *, void *);
extern void sceVu0Normalize(void *, void *);
extern f32 RandRangeFloat_1ca5d0(f32);

void GuardEffectInitStreak_2d54c0(void *p, s32 idx)
{
    u8 *q;
    u8 *e;

    q = (u8 *)p;
    e = q + idx * 48 + 0x20;
    sceVu0CopyVector(e, q);
    sceVu0CopyVector(e + 0x10, q + 0x10);
    *(f32 *)(e + 0x00) = *(f32 *)(e + 0x00) + (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
    *(f32 *)(e + 0x04) = *(f32 *)(e + 0x04) + (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
    *(f32 *)(e + 0x08) = *(f32 *)(e + 0x08) + (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
    *(f32 *)(e + 0x10) = *(f32 *)(e + 0x10) + (RandRangeFloat_1ca5d0(1.0f) - 0.5f);
    *(f32 *)(e + 0x14) = *(f32 *)(e + 0x14) + (RandRangeFloat_1ca5d0(1.0f) - 0.5f);
    *(f32 *)(e + 0x18) = *(f32 *)(e + 0x18) + (RandRangeFloat_1ca5d0(1.0f) - 0.5f);
    sceVu0Normalize(e + 0x10, e + 0x10);
    *(f32 *)(e + 0x20) = *(f32 *)(q + 0x32C) * (1.0f + RandRangeFloat_1ca5d0(4.0f));
    *(f32 *)(e + 0x24) = *(f32 *)(q + 0x32C) * (2.0f + RandRangeFloat_1ca5d0(4.0f));
}
