/* rgp:protos */
#define RGP_SELF_EvCmdBgmStop_260020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdBgmStop_260020(void)
{
    s32 r;

    r = (BgmPlayTrack_2075e0(0, 1), (s32)0);
    return 1;
}
