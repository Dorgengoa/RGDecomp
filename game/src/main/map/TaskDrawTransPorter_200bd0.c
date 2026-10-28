/* rgp:protos */
#define RGP_SELF_TaskDrawTransPorter_200bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TaskDrawTransPorter_200bd0(void *arg)
{
    void *p;
    void *q;

    p = GetGateObj_1fdac0();
    if (p == 0) return;
    q = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(q, *(s32 *)((s32)p + 0x4DC), 1.0f);
    q = GetMapMgr_201a90();
    MapMgrSlotsShowEntries_1e1660(q);
}
