/* rgp:protos */
#define RGP_SELF_GetVsyncCount_15df00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_004810C4. */

extern s32 D_004810C4;

s32 GetVsyncCount_15df00(void)
{
    return D_004810C4;
}
