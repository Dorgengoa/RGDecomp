#include "types.h"

typedef struct {
    u8 pad0[0x18];
    f32 p[3];
    f32 ax[3];
    f32 ay[3];
    f32 az[3];
} Box;

s32 XformPointInBoxSide_2e77e0(Box *arg0, f32 *arg1, f32 f12, f32 f13, f32 f14, f32 f15)
{
    f32 d[3];
    f32 x;
    f32 y;
    f32 z;
    f32 a;

    {
        u8 *p_ = (u8 *)d;
        u32 n_ = 12;
        if (p_) while (n_) { *p_ = 0; n_--; p_++; }
    }
    d[0] = arg1[0] - arg0->p[0];
    d[1] = arg1[1] - arg0->p[1];
    d[2] = arg1[2] - arg0->p[2];
    x = arg0->ax[0] * d[0] + arg0->ax[1] * d[1] + arg0->ax[2] * d[2];
    if (x < 0.0f) {
        x = -x;
    }
    if (f13 < 0.0f) {
        f13 = -f13;
    }
    if (!(x <= f13)) {
        return 0;
    }
    y = arg0->ay[0] * d[0] + arg0->ay[1] * d[1] + arg0->ay[2] * d[2];
    if (y < f14 || f15 < y) {
        return 0;
    }
    z = arg0->az[0] * d[0] + arg0->az[1] * d[1] + arg0->az[2] * d[2];
    a = (z < 0.0f) ? -z : z;
    if (f12 < 0.0f) {
        f12 = -f12;
    }
    if (!(a <= f12)) {
        return 0;
    }
    if (z >= 0.0f) {
        return 1;
    }
    return 2;
}
