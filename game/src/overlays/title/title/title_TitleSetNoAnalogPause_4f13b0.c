/* rgp:protos */
#define RGP_SELF_title_TitleSetNoAnalogPause_4f13b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F13B0 -- sw $4, -0xEDC($28) */

extern s32 D_00484294;

void title_TitleSetNoAnalogPause_4f13b0(s32 v)
{
    D_00484294 = v;
}
