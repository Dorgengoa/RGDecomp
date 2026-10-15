#include "types.h"

extern s32 GetCompassHud_1fdaa0(void);
extern void CompassHudFadeOutStart_3715f0(s32, s32);
extern s32 GetMapMgr_201a90(void);
extern void MapMgrMinimapFadeOut_1e2ad0(s32, s32);
extern void MapMgrWarpMenuFadeOutStart_1e26a0(s32, s32);
extern void IconStealthFadeOut_2029d0(f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void HudFadeOutAll_2f47e0(s32 p0)
{
    s32 r0;
    s32 r2;

    r0 = GetCompassHud_1fdaa0();
    CompassHudFadeOutStart_3715f0(r0, p0);
    r2 = GetMapMgr_201a90();
    MapMgrMinimapFadeOut_1e2ad0(r2, p0);
    MapMgrWarpMenuFadeOutStart_1e26a0(r2, p0);
    IconStealthFadeOut_2029d0(((f32)p0));
}
