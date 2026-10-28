/* rgp:protos */
#define RGP_SELF_StreamIsChanActive_1cd8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int StreamIsChanActive_1cd8c0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = ((s32)GetStreamMgr_207ea0());
    return StreamMgrChanIsActive_1d6540(r0, p1, p2);
}
