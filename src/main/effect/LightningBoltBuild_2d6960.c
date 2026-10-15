#include "types.h"

extern f32 VecDistance_13d3d0(f32 *a, f32 *b);
extern void sceVu0CopyVector(void *dst, void *src);
extern void sceVu0SubVector(f32 *, f32 *, f32 *);
extern void sceVu0Normalize(f32 *, f32 *);
extern void sceVu0ScaleVector(f32 *, f32 *, f32);
extern void sceVu0AddVector(f32 *, f32 *, f32 *);
extern f32 RandRangeFloat_1ca5d0(f32 t);

void LightningBoltBuild_2d6960(void *p, f32 *a, f32 *b, f32 w)
{
    f32 d[4];
    u8 *q;
    f32 len;
    f32 amp;
    f32 freq;
    s32 i;
    f32 *v;

    q = (u8 *)p;
    b[3] = 1.0f;
    a[3] = 1.0f;
    len = VecDistance_13d3d0(a, b);
    sceVu0CopyVector(q, a);
    sceVu0CopyVector(q + 0x80, b);
    sceVu0SubVector(d, b, a);
    sceVu0Normalize(d, d);
    sceVu0ScaleVector(d, d, len / 9.0f);
    amp = 3.0f + w / 20.0f;
    freq = 2.0f * amp;
    for (i = 1; i < 8; i++) {
        v = (f32 *)(q + i * 16);
        sceVu0AddVector(v, (f32 *)(q + (i - 1) * 16), d);
        v[0] += amp - RandRangeFloat_1ca5d0(freq);
        v[1] += amp - RandRangeFloat_1ca5d0(freq);
        v[2] += amp - RandRangeFloat_1ca5d0(freq);
    }
    *(s16 *)(q + 0xC2) = 9;
    *(f32 *)(q + 0x90) = 1.0f;
    *(f32 *)(q + 0x94) = 1.0f / (3.0f + RandRangeFloat_1ca5d0(2.0f));
    *(f32 *)(q + 0x98) = 0.25f + w / 40.0f;
    *(q + 0xC0) = 0;
}
