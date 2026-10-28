/* rgp:protos */
#define RGP_SELF_MapCaptionGetImageSize_33f200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapCaptionGetImageSize_33f200(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GetCaptionCfg_340430());
    r1 = (CaptionCfgGetImageSize_340130(r0, p1, p2), (s32)0);
    return 1;
}
