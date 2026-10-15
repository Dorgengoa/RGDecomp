#include "types.h"

typedef struct { f32 x, y, z, w; } V_0014b720;

extern void SplineEvalBezierSolveTime_14b8a0(void *, V_0014b720 *, V_0014b720 *);

void SplineEvalBezierScalar_14b720(void *out, f32 *s1, f32 *s2)
{
    V_0014b720 a[5];
    V_0014b720 b[5];

    a[0].x = s1[0];
    a[1].x = s1[1];
    a[2].x = s1[2];
    a[3].x = s1[3];
    a[4].x = s1[4];
    b[0].x = s2[0];
    b[1].x = s2[1];
    b[2].x = s2[2];
    b[3].x = s2[3];
    b[4].x = s2[4];
    SplineEvalBezierSolveTime_14b8a0(out, a, b);
}
