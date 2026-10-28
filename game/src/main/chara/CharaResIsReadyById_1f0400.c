/* rgp:protos */
#define RGP_SELF_CharaResIsReadyById_1f0400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaResIsReadyById_1f0400(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = CharaResFindById_1efba0(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    r1 = CharaResRecIsReady_1f4890(r0);
    return r1;
}
