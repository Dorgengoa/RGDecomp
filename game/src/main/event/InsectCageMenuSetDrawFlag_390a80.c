/* rgp:protos */
#define RGP_SELF_InsectCageMenuSetDrawFlag_390a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048335C;

int InsectCageMenuSetDrawFlag_390a80(s32 p0, s32 p1)
{
    return BitArraySetReturnOld_384360(&D_0048335C, p0, p1);
}
