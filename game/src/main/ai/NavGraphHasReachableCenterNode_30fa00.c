/* rgp:protos */
#define RGP_SELF_NavGraphHasReachableCenterNode_30fa00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavGraphHasReachableCenterNode_30fa00(s32 arg0)
{
    s32 rec;
    u32 i;

    rec = NavGraphGetNodes_310cc0((void *)arg0);
    if (rec == 0) {
        return 0;
    }
    i = 0;
    while (i < ((unsigned short)NavGraphGetNodeCount_310cb0(arg0))) {
        if ((NavNodeGetFlags_3119a0(rec) & 1) && (((short)NavNodeGetReachable_311960(rec)) != 0)) {
            return 1;
        }
        i += 1;
        rec += 0x24;
    }
    return 0;
}
