#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern void MapMgrInitThunk_1e5830(s32);
extern s32 GetMinimapMgr_201a70(void);
extern void MinimapMgrReset_322290(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapAndMinimapInit_201460(void)
{
    s32 r0;
    s32 r2;

    r0 = GetMapMgr_201a90();
    MapMgrInitThunk_1e5830(r0);
    r2 = GetMinimapMgr_201a70();
    MinimapMgrReset_322290(r2);
}
