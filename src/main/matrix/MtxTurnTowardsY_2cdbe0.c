#include "types.h"

extern f32 Acosf_129178(f32 arg0);
extern void sceVu0CopyMatrix(void *arg0, void *arg1);
extern void sceVu0CopyVector(void *arg0, void *arg1);
extern f32 sceVu0InnerProduct(void *arg0, void *arg1);
extern void sceVu0Normalize(void *arg0, void *arg1);
extern void sceVu0OuterProduct(void *arg0, void *arg1, void *arg2);
extern void sceVu0RotMatrixY(void *arg0, void *arg1, f32 arg2);
extern void sceVu0SubVector(void *arg0, void *arg1, void *arg2);
extern f32 D_0047D1DC;

f32 MtxTurnTowardsY_2cdbe0(s32 arg0, u8 *arg1, s32 arg2, f32 lim)
{
    f32 v80[4];
    f32 v70[4];
    f32 v60[4];
    f32 v50[4];
    f32 a;
    f32 t;
    f32 ab;

    sceVu0CopyVector(v80, arg1 + 0x20);
    v80[1] = 0.0f;
    sceVu0Normalize(v80, v80);
    sceVu0SubVector(v70, (void *)arg2, arg1 + 0x30);
    v70[1] = 0.0f;
    sceVu0Normalize(v70, v70);
    t = Acosf_129178(sceVu0InnerProduct(v80, v70));
    a = t;
    if (t < 0.0f) {
        t = -t;
    }
    if (t < D_0047D1DC) {
        sceVu0CopyMatrix((void *)arg0, arg1);
        return 0.0f;
    }
    sceVu0OuterProduct(v60, v80, v70);
    if (v60[1] < 0.0f) {
        a = -a;
    }
    if (a < 0.0f) {
        ab = -a;
    } else {
        ab = a;
    }
    if (ab < lim) {
        lim = ab;
    }
    if (a < 0.0f) {
        lim *= -1.0f;
    }
    if (ab <= D_0047D1DC) {
        sceVu0CopyMatrix((void *)arg0, arg1);
        return 0.0f;
    }
    sceVu0CopyVector(v50, arg1 + 0x30);
    sceVu0RotMatrixY((void *)arg0, arg1, lim);
    sceVu0CopyVector((void *)(arg0 + 0x30), v50);
    return a;
}
