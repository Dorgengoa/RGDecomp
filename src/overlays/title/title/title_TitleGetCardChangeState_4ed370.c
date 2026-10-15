#include "types.h"

/* title.bin overlay, 0x004ED370 -- lh $2, -0xFCC($28) */

extern s16 D_004841A4;

s16 title_TitleGetCardChangeState_4ed370(void)
{
    return D_004841A4;
}
