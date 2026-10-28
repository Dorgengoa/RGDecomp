/* rgp:protos */
#define RGP_SELF_GroupTableFindEntryByCode_422910 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
/*rgp*/

s32 GroupTableFindEntryByCode_422910(s32 p0, s32 p1, int rgp_a2, int rgp_a3)
{
    return ((s32)GroupTableFindEntry_422950(p0, (s16)(p1 / 10), (s16)(p1 % 10), (int)rgp_a3));
}
