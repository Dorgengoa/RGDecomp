#include "types.h"
#include "vec.h"
#pragma opt_dead_assignments off
#pragma opt_arithtransformation off

typedef Vec4 V17fb20;

extern "C" {
f32 Vu0InnerProduct_13bd60(V17fb20 *, V17fb20 *);
void VecNormalize_13bd90(V17fb20 *, V17fb20 *);
void VecScale_13be00(V17fb20 *, V17fb20 *, f32);
void VecAdd_13be20(V17fb20 *, V17fb20 *, V17fb20 *);
void VecSub_13be40(V17fb20 *, V17fb20 *, V17fb20 *);
f32 VecDistSqXZ_13d330(V17fb20 *, V17fb20 *);
s32 PointInTriangleXz_13d6f0(V17fb20 *, V17fb20 *, V17fb20 *, V17fb20 *);
s32 SegmentSphereIntersectWorld_13d9d0(V17fb20 *, V17fb20 *, V17fb20 *, V17fb20 *);
void sceVu0OuterProduct(V17fb20 *, V17fb20 *, V17fb20 *);
}

static inline void Clr(u8 *p, u32 n)
{
    if (p != 0) {
        while (n != 0) {
            *p = 0;
            n--;
            p++;
        }
    }
}

extern "C" s32 SphereTriIntersectMaybe_17fb20(V17fb20 *arg0, V17fb20 *arg1, V17fb20 *arg2, V17fb20 *arg3) {
    void * arg_h0;

    f32 rr;
    V17fb20 up;
    V17fb20 dir;
    s32 n;
    V17fb20 b;
    V17fb20 a;
    V17fb20 c;
    V17fb20 tri[3];
    s32 i;
    s32 off;
    V17fb20 *src;
    f32 d;
    f32 inv;

    rr = arg0->w * arg0->w;
    Clr((u8 *)&up, 16);
    up.y = arg2->y;
    arg_h0 = &up;
    sceVu0OuterProduct((V17fb20 *)arg_h0, arg2, &up);
    sceVu0OuterProduct(&dir, arg2, &up);
    VecNormalize_13bd90(&dir, &dir);
    VecScale_13be00(&dir, &dir, arg0->w);
    n = 0;
    VecAdd_13be20(&a, arg0, &dir);
    VecSub_13be40(&b, arg0, &dir);
    if (PointInTriangleXz_13d6f0(&a, arg1, arg1 + 1, arg1 + 2) != 0) {
        *arg3 = a;
        n++;
    }
    if (PointInTriangleXz_13d6f0(&b, arg1, arg1 + 1, arg1 + 2) != 0) {
        arg3[n] = b;
        n++;
    }
    src = arg1;
    c = *arg0;
    c.y = 0.0f;
    for (i = 0; i < 3; i++) {
        off = i << 4;
        if (VecDistSqXZ_13d330(arg0, (V17fb20 *)((u8 *)src + off)) <= rr) {
            arg3[n] = *(V17fb20 *)((u8 *)arg1 + off);
            n++;
        }
        tri[i] = arg1[i];
        tri[i].y = 0.0f;
    }
    n += SegmentSphereIntersectWorld_13d9d0(&c, &tri[0], &tri[1], &arg3[n]);
    n += SegmentSphereIntersectWorld_13d9d0(&c, &tri[1], &tri[2], &arg3[n]);
    n += SegmentSphereIntersectWorld_13d9d0(&c, &tri[2], &tri[0], &arg3[n]);
    if (n <= 0) {
        return 0;
    }
    d = Vu0InnerProduct_13bd60(arg2, arg1);
    inv = 1.0f / arg2->y;
    for (i = 0; i < n; i++) {
        arg3[i].y = inv * (d - arg2->x * arg3[i].x - arg2->z * arg3[i].z);
    }
    return n;
}
