/* rgp:protos */
#define RGP_SELF_VertexDecodeS8_14b3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void VertexDecodeS8_14b3a0(f32 *out, s8 *src, f32 *scale)
{
    f32 k;
    f32 t;

    k = 0.0078125f;
    t = k * (f32)src[0];
    out[0] = t * scale[0];
    t = k * (f32)src[1];
    out[1] = t * scale[1];
    t = k * (f32)src[2];
    out[2] = t * scale[2];
}
