/* rgp:protos */
#define RGP_SELF_EffCurveSplineEval_1973e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T1973e0 {
    u8  pad00[8];
    s32 count;
    u8  pad0C[0x1C - 0x0C];
    f32 *tbl;
} T1973e0;

extern u8 D_0044A9F0[];
/*rgp*/

f32 EffCurveSplineEval_1973e0(T1973e0 *self, s32 i0, s32 i1, f32 t)
{
    f32 t2;
    f32 t3;
    s32 p;
    s32 q;
    s32 n;
    f32 *tbl;
    f32 a;
    f32 b;
    f32 c2;
    f32 c3;

    t2 = t * t;
    t3 = t2 * t;
    p = i0 - 1;
    if (p < 0) {
        p = 0;
    }
    n = self->count;
    if (p >= n) {
        p = n - 1;
    }
    q = i1 + 1;
    if (q < 0) {
        q = 0;
    }
    if (q >= n) {
        q = n - 1;
    }
    tbl = self->tbl;
    a = tbl[i0];
    b = tbl[i1];
    c2 = 0.5f * ((a - tbl[p]) + (b - a));
    c3 = 0.5f * ((b - a) + (tbl[q] - b));
    {
        f32 v[4] __attribute__((aligned(16))) = {0};

        v[0] = a;
        v[1] = b;
        v[2] = c2;
        v[3] = c3;
        MtxMulVec4_13c900(v, D_0044A9F0, v);
        return v[3] + (v[0] * t3 + v[1] * t2 + v[2] * t);
    }
}
