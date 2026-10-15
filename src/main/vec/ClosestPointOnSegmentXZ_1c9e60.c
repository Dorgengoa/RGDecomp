#include "types.h"

/* Byte-shape clone of already-merged ClosestPointOnSegment_1c9f60 (src/s31a/ClosestPointOnSegment_1c9f60.c),
   found via CENSUS open-vs-CLOSED signature search -- only the two vector
   helper callees differ (VecDistSqXZ_1cb390/VecSubDotXZ_1cba10 instead of
   VecDistSq_1cb3c0/VecDotDiff_1cba40). */

typedef struct V1C9 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V1C9;

extern void VecSub_1cbd00(V1C9 *out, void *p, void *q);
extern f32 VecDistSqXZ_1cb390(V1C9 *a, V1C9 *b);
extern f32 VecSubDotXZ_1cba10(V1C9 *a, V1C9 *b, V1C9 *c);
extern void VecLerpPoint_1cbac0(void *a, void *c, void *b, f32 s);

void ClosestPointOnSegmentXZ_1c9e60(void *a, void *b, void *c, void *d)
{
    V1C9 v70;
    V1C9 v60;
    f32 len;
    f32 t;
    f32 s;

    VecSub_1cbd00(&v70, b, d);
    VecSub_1cbd00(&v60, c, d);
    len = VecDistSqXZ_1cb390(&v70, &v60);
    t = 0.0f;
    if (len == 0.0f) {
        t = 0.0f;
    } else {
        t = VecSubDotXZ_1cba10(&v70, &v60, &v70) / len;
    }
    if (t <= 0.0f) {
        s = 0.0f;
    } else {
        s = (t >= 1.0f) ? 1.0f : t;
    }
    VecLerpPoint_1cbac0(a, c, b, s);
}
