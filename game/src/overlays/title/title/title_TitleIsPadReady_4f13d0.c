/* rgp:protos */
#define RGP_SELF_title_TitleIsPadReady_4f13d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F13D0 -- lbu $2, -0x4D3C($28) */

extern u8 D_00480434;

u8 title_TitleIsPadReady_4f13d0(void)
{
    return D_00480434;
}
