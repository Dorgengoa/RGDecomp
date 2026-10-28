/* rgp:protos */
#define RGP_SELF_MapGetActiveArea_1e56e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapGetActiveArea_1e56e0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = MapGetAreaSlot2_1e5740(p0);
    if (r0 != 0) {
        r1 = ((unsigned char)MapDataIsLoaded_1e79d0(r0));
        if (r1 != 0) {
            return r0;
        }
    }
    return MapGetFirstAreaSlot_1e5760(p0);
}
