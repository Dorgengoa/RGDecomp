#include "types.h"

typedef struct { f32 m[4]; } M_00352740;

extern void XformToLocal_2e7440(void *, M_00352740 *, void *);
extern s32 EventVolumeRecAnyHitTrainWarp_2e4ab0(void *, M_00352740 *, f32);

s32 EvTargetSphereInVolumes_352740(void *a, void *b, void *c, f32 v)
{
    M_00352740 m;

    if (c == 0) return 0;
    XformToLocal_2e7440((void *)((s32)a + 0x80), &m, b);
    return EventVolumeRecAnyHitTrainWarp_2e4ab0(c, &m, v);
}
