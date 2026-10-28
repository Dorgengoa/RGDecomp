/* rgp:protos */
#define RGP_SELF_CollSpherePushOutMaybe_16dea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"
#define CPY(a, b) (*(u128 *)&(a) = *(u128 *)&(b))

typedef struct Tri {
    Vec4 v[3];
    Vec4 n;
    s16 pad40[3];
    s16 flags;
    u8 pad48[0x18];
} Tri;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CollSpherePushOutMaybe_16dea0(Tri *tri0, s32 count, Vec4 *pos, Vec4 *out, s32 mask, f32 r) { RG_VU0_FRAME;
    Vec4 p __attribute__((aligned(16)));
    Vec4 hi __attribute__((aligned(16)));
    Vec4 lo __attribute__((aligned(16)));
    Vec4 bmax __attribute__((aligned(16)));
    Vec4 bmin __attribute__((aligned(16)));
    Vec4 smax __attribute__((aligned(16)));
    Vec4 smin __attribute__((aligned(16)));
    Vec4 n __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 e __attribute__((aligned(16)));
    Vec4 acc __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 pts[2] __attribute__((aligned(16)));
    Vec4 mid __attribute__((aligned(16)));
    s32 i;
    Tri *tri;
    s32 hits;
    s32 j;
    s32 res;
    f32 rad;
    f32 dist;
    f32 ad;
    f32 len;

    p = *pos;
    p.w = r;
    p.y += r;
    *out = *pos;
    VEC4_ZERO(smax);
    VEC4_ZERO(smin);
    CPY(bmax, p);
    CPY(bmin, p);
    bmax.x += p.w;
    bmax.y += p.w;
    bmax.z += p.w;
    bmin.x -= p.w;
    bmin.y -= p.w;
    bmin.z -= p.w;

    tri = tri0;
    for (i = 0; i < count; i++, tri++) {
        if (tri->flags & mask) continue;
        VecMinMax3_13df40(&lo, &hi, &tri->v[0], &tri->v[1], &tri->v[2]);
        if (bmax.x < hi.x) continue;
        if (bmax.y < hi.y) continue;
        if (bmax.z < hi.z) continue;
        if (!(bmin.x <= lo.x)) continue;
        if (!(bmin.y <= lo.y)) continue;
        if (!(bmin.z <= lo.z)) continue;
        VecNormalize_13bd90(&n, &tri->n);
        rad = p.w;
        VecSub_13be40(&d, &p, &tri->v[0]);
        ad = dist = Vu0InnerProduct_13bd60(&n, &d);
        if (dist < 0.0f) ad = -dist;
        if (!(ad <= rad)) continue;
        CPY(d, tri->n);
        VecScale_13be00(&d, &d, -(f32)dist);
        CPY(e, d);
        VecAddInPlace_13e070(&d, &p);
        if (PointInTriangle_13d720(&d, &tri->v[0], &tri->v[1], &tri->v[2], &tri->n) != 0) {
            VecNormalize_13bd90(&e, &e);
            VecScale_13be00(&e, &e, -(rad - (dist < 0.0f ? -dist : dist)));
            VecMax_13dfe0(&smin, &smin, &e);
            VecMin_13df90(&smax, &smax, &e);
        } else {
            VEC4_ZERO(acc);
            hits = 0;
            for (j = 0; j < 3; j++) {
                res = SegmentSphereIntersectWorld_13d9d0(&p, &tri->v[j], &tri->v[(j + 1) % 3], pts);
                if (res > 0) {
                    CPY(mid, pts[0]);
                    if (res >= 2) {
                        VecAddInPlace_13e070(&mid, &pts[1]);
                        VecScale_13be00(&mid, &mid, 0.5f);
                    }
                    VecSub_13be40(&c, &p, &mid);
                    dist = VecLength_13d4a0(&c);
                    VecNormalize_13bd90(&c, &c);
                    VecScale_13be00(&c, &c, rad - dist);
                    VecAddInPlace_13e070(&acc, &c);
                    hits++;
                }
            }
            if (hits > 0) {
                VecScale_13be00(&acc, &acc, 1.0f / (f32)hits);
                VecMax_13dfe0(&smin, &smin, &acc);
                VecMin_13df90(&smax, &smax, &acc);
            }
        }
    }
    out->x += 0.5f * (smin.x + smax.x);
    out->z += 0.5f * (smin.z + smax.z);
    return 1;
}
