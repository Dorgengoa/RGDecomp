/* rgp:protos */
#define RGP_SELF_CharaDropHeldTarget_211de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int CharaDropHeldTarget_211de0(s32 p0, s32 p1)
{
    return CharaReleaseHeldTarget_2116b0(p0, p1, 0.0f, 0.0f, 0.0f);
}
