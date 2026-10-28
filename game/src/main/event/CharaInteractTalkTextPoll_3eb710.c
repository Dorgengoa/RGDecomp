/* rgp:protos */
#define RGP_SELF_CharaInteractTalkTextPoll_3eb710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int CharaInteractTalkTextPoll_3eb710(s32 p0)
{
    u128 v20[3];

    ActionPacketReset_3e3d00(v20);
    return TalkTextPollByKind_3e1ab0(v20, (p0 + 0x34));
}
