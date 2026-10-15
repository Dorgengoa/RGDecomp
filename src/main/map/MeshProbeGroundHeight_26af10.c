#include "types.h"

typedef struct { s32 w[12]; } A30;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s16 h[10]; } B14;
typedef struct {
    A30 a;
    V4 v;
    B14 b;
    s32 c;
    u8 pad58[8];
} E;

extern s32 MeshRaycastWrapper_16f610(E *arg0, s32 arg1, void *arg2, void *arg3, void *arg4, s32 arg5, s32 arg6);
extern void sceVu0CopyVector(void *arg0, void *arg1);

void MeshProbeGroundHeight_26af10(f32 *pos, E *arr, s32 arg2, s32 arg3, f32 *out, E *dst, f32 h)
{
    f32 spA0[4];
    f32 sp90[4];
    f32 sp80[4];
    s32 r;

    sceVu0CopyVector(spA0, pos);
    sceVu0CopyVector(sp90, pos);
    spA0[1] -= h;
    sp90[1] += h;
    r = MeshRaycastWrapper_16f610(arr, arg2, spA0, sp90, sp80, 1, arg3);
    if (r < 0) {
        return;
    }
    *out = sp80[1] - pos[1];
    dst->a = arr[r].a;
    dst->v = arr[r].v;
    dst->b = arr[r].b;
    dst->c = arr[r].c;

}
