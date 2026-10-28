/* rgp:protos */
#define RGP_SELF_CaptionCalcCenterX_33f2c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CaptionCalcCenterX_33f2c0(void)
{
    s32 v3C;
    s32 v38;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 t0;
    s32 rv4;

    r0 = GetDrawCtx_15de80();
    r1 = ((s32)GetCaptionCfg_340430());
    r2 = DrawEnvGetWidth_1451e0(r0);
    CaptionCfgGetImageSize_340130(r1, &v3C, &v38);
    t0 = v3C;
    rv4 = ((r2 - t0) >> 1);
    if ((r2 - t0) < 0) {
        rv4 = (((r2 - t0) + 1) >> 1);
    }
    return rv4;
}
