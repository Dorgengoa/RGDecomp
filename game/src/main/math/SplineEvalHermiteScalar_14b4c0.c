/* rgp:protos */
#define RGP_SELF_SplineEvalHermiteScalar_14b4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 v[4]; } FV4;
typedef struct { f32 x, y, z; } FV3;

extern u8 D_00449D90[];
/*rgp*/

void SplineEvalHermiteScalar_14b4c0(f32 *out, FV3 *a, FV3 *b, f32 t)
{
    FV4 n[3] __attribute__((aligned(16)));
    FV4 m[3] __attribute__((aligned(16)));
    FV4 ctl __attribute__((aligned(16)));
    FV4 res __attribute__((aligned(16)));
    u32 i;

    n[0].v[0] = a->x;
    n[1].v[0] = a->y;
    n[2].v[0] = a->z;
    m[0].v[0] = b->x;
    m[1].v[0] = b->y;
    m[2].v[0] = b->z;

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
