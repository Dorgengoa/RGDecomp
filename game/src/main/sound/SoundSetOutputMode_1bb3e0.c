/* rgp:protos */
#define RGP_SELF_SoundSetOutputMode_1bb3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SoundSetOutputMode_1bb3e0(s32 p0)
{
    if (p0 != 0) {
        SoundSendCmd_1b6cc0(0xA, 1, 1);
    } else {
        SoundSendCmd_1b6cc0(0xA, 1, 0);
    }
}
