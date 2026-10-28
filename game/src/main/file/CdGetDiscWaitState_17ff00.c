/* rgp:protos */
#define RGP_SELF_CdGetDiscWaitState_17ff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_00481210. */

extern s32 D_00481210;

s32 CdGetDiscWaitState_17ff00(void)
{
    return D_00481210;
}
