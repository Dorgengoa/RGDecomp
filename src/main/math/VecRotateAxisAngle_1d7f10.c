#include "types.h"

typedef unsigned __int128 u128;

extern f32 Sinf_128fd0(f32);
extern f32 Cosf_128d30(f32);
extern void VecScale_13be00(f32 *, f32 *, f32);
extern f32 Vu0InnerProduct_13bd60(f32 *, f32 *);
extern void sceVu0OuterProduct(f32 *, f32 *, f32 *);

void VecRotateAxisAngle_1d7f10(f32 *out, f32 *v, f32 *axis, f32 t)
{
    f32 tmp[4];
    f32 cr[4];
    f32 h;
    f32 s;
    f32 k;

    if (t == 0.0f) {
        *(u128 *)out = *(u128 *)v;
        return;
    }
    h = t / 2.0f;
    VecScale_13be00(tmp, axis, Sinf_128fd0(h));
    tmp[3] = Cosf_128d30(h);
    s = tmp[3] * tmp[3] - Vu0InnerProduct_13bd60(tmp, tmp);
    k = 2.0f * Vu0InnerProduct_13bd60(tmp, v);
    sceVu0OuterProduct(cr, tmp, v);
    out[0] = s * v[0] + k * tmp[0] + 2.0f * tmp[3] * cr[0];
    out[1] = s * v[1] + k * tmp[1] + 2.0f * tmp[3] * cr[1];
    out[2] = s * v[2] + k * tmp[2] + 2.0f * tmp[3] * cr[2];
    out[3] = 0.0f;
}
