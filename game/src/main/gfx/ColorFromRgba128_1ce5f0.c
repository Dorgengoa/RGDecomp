/* rgp:protos */
#define RGP_SELF_ColorFromRgba128_1ce5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void ColorFromRgba128_1ce5f0(f32 *out, s32 a, s32 b, s32 c, s32 d)
{
    s32 i;

    out[0] = (f32)a / 128.0f;
    out[1] = (f32)b / 128.0f;
    out[2] = (f32)c / 128.0f;
    out[3] = (f32)d / 128.0f;
    for (i = 0; i < 3; i++) {
        if (out[i] < 0.0f) {
            out[i] = 0.0f;
        }
        if (2.0f <= out[i]) {
            out[i] = 2.0f;
        }
    }
    if (out[3] < 0.0f) {
        out[3] = 0.0f;
    }
    if (1.0f < out[3]) {
        out[3] = 1.0f;
    }
}
