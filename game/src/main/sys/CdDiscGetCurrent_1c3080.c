/* rgp:protos */
#define RGP_SELF_CdDiscGetCurrent_1c3080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_00481560. */

extern s32 D_00481560;

s32 CdDiscGetCurrent_1c3080(void)
{
    return D_00481560;
}
