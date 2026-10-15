#include "types.h"

extern void NavMgrPoolReset_2d1980(s32);
extern void NavMgrPoolClear_2d1ba0(s32);
extern void NavMgrClearActive_30d470(s32);
extern s32 PtrArrayAlloc_30d490(s32, s32, s32, s32);
extern s32 NavMgrAllocGraphs_30d520(s32, s32, s32, s32);
extern void NavMgrReset_30da70(void);
extern s32 BitArrayAlloc_42ced0(s32, s32, s32, s32);
extern void UskMemoryRefSet_42cff0(s32, s32);
extern void UskMemoryLeaseEnd_42d6b0(s32);
extern void UskMemoryLeaseBegin_42d740(s32, s32);
extern s32 UskMemoryGetStack_42d890(s32);

s32 NavMgrInit_30d360(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_16;

    NavMgrReset_30da70();
    if (arg2 == 0) {
        return 0;
    }
    UskMemoryLeaseBegin_42d740(arg2, 0);
    temp_16 = UskMemoryGetStack_42d890(arg2);
    NavMgrPoolClear_2d1ba0(arg0 + 4);
    if (arg1 > 0 && temp_16 != 0) {
        if (NavMgrAllocGraphs_30d520(arg0 + 4, arg1, temp_16, 0x10) != 0 &&
            PtrArrayAlloc_30d490(arg0 + 0xC, arg1, temp_16, 4) != 0 &&
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
