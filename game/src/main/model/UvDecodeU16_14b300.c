/* rgp:protos */
#define RGP_SELF_UvDecodeU16_14b300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void UvDecodeU16_14b300(f32 *out, u16 *ang, f32 *scale)
{
    u32 a;
    f32 t;

    a = ang[0];
    t = 0.000030517578125f * (f32)a;
    out[0] = t * scale[0];
    a = ang[1];
    t = 0.000030517578125f * (f32)a;
    out[1] = t * scale[1];
}
