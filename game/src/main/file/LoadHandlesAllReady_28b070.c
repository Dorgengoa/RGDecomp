/* rgp:protos */
#define RGP_SELF_LoadHandlesAllReady_28b070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

u8 LoadHandlesAllReady_28b070(s32 p0, s32 p1)
{
    s32 l1;
    s32 l0;
    s32 r2;

    l1 = 0;
    l0 = 0;
    while (l0 < p1) {
        r2 = ((unsigned char)LoadHandleIsReady_28b200((p0 + (((l0 << 3) - l0) << 3))));
        if (r2 != 0) {
            l1 = (l1 + 1);
        }
        l0 = (l0 + 1);
    }
    return (l1 == p1);
}
