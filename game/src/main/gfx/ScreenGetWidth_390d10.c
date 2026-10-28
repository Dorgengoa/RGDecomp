/* rgp:protos */
#define RGP_SELF_ScreenGetWidth_390d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int ScreenGetWidth_390d10(void)
{
    s32 r0;

    r0 = GetDrawCtx_15de80();
    return DrawEnvGetWidth_1451e0(r0);
}
