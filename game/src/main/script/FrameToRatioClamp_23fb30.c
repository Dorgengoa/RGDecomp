/* rgp:protos */
#define RGP_SELF_FrameToRatioClamp_23fb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

f32 FrameToRatioClamp_23fb30(s32 n, f32 v)
{
    if (n <= 0) return v;
    v = v / (f32)n;
    if (v < 0.0f) v = 0.0f;
    if (v > 1.0f) v = 1.0f;
    return v;
}
