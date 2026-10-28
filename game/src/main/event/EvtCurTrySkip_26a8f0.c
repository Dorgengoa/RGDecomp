/* rgp:protos */
#define RGP_SELF_EvtCurTrySkip_26a8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482040;

s32 EvtCurTrySkip_26a8f0(s32 p0)
{
    s32 t0;
    s32 r0;

    t0 = D_00482040;
    if (t0 != 0) {
        r0 = EventPlayerTrySkip_249a30(t0, p0);
        return r0;
    }
    return 0;
}
