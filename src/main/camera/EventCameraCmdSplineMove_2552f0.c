#include "types.h"

extern void SplinePathPairBuild_256de0(void *);
extern void SplinePathPairStart_256dd0(void *);
extern void SplinePathPairStep_256d20(void *, f32 *, f32 *);
extern s32 SplinePathPairIsDone_256d00(void *);
extern void VecSub_13be40(f32 *, const f32 *, const f32 *); /* dst = a - b */
extern void sceVu0CopyVector(void *, const void *);

struct Obj1 {
    u8 pad000[0x38];
    s32 m38;
    u8 pad03C[0x14];
    f32 m50[4];
    f32 m60[4];
    u8 pad070[0xE0];
    f32 m150[4];
    f32 m160[4];
    u8 pad170[0x50];
    u8 m1C0[0x10];
};

/* p0 is live-in but never read - the family's descriptor argument. */
s32 EventCameraCmdSplineMove_2552f0(void *p0, struct Obj1 *p1)
{
    f32 v30[4];
    f32 v20[4];

    if (p1->m38 <= 0) {
        SplinePathPairBuild_256de0(p1->m1C0);
        SplinePathPairStart_256dd0(p1->m1C0);
        p1->m38 = 1;
    }
    SplinePathPairStep_256d20(p1->m1C0, v30, v20);
    VecSub_13be40(p1->m150, v30, p1->m50);
    VecSub_13be40(p1->m160, v20, p1->m60);
    sceVu0CopyVector(p1->m50, v30);
    sceVu0CopyVector(p1->m60, v20);
    if (SplinePathPairIsDone_256d00(p1->m1C0) != 0) {
        p1->m38 = 0;
        return 0;
    }
    return 1;
}
