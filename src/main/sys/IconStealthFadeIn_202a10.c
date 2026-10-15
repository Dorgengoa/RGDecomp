#include "types.h"

extern f32 D_00481B98;

void IconStealthFadeIn_202a10(f32 x)
{
    if (x <= 0.0f) D_00481B98 = 1.0f;
    else D_00481B98 = 1.0f / x;
}
