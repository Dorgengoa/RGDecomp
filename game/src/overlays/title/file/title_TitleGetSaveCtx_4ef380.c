/* rgp:protos */
#define RGP_SELF_title_TitleGetSaveCtx_4ef380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EF380 -- lw $2, -0xFEC($28) */

extern s32 D_00484184;

s32 title_TitleGetSaveCtx_4ef380(void)
{
    return D_00484184;
}
