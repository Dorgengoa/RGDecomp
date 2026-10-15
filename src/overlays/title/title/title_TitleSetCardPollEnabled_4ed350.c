#include "types.h"

/* title.bin overlay, 0x004ED350 -- sb $4, -0xFC8($28) */

extern u8 D_004841A8;

void title_TitleSetCardPollEnabled_4ed350(u8 v)
{
    D_004841A8 = v;
}
