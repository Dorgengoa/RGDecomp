/* rgp:protos */
#define RGP_SELF_MapEvCollectCollPolysMaybe_1ff270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapEvCollectCollPolysMaybe_1ff270(u8 *a0, s32 a1, s32 a2, void *rgp_a3)
{
    s32 x;
    void *y;

    if (a0 == 0 || a1 <= 0) {
        return 0;
    }
    x = EventCollectCollPolys_1ff3b0((void *)a0, (int)a1, (void *)a2, (void *)rgp_a3);
    y = GetMapMgr_201a90();
    return x + MapSlotsCollectCollTrisMaybe_1e35b0(y, a0 + x * 96, a1 - x, a2);
}
