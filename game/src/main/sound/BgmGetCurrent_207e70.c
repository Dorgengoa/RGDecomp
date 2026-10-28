/* rgp:protos */
#define RGP_SELF_BgmGetCurrent_207e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s16 D_00481C84. */

extern s16 D_00481C84;

s16 BgmGetCurrent_207e70(void)
{
    return D_00481C84;
}
