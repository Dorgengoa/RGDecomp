#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 MapMgrLoadStep_1e1c50(s32);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrResolveAllTargets_2e8840(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TaskLoadMap_201200(void)
{
    s32 r0;
    s32 r1;
    s32 rv4;
    s32 r2;
    s32 r3;

    r0 = GetMapMgr_201a90();
    r1 = MapMgrLoadStep_1e1c50(r0);
    rv4 = r1;
    if (r1 != 0) {
        r2 = GetEventObjMgr_2d1960();
        r3 = EventObjMgrResolveAllTargets_2e8840(r2);
        rv4 = r3;
    }
    return rv4;
}
