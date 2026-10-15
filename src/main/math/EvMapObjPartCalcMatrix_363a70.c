#include "types.h"

typedef unsigned __int128 u128;

typedef union Vec4 {
    u128 q;
    f32 f[4];
    s32 i[4];
} Vec4;

extern void VecAdd_13be20(Vec4 *, void *, void *);
extern void VecScale_13be00(Vec4 *, void *, f32);
extern void VecSub_13be40(Vec4 *, void *, void *);
extern void sceVu0OuterProduct(Vec4 *, void *, void *);
extern void VecNormalize_13bd90(Vec4 *, void *);
extern void sceVu0UnitMatrix(void *);

/* Stack locals are allocated in REVERSE declaration order: first declared
   gets the highest slot (0xB0), last declared the lowest (0x30). */
void EvMapObjPartCalcMatrix_363a70(u8 *a, u8 *b)
{
    Vec4 vb0, va0, v90, v80, v70, v60, v50, v40, v30;

    vb0.q = *(u128 *)(a + 0x00);
    va0.q = *(u128 *)(a + 0x40);
    v90.q = *(u128 *)(a + 0x80);
    VecAdd_13be20(&v60, &va0, &v90);
    VecScale_13be00(&v60, &v60, 0.5f);
    VecSub_13be40(&v80, &vb0, &v60);
    VecSub_13be40(&v70, &va0, &v90);
    sceVu0OuterProduct(&v50, &v80, &v70);
    VecNormalize_13bd90(&v50, &v50);
    v40.q = *(u128 *)(a + 0x00);
    VecSub_13be40(&v40, &v40, a + 0xF0);
    VecNormalize_13bd90(&v40, &v40);
    sceVu0OuterProduct(&v30, &v50, &v40);
    VecNormalize_13bd90(&v30, &v30);
    VecScale_13be00(&v30, &v30, -1.0f);
    sceVu0UnitMatrix(b);
    *(u128 *)(b + 0x00) = v30.q;
    *(s32 *)(b + 0x0C) = 0;
    *(u128 *)(b + 0x10) = v50.q;
    *(s32 *)(b + 0x1C) = 0;
    *(u128 *)(b + 0x20) = v40.q;
    *(s32 *)(b + 0x2C) = 0;
}
