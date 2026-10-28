/* rgp:protos */
#define RGP_SELF_SystemVmGetRunningEntry_250b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_00481F7C. */

extern s32 D_00481F7C;

s32 SystemVmGetRunningEntry_250b70(void)
{
    return D_00481F7C;
}
