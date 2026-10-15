#include "types.h"

extern void *GetGateObj_1fdac0(void *);
extern void *GetDrawCtx_15de80(void);
extern void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern void *GetMapMgr_201a90(void);
extern void MapMgrSlotsShowEntries_1e1660(void *);

void TaskDrawTransPorter_200bd0(void *arg)
{
    void *p;
    void *q;

    p = GetGateObj_1fdac0(arg);
    if (p == 0) return;
    q = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(q, *(s32 *)((s32)p + 0x4DC), 1.0f);
    q = GetMapMgr_201a90();
    MapMgrSlotsShowEntries_1e1660(q);
}
