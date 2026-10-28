/* rgp:protos */
#define RGP_SELF_VideoDecBeginPut_1d2790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void VideoDecBeginPut_1d2790(s32 p0, s32 p1, s32 p2, s32 p3, void *rgp_a4)
{
    ViBufBeginPut_1d44b0((p0 + 0x48), p1, p2, p3, (void *)rgp_a4);
}
