/* rgp:protos */
#define RGP_SELF_LoadHandlesPollAllReady_28b000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

unsigned char LoadHandlesPollAllReady_28b000(s32 p0, s32 p1)
{
    s32 l0;

    l0 = 0;
    while (l0 < p1) {
        LoadHandleGetStatus_28b2e0((p0 + (((l0 << 3) - l0) << 3)));
        l0 = (l0 + 1);
    }
    return LoadHandlesAllReady_28b070(p0, p1);
}
