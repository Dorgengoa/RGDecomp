/* rgp:protos */
#define RGP_SELF_MapEvQueryCollTrisMaybe_1ff1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapEvQueryCollTrisMaybe_1ff1e0(u8 *a0, s32 a1, s32 a2, void *rgp_a3)
{
    s32 x;
    void *y;

    if (a0 == 0 || a1 <= 0) {
        return 0;
    }
    x = EventCollectCollTris_1ff300((void *)a0, (int)a1, (void *)a2, (void *)rgp_a3);
    y = GetMapMgr_201a90();
    return x + MapSlotsQueryCollTrisMaybe_1e34f0(y, a0 + x * 96, a1 - x, a2);
}
