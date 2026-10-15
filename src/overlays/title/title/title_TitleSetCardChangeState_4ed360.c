#include "types.h"

/* title.bin overlay, 0x004ED360 -- sh $4, -0xFCC($28) */

extern s16 D_004841A4;

void title_TitleSetCardChangeState_4ed360(s16 v)
{
    D_004841A4 = v;
}
