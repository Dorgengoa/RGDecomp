#include "types.h"
#pragma opt_propagation off
typedef struct V { f32 x, y, z, w; } V;

extern void VecSub_1cbd00(V *, s8 *, V *);
extern f32 VecDistSq_1cb3c0(V *, V *);
extern f32 VecDotDiff_1cba40(V *, V *, V *);
extern void VecLerpPoint_1cbac0(V *, s8 *, s8 *, f32);

static inline f32 clamp01(f32 t)
{
    f32 r;
    if (t <= 0.0f) {
        return 0.0f;
    }
    if (!(t < 1.0f)) {
        r = 1.0f;
        goto out;
    }
    return t;
out:
    return r;
}

void PointSegmentDistSq_1c92e0(s8 *arg0, s8 *arg1, V *arg2)
{
    V sp70;
    V sp60;
    V sp50;
    f32 d;
    f32 t;

    VecSub_1cbd00(&sp60, arg0, arg2);
    VecSub_1cbd00(&sp50, arg1, arg2);
    d = VecDistSq_1cb3c0(&sp60, &sp50);
    if (d == 0.0f) {
        t = 0.0f;
    } else {
        t = VecDotDiff_1cba40(&sp60, &sp50, &sp60) / d;
    }
    VecLerpPoint_1cbac0(&sp70, arg1, arg0, clamp01(t));
    VecDistSq_1cb3c0(&sp70, arg2);
}
