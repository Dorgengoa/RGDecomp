#include "types.h"

extern s32 GetMinimapMgr_201a70(void);
extern void MinimapMgrDraw_321fa0(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapMgrMinimapDraw_1e2820(s32 p0, s32 p1, f32 fa0)
{
    s32 r0;

    r0 = GetMinimapMgr_201a70();
    MinimapMgrDraw_321fa0(r0, p1, fa0);
}
