#include "types.h"
typedef unsigned __int128 u128;

typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 Vu0InnerProduct_13bd60(V4 *, V4 *);
extern void VecNormalize_13bd90(V4 *, V4 *);
extern void VecScale_13be00(V4 *, V4 *, f32);
extern void sceVu0OuterProduct(V4 *, V4 *, V4 *);

void VecRotateAxisPair_1d78a0(V4 *out, V4 *in, V4 *axis, f32 ang)
{
    V4 q0;
    V4 q1;
    V4 q2;
    V4 c0;
    V4 c1;
    V4 c2;
    f32 h;
    f32 a;
    f32 b;

    if (ang == 0.0f) {
        *(u128 *)&out[0] = *(u128 *)&in[0];
    } else {
        h = ang / 2.0f;
        VecScale_13be00(&q0, axis, Sinf_128fd0(h));
        q0.w = Cosf_128d30(h);
        a = q0.w * q0.w - Vu0InnerProduct_13bd60(&q0, &q0);
        b = 2.0f * Vu0InnerProduct_13bd60(&q0, &in[0]);
        sceVu0OuterProduct(&c0, &q0, &in[0]);
        out[0].x = a * in[0].x + b * q0.x + 2.0f * q0.w * c0.x;
        out[0].y = a * in[0].y + b * q0.y + 2.0f * q0.w * c0.y;
        out[0].z = a * in[0].z + b * q0.z + 2.0f * q0.w * c0.z;
        *(s32 *)&out[0].w = 0;
    }
    VecNormalize_13bd90(&out[0], &out[0]);
    if (ang == 0.0f) {
        *(u128 *)&out[1] = *(u128 *)&in[1];
    } else {
        h = ang / 2.0f;
        VecScale_13be00(&q1, axis, Sinf_128fd0(h));
        q1.w = Cosf_128d30(h);
        a = q1.w * q1.w - Vu0InnerProduct_13bd60(&q1, &q1);
        b = 2.0f * Vu0InnerProduct_13bd60(&q1, &in[1]);
        sceVu0OuterProduct(&c1, &q1, &in[1]);
        out[1].x = a * in[1].x + b * q1.x + 2.0f * q1.w * c1.x;
        out[1].y = a * in[1].y + b * q1.y + 2.0f * q1.w * c1.y;
        out[1].z = a * in[1].z + b * q1.z + 2.0f * q1.w * c1.z;
        *(s32 *)&out[1].w = 0;
    }
    VecNormalize_13bd90(&out[1], &out[1]);
    if (ang == 0.0f) {
        *(u128 *)&out[2] = *(u128 *)&in[2];
    } else {
        h = ang / 2.0f;
        VecScale_13be00(&q2, axis, Sinf_128fd0(h));
        q2.w = Cosf_128d30(h);
        a = q2.w * q2.w - Vu0InnerProduct_13bd60(&q2, &q2);
        b = 2.0f * Vu0InnerProduct_13bd60(&q2, &in[2]);
        sceVu0OuterProduct(&c2, &q2, &in[2]);
        out[2].x = a * in[2].x + b * q2.x + 2.0f * q2.w * c2.x;
        out[2].y = a * in[2].y + b * q2.y + 2.0f * q2.w * c2.y;
        out[2].z = a * in[2].z + b * q2.z + 2.0f * q2.w * c2.z;
        *(s32 *)&out[2].w = 0;
    }
    VecNormalize_13bd90(&out[2], &out[2]);
}
