#include "types.h"

typedef struct S1E9650 {
    f32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
    f32 m40;
    f32 m44;
    f32 m48;
} S1E9650;

void AreaBoxCalc_1e9650(S1E9650 *p)
{
    f32 d;

    d = p->m0C - p->m00;
    d = (d < 0.0f) ? -d : d;
    p->m1C = 0.5f * d;
    d = p->m10 - p->m04;
    d = (d < 0.0f) ? -d : d;
    p->m20 = 0.5f * d;
    d = p->m14 - p->m08;
    d = (d < 0.0f) ? -d : d;
    p->m24 = 0.5f * d;
    p->m28 = 0.5f * (p->m0C + p->m00);
    p->m2C = 0.5f * (p->m10 + p->m04);
    p->m30 = 0.5f * (p->m14 + p->m08);
    p->m34 = 1.0f;
    p->m38 = 0.0f;
    p->m3C = 0.0f;
    p->m40 = 1.0f;
    p->m18 = p->m24 * (8.0f * p->m1C * p->m20);
    p->m44 = p->m2C + p->m20;
    p->m48 = p->m2C - p->m20;
}
