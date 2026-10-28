/* rgp:protos */
#define RGP_SELF_VecRotateAxisAngle_1d7f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void VecRotateAxisAngle_1d7f10(f32 *out, f32 *v, f32 *axis, f32 t)
{ RG_VU0_FRAME;
    f32 tmp[4] __attribute__((aligned(16)));
    f32 cr[4] __attribute__((aligned(16)));
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
