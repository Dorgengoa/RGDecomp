/* rgp:protos */
#define RGP_SELF_MapBlockBoundsContainsXZ_1dfc20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapBlockBoundsContainsXZ_1dfc20(u8 *p0, void *p1, f32 x)
{
    if (((unsigned char)MapDataIsEnabled_1e7c20(p0)) == 0) {
        return 0;
    }
    if (MapBlockBoxListHitExclude_1e0220(p0 + 0x54, p1, -x) != 0) {
        return 0;
    }
    return AreaBoxContainsPointXZThunk_1e9310(p0 + 0x74, p1, x);
}
