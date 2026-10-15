#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern void MapMgrWarpMenuDraw_1e2680(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawMenuWarp_1ffb60(void)
{
    s32 r0;

    r0 = GetMapMgr_201a90();
    MapMgrWarpMenuDraw_1e2680(r0);
}
