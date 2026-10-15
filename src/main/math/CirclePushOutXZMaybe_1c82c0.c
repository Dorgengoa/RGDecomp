#include "types.h"
#include "vec.h"

extern f32 sqrtf(f32);
extern f32 VecLengthSq_1cb470(Vec4 *);
extern f32 VecDot3_1cba90(Vec4 *, Vec4 *);
extern void VecScaleDir_1cbc80(Vec4 *, Vec4 *, f32);
extern void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
extern f32 D_0047DB48;

u8 CirclePushOutXZMaybe_1c82c0(Vec4 *out, Vec4 *a, Vec4 *b, f32 r0, f32 r1)
{
    Vec4 d = {0};
    Vec4 oc;
    f32 len;
    f32 dist;
    f32 rr;
    f32 dot;
    f32 t;
    u8 ret;

    d.x = b->x - a->x;
    d.z = b->z - a->z;
    if (VecLengthSq_1cb470(&d) <= D_0047DB48) {
        d.z = 1.0f;
    }
    len = VecLengthSq_1cb470(&d);
    if (len <= D_0047DB48) {
        t = 0.0f;
    } else {
        VecSub_1cbd00(&oc, b, a);
        dist = VecLengthSq_1cb470(&oc);
        rr = (r1 + r0) * (r1 + r0);
        if (!(dist < rr)) {
            t = 0.0f;
        } else {
            dot = VecDot3_1cba90(&d, &oc);
            t = (sqrtf(dot * dot - len * (dist - rr)) - dot) / len;
        }
    }
    if (t <= 0.0f) {
        ret = 0;
    } else {
        VecScaleDir_1cbc80(out, &d, t);
        ret = 1;
    }
    return ret;
}
