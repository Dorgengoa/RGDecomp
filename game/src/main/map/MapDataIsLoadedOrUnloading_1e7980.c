/* rgp:protos */
#define RGP_SELF_MapDataIsLoadedOrUnloading_1e7980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

u8 MapDataIsLoadedOrUnloading_1e7980(s32 p0)
{
    u8 a;

    a = (((signed char)MapDataGetState_1e7a00(p0)) == 2);
    if (a == 0) {
        a = (((signed char)MapDataGetState_1e7a00(p0)) == 3);
    }
    return a;
}
