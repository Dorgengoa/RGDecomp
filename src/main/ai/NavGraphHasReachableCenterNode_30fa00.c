#include "types.h"

extern u32 NavGraphGetNodeCount_310cb0(s32);
extern s32 NavGraphGetNodes_310cc0(void);
extern s32 NavNodeGetReachable_311960(s32);
extern s32 NavNodeGetFlags_3119a0(s32);

s32 NavGraphHasReachableCenterNode_30fa00(s32 arg0)
{
    s32 rec;
    u32 i;

    rec = NavGraphGetNodes_310cc0();
    if (rec == 0) {
        return 0;
    }
    i = 0;
    while (i < NavGraphGetNodeCount_310cb0(arg0)) {
        if ((NavNodeGetFlags_3119a0(rec) & 1) && (NavNodeGetReachable_311960(rec) != 0)) {
            return 1;
        }
        i += 1;
        rec += 0x24;
    }
    return 0;
}
