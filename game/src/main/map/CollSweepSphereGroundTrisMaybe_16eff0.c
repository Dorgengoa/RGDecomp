/* rgp:protos */
#define RGP_SELF_CollSweepSphereGroundTrisMaybe_16eff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef rg_u128 u128;

typedef union Vec {
    u128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
} Vec;

typedef struct Tri {
    Vec v0;
    Vec v1;
    Vec v2;
    Vec n;
    u8 pad40[6];
    s16 flags;
    u8 pad48[0x18];
} Tri;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1DC;

s32 CollSweepSphereGroundTrisMaybe_16eff0(Tri *tri, s32 count, Vec *ray, s32 max, s32 *idx, Vec *pts, s32 sort, s32 mask, f32 ext) {
    Vec best __attribute__((aligned(16)));
    Vec cmax __attribute__((aligned(16)));
    Vec cmin __attribute__((aligned(16)));
    Vec hi __attribute__((aligned(16)));
    Vec lo __attribute__((aligned(16)));
    Vec p __attribute__((aligned(16)));
    Vec hits[11] __attribute__((aligned(16)));
    volatile Vec tmp __attribute__((aligned(16)));
    u128 tq;
    f32 r;
    s32 i;
    s32 found;
    f32 f;
    s32 n;
    f32 y;
    f32 yhi;
    f32 ylo;
    s32 k;
    s32 have;
    Vec *o;
    s32 a;
    s32 b;
    s32 t;


    r = ray->f.w;
    found = 0;
    p.q = ray->q;
    p.f.y += ext;
    VecMaxMin_13df70(&hi, &lo, ray, &p);
    hi.f.x += r;
    hi.f.z += r;
    lo.f.x -= r;
    lo.f.z -= r;
    for (i = 0; i < count; i++, tri++) {
        if (tri->flags & mask) {
            continue;
        }
        f = tri->n.f.y;
        f = (f < 0.0f) ? -f : f;
        if (f < D_0047D1DC) {
            continue;
        }
        VecMinMax3_13df40(&cmin, &cmax, &tri->v0, &tri->v1, &tri->v2);
        if (hi.f.x < cmax.f.x) {
            continue;
        }
        if (hi.f.y < cmax.f.y) {
            continue;
        }
        if (hi.f.z < cmax.f.z) {
            continue;
        }
        if (!(lo.f.x <= cmin.f.x)) {
            continue;
        }
        if (!(lo.f.y <= cmin.f.y)) {
            continue;
        }
        if (!(lo.f.z <= cmin.f.z)) {
            continue;
        }
        n = SphereTriIntersectMaybe_17fb20(ray, tri, &tri->n, hits);
        if (n <= 0) {
            continue;
        }
        have = 0;
        ylo = lo.f.y;
        yhi = hi.f.y;
        for (k = 0; k < n; k++) {
            y = hits[k].f.y;
            if (have != 0) {
                y = y;
            }
            if (y <= yhi && !(y < ylo)) {
                if (have == 0) {
                    best.q = hits[k].q;
                    have = 1;
                } else if (!(y <= best.f.y)) {
                    best.q = hits[k].q;
                }
            }
        }
        if (have == 0) {
            continue;
        }
        if (!(found < max)) {
            break;
        }
        idx[found] = i;
        o = &pts[found];
        o->q = best.q;
        o->f.w = VecDistance_13d3d0(ray, &best);
        found++;
    }
    if (sort == 0) {
        return found;
    }
    {
        if (sort > 0) {
            for (a = 0; a < found - 1; a++) {
                for (b = a + 1; b < found; b++) {
                    if (!(pts[a].f.w <= pts[b].f.w)) {
                        t = idx[a];
                        idx[a] = idx[b];
                        idx[b] = t;
                        tq = pts[a].q;
                        tmp.q = tq;
                        pts[a].q = pts[b].q;
                        pts[b].q = tq;
                    }
                }
            }
        }
        if (sort < 0) {
            for (a = 0; a < found - 1; a++) {
                for (b = a + 1; b < found; b++) {
                    if (!(pts[a].f.w <= pts[b].f.w)) {
                        t = idx[a];
                        idx[a] = idx[b];
                        idx[b] = t;
                        tq = pts[a].q;
                        tmp.q = tq;
                        pts[a].q = pts[b].q;
                        pts[b].q = tq;
                    }
                }
            }
        }
    }
    return found;
}
