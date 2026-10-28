/* rgp:protos */
#define RGP_SELF_VertexDecodeS16_14b410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void VertexDecodeS16_14b410(f32 *out, s16 *src, f32 *scale)
{
    f32 k;
    f32 t;

    k = 0.000030517578125f;
    t = k * (f32)src[0];
    out[0] = t * scale[0];
    t = k * (f32)src[1];
    out[1] = t * scale[1];
    t = k * (f32)src[2];
    out[2] = t * scale[2];
}
