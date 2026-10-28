/* rgp:protos */
#define RGP_SELF_NavMgrInit_30d360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavMgrInit_30d360(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_16;

    NavMgrReset_30da70((void *)arg0);
    if (arg2 == 0) {
        return 0;
    }
    UskMemoryLeaseBegin_42d740(arg2, 0);
    temp_16 = ((s32)UskMemoryGetStack_42d890(arg2));
    NavMgrPoolClear_2d1ba0(arg0 + 4);
    if (arg1 > 0 && temp_16 != 0) {
        if (NavMgrAllocGraphs_30d520(arg0 + 4, arg1, temp_16, 0x10) != 0 &&
            ((unsigned char)PtrArrayAlloc_30d490(arg0 + 0xC, arg1, temp_16, 4)) != 0 &&
            BitArrayAlloc_42ced0(arg0 + 0x1C, arg1, temp_16, 4) != 0) {
            NavMgrClearActive_30d470(arg0 + 4);
        } else {
            NavMgrPoolReset_2d1980(arg0 + 4);
        }
    }
    UskMemoryLeaseEnd_42d6b0(arg2);
    UskMemoryRefSet_42cff0(arg0, arg2);
    return 1;
}
