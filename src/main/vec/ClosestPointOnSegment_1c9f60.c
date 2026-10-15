#include "types.h"

typedef struct V1C9 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V1C9;

extern void VecSub_1cbd00(V1C9 *out, void *p, void *q);
extern f32 VecDistSq_1cb3c0(V1C9 *a, V1C9 *b);
extern f32 VecDotDiff_1cba40(V1C9 *a, V1C9 *b, V1C9 *c);
extern void VecLerpPoint_1cbac0(void *a, void *c, void *b, f32 s);

void ClosestPointOnSegment_1c9f60(void *a, void *b, void *c, void *d)
{
    V1C9 v70;
    V1C9 v60;
    f32 len;
    f32 t;
    f32 s;

    VecSub_1cbd00(&v70, b, d);
    VecSub_1cbd00(&v60, c, d);
    len = VecDistSq_1cb3c0(&v70, &v60);
    t = 0.0f;
    if (len == 0.0f) {
        t = 0.0f;
    } else {
        t = VecDotDiff_1cba40(&v70, &v60, &v70) / len;
    }
    if (t <= 0.0f) {
        s = 0.0f;
    } else {
        s = (t >= 1.0f) ? 1.0f : t;
    }
    VecLerpPoint_1cbac0(a, c, b, s);
}
