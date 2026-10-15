/* main s27m: CLOSED -- NavXformPointToLocal_310d50 takes (arg0, buf, arg1); the arg3 test is
   `if (arg3 != 0) {...} else {...}` (arm order). */
#include "types.h"

extern void VecCopy_1cbe30(void *);
extern s32 NavGraphGetNode_310cd0(s32, s32);
extern void NavXformPointToLocal_310d50(s32, void *, s32);
extern s32 NavEdgeGetNodeB_3116f0(s32);
extern s32 NavEdgeGetNodeA_311700(s32);
extern f32 NavNodeDistSq_3118d0(s32, void *);

s32 NavEdgeNearestNode_30f940(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 sp40[0x10];
    f32 temp_f20;
    s32 temp_17;
    s32 temp_16;

    if (arg2 == 0) {
        return 0;
    }
    if (arg3 != 0) {
        VecCopy_1cbe30(sp40);
    } else {
        NavXformPointToLocal_310d50(arg0, sp40, arg1);
    }
    temp_16 = NavGraphGetNode_310cd0(arg0, NavEdgeGetNodeA_311700(arg2));
    temp_17 = NavGraphGetNode_310cd0(arg0, NavEdgeGetNodeB_3116f0(arg2));
    temp_f20 = NavNodeDistSq_3118d0(temp_16, sp40);
    if (!(!(temp_f20 < NavNodeDistSq_3118d0(temp_17, sp40)))) {
        return temp_16;
    }
    return temp_17;
    return temp_16;
}
