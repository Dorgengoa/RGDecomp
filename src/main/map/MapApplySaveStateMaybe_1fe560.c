#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern void MapSlotsRefreshBlocksEnabled_1e2b70(s32);
extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjApplySaveStateMaybe_2e7a40(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapApplySaveStateMaybe_1fe560(void)
{
    s32 r0;
    s32 r2;

    r0 = GetMapMgr_201a90();
    MapSlotsRefreshBlocksEnabled_1e2b70(r0);
    r2 = GetEventObjMgr_2d1960();
    EventObjApplySaveStateMaybe_2e7a40(r2);
}
