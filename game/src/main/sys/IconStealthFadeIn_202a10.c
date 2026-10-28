/* rgp:protos */
#define RGP_SELF_IconStealthFadeIn_202a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_00481B98;

void IconStealthFadeIn_202a10(f32 x)
{
    if (x <= 0.0f) D_00481B98 = 1.0f;
    else D_00481B98 = 1.0f / x;
}
