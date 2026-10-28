/* rgp:protos */
#define RGP_SELF_MeshProbeGroundHeight_26af10 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/

int MeshProbeGroundHeight_26af10(f32 *pos, E *arr, s32 arg2, s32 arg3, f32 *out, E *dst, f32 h)
{ int rgp_v0 = 0;
    f32 spA0[4] __attribute__((aligned(16)));
    f32 sp90[4] __attribute__((aligned(16)));
    f32 sp80[4] __attribute__((aligned(16)));
    s32 r;

    sceVu0CopyVector(spA0, pos);
    sceVu0CopyVector(sp90, pos);
    spA0[1] -= h;
    sp90[1] += h;
    r = (rgp_v0 = MeshRaycastWrapper_16f610(arr, arg2, spA0, sp90, sp80, 1, arg3));
    if (r < 0) {
        return rgp_v0;
    }
    *out = sp80[1] - pos[1];
    dst->a = arr[r].a;
    dst->v = arr[r].v;
    dst->b = arr[r].b;
    dst->c = arr[r].c;

return rgp_v0; }
