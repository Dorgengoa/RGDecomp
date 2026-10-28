/* rgp:protos */
#define RGP_SELF_IconStealthFadeOut_2029d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_00481B98;

void IconStealthFadeOut_2029d0(f32 x)
{
    if (x <= 0.0f) D_00481B98 = -1.0f;
    else D_00481B98 = -1.0f / x;
}
