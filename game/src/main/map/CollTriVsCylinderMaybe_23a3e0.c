/* rgp:protos */
#define RGP_SELF_CollTriVsCylinderMaybe_23a3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct Edge {
    s32 a;
    s32 b;
} Edge;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Edge D_0045D710[];

s32 CollTriVsCylinderMaybe_23a3e0(V4 *tri, V4 *pt, f32 h, f32 r)
{
    V4 poly[6] __attribute__((aligned(16)));
    V4 nv __attribute__((aligned(16)));
    V4 m __attribute__((aligned(16)));
    f32 lo;
    f32 hi;
    f32 r2;
    s32 k;
    V4 *p;
    V4 *q;
    s32 n;
    s32 i;
    V4 *a;
    s32 j;
    V4 *b;

    if (h <= 0.0f) {
        return 0;
    }
    lo = pt->y;
    hi = lo + h;
    if (tri[0].y < lo && tri[1].y < lo && tri[2].y < lo) {
        n = 0;
        goto done;
    }
    if (!(tri[0].y <= hi || tri[1].y <= hi || tri[2].y <= hi)) {
        n = 0;
        goto done;
    }
    n = 0;
    for (i = 0; i < 3; i++) {
        a = &tri[D_0045D710[i].a];
        b = &tri[D_0045D710[i].b];
        if (a->y < b->y) {
            if (!(a->y <= hi)) {
                continue;
            }
            if (!(a->y < lo)) {
                VecCopy_1cbe30(&poly[n], a);
                n++;
            } else {
                if (b->y <= lo) {
                    continue;
                }
                VecLerp_1cbb20(&poly[n], b, a, (lo - a->y) / (b->y - a->y));
                n++;
            }
            if (b->y <= hi) {
                continue;
            }
            VecLerp_1cbb20(&poly[n], b, a, (hi - a->y) / (b->y - a->y));
            n++;
        } else {
            if (a->y < lo) {
                continue;
            }
            if (a->y <= hi) {
                VecCopy_1cbe30(&poly[n], a);
                n++;
            } else {
                if (!(b->y < hi)) {
                    continue;
                }
                VecLerp_1cbb20(&poly[n], b, a, (hi - a->y) / (b->y - a->y));
                n++;
            }
            if (!(b->y < lo)) {
                continue;
            }
            VecLerp_1cbb20(&poly[n], b, a, (lo - a->y) / (b->y - a->y));
            n++;
        }
    }
done:
    if (n < 3) {
        return 0;
    }
    r2 = r * r;
    ClosestPointOnSegmentXZ_1c9e60(&nv, &poly[n - 1], &poly[0], pt);
    if (VecDistSqXZ_1cb390(&nv, pt) <= r2) {
        return 1;
    }
    for (j = 1; j < n; j++) {
        ClosestPointOnSegmentXZ_1c9e60(&nv, &poly[j - 1], &poly[j], pt);
        if (VecDistSqXZ_1cb390(&nv, pt) <= r2) {
            return 1;
        }
    }
    for (i = 0; i < n; i++) {
        poly[i].y = pt->y;
    }
    for (k = 2; k < n; k++) {
        p = &poly[k];
        if (poly[0].x == p[-1].x && poly[0].x == p->x) {
            continue;
        }
        if (poly[0].z == p[-1].z && poly[0].z == p->z) {
            continue;
        }
        q = &poly[k - 1];
        TriNormal_1cb970(&m, &poly[0], q, p);
        if (VecLengthSq_1cb470(&m, 0) < 1.0f) {
            continue;
        }
        ClosestPointOnTriWithNormal_1c9ce0(&nv, &poly[0], q, p, &m, pt);
        if (VecDistSqXZ_1cb390(&nv, pt) <= r2) {
            return 1;
        }
    }
    return 0;
}
