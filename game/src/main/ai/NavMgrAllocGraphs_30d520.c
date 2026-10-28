/* rgp:protos */
#define RGP_SELF_NavMgrAllocGraphs_30d520 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavMgrAllocGraphs_30d520(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    *(s32 *)((u8 *)arg0 + 0x0) = 0;
    *(s32 *)((u8 *)arg0 + 0x4) = 0;
    if (arg1 == 0) {
        return 0;
    }
    temp_2 = ((s32)ConstructNewArray_100710(((s32)BumpArenaAlloc_42e300((arg1 * 0x120) + 0x10, arg2, arg3)), &NavGraphCtor_30d840, &NavGraphDtor_30d5c0, 0x120, arg1));
    *(s32 *)((u8 *)arg0 + 0x0) = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)arg0 + 0x4) = arg1;
    return 1;
}
