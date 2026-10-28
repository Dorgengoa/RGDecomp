/* rgp:protos */
#define RGP_SELF_MapEvCollectCollTrisNearMaybe_1ff130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapEvCollectCollTrisNearMaybe_1ff130(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0) {
    s32 temp_17;

    if ((arg0 == 0) || (arg1 <= 0)) return 0;
    temp_17 = EventCollectCollPolys_1ff3b0(arg0, arg1, arg2, arg4);
    return temp_17 + MapSlotsCollectCollTrisNearMaybe_1e3410(((s32)GetMapMgr_201a90()), arg0 + (temp_17 * 0x60), arg1 - temp_17, arg2, arg3, fparg0);
    return 0;
}
