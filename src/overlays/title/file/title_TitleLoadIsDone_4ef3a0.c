#include "types.h"

/* title.bin overlay, 0x004EF3A0 -- xori 2 then sltiu 1 -- that is `== 2` */

extern s16 D_004841F0;

s32 title_TitleLoadIsDone_4ef3a0(void)
{
    return D_004841F0 == 2;
}
