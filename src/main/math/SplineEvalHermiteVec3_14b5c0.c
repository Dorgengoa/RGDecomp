#include "types.h"

typedef struct { f32 v[4]; } FV4;
typedef struct { f32 x, y, z; } FV3;

extern u8 D_00449D90[];
extern void MtxMulVec4_13c900(FV4 *, void *, FV4 *);

void SplineEvalHermiteVec3_14b5c0(f32 *out, FV3 *a, FV3 *b, f32 t)
{
    FV4 n[3];
    FV4 m[3];
    FV4 ctl;
    FV4 res;
    u32 i;

    n[0].v[0] = a[0].x;
    n[0].v[1] = a[0].y;
    n[0].v[2] = a[0].z;
    n[1].v[0] = a[1].x;
    n[1].v[1] = a[1].y;
    n[1].v[2] = a[1].z;
    n[2].v[0] = a[2].x;
    n[2].v[1] = a[2].y;
    n[2].v[2] = a[2].z;
    m[0].v[0] = b[0].x;
    m[0].v[1] = b[0].y;
    m[0].v[2] = b[0].z;
    m[1].v[0] = b[1].x;
    m[1].v[1] = b[1].y;
    m[1].v[2] = b[1].z;
    m[2].v[0] = b[2].x;
    m[2].v[1] = b[2].y;
    m[2].v[2] = b[2].z;

    for (i = 0; i < 3; i++) {
        ctl.v[0] = n[0].v[i];
        ctl.v[1] = m[0].v[i];
        ctl.v[2] = n[1].v[i];
        ctl.v[3] = m[2].v[i];
        MtxMulVec4_13c900(&res, D_00449D90, &ctl);
        out[i] = res.v[3] + t * (res.v[2] + t * (res.v[1] + res.v[0] * t));
    }
    out[3] = 1.0f;
}
