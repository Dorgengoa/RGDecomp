#include "types.h"

extern f32 ArcInitialVelocity_259070(f32, f32, f32, f32);

void JumpArcLerp_258f70(f32 *p0, const f32 *p1, const f32 *p2, f32 p3, f32 p4, f32 p5)
{
    f32 y;
    f32 t;
    s32 n;
    s32 i;

    y = p1[1];
    t = ArcInitialVelocity_259070(y, p2[1], p3, 1.0f + p4);
    n = (s32)p5;
    for (i = 0; i < n; i++) {
        t = t + p3;
        y = y + t;
    }
    p0[0] = p1[0] + p5 * (p2[0] - p1[0]) / p4;
    p0[1] = y;
    p0[2] = p1[2] + p5 * (p2[2] - p1[2]) / p4;
    p0[3] = 1.0f;
}
