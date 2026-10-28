/* rgp:protos */
#define RGP_SELF_MapMgrMinimapFadeIn_1e2b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapMgrMinimapFadeIn_1e2b20(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = GetGameMode_1f59c0();
    rv3 = r0;
    if (r0 != 0x14) {
        r1 = ((s32)GetMinimapMgr_201a70());
        r2 = (MinimapMgrFadeInStart_321e80(r1, ((f32)p1)), (s32)0);
        rv3 = r2;
    }
    return rv3;
}
