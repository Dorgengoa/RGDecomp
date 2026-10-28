/* rgp:protos */
#define RGP_SELF_AxisAngleBetweenVecs_1d7da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 sqrtf(f32);

void AxisAngleBetweenVecs_1d7da0(V4 *arg0, f32 *arg1, s32 arg2, s32 arg3) {
    V4 q __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    f32 d;
    f32 s;
    f32 t;

    VecNormalize_13bd90(&a, arg2);
    VecNormalize_13bd90(&b, arg3);
    sceVu0OuterProduct(&c, &a, &b);
    d = 2.0f * (1.0f + sceVu0InnerProduct(&a, &b));
    if (d <= 0.0f) {
        q.x = 0.0f;
        q.y = 0.0f;
        q.z = 0.0f;
        q.w = 0.0f;
    } else {
        s = sqrtf(d);
        VecScale_13be00(&q, &c, 1.0f / s);
        q.w = s / 2.0f;
    }
    t = 2.0f * Acosf_129178(q.w);
    *arg1 = t;
    VecScale_13be00(arg0, &q, 1.0f / dptofp(Sin_128880(fptodp(t / 2.0f))));
    arg0->w = 1.0f;
}
