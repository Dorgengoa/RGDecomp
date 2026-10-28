/* rgp:protos */
#define RGP_SELF_title_TitleLoadIsDone_4ef3a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EF3A0 -- xori 2 then sltiu 1 -- that is `== 2` */

extern s16 D_004841F0;

s32 title_TitleLoadIsDone_4ef3a0(void)
{
    return D_004841F0 == 2;
}
