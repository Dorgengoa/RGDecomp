/* rgp:protos */
#define RGP_SELF_VideoDecNodata_1d4f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B3258[];

s32 VideoDecNodata_1d4f10(void)
{
    ThreadYield_1d2b70();
    ViBufAddDma_1d4240(D_004B3258);
    return 1;
}
