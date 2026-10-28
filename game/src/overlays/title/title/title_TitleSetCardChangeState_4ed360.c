/* rgp:protos */
#define RGP_SELF_title_TitleSetCardChangeState_4ed360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004ED360 -- sh $4, -0xFCC($28) */

extern s16 D_004841A4;

void title_TitleSetCardChangeState_4ed360(s16 v)
{
    D_004841A4 = v;
}
