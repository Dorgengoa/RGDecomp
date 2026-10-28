/* rgp:protos */
#define RGP_SELF_HudFadeInAll_2f4850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void HudFadeInAll_2f4850(s32 p0)
{
    s32 r0;
    s32 r2;

    r0 = ((s32)GetCompassHud_1fdaa0());
    CompassHudFadeInStart_371630(r0, p0);
    r2 = ((s32)GetMapMgr_201a90());
    MapMgrMinimapFadeIn_1e2b20(r2, p0);
    MapMgrWarpMenuFadeInStart_1e26b0(r2, p0);
    IconStealthFadeIn_202a10(((f32)p0));
}
