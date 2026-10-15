#include "types.h"
#include "vec.h"

extern s32 DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
extern f32 D_0047D248;
extern f32 D_0047D1E0;
extern Vec4 D_00481480 __attribute__((section(".sdata")));
extern Vec4 D_00481490 __attribute__((section(".sdata")));

void SoundCalcDistVolPan_1b7de0(f32 *out0, f32 *out1, Vec4 *pos, f32 lo, f32 hi)
{
    Vec4 dir;
    Vec4 side;
    s32 lock;
    f32 d;
    f32 v;
    f32 f;
    f32 sq;
    s32 sign;

    lock = DisableIntr_120660();
    d = VecDistance_13d3d0(pos, &D_00481480);
    v = 1.0f - (d - lo) / (hi - lo);
    if (!(d <= hi)) {
        v = 0.0f;
    }
    if (d < lo) {
        v = 1.0f;
    }
    *out0 = v;
    *out1 = 0.0f;
    *(u128 *)&dir = *(u128 *)&D_00481490;
    dir.y = 0.0f;
    VecNormalize_13bd90(&dir, &dir);
    side.y = 0.0f;
    side.x = dir.z;
    side.z = -dir.x;
    VecSub_13be40(&dir, pos, &D_00481480);
    dir.y = 0.0f;
    VecNormalize_13bd90(&dir, &dir);
    f = -Vu0InnerProduct_13bd60(&dir, &side);
    sign = 1;
    if (f < 0.0f) {
        sign = -1;
    }
    f = (f < 0.0f) ? -f : f;
    sq = f * f;
    sq = sq * sq;
    v = D_0047D248 * ((f32)sign * sq);
    *out1 = v;
    if (v < 0.0f) {
        v = -v;
    }
    *out0 *= 1.0f + D_0047D1E0 * v;
    if (lock) {
        EnableIntr_1206b0();
    }
}
