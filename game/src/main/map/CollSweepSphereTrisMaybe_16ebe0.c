/* rgp:protos */
#define RGP_SELF_CollSweepSphereTrisMaybe_16ebe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CollSweepSphereTrisMaybe_16ebe0(u8 *e, s32 n, Vec4 *a, Vec4 *b, s32 max, s32 *idx, Vec4 *hit, s32 sort, s32 mask)
{ RG_VU0_FRAME;
    Vec4 best __attribute__((aligned(16)));
    Vec4 tmax __attribute__((aligned(16)));
    Vec4 tmin __attribute__((aligned(16)));
    Vec4 hi __attribute__((aligned(16)));
    Vec4 lo __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    Vec4 pts[11] __attribute__((aligned(16)));
    Vec4 tmp __attribute__((aligned(16)));
    volatile Vec4 sw __attribute__((aligned(16)));
    u128 tq;
    f32 d;
    f32 *pw;
    s32 k;
    Vec4 *p;
    s32 found;
    s32 i;
    f32 rad;
    s32 j;
    s32 t;
    f32 len;
    s32 off;
    s32 count;

    rad = a->w;
    count = 0;
    len = VecDistance_13d3d0(a, b);
    VecMaxMin_13df70(&hi, &lo, a, b);
    VecSub_13be40(&dir, b, a);
    VecNormalize_13bd90(&dir, &dir);
    hi.x += rad;
    hi.y += rad;
    hi.z += rad;
    lo.x -= rad;
    lo.y -= rad;
    lo.z -= rad;
    for (i = 0; i < n; i++, e += 0x60) {
        if (*(s16 *)(e + 0x46) & mask) {
            continue;
        }
        VecMinMax3_13df40(&tmin, &tmax, e, e + 0x10, e + 0x20);
        if (hi.x < tmax.x || hi.y < tmax.y || hi.z < tmax.z) {
            continue;
        }
        if (!(lo.x <= tmin.x) || !(lo.y <= tmin.y) || !(lo.z <= tmin.z)) {
            continue;
        }
        k = SweptSphereTriContactsMaybe_17f970(a, &dir, e, e + 0x30, pts);
        if (k <= 0) {
            continue;
        }
        found = 0;
        for (j = 0; j < k; j++) {
            off = j * 16;
            VecSub_13be40(&tmp, &pts[j], a);
            d = Vu0InnerProduct_13bd60(&tmp, &dir);
            p = (Vec4 *)((u8 *)pts + off);
            pw = &p->w;
            *pw = d;
            if (d < 0.0f) {
                continue;
            }
            if (!(d <= len)) {
                continue;
            }
            if (found == 0) {
                found = 1;
                best = *p;
            } else if (*pw < best.w) {
                best = *p;
            }
        }
        if (found == 0) {
            continue;
        }
        if (!(count < max)) {
            break;
        }
        idx[count] = i;
        *(u128 *)&hit[count] = *(u128 *)&best;
        count++;
    }
    if (sort == 0) {
        return count;
    }
    if (sort > 0) {
        s32 si;
        s32 sj;
        for (si = 0; si < count - 1; si++) {
            for (sj = si + 1; sj < count; sj++) {
                if (!(hit[si].w <= hit[sj].w)) {
                    t = idx[si];
                    idx[si] = idx[sj];
                    idx[sj] = t;
                    tq = *(u128 *)&hit[si];
                    *(volatile u128 *)&sw = tq;
                    *(u128 *)&hit[si] = *(u128 *)&hit[sj];
                    *(u128 *)&hit[sj] = tq;
                }
            }
        }
    }
    if (sort < 0) {
        s32 si;
        s32 sj;
        for (si = 0; si < count - 1; si++) {
            for (sj = si + 1; sj < count; sj++) {
                if (!(hit[si].w <= hit[sj].w)) {
                    t = idx[si];
                    idx[si] = idx[sj];
                    idx[sj] = t;
                    tq = *(u128 *)&hit[si];
                    *(volatile u128 *)&sw = tq;
                    *(u128 *)&hit[si] = *(u128 *)&hit[sj];
                    *(u128 *)&hit[sj] = tq;
                }
            }
        }
    }
    return count;
}
