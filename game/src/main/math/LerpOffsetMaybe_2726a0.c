/* rgp:protos */
#define RGP_SELF_LerpOffsetMaybe_2726a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
f32 LerpOffsetMaybe_2726a0(f32 a, f32 b, f32 c, f32 d)
{
    f32 t;

    t = b - a;
    t = t - c;
    t = t * d;
    t = t + a;
    return t;
}
