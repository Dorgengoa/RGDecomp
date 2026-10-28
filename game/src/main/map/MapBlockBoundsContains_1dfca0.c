/* rgp:protos */
#define RGP_SELF_MapBlockBoundsContains_1dfca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapBlockBoundsContains_1dfca0(u8 *p0, void *p1, f32 x)
{
    if (((unsigned char)MapDataIsEnabled_1e7c20(p0)) == 0) {
        return 0;
    }
    if (MapBlockBoxListHitExclude_1e0220(p0 + 0x54, p1, -x) != 0) {
        return 0;
    }
    return AreaBoxContainsPointThunk_1e93c0(p0 + 0x74, p1, x);
}
