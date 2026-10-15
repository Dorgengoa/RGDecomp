#include "types.h"

extern s32 GetGameMode_1f59c0(void);
extern s32 GetMinimapMgr_201a70(void);
extern s32 MinimapMgrFadeOutStart_321e60(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapMgrMinimapFadeOut_1e2ad0(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = GetGameMode_1f59c0();
    rv3 = r0;
    if (r0 != 0x14) {
        r1 = GetMinimapMgr_201a70();
        r2 = MinimapMgrFadeOutStart_321e60(r1, ((f32)p1));
        rv3 = r2;
    }
    return rv3;
}
