/* rgp:protos */
#define RGP_SELF_VideoDecRestartDma_1d4eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B3258[];

s32 VideoDecRestartDma_1d4eb0(void)
{
    ViBufRestartDma_1d3e70(D_004B3258);
    return 1;
}
