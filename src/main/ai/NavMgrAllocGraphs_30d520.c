#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

extern s32 ConstructNewArray_100710(s32 arg0, void *arg1, void *arg2, s32 arg3, s32 arg4);
extern s32 BumpArenaAlloc_42e300(s32 arg0, s32 arg1, s32 arg2);
extern void NavGraphDtor_30d5c0(void);
extern void NavGraphCtor_30d840(void);

s32 NavMgrAllocGraphs_30d520(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    *(s32 *)((u8 *)arg0 + 0x0) = 0;
    *(s32 *)((u8 *)arg0 + 0x4) = 0;
    if (arg1 == 0) {
        return 0;
    }
    temp_2 = ConstructNewArray_100710(BumpArenaAlloc_42e300((arg1 * 0x120) + 0x10, arg2, arg3), &NavGraphCtor_30d840, &NavGraphDtor_30d5c0, 0x120, arg1);
    *(s32 *)((u8 *)arg0 + 0x0) = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)arg0 + 0x4) = arg1;
    return 1;
}
