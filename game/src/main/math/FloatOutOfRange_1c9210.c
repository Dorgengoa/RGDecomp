/* rgp:protos */
#define RGP_SELF_FloatOutOfRange_1c9210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

f32 FloatOutOfRange_1c9210(float rgp_f0, float rgp_f1, float rgp_f2)
{
    f32 x;
    f32 z;
    s32 temp_2;

    x = FloatInRange_1c9280((float)rgp_f0, (float)rgp_f1, (float)rgp_f2);
    z = 0.0f;
    temp_2 = (x != z) ^ 1;
    return (f32) (u32) temp_2;
}
