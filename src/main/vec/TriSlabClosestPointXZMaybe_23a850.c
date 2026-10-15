#include "types.h"

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Edge { s32 a; s32 b; } Edge;

extern void ClosestPointOnSegmentXZ_1c9e60(V4 *, V4 *, V4 *, V4 *);
extern f32 VecDistSqXZ_1cb390(V4 *, V4 *);
extern void VecLerp_1cbb20(V4 *, V4 *, V4 *, f32);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern Edge D_0045D710[3];

s32 TriSlabClosestPointXZMaybe_23a850(V4 *out, V4 *tri, V4 *org, f32 h)
{
    V4 pts[6];
    V4 tmp;
    f32 y0;
    f32 y1;
    f32 ya;
    f32 yb;
    f32 best;
    f32 d;
    s32 n;
    s32 i;
    V4 *a;
    V4 *b;

    if (h <= 0.0f) {
        return 0;
    }
    y0 = org->y;
    y1 = y0 + h;
    if (tri[0].y < y0 && tri[1].y < y0 && tri[2].y < y0) {
        n = 0;
    } else if (!(tri[0].y <= y1) && !(tri[1].y <= y1) && !(tri[2].y <= y1)) {
        n = 0;
    } else {
        n = 0;
        for (i = 0; i < 3; i++) {
            a = &tri[D_0045D710[i].a];
            ya = a->y;
            b = &tri[D_0045D710[i].b];
            yb = b->y;
            if (ya < yb) {
                if (ya <= y1) {
                    if (!(ya < y0)) {
                        VecCopy_1cbe30(&pts[n], a);
                        n++;
                    } else if (!(yb <= y0)) {
                        VecLerp_1cbb20(&pts[n], b, a, (y0 - ya) / (yb - ya));
                        n++;
                    } else {
                        continue;
                    }
                    if (!(b->y <= y1)) {
                        VecLerp_1cbb20(&pts[n], b, a, (y1 - a->y) / (b->y - a->y));
                        n++;
                    }
                }
            } else if (!(ya < y0)) {
                if (ya <= y1) {
                    VecCopy_1cbe30(&pts[n], a);
                    n++;
                } else if (yb < y1) {
                    VecLerp_1cbb20(&pts[n], b, a, (y1 - ya) / (yb - ya));
                    n++;
                } else {
                    continue;
                }
                if (b->y < y0) {
                    VecLerp_1cbb20(&pts[n], b, a, (y0 - a->y) / (b->y - a->y));
                    n++;
                }
            }
        }
    }
    if (n < 3) {
        return 0;
    }
    ClosestPointOnSegmentXZ_1c9e60(out, &pts[n - 1], &pts[0], org);
    best = VecDistSqXZ_1cb390(out, org);
    for (i = 1; i < n; i++) {
        ClosestPointOnSegmentXZ_1c9e60(&tmp, &pts[i - 1], &pts[i], org);
        d = VecDistSqXZ_1cb390(&tmp, org);
        if (d < best) {
            best = d;
            VecCopy_1cbe30(out, &tmp);
        }
    }
    return 1;
}
