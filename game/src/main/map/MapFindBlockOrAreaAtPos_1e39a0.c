/* rgp:protos */
#define RGP_SELF_MapFindBlockOrAreaAtPos_1e39a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
s32 MapFindBlockOrAreaAtPos_1e39a0(s32 p0, s32 p1, float rgp_f0)
{
    s32 v;
    MapFindSmallestBlockAtPos_1e3b50(p0, 0, &v, p1, (float)rgp_f0);
    return v;
}
