#include "types.h"

extern void MinimapMgrSetViewMode_321c00(s32, s32);
extern void MinimapMgrSetScreenAnchorPos_321b60(s32, s32, s32);
extern void MinimapMgrSetSize_321ac0(s32, s32, s32);
extern void MinimapMgrSetWinSize_321a20(s32, s32, s32);
extern void MinimapMgrRefreshAll_3219a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MinimapMgrResetView_321770(s32 p0)
{
    MinimapMgrSetViewMode_321c00(p0, 0);
    MinimapMgrSetScreenAnchorPos_321b60(p0, -1, -1);
    MinimapMgrSetSize_321ac0(p0, 0x140, 0x140);
    MinimapMgrSetWinSize_321a20(p0, 0xA0, 0x90);
    MinimapMgrRefreshAll_3219a0(p0);
}
