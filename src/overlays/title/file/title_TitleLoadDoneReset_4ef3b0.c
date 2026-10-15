#include "types.h"

/* title.bin overlay, 0x004EF3B0 -- sh $0, -0xF80($28) */

extern s16 D_004841F0;

void title_TitleLoadDoneReset_4ef3b0(void)
{
    D_004841F0 = 0;
}
