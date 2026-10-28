/* rgp:protos */
#define RGP_SELF_GetEntryTableGlobal_32c2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_00482B90. */

extern s32 D_00482B90;

s32 GetEntryTableGlobal_32c2e0(void)
{
    return D_00482B90;
}
