/* rgp:protos */
#define RGP_SELF_VideoDecEndPut_1d2740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void VideoDecEndPut_1d2740(s32 p0, s32 p1)
{
    ViBufEndPut_1d4450((p0 + 0x48), p1);
}
