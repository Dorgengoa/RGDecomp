/* rgp:protos */
#define RGP_SELF_EvCmdPartyRefreshMembersMaybe_241120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdPartyRefreshMembersMaybe_241120(void)
{
    s32 r;

    r = PartyRefreshMembersMaybe_2f40b0(1);
    return 1;
}
