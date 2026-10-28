/* rgp:protos */
#define RGP_SELF_EvCmdStreamFadeIn_244b40 1
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

s32 EvCmdStreamFadeIn_244b40(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    r1 = ScriptGetInt_2490f0(p0);
    r2 = (StreamSetChanVolumeFade_1cd960(r0, 0, r1, 1.0f), (s32)0);
    return 1;
}
