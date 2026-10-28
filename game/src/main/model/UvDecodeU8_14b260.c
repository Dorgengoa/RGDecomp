/* rgp:protos */
#define RGP_SELF_UvDecodeU8_14b260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void UvDecodeU8_14b260(f32 *out, u8 *in, f32 *scale)
{
    out[0] = (f32)in[0] * 0.0078125f * scale[0];
    out[1] = (f32)in[1] * 0.0078125f * scale[1];
}
