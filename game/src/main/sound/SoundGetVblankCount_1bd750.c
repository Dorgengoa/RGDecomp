/* rgp:protos */
#define RGP_SELF_SoundGetVblankCount_1bd750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_00481508. */

extern s32 D_00481508;

s32 SoundGetVblankCount_1bd750(void)
{
    return D_00481508;
}
