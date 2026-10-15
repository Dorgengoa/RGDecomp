#include "types.h"
#pragma optimization_level 3

extern void MtxMulVec4_13c900(f32 *out, f32 *mtx, f32 *v);
extern f32 D_00449D50[16];

void SplineEvalBezierSolveTime_14b8a0(f32 *out, f32 (*p)[4], f32 (*q)[4], f32 a, f32 b, f32 t)
{
    f32 coef[4];
    f32 u[4];
    f32 v[4];
    s32 i;
    f32 target;
    f32 s;
    s32 ge;

    target = a * (1.0f - t) + b * t;
    for (i = 0; i < 3; i++) {
        f32 lo;
        f32 hi;
        f32 mid;
        u[0] = a;
        v[0] = p[0][i];
        u[1] = p[1][i] + a;
        v[1] = p[2][i] + p[0][i];
        u[2] = q[3][i] + b;
        v[2] = q[4][i] + q[0][i];
        v[3] = q[0][i];
        u[3] = b;
        MtxMulVec4_13c900(coef, D_00449D50, u);
        lo = 0.0f;
        s = t;
        if (t > lo) {
            hi = 1.0f;
            if (t < hi) {
                do {
                    mid = (lo + hi) / 2.0f;
                    ge = !(coef[3] + mid * (coef[2] + mid * (coef[1] + coef[0] * mid)) < target);
                    if (!ge) {
                        lo = mid;
                    } else {
                        hi = mid;
                    }
                } while (!(hi - lo < 0.001f));
                s = 0.5f * (lo + hi);
            }
        }
        MtxMulVec4_13c900(coef, D_00449D50, v);
        out[i] = coef[3] + s * (coef[2] + s * (coef[1] + coef[0] * s));
    }
    out[3] = 1.0f;
}
